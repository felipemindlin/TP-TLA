#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

// Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	Token token;
// 	switch (lexicalAnalyzerContext->lexeme[0]) {
// 		case '-': token = SUB; break;
// 		case '*': token = MUL; break;
// 		case '/': token = DIV; break;
// 		case '+': token = ADD; break;
// 	}
// 	lexicalAnalyzerContext->semanticValue->token = token;
// 	return token;
// }

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '(': token = OPEN_PARENTHESIS; break;
		case ')': token = CLOSE_PARENTHESIS; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

/* OUR FUNCTIONS */
// TODO: definir estandar de nombres para funciones "privadas"
// Not exposed to the header file
Token AsteriskArithmeticOperatorPicker(char * lexeme, int length) {
	if (length == 2 && lexeme[1] == '*') return EXP;
	else if (length == 1) return MUL;
	else return UNKNOWN;
}

// Not exposed to the header file
Token SlashArithmeticOperatorPicker(char * lexeme, int length) {
	if (length == 2 && lexeme[1] == '/') return FLOOR_DIV;
	else if (length == 1) return DIV;
	else return UNKNOWN;
}

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0] ) {
		case '-': token = SUB; break;
		case '*': token = AsteriskArithmeticOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length); 
			break;
		case '/': token = SlashArithmeticOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length); 
			break;
		case '+': token = ADD; break;
		case '%': token = MOD; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

// Not exposed to the header file
Token AsteriskAssignmentOperatorPicker(char * lexeme, int length) {
	if (length == 3 && lexeme[1] == '*') return ASSIGN_EXP;
	else if (length == 2) return ASSIGN_MUL;
	else return UNKNOWN;
}

// Not exposed to the header file
Token SlashAssignmentOperatorPicker(char * lexeme, int length) {
	if (length == 3 && lexeme[1] == '/') return ASSIGN_FLOOR_DIV;
	else if (length == 2) return ASSIGN_DIV;
	else return UNKNOWN;
}

Token AssignmentOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '=': token = ASSIGN; break;
		case '+': token = ASSIGN_ADD; break;
		case '-': token = ASSIGN_SUB; break;
		case '*': token = AsteriskAssignmentOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length); 
			break;
		case '/': token = SlashAssignmentOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length); 
			break;
		case '%': token = ASSIGN_MOD; break;
		case '&': token = ASSIGN_BITWISE_AND; break;
		case '|': token = ASSIGN_BITWISE_OR; break;
		case '^': token = ASSIGN_BITWISE_XOR; break;
		case '<': token = ASSIGN_BITWISE_LSHIFT; break;
		case '>': token = ASSIGN_BITWISE_RSHIFT; break;
		case ':': token = ASSIGN_WALRUS; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

// Not exposed to header file
Token LeftChevronComparisonOperatorPicker(char * lexeme, int length) {
	if (length == 2 && lexeme[1] == '=') return COMPARISON_GTE;
	else if (length == 1) return COMPARISON_GT;
	else return UNKNOWN;
}

// Not exposed to header file
Token RightChevronComparisonOperatorPicker(char * lexeme, int length) {
	if (length == 2 && lexeme[1] == '=') return COMPARISON_LTE;
	else if (length == 1) return COMPARISON_LT;
	else return UNKNOWN;
}

Token ComparisonOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '=': token = COMPARISON_EQ; break;
		case '!': token = COMPARISON_NEQ; break;
		case '>': token = RightChevronComparisonOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length);
			break;
		case '<': token = LeftChevronComparisonOperatorPicker
			(lexicalAnalyzerContext->lexeme, lexicalAnalyzerContext->length); 
			break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token BitwiseOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '^': token = BITWISE_XOR; break;
		case '&': token = BITWISE_AND; break;
		case '|': token = BITWISE_OR; break;
		case '~': token = BITWISE_NOT; break;
		case '<': token = BITWISE_LSHIFT; break;
		case '>': token = BITWISE_RSHIFT; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}