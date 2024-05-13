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

/** CONSTANT SECTION **/
Constant * IntegerConstantSemanticAction(const int value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->integer = value;
    constant->type = CT_INTEGER;
	return constant;
}

Constant * BooleanConstantSemanticAction(const boolean value) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->boolean = value;
    constant->type = CT_BOOLEAN;
	return constant;
}

Constant * FloatConstantSemanticAction(const double decimal) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->decimal = decimal;
    constant->type = CT_FLOAT;
	return constant;
}

Constant * StringConstantSemanticAction(char * restrict string) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->string = string;
    constant->type = CT_STRING;
	return constant;
}

Constant * ListConstantSemanticAction(List * lst) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->list = lst;
    constant->type = CT_LIST;
	return constant;
}

Constant * TupleConstantSemanticAction(Tuple * tpl) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Constant * constant = calloc(1, sizeof(Constant));
	constant->tuple = tpl;
    constant->type = CT_TUPLE;
	return constant;
}

/** EXPRESSION SECTION **/
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

Expression * ConstantExpressionSemanticAction(Constant * constant) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->constant = constant;
	expression->type = CONSTANT_EXPRESSION;
	return expression;
}

Expression * VariableCallExpressionSemanticAction(VariableCall * var) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->variableCall = var;
	expression->type = VARIABLE_CALL_EXPRESSION;
	return expression;
}

Expression * FunctionCallExpressionSemanticAction(FunctionCall * fcall) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Expression * expression = calloc(1, sizeof(Expression));
	expression->functionCall = fcall;
	expression->type = FUNCTION_CALL_EXPRESSION;
	return expression;
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

Sentence * BlockSentenceSemanticAction(Block * block) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Sentence * sentence = calloc(1, sizeof(Sentence));
	sentence->block = block;
	sentence->type = BLOCK_SENTENCE;
	return sentence;
}

/** BLOCK SECTION **/
Block * FunctionDefinitionBlockSemanticAction(FunctionDefinition * fdef, Program * nextProg) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Block * block = calloc(1, sizeof(Block));
    block->type = BT_FUNCTION_DEFINITION;
    block->functionDefinition = fdef;
    block->nextProgram = nextProg;
    return block;
}

Block * ClassDefinitionBlockSemanticAction(ClassDefinition * cdef, Program * nextProg) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Block * block = calloc(1, sizeof(Block));
    block->type = BT_CLASS_DEFINITION;
    block->classDefinition = cdef;
    block->nextProgram = nextProg;
    return block;
}

Block * ConditionalBlockSemanticAction(Conditional * cond, Program * nextProg) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->type = BT_CONDITIONAL;
	block->conditional = cond;
	block->nextProgram = nextProg;
	return block;
}

Block * WhileLoopBlockSemanticAction(WhileBlock * wblock, Program * nextProg) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->type = BT_WHILE;
	block->whileBlock = wblock;
	block->nextProgram = nextProg;
	return block;
}

Block * ForLoopBlockSemanticAction(ForBlock * fblock, Program * nextProg) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Block * block = calloc(1, sizeof(Block));
	block->type = BT_FOR;
	block->forBlock = fblock;
	block->nextProgram = nextProg;
	return block;
}

/** WHILE BLOCK SECTION **/
WhileBlock * WhileBlockSemanticAction(Conditional * cond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	WhileBlock * whileBlock = calloc(1, sizeof(WhileBlock));
	whileBlock->condition = cond;
	return whileBlock;
}

/** FOR BLOCK SECTION **/
ForBlock * ForBlockSemanticAction(Expression * left, Expression * right) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ForBlock * forBlock = calloc(1, sizeof(ForBlock));
    forBlock->left = left;
    forBlock->right = right;
	return forBlock;
}

/** FUNCTION DEFINITION SECTION **/
FunctionDefinition * GenericFunctionDefinitionSemanticAction(char * restrict id, Parameters * params) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    FunctionDefinition * functionDefinition = calloc(1, sizeof(FunctionDefinition));
    functionDefinition->functionName = id;
    functionDefinition->parameters = params;
    functionDefinition->type = FD_GENERIC;
    return functionDefinition;
}

FunctionDefinition * ObjectFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, Object * object) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    FunctionDefinition * functionDefinition = calloc(1, sizeof(FunctionDefinition));
    functionDefinition->functionName = id;
    functionDefinition->parameters = params;
    functionDefinition->objectType = object;
    functionDefinition->type = FD_OBJECT_TYPE;
    return functionDefinition;
}

FunctionDefinition * VariableCallFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, VariableCall * retVar) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    FunctionDefinition * functionDefinition = calloc(1, sizeof(FunctionDefinition));
    functionDefinition->functionName = id;
    functionDefinition->parameters = params;
    functionDefinition->returnVariableType = retVar;
    functionDefinition->type = FD_VARIABLE_CALL_TYPE;
    return functionDefinition;

}

