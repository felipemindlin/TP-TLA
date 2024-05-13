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

Program * GeneralProgramSemanticAction(CompilerState * compilerState, Depth * dp, Sentence * sentence, Program * nprog) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Program * program = calloc(1, sizeof(Program));
	program->depth = dp;
	program->sentence = sentence;
	program->nextProgram = nprog;
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

Program * FinishedProgramSemanticAction(CompilerState * compilerState) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	compilerState->succeed = true;
	return NULL;
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

/** SENTENCE SECTION **/
Sentence * ExpressionSentenceSemanticAction(Expression * exp) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Sentence * sentence = calloc(1, sizeof(Sentence));
	sentence->expression = exp;
	sentence->type = EXPRESSION_SENTENCE;
	return sentence;
}

Sentence * VariableSentenceSemanticAction(Variable * var) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Sentence * sentence = calloc(1, sizeof(Sentence));
	sentence->variable = var;
	sentence->type = VARIABLE_SENTENCE;
	return sentence;
}

/** VARIABLE SECTION **/
Variable * ExpressionVariableSemanticAction(char * restrict id, Expression * expr) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->expression = expr;
	variable->identifier = id;
	variable->type = VT_EXPRESSION_VARIABLE;
	return variable;
}

Variable * FunctionCallVariableSemanticAction(char * restrict id, FunctionCall * fuckall) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->functionCall = fuckall;
	variable->identifier = id;
	variable->type = VT_FUNCCALL_VARIABLE;
	return variable;
}

Variable * MethodCallVariableSemanticAction(char * restrict id, MethodCall * methall) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->methodCall = methall;
	variable->identifier = id;
	variable->type = VT_METHODCALL_VARIABLE;
	return variable;
}

Variable * FieldGetterVariableSemanticAction(char * restrict id, FieldGetter * field) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->fieldGetter = field;
	variable->identifier = id;
	variable->type = VT_FIELDGETTER_VARIABLE;
	return variable;
}

Variable * ObjectVariableSemanticAction(char * restrict id, Object * obj) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Variable * variable = calloc(1, sizeof(Variable));
	variable->object = obj;
	variable->identifier = id;
	variable->type = VT_OBJECT_VARIABLE;
	return variable;
}

/** METHOD CALL SECTION **/
MethodCall * VariableMethodCallSemanticAction(VariableCall * var, FunctionCall * method) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	MethodCall * methodCall = calloc(1, sizeof(MethodCall));
	methodCall->variableCall = var;
	methodCall->functionCall = method;
	methodCall->type = MCT_VARIABLE_TRIGGER;
	return methodCall;
}

/** FIELD GETTER SECTION **/
FieldGetter * VariableFieldGetterSemanticAction(VariableCall * var, VariableCall * field) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FieldGetter * fieldGetter = calloc(1, sizeof(FieldGetter));
	fieldGetter->variableCall = var;
	fieldGetter->field = field;
	fieldGetter->type = FG_VARIABLE_OWNER;
	return fieldGetter;
}

/** OBJECT SECTION **/
Object * ObjectSemanticAction(char * restrict id, ObjectType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Object * object = calloc(1, sizeof(Object));
	object->className = id;
	object->type = type;
	return object;
}

/** LIST SECTION **/
List * EmptyListSemanticAction() {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List * list = calloc(1, sizeof(List));
	list->type = LT_EMPTY_LIST;
	return list;
}

List * TypedListSemanticAction(Object * obj) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List * list = calloc(1, sizeof(List));
	list->objectType = obj;
	list->type = LT_TYPED_LIST;
	return list;
}

List * ParametrizedListSemanticAction(Parameters * params) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	List * list = calloc(1, sizeof(List));
	list->elements = params;
	list->type = LT_PARAMETRIZED_LIST;
	return list;
}