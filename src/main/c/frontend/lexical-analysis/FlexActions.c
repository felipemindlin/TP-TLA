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
	lexicalAnalyzerContext->semanticValue->var_name = strdup(lexicalAnalyzerContext->lexeme);
	return IDENTIFIER;
}

Token BuiltinIdentifierLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext, BuiltinIdentifier id){
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    switch(id){
        case BI_ABS: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ABS; break;
        case BI_AITER: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_AITER; break;
        case BI_ALL: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ALL; break;
        case BI_ANEXT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ANEXT; break;
        case BI_ANY: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ANY; break;
        case BI_ASCII: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ASCII; break;
        case BI_BIN: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_BIN; break;
        case BI_BOOL: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_BOOL; break;
        case BI_BREAKPOINT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_BREAKPOINT; break;
        case BI_BYTEARRAY: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_BYTEARRAY; break;
        case BI_BYTES: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_BYTES; break;
        case BI_CALLABLE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_CALLABLE; break;
        case BI_CLASSMETHOD: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_CLASSMETHOD; break;
        case BI_COMPILE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_COMPILE; break;
        case BI_COMPLEX: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_COMPLEX; break;
        case BI_DELATTR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_DELATTR; break;
        case BI_DICT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_DICT; break;
        case BI_DIR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_DIR; break;
        case BI_DIVMOD: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_DIVMOD; break;
        case BI_ENUMERATE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ENUMERATE; break;
        case BI_EVAL: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_EVAL; break;
        case BI_EXEC: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_EXEC; break;
        case BI_FILTER: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_FILTER; break;
        case BI_FLOAT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_FLOAT; break;
        case BI_FORMAT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_FORMAT; break;
        case BI_FROZENSET: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_FROZENSET; break;
        case BI_GETATTR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_GETATTR; break;
        case BI_GLOBALS: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_GLOBALS; break;
        case BI_HASATTR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_HASATTR; break;
        case BI_HASH: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_HASH; break;
        case BI_HELP: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_HELP; break;
        case BI_HEX: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_HEX; break;
        case BI_ID: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ID; break;
        case BI_INPUT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_INPUT; break;
        case BI_INT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_INT; break;
        case BI_ISINSTANCE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ISINSTANCE; break;
        case BI_ISSUBCLASS: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ISSUBCLASS; break;
        case BI_ITER: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ITER; break;
        case BI_LEN: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_LEN; break;
        case BI_LIST: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_LIST; break;
        case BI_LOCALS: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_LOCALS; break;
        case BI_MAP: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_MAP; break;
        case BI_MEMORYVIEW: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_MEMORYVIEW; break;
        case BI_MIN: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_MIN; break;
        case BI_NEXT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_NEXT; break;
        case BI_OBJECT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_OBJECT; break;
        case BI_OCT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_OCT; break;
        case BI_OPEN: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_OPEN; break;
        case BI_ORD: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ORD; break;
        case BI_POW: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_POW; break;
        case BI_PRINT: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_PRINT; break;
        case BI_RANGE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_RANGE; break;
        case BI_REPR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_REPR; break;
        case BI_REVERSED: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_REVERSED; break;
        case BI_ROUND: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ROUND; break;
        case BI_SET: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SET; break;
        case BI_SETATTR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SETATTR; break;
        case BI_SLICE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SLICE; break;
        case BI_SORTED: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SORTED; break;
        case BI_STATICMETHOD: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_STATICMETHOD; break;
        case BI_STR: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_STR; break;
        case BI_SUM: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SUM; break;
        case BI_SUPER: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_SUPER; break;
        case BI_TUPLE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_TUPLE; break;
        case BI_TYPE: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_TYPE; break;
        case BI_VARS: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_VARS; break;
        case BI_ZIP: lexicalAnalyzerContext->semanticValue->builtin_definition = BTF_ZIP;
    }
    return BUILTIN_IDENTIFIER;
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

Token ReturnKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return RETURN_KEYWORD_TOKEN;
}

Token PassKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return PASS_KEYWORD_TOKEN;
}

Token YieldKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return YIELD_KEYWORD_TOKEN;
}

Token RaiseKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return RAISE_KEYWORD_TOKEN;
}

Token TryKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return TRY_KEYWORD_TOKEN;
}

Token ExceptKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return EXCEPT_KEYWORD_TOKEN;
}

Token FinallyKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return FINALLY_KEYWORD_TOKEN;
}

Token MatchKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return MATCH_KEYWORD_TOKEN;
}

Token CaseKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return CASE_KEYWORD_TOKEN;
}

Token TypeKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return TYPE_KEYWORD_TOKEN;
}

Token AssertKeywordLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return ASSERT_KEYWORD_TOKEN;
}

Token DotLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
    _logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
    return DOT;
}

Token IdentityEvaluationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->length) {
		case 2: token = IS; 	break;
		case 6: token = IS_NOT; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token MembershipEvaluationLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case 'i': token = IN; break;
		case 'n': token = NOT_IN; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
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