FunctionDefinition * TupleFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, Tuple * tupleVar) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    FunctionDefinition * functionDefinition = calloc(1, sizeof(FunctionDefinition));
    functionDefinition->functionName = id;
    functionDefinition->parameters = params;
    functionDefinition->tupleReturnType = tupleVar;
    functionDefinition->type = FD_TUPLE_TYPE;
    return functionDefinition;
}

FunctionDefinition * ListFunctionDefinitionSemanticAction(char * restrict id, Parameters * params, List * listVar) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    FunctionDefinition * functionDefinition = calloc(1, sizeof(FunctionDefinition));
    functionDefinition->functionName = id;
    functionDefinition->parameters = params;
    functionDefinition->listReturnType = listVar;
    functionDefinition->type = FD_LIST_TYPE;
    return functionDefinition;
}

/** CLASS DEFINITION SECTION **/
ClassDefinition * ClassDefinitionSemanticAction(char * restrict id) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    ClassDefinition * classDefinition = calloc(1, sizeof(ClassDefinition));
    classDefinition->className = id;
    classDefinition->type = CDT_NOT_INHERITS;
    return classDefinition;
}

ClassDefinition * TupleClassDefinitionSemanticAction(char * restrict id, Tuple * tpl) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    ClassDefinition * classDefinition = calloc(1, sizeof(ClassDefinition));
    classDefinition->className = id;
    classDefinition->tuple = tpl;
    classDefinition->type = CDT_TUPLE_INHERITANCE;
    return classDefinition;
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

MethodCall * ConstantMethodCallSemanticAction(Constant * cons, FunctionCall * method) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	MethodCall * methodCall = calloc(1, sizeof(MethodCall));
	methodCall->constant = cons;
	methodCall->functionCall = method;
	methodCall->type = MCT_CONSTANT_TRIGGER;
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

FieldGetter * ConstantFieldGetterSemanticAction(Constant * cons, VariableCall * field) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	FieldGetter * fieldGetter = calloc(1, sizeof(FieldGetter));
	fieldGetter->constant = cons;
	fieldGetter->field = field;
	fieldGetter->type = FG_CONSTANT_OWNER;
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
    if(params != NULL) {
	    list->type = LT_PARAMETRIZED_LIST;
    }
    else {
	    list->type = LT_EMPTY_LIST;
    }
	return list;
}

/** TUPLE SECTION **/
Tuple * ParametrizedTupleSemanticAction(Parameters * params) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tuple * tuple = calloc(1, sizeof(List));
	tuple->elements = params;
    if(params != NULL) {
	    tuple->type = LT_PARAMETRIZED_LIST;
    }
    else {
	    tuple->type = LT_EMPTY_LIST;
    }
	return tuple;
}

Tuple * TypedTupleSemanticAction(Object * obj) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Tuple * tuple = calloc(1, sizeof(List));
	tuple->objectType = obj;
	tuple->type = LT_TYPED_LIST;
	return tuple;
}

/** BINARY COMPARATOR SECTION **/
BinaryComparator * BinaryComparatorSemanticAction(BinaryComparatorType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	BinaryComparator * binaryComparator = calloc(1, sizeof(BinaryComparator));
	binaryComparator->type = type;
	return binaryComparator;
}

/** COMPARABLE VALUE SECTION **/
ComparableValue * VariableComparableValueSemanticAction(VariableCall * var, ComparableValueType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ComparableValue * comparableValue = calloc(1, sizeof(ComparableValue));
	comparableValue->variable = var;
	comparableValue->type = type;
	return comparableValue;
}

ComparableValue * ExpressionComparableValueSemanticAction(Expression * expr, ComparableValueType type) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	ComparableValue * comparableValue = calloc(1, sizeof(ComparableValue));
	comparableValue->expression = expr;
	comparableValue->type = type;
	return comparableValue;
}

/** CONDITIONAL SECTION **/
Conditional * BinaryConditionalSemanticAction(CondType type, Conditional * leftCond, Conditional * rightCond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = type;
    conditional->leftCond = leftCond;
    conditional->rightCond = rightCond;
    return conditional;
}

Conditional * UnaryLogicOperatorConditionalSemanticAction(Conditional * cond) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = LOGIC_NOT;
    conditional->notConditional = cond;
    return conditional;
}

Conditional * ExpressionConditionalSemanticAction(Expression * exp) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
    Conditional * conditional = calloc(1, sizeof(Conditional));
    conditional->type = EXPRESSION_VALUE;
    conditional->expression = exp;
    return conditional;
}

Conditional * ExpressionComparisonConditionalSemanticAction(BinaryComparator * bcomp, Expression * left, Expression * right) {
	_logSyntacticAnalyzerAction(__FUNCTION__);
	Conditional * conditional = calloc(1, sizeof(Conditional));
	conditional->type = COMPARISON_EXPRESSION;
    conditional->leftCompExpression = left;
    conditional->rightCompExpression = right;
    conditional->binaryComparator = bcomp;
    return conditional;
}
