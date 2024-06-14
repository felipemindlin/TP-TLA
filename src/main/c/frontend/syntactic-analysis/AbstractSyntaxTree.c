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
	if (object == NULL) return;

    free(object);
}

void releaseClassDefinition(ClassDefinition * classDefinition) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (classDefinition == NULL) return;

    releaseTuple(classDefinition->tuple);
    free(classDefinition->className);
    free(classDefinition);
}

void releaseList(List * list) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (list == NULL) return;
    switch (list->type) {
        case LT_TYPED_LIST:
            releaseObject(list->objectType);
        case LT_PARAMETRIZED_LIST:
            releaseParameters(list->elements);
    }
    free(list);
}

void releaseTuple(Tuple * tuple){
	releaseList((List *)tuple);
}

void releaseMethodCall(MethodCall * methodCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (methodCall == NULL) return;

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

void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant == NULL) return;

    switch (constant->type) {
        case CT_STRING:
            free(constant->string);
        break;
        case CT_LIST:
            releaseList(constant->list);
        break;
        case CT_TUPLE:
            releaseTuple(constant->tuple);
    }
    free(constant);
}

void releaseExpression(Expression * expression) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (expression == NULL) return;
    switch (expression->type) {
        case ADDITION:
        case DIVISION:
        case MULTIPLICATION:
        case SUBTRACTION:
        case LOGIC_OR:
        case LOGIC_AND:
            releaseExpression(expression->leftExpression);
            releaseExpression(expression->rightExpression);
        break;
        case VARIABLE_CALL_EXPRESSION:
            releaseVariableCall(expression->variableCall);
        break;
        case CONSTANT_EXPRESSION:
            releaseConstant(expression->constant);
            break;
        case METHOD_CALL_EXPRESSION:
            releaseMethodCall(expression->methodCall);
            break;
        case FIELD_GETTER_EXPRESSION:
            releaseFieldGetter(expression->fieldGetter);
            break;
        case LOGIC_NOT:
            releaseExpression(expression->notExpression);
            break;
        case COMPARISON_EXPRESSION:
            releaseExpression(expression->leftCompExpression);
            releaseExpression(expression->rightCompExpression);
            break;
        case FUNCTION_CALL_EXPRESSION:
            releaseFunctionCall(expression->functionCall);
		}
    free(expression);
}

void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program == NULL) return;

    if(program->depth != NULL){
        releaseDepth(program->depth);
    }
    if(program->sentence != NULL){
        releaseSentence(program->sentence);
    }
    if(program->nextProgram != NULL){
        releaseProgram(program->nextProgram);
    }
    free(program);
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
		releaseExpression(variable->expression);
		free(variable);
	}
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
	if (block == NULL) return;

    switch (block->type) {
        case BT_FUNCTION_DEFINITION:
            // free(sentence->functionName); no es necesario casi seguro que no tiene sentido freear un const char * pero lo dejo para charlar
            if(block->functionDefinition != NULL){
                releaseFunctionDefinition(block->functionDefinition);
            }
        break;
        case BT_CLASS_DEFINITION:
            if(block->classDefinition != NULL){
                releaseClassDefinition(block->classDefinition);
            }
        break;
        case BT_CONDITIONAL:
            if(block->conditional != NULL){
                releaseConditionalBlock(block->conditional);
            }
            if(block->nextCond != NULL){
                releaseBlock(block->nextCond);
            }
            break;
        case BT_FOR:
            if(block->forBlock != NULL){
                releaseForBlock(block->forBlock);
            }
            break;
        case BT_WHILE:
            if(block->whileBlock){
                releaseWhileBlock(block->whileBlock);
            }
    }
    if(block->nextProgram != NULL) {
        releaseProgram(block->nextProgram);
    }
}

void releaseConditionalBlock(ConditionalBlock * cblock) {
    if(cblock != NULL){
        releaseExpression(cblock->expression);
        free(cblock);
    }
}

void releaseWhileBlock(WhileBlock * wblock) {
    if(wblock != NULL) {
        releaseExpression(wblock->expression);
        free(wblock);
    }
}

void releaseForBlock(ForBlock * fblock) {
    if(fblock != NULL) {
        releaseExpression(fblock->left);
        releaseExpression(fblock->right);
        free(fblock);
    }
}

void releaseSentence(Sentence * sentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sentence == NULL) return;

    switch (sentence->type) {
        case EXPRESSION_SENTENCE:
            // free(sentence->functionName); // no es necesario casi seguro que no tiene sentido freear un const char * pero lo dejo para charlar
            if(sentence->expression != NULL){
                releaseExpression(sentence->expression);
            }
        break;
        case VARIABLE_SENTENCE:
            if(sentence->variable != NULL){
                releaseVariable(sentence->variable);
            }
        case BLOCK_SENTENCE:
            if(sentence->block != NULL){
                releaseBlock(sentence->block);
            }
        break;
    }
    free(sentence);
}

void releaseVariableCall(VariableCall * variableCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (variableCall != NULL) {
		// free(variableCall->variableName); // same as above
		free(variableCall);
	}
}

void releaseFunctionCall(FunctionCall * functionCall){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (functionCall != NULL) {
        if(functionCall->type == FC_DEF) {
            // free(functionCall->functionName); // same as above
        } else {
            releaseObject(functionCall->object);
        }
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

void releaseDepth(Depth * depth){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (depth != NULL) {
		free(depth);
	}
}


