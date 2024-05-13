#include "AbstractSyntaxTree.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;

void initializeAbstractSyntaxTreeModule() {
	_logger = createLogger("AbstractSyntxTree");
}

void shutdownAbstractSyntaxTreeModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/** PUBLIC FUNCTIONS */

void releaseObject(Object * object) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (object != NULL) {
		free(object->className);
		free(object);
	}
}

void releaseClassDefinition(ClassDefinition * classDefinition) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (classDefinition != NULL) {
		releaseTuple(classDefinition->tuple);
		free(classDefinition->className);
		free(classDefinition);
	}
}

void releaseList(List * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (list != NULL) {
		switch (list->type) {
			case LT_TYPED_LIST:
				releaseObject(list->objectType);
			case LT_PARAMETRIZED_LIST:
				releaseParameters(list->elements);
		}
		free(list);
	}
}

void releaseTuple(Tuple * tuple){
	releaseList(tuple);
}

void releaseMethodCall(MethodCall * methodCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (methodCall != NULL) {
		switch (methodCall->type) {
			case MCT_VARIABLE_TRIGGER:
				releaseVariableCall(methodCall->variableCall);
				break;
			case MCT_CONSTANT_TRIGGER:
				releaseConstant(methodCall->constant);
				break;
		}
		releaseFunctionCall(methodCall->functionCall);
		free(methodCall);
	}
}

void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
		switch (constant->type) {
			case CT_INTEGER:
			case CT_BOOLEAN:
			case CT_FLOAT:
			case CT_STRING:
				break;
			case CT_LIST:
				releaseList(constant->list);
				break;
            case CT_TUPLE:
                releaseTuple(constant->tuple);
		}
		free(constant);
	}
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression != NULL) {
		switch (expression->type) {
			case ADDITION:
			case DIVISION:
			case MULTIPLICATION:
			case SUBTRACTION:
				releaseExpression(expression->leftExpression);
				releaseExpression(expression->rightExpression);
				break;
			case VARIABLE_CALL_EXPRESSION:
				releaseVariableCall(expression->variableCall);
				break;
            case CONSTANT_EXPRESSION:
                releaseConstant(expression->constant);
		}
		free(expression);
	}
}

void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseDepth(program->depth);
		releaseSentence(program->sentence);
		releaseProgram(program->nextProgram);
		free(program);
	}
}

void releaseFieldGetter(FieldGetter * fieldGetter) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (fieldGetter != NULL) {
		switch (fieldGetter->type) {
			case FG_CONSTANT_OWNER:
				releaseConstant(fieldGetter->constant);
				break;
			case FG_VARIABLE_OWNER:
				releaseVariableCall(fieldGetter->variableCall);
				break;
	}
	free(fieldGetter);
	}
}

void releaseVariable(Variable * variable){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (variable != NULL) {
		switch (variable->type) {
			case VT_EXPRESSION_VARIABLE:
				releaseExpression(variable->expression);
				break;
			case VT_FUNCCALL_VARIABLE:
				releaseFunctionCall(variable->functionCall);
				break;
			case VT_METHODCALL_VARIABLE:
				releaseMethodCall(variable->methodCall);
				break;
			case VT_FIELDGETTER_VARIABLE:
				releaseFieldGetter(variable->fieldGetter);
				break;
			case VT_OBJECT_VARIABLE:
				releaseObject(variable->object);
				break;
		}
		free(variable);
	}

}

void releaseConditional(Conditional * conditional){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (conditional != NULL) {
		switch (conditional->type) {
			case LOGIC_AND:
            case LOGIC_OR:
                releaseConditional(conditional->leftCond);
                releaseConditional(conditional->rightCond);
				break;
			case LOGIC_NOT: //or FACTOR tienen el mismo value de enum revisar
                releaseConditional(conditional->notConditional);
				break;
	        case EXPRESSION_VALUE:
                releaseExpression(conditional->expression);
                break;
            case COMPARISON_EXPRESSION:
                releaseExpression(conditional->leftCompExpression);
                releaseExpression(conditional->rightCompExpression);
                releaseBinaryComparator(conditional->binaryComparator);
		}
		free(conditional);
	}
}

void releaseBinaryComparator(BinaryComparator * binaryComparator) {
    free(binaryComparator);
}

void releaseFunctionDefinition(FunctionDefinition * functionDefinition){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (functionDefinition != NULL) {
		switch (functionDefinition->type) {
			case FD_GENERIC:
				break;
			case FD_OBJECT_TYPE:
				releaseObject(functionDefinition->objectType);
				break;
			case FD_VARIABLE_CALL_TYPE:
				releaseVariableCall(functionDefinition->returnVariableType);
				break;
			case FD_LIST_TYPE:
				releaseList(functionDefinition->listReturnType);
				break;
			case FD_TUPLE_TYPE:
				releaseTuple(functionDefinition->tupleReturnType);
				break;
		}
		releaseParameters(functionDefinition->parameters);
		free(functionDefinition->functionName);
		free(functionDefinition);
	}
}


void releaseBlock(Block * block){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (block != NULL) {
		switch (block->type) {
			case BT_FUNCTION_DEFINITION:
				// free(sentence->functionName); no es necesario casi seguro que no tiene sentido freear un const char * pero lo dejo para charlar
				releaseFunctionDefinition(block->functionDefinition);
				break;
			case BT_CLASS_DEFINITION:
				releaseClassDefinition(block->classDefinition);
				break;
			// case BT_CONDITIONAL:
			// 	releaseConditional()
			// 	break;
			// case BT_FOR:
			// 	releaseVariable(sentence->variable);
			// 	break;
			// case BT_WHILE:
			// 	releaseBlock(sentence->block);
			// 	break;
		}
		releaseProgram(block->nextProgram);
		free(block);
	}
}

void releaseSentence(Sentence * sentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sentence != NULL) {
		switch (sentence->type) {
			case EXPRESSION_SENTENCE:
				// free(sentence->functionName); no es necesario casi seguro que no tiene sentido freear un const char * pero lo dejo para charlar
				releaseExpression(sentence->expression);
				break;
			case VARIABLE_SENTENCE:
				releaseVariable(sentence->variable);
			case BLOCK_SENTENCE:
				releaseBlock(sentence->block);
				break;
		}
		free(sentence);
	}
}

void releaseVariableCall(VariableCall * variableCall){

	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (variableCall != NULL) {
		//free(variableCall->variableName); same as above
		free(variableCall);
	}
}

void releaseFunctionCall(FunctionCall * functionCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (functionCall != NULL) {
		// free(functionCall->functionName); same as above
		releaseParameters(functionCall->functionArguments);
		free(functionCall);
	}
}

void releaseParameters(Parameters * parameters){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (parameters != NULL) {
		releaseExpression(parameters->leftExpression);
		releaseParameters(parameters->rightParameters);
		free(parameters);
	}
}

void releaseNewline(Newline * newline){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (newline != NULL) {
		free(newline);
	}
}

void releaseDepth(Depth * depth){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (depth != NULL) {
		free(depth);
	}
}


