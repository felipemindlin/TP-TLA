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

void releaseConstant(Constant * constant) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (constant != NULL) {
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
			case FACTOR:
				releaseFactor(expression->factor);
				break;
		}
		free(expression);
	}
}

void releaseFactor(Factor * factor) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (factor != NULL) {
		switch (factor->type) {
			case CONSTANT:
				releaseConstant(factor->constant);
				break;
			case EXPRESSION:
				releaseExpression(factor->expression);
				break;
		}
		free(factor);
	}
}

void releaseProgram(Program * program) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (program != NULL) {
		releaseExpression(program->expression);
		free(program);
	}
}

void releaseVariable(Variable * variable){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (variable != NULL) {
		free(variable);
	}

}

void releaseConditional(Conditional * conditional){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (conditional != NULL) {
		switch (conditional->type) {
			case BOOLEAN_COND:
                releaseConditional(conditional->leftCond);
                releaseConditional(conditional->rightCond);
                break;
			case VARIABLE_AND_BOOLEAN_COND:
                releaseConditional(conditional->cond);
                releaseVariableCall(conditional->condVar);
                break;
			case VARIABLE_BOOLEAN_COND:
                releaseVariableCall(conditional->leftCondVar);
                releaseVariableCall(conditional->rightCondVar);
                break;
			case COMPARISON_COND:
                releaseExpression(conditional->leftExpression);
                releaseExpression(conditional->rightExpression);
                break;
			case VARIABLE_COMPARISON_COND:
                releaseVariableCall(conditional->leftExpressionVar);
                releaseVariableCall(conditional->rightExpressionVar);
                break;
			case VARIABLE_AND_CONST_COMPARISON_COND:
                releaseVariableCall(conditional->expressionVar);
                releaseVariableCall(conditional->exp);
                break;
			case OBJECT_COMPARISON_COND:
                releaseObject(conditional->leftObject);
                releaseObject(conditional->rightObject);
                break;
			case VARIABLE_OBJECT_COMPARISON_COND:
                releaseVariableCall(conditional->variableLeftObj);
                releaseVariableCall(conditional->variableRightObj);
				break;
			case VARIABLE_AND_OBJECT_COMPARISON_COND:
                releaseVariableCall(conditional->variableObj);
                releaseObject(conditional->obj);
                break;
            case EXPRESSION_COND:
                releaseExpression(conditional->expression);
                break;
            case VARIABLE_COND:
                releaseVariableCall(conditional->variable);
                break;
            case OBJECT_COND:
                releaseObject(conditional->object);
		}
		free(condtional);
	}
}

void releaseSentence(Sentence * sentence){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (sentence != NULL) {
		switch (sentence->type) {
			case FUNCTION_DEFINITION:
				// free(sentence->functionName); no es necesario casi seguro que no tiene sentido freear un const char * pero lo dejo para charlar
				releaseParameters(sentence->parameters);
				break;
			case FUNCTION_CALL:
				releaseFunctionCall(sentence->functionCall);
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

void releaseObject(Object * object) {
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);

}
