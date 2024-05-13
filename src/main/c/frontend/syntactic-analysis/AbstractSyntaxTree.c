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
			case IN_PARENTHESIS_EXPRESSION:
				releaseExpression(expression->expression);
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

void releaseVariable(Variable * variable){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (variable != NULL) {
		free(variable);
	}

}

void releaseConditional(Conditional * condtional){
	logDebugging(_logger, "Executing destructor: %s", __FUNCTION__);
	if (condtional != NULL) {
		switch (condtional->type) {
			case LOGIC_AND:
			case LOGIC_OR:
			case EQUALS_COMPARISON:
			case NOT_EQUALS_COMPARISON:
			case GREATER_THAN_COMPARISON:
			case GREATER_THAN_OR_EQUALS_COMPARISON:
			case LESS_THAN_COMPARISON:
			case LESS_THAN_OR_EQUALS_COMPARISON:
				releaseConditional(condtional->leftCond);
				releaseConditional(condtional->rightCond);
				break;
			case LOGIC_NOT: //or FACTOR tienen el mismo value de enum revisar
				break;
		}
		free(condtional);
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
			case BLOCK_SENTENCE:
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


