#include "BisonActions.h"
/* GLOBAL VARIABLES*/
static int expectedDepth = 0;
static int currentDepth = 0;


/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeBisonActionsModule() {
	_logger = createLogger("BisonActions");
}

void shutdownBisonActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** IMPORTED FUNCTIONS */

extern unsigned int flexCurrentContext(void);

/* PRIVATE FUNCTIONS */

static void _logSyntacticAnalyzerAction(const char * functionName);

/**
 * Logs a syntactic-analyzer action in DEBUGGING level.
 */
static void _logSyntacticAnalyzerAction(const char * functionName) {
	logDebugging(_logger, "%s (Expected depth: %d, Current: %d)", functionName, expectedDepth, currentDepth);
}

/* PUBLIC FUNCTIONS */

Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Constant * BooleanConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->value = value;
	return constant;
}

Expression * ArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * BitArithmeticExpressionSemanticAction(Expression * leftExpression, Expression * rightExpression, ExpressionType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->leftExpression = leftExpression;
	expression->rightExpression = rightExpression;
	expression->type = type;
	return expression;
}

Expression * FactorExpressionSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->factor = factor;
	expression->type = FACTOR;
	return expression;
}

Factor * ConstantFactorSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->constant = constant;
	factor->type = CONSTANT;
	return factor;
}

Factor * ExpressionFactorSemanticAction(Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Factor * factor = calloc(1, sizeof(Factor));
	factor->expression = expression;
	factor->type = EXPRESSION;
	return factor;
}

Program * ExpressionProgramSemanticAction(CompilerState * compilerState, Expression * expression) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->expression = expression;
	compilerState->abstractSyntaxtTree = program;
	if (0 < flexCurrentContext()) {
		logError(_logger, "The final context is not the default (0): %d", flexCurrentContext());
		compilerState->succeed = false;
	}
	else {
		compilerState->succeed = true;
	}
	return program;
}

Sentence * FunctionCallSentenceSemanticAction(FunctionCall * callee, SentenceType type) {
	if (expectedDepth != currentDepth) {
		logError(_logger, "Expected depth (%d) is different from current depth (%d).", expectedDepth, currentDepth);
		return NULL;
	} else {
		currentDepth = 0;
		expectedDepth = (expectedDepth == 0)? 0 : expectedDepth - 1; 
	}
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Sentence * sentence = calloc(1, sizeof(Sentence));
	sentence->functionCall = callee;
	sentence->type = type;
	return sentence;
}

Sentence * FunctionDefinitionSentenceSemanticAction(const char * function, Parameters * parameters, SentenceType type) {
	if (expectedDepth != currentDepth) {
		logError(_logger, "Expected depth (%d) is different from current depth (%d).", expectedDepth, currentDepth);
	} else {
		currentDepth = 0;
	}
	_logSyntacticAnalyzerAction(__FUNCTION__);
	expectedDepth++;
	Sentence * sentence = calloc(1, sizeof(Sentence));
	sentence->type = type;
	sentence->functionName = function;
	sentence->parameters = parameters;
	return sentence;
}

FunctionCall * FunctionCallSemanticAction(const char * function, Parameters * parameters) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FunctionCall * functionCall = calloc(1, sizeof(FunctionCall));
	functionCall->functionName = function; // function is obtained from strdup, should be freed
	functionCall->functionArguments = parameters;
	return functionCall;
}

VariableCall * VariableCallSemanticAction(const char * variable) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	VariableCall * variableCall = calloc(1, sizeof(VariableCall));
	variableCall->variableName = variable;
	return variableCall;
}

Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * followingParameters, 
									ParamType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Parameters * parameters = calloc(1, sizeof(Parameters));
	parameters->leftExpression = leftExpression;
	parameters->rightParameters = followingParameters;
	parameters->type = type;
	return parameters;
}

Depth * DepthSemanticAction(DepthType type) {
	if (type != END_DEPTH) { currentDepth++; }
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Depth * depth = calloc(1, sizeof(Depth));
	depth->type = type;
	return depth;
}

Newline * NewlineSemanticAction(NewlineType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Newline * newline = calloc(1, sizeof(Newline));
	newline->type = type;
	return newline;
}