#include "BisonActions.h"
/* GLOBAL VARIABLES*/
static int expectedDepth = 0;
static int currentDepth = 0;


#define OBJECT_STR "object"

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
	constant->integer = value;
    constant->type = CONSTANT_INT;
	return constant;
}

Constant * BooleanConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->boolean = value;
    constant->type = CONSTANT_BOOLEAN;
	return constant;
}

Constant * StringConstantSemanticAction(const char * value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->string = malloc(strlen(value)+1);
    constant->string = strcpy(constant->string, value);
    constant->type = CONSTANT_STRING;
	return constant;
}

Constant * FloatConstantSemanticAction(const float value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->decimal = value;
    constant->type = CONSTANT_FLOAT;
	return constant;
}

Constant * ListConstantSemanticAction(List * value){
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->list = value;
    constant->type = CONSTANT_LIST;
	return constant;
}

Constant * TupleConstantSemanticAction(Tuple * value){
    _logSyntacticAnalyzerAction(__FUNCTION__);
    Constant * constant = calloc(1, sizeof(Constant));
    constant->tuple = value;
    constant->type = CONSTANT_TUPLE;
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

ClassDefinition * ClassDefintionSemanticAction(const char * className, const char * parent) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    ClassDefiniton * classDefinition = calloc(1, sizeof(ClassDefinition));
    classDefinition->className = malloc(strlen(className)+1);
    classDefinition->className = strcpy(classDefinition->className, className);
    if(parent == NULL){
        classDefinition->parent = malloc(strlen(parent)+1);
        classDefinition->parent = strcpy(classDefinition->parent, parent);

    } else {
        classDefinition->parent = malloc(strlen(OBJECT_STR)+1);
        classDefinition->parent = strcpy(classDefinition->parent, OBJECT_STR);
    }
    return classDefinition;
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

List * ListSemanticAction(Parameters * elements) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    List * list = calloc(1, sizeof(List));
	list->elements = elements;
	return list;
}

Tuple * TupleSemanticAction(Parameters * elements) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Tuple * tuple = calloc(1, sizeof(Tuple));
	tuple->elements = elements;
	return tuple;
}

VariableCall * VariableCallSemanticAction(const char * variable) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	VariableCall * variableCall = calloc(1, sizeof(VariableCall));
	variableCall->variableName = variable;
	return variableCall;
}

Parameters * ParametersSemanticAction(Expression * leftExpression, Parameters * followingParameters, ParamType type) {
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

Conditional * ConditionalBooleanSemanticAction(Conditional * left, Conditional * right, const BooleanCond booleanCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->leftCond = left;
    switch(booleanCond) {
        case LOGIC_NOT: conditional->rightCond = NULL; break;
        default: conditional->rightCond = right; break;
    }
    conditional->booleanCond = booleanCond;
    conditional->type = BOOLEAN_COND;
    return conditional;
}

Conditional * ConditionalBooleanVariableSemanticAction(VariableCall * left, VariableCall * right, const BooleanCond booleanCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->leftVarCond = left;
    switch(booleanCond) {
        case LOGIC_NOT: conditional->rightVarCond = NULL; break;
        default: conditional->rightVarCond = right; break;
    }
    conditional->boolCondition = booleanCond;
    conditional->type = VARIABLE_BOOLEAN_COND;
    return conditional;
}

Conditional * ConditionalBooleanAndVariableSemanticAction(VariableCall * var, Conditional * cond, const BooleanCond booleanCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->condVar = var;
    conditional->cond = cond;
    conditional->boolCond = booleanCond;
    conditional->type = VARIABLE_AND_BOOLEAN_COND;
    return conditional;
}

Conditional * ConditionalExpressionSemanticAction(Expression * left, Conditional * right, ComparisonCond comparisonCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = COMPARISON_COND;
    conditional->leftExpression = left;
    conditional->rightExpression = right;
    conditional->comparisonCond = comparisonCond;
    return conditional;
}

Conditional * ConditionalFactorVariableSemanticAction(VariableCall * left, VariableCall * right, const ComparisonCond comparisonCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = VARIABLE_COMPARISON_COND;
    conditional->leftExpressionVar = left;
    conditional->rightExpressionVar = right;
    conditional->comprCondition = comparisonCond;
    return conditional;
}
Conditional * ConditionalFactorAndVariableSemanticAction(VariableCall * var, Factor * fact, const ComparisonCond comparisonCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = VARIABLE_AND_CONST_COMPARISON_COND;
    conditional->expressionVar = var;
    conditional->exp = fact;
    conditional->comprCond = comparisonCond;
    return conditional;
}

Conditional * ConditionalSingleFactorSemanticAction(Factor * factor) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = EXPRESSION_COND;
    conditional->expression = expression;
    return conditional;
}

Conditional * ConditionalObjectSemanticAction(Object * left, Object * right, ObjectCond objectCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = OBJECT_COMPARISON_COND;
    conditional->leftObject = left;
    conditional->rightObject = right;
    conditional->objectCond = objectCond;
    return conditional;
}

Conditional * ConditionalObjectVariableSemanticAction(VariableCall * left, VariableCall * right, const ObjectCond objectCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = VARIABLE_OBJECT_COMPARISON_COND;
    conditional->variableLeftObject = left;
    conditional->variableRightObject = right;
    conditional->objCondition = objectCond;
    return conditional;
}

Conditional * ConditionalObjectAndVariableSemanticAction(VariableCall * var, Object * obj, const ObjectCond objectCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = VARIABLE_AND_OBJECT_COMPARISON_COND;
    conditional->variableObj = var;
    conditional->obj = obj;
    conditional->objCond = objectCond;
    return conditional;
}

Conditional * ConditionalSingleObjectSemanticAction(Object * object) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = OBJECT_COND;
    conditional->object = object;
    return conditional;
}


Conditional * ConditionalVariableSemanticAction(VariableCall * variable) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = VARIABLE_COND;
    conditional->variable = variable;
    return conditional;
}

While * WhileBlockSemanticAction(Conditional * conditional) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    While * whileBlock = calloc(1,sizeof(While));
    whileBlock->conditional = conditional;
    return conditional;
}

For * ForFactorBlockSemanticAction(Factor * left, Factor * right) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    For * forBlock = calloc(1,sizeof(For));
    forBlock->type = FOR_FACTOR;
    forBlock->left = left;
    forBlock->right = right;
    return forBlock;
}
For * ForVariableBlockSemanticAction(VariableCall * left, VariableCall * right) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    For * forBlock = calloc(1,sizeof(For));
    forBlock->type = FOR_VARIABLE;
    forBlock->leftVar = left;
    forBlock->rightVar = right;
    return forBlock;
}

For * ForFactorAndVariableBlockSemanticAction(VariableCall * var, Factor * fact, Which wich) {
    _logSyntacticAnalyzerAction(__FUNCTION__);
    For * forBlock = calloc(1,sizeof(For));
    forBlock->type = FOR_FACTOR_AND_VARIABLE;
    forBlock->which = which;
    forBlock->var = var;
    forBlock->fact = fact;
    return forBlock;
}
