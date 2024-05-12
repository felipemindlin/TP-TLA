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

// Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
// 	return INTEGER;
// }

// Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
// 	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
// 	Token token;
// 	switch (lexicalAnalyzerContext->lexeme[0]) {
// 		case '(': token = OPEN_PARENTHESIS; break;
// 		case ')': token = CLOSE_PARENTHESIS; break;
// 	}
// 	lexicalAnalyzerContext->semanticValue->token = token;
// 	return token;
// }

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

/* OUR FUNCTIONS */
// TODO: definir estandar de nombres para funciones "privadas"

// Standard objects found in: https://docs.python.org/3/library/functions.html
Token IdentifierLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    if(isDefinedFunction(lexicalAnalyzerContext->lexeme){
        lexicalAnalyzerContext->semanticValue->object = malloc(sizeof(Object));
        lexicalAnalyzerContext->semanticValue->object->className = strdup(lexicalAnalyzerContext->lexeme);
        return BUILTIN_OBJECT;
    }
	lexicalAnalyzerContext->semanticValue->var_name = strdup(lexicalAnalyzerContext->lexeme);
	return IDENTIFIER;
}


Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}


Token IfLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return IF;
}


Token ElifLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return ELIF;
}


Token ElseLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return ELSE;
}

Token ForLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return FOR;
}

Token WhileLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return WHILE;
}
Token BreakLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return BREAK;
}
Token ContinueLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return CONTINUE;
}

Token FloatLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->fp_number = atof(lexicalAnalyzerContext->lexeme);
	return FLOAT;
}

Token ClassLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return CLASS;
}

Token ReturnsLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return RETURNS;
}

Token DotLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return DOT;
}

Token BooleanLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	boolean value;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case 'T': value = true; break;
		case 'F': value = false; break;
	}
	lexicalAnalyzerContext->semanticValue->boolean = value;
	return BOOLEAN;
}

Token ConditionalLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token value;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case 'a': value = LOGICAL_AND;
		case 'o': value = LOGICAL_OR;
	}
	return value;
}

Token NoneLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return NONE;
}

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

Token TabLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = TAB;
	return TAB;
}

Token NewlineLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = NEWLINE_TOKEN;
	return NEWLINE_TOKEN;
}

Token ColonLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	lexicalAnalyzerContext->semanticValue->token = COLON;
	return COLON;
}

Token CommaLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = COMMA;
	return COMMA;
}

Token BracketLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '[': token = OPEN_BRACKET; break;
		case ']': token = CLOSE_BRACKET; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token BraceLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '{': token = OPEN_BRACE; break;
		case '}': token = CLOSE_BRACE; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token DefineLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->token = DEF;
	return DEF;
}


int isDefinedFunction(char * lexeme) {
return strcmp(lexeme, "abs") == 0
    || strcmp(lexeme, "aiter") == 0
    || strcmp(lexeme, "all") == 0
    || strcmp(lexeme, "anext") == 0
    || strcmp(lexeme, "any") == 0
    || strcmp(lexeme, "ascii") == 0
    || strcmp(lexeme, "bin") == 0
    || strcmp(lexeme, "bool") == 0
    || strcmp(lexeme, "breakpoint") == 0
    || strcmp(lexeme, "bytearray") == 0
    || strcmp(lexeme, "bytes") == 0
    || strcmp(lexeme, "callable") == 0
    || strcmp(lexeme, "classmethod") == 0
    || strcmp(lexeme, "compile") == 0
    || strcmp(lexeme, "complex") == 0
    || strcmp(lexeme, "delattr") == 0
    || strcmp(lexeme, "dict") == 0
    || strcmp(lexeme, "dir") == 0
    || strcmp(lexeme, "divmod") == 0
    || strcmp(lexeme, "enumerate") == 0
    || strcmp(lexeme, "eval") == 0
    || strcmp(lexeme, "exec") == 0
    || strcmp(lexeme, "filter") == 0
    || strcmp(lexeme, "float") == 0
    || strcmp(lexeme, "format") == 0
    || strcmp(lexeme, "frozenset") == 0
    || strcmp(lexeme, "getattr") == 0
    || strcmp(lexeme, "globals") == 0
    || strcmp(lexeme, "hasattr") == 0
    || strcmp(lexeme, "hash") == 0
    || strcmp(lexeme, "help") == 0
    || strcmp(lexeme, "hex") == 0
    || strcmp(lexeme, "id") == 0
    || strcmp(lexeme, "input") == 0
    || strcmp(lexeme, "int") == 0
    || strcmp(lexeme, "isinstance") == 0
    || strcmp(lexeme, "issubclass") == 0
    || strcmp(lexeme, "iter") == 0
    || strcmp(lexeme, "len") == 0
    || strcmp(lexeme, "list") == 0
    || strcmp(lexeme, "locals") == 0
    || strcmp(lexeme, "map") == 0
    || strcmp(lexeme, "memoryview") == 0
    || strcmp(lexeme, "min") == 0
    || strcmp(lexeme, "next") == 0
    || strcmp(lexeme, "object") == 0
    || strcmp(lexeme, "oct") == 0
    || strcmp(lexeme, "open") == 0
    || strcmp(lexeme, "ord") == 0
    || strcmp(lexeme, "pow") == 0
    || strcmp(lexeme, "print") == 0
    || strcmp(lexeme, "range") == 0
    || strcmp(lexeme, "repr") == 0
    || strcmp(lexeme, "reversed") == 0
    || strcmp(lexeme, "round") == 0
    || strcmp(lexeme, "set") == 0
    || strcmp(lexeme, "setattr") == 0
    || strcmp(lexeme, "slice") == 0
    || strcmp(lexeme, "sorted") == 0
    || strcmp(lexeme, "staticmethod") == 0
    || strcmp(lexeme, "str") == 0
    || strcmp(lexeme, "sum") == 0
    || strcmp(lexeme, "super") == 0
    || strcmp(lexeme, "tuple") == 0
    || strcmp(lexeme, "type") == 0
    || strcmp(lexeme, "vars") == 0
    || strcmp(lexeme, "zip") == 0;
}
