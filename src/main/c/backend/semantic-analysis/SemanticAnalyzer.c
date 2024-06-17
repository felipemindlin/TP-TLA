#include "SemanticAnalyzer.h"

static Logger * _logger = NULL;

/** PRIVATE FUNCTIONS SECTION **/

/**
 * @brief Get the resulting data type of an arithmetic operation between two other data types.
 * @param left The data type of the left operand.
 * @param right The data type of the right operand.
 * @return The resulting data type of the operation, or SA_ERROR if the operation is not defined for the given data types.
 */
static SaDataType getOperationDataType(const SaDataType left, const SaDataType right) {
    SaValidBinaryArithmeticTypes jumpIdx = left * 2 + right * 3;
    switch (jumpIdx) {
        case SA_INT_INT_OP:
        case SA_INT_BOOL_OP:
        case SA_BOOL_INT_OP:
            return SA_INTEGER;
        case SA_BOOL_BOOL_OP:
            return SA_BOOLEAN;
        case SA_FLT_INT_OP:
        case SA_FLT_FLT_OP:
        case SA_FLT_BOOL_OP:
        case SA_INT_FLT_OP:
        case SA_BOOL_FLT_OP:
            return SA_FLOAT;
        case SA_STR_STR_OP:
            return SA_STRING;
        default:
            return SA_ERROR;
    }
}

/**
 * @brief Creates an invalid computation result initialized with the correct values;
 */
static SaComputationResult generateInvalidComputationResult() {
    return (SaComputationResult) {
        .dataType = SA_ERROR,
        .success = false
    };
}

/**
 * @brief Wrapper for generateInvalidComputationResult, intended for function pointers.
 */
static SaComputationResult generateInvalidBinaryOperation(const SaComputationResult left, const SaComputationResult right) {
    return generateInvalidComputationResult();
}

/**
 * Converts and expression type to the proper binary operator. If that's not
 * possible, returns a binary operator that always returns an invalid
 * computation result.
 */
static BinaryArithmeticOperation _expressionTypeToBinaryOperator(const ExpressionType type) {
	switch (type) {
		case ADDITION: 
        case MULTIPLICATION:
            return binaryArithmeticOperatorW;
        case SUBTRACTION:
        case DIVISION:
        case TRUNCATED_DIVISION:
        case MODULO:
        case EXPONENTIATION:
            return binaryArithmeticOperatorWO;
		default:
			logCritical(_logger, "Unknown expression type for conversion: %d", type);
			return generateInvalidBinaryOperation;
	}
}

/** PUBLIC FUNCTIONS SECTION **/

void initializeSemanticAnalyzerModule() {
    _logger = createLogger("Test");
}

void shutdownSemanticAnalyzerModule() {
    if (_logger != NULL) {
        destroyLogger(_logger);
    }
}

/**
 * @brief Check if a function with an operator WITH string support is defined for the given operands.
 * @param left The left operand.
 * @param right The right operand.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult binaryArithmeticOperatorW(SaComputationResult left, SaComputationResult right) {
    if (!left.success || !right.success) {
        return generateInvalidComputationResult();
    }
    SaDataType operationDataType = getOperationDataType(left.dataType, right.dataType);
    if (operationDataType == SA_ERROR) {
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) { 
        .dataType = operationDataType,
        .success = true
    };
}

/**
 * @brief Check if a function with an operator WITHOUT string support is defined for the given operands.
 * @param left The left operand.
 * @param right The right operand.
 * @return A computation result with the subjacent data type if successful.
 */
SaComputationResult binaryArithmeticOperatorWO(SaComputationResult left, SaComputationResult right) {
    logDebugging(_logger, "Performing addition...");
    if (!left.success || !right.success) {
        return generateInvalidComputationResult();
    }
    SaDataType operationDataType = getOperationDataType(left.dataType, right.dataType);
    if (operationDataType == SA_ERROR || operationDataType == SA_STRING) {
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) { 
        .dataType = operationDataType,
        .success = true
    };
}

SaComputationResult computeProgram(Program * program) {
    logDebugging(_logger, "Computing program (ADDR: %lx)...", program);
    if (program == NULL) {
        logDebugging(_logger, "reached EOF. Backtracking...");
        return (SaComputationResult) {
            .dataType = SA_VOID,
            .success = true
        };
    }

    SaComputationResult nextResult = computeProgram(program->nextProgram);
    if (!nextResult.success) {
        logDebugging(_logger, "...invalid.");
        return nextResult;
    } else if (program->sentence == NULL) {
        logDebugging(_logger, "...empty line");
        return nextResult;
    } else {
        logDebugging(_logger, "...non-empty line");
        return computeSentence(program->sentence);
    }
}

SaComputationResult computeSentence(Sentence * sentence) {
    logDebugging(_logger, "Computing sentence (ADDR: %lx)...", sentence);
    switch (sentence->type){
        case EXPRESSION_SENTENCE:
            logDebugging(_logger, "...of expression type %d", sentence->expression->type);
            return computeExpression(sentence->expression);
        // TODO: implement the rest of the sentence types
        case VARIABLE_SENTENCE:
        case BLOCK_SENTENCE:
        case RETURN_SENTENCE:
        default:
            logError(_logger, "The specified sentence type is not supported: %d", sentence->type);
            return generateInvalidComputationResult();
    }  
}

SaComputationResult computeExpression(Expression * expression) {
    logDebugging(_logger, "Computing expression (ADDR: %lx)...", expression);
    switch (expression->type) {
        case CONSTANT_EXPRESSION:
            logDebugging(_logger, "...of a constant of type %d", expression->constant->type);
            return computeConstant(expression->constant);
        // TODO:implement as many expressions as possible
        case ADDITION:
        case MULTIPLICATION:
        case SUBTRACTION:
        case DIVISION:
        case TRUNCATED_DIVISION:
        case MODULO:
        case EXPONENTIATION:
            logDebugging(_logger, "...of an arithmetic operator (type: %d)", expression->type);
            return (_expressionTypeToBinaryOperator(expression->type))
                (computeExpression(expression->leftExpression), computeExpression(expression->rightExpression));
        default:
            logError(_logger, "The specified expression type is not supported: %d", expression->type);
            return generateInvalidComputationResult();
    }
}

SaComputationResult computeConstant(Constant * constant) {
    logDebugging(_logger, "Computing constant (ADDR: %lx)...", constant);
    switch (constant->type) {
        case CT_BOOLEAN:
            logDebugging(_logger, "...of boolean type (value: %s)", constant->boolean ? "true" : "false");
            return (SaComputationResult) {
                .dataType = SA_BOOLEAN,
                .success = true
            };
        case CT_INTEGER:
            logDebugging(_logger, "...of integer type (value: %ld)", constant->integer);
            return (SaComputationResult) {
                .dataType = SA_INTEGER,
                .success = true
            };
        case CT_FLOAT:
            logDebugging(_logger, "...of float type (value: ~%.3f)", constant->decimal);
            return (SaComputationResult) {
                .dataType = SA_FLOAT,
                .success = true
            };
        case CT_STRING:
            logDebugging(_logger, "...of string type (addr: %lx)", constant->string);
            return (SaComputationResult) {
                .dataType = SA_STRING,
                .success = true
            };
        default:
            logError(_logger, "The specified constant type is not supported: %d", constant->type);
            return generateInvalidComputationResult();
    }
}