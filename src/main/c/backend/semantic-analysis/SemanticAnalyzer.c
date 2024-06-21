#include "SemanticAnalyzer.h"
#include "utils.h"
static const boolean redeclarationIsError = false;

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
            return SA_FLOAT;
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
        case COMPARISON_EXPRESSION:
            return binaryComparisonOperator;
        case LOGIC_AND:
        case LOGIC_OR:
            return binaryBooleanOperator;
        case LOGIC_NOT:
            return notBooleanOperator;
		default:
			logCritical(_logger, "Unknown expression type for conversion: %d", type);
			return generateInvalidBinaryOperation;
	}
}

/**
 * @brief Check if a function or class definition is present in the given sentence.
 * @param sentence The sentence to be checked.
 * @return True if a definition is present, false otherwise.
 */
static boolean _hasDefinition(Sentence * sentence) {
    if (sentence == NULL) return false;
    else return (sentence->type == BLOCK_SENTENCE && (sentence->block->type == BT_FUNCTION_DEFINITION || sentence->block->type == BT_CLASS_DEFINITION))
                || _hasDefinition(sentence->nextSentence);
}

/**
 * @brief Add a symbol to the symbol table. If the symbol is already declared, it will be updated unless the data types mismatch.
 * @param identifier The identifier/name of the symbol.
 * @param comp The computation result of the expression assigned to the symbol.
 * @return true if the symbol was added or updated successfully, false otherwise.
 */
static boolean _addToSymbolTable(const char * identifier, SaComputationResult comp) {
    SaDataType dataType = (comp.dataType == SA_UNDECLARED)? SA_OBJECT : comp.dataType;
    tKey key = { .varname = identifier };
    tValue value = { .type = dataType };
    tValue existingValue;

    boolean isAlreadyDeclared = symbolTableFind(&key, &existingValue);
    boolean isMismatchType = existingValue.type != SA_UNDECLARED && existingValue.type != comp.dataType;

    if (isAlreadyDeclared && isMismatchType) {
        logWarning(_logger, "Symbol %s is already declared with a mismatching type", identifier);
        return false;
    }

    symbolTableInsert(&key, &value);
    if (isAlreadyDeclared) {
        logInformation(_logger, "Symbol %s updated with type %d in the symbol table", key.varname, value.type);
    } else {
        logInformation(_logger, "Symbol %s added with type %d to the symbol table", key.varname, value.type);
    }
    return true;
}

/**
 * @brief Get the data type of a symbol from the symbol table. If the symbol is not present, it is added to the table with "undeclared" type.
 * @param identifier The identifier/name of the symbol.
 * @return The value of the symbol if it is present in the table, a literal "undefined" value otherwise.
 */
static tValue _getFromSymbolTable(const char * identifier) {
    tKey key = { .varname = identifier };
    tValue value;

    boolean found = symbolTableFind(&key, &value);

    value.type = SA_UNDECLARED;
    logInformation(_logger, "Undeclared symbol %s with type %d added to the symbol table", key.varname, value.type);
    symbolTableInsert(&key, &value);

    return value;
}

/** PUBLIC FUNCTIONS SECTION **/

void initializeSemanticAnalyzerModule() {
    _logger = createLogger("SemanticAnalyzer");
    symbolTableInit();
    funcListInit();
    logInformation(_logger, "Semantic Analyzer module initialized");
}

void shutdownSemanticAnalyzerModule() {
    if (_logger != NULL) {
        destroyLogger(_logger);
    }
    symbolTableDestroy();
}

SaComputationResult binaryComparisonOperator(SaComputationResult left, SaComputationResult right) {
    if (!left.success || !right.success) {
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) {
        .dataType = SA_BOOLEAN,
        .success = true
    };
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
        .dataType = SA_FLOAT,
        .success = true
    };
}

SaComputationResult binaryBooleanOperator(SaComputationResult left, SaComputationResult right) {
    logDebugging(_logger, "Performing boolean operation ...");
    if (!left.success || !right.success) {
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) {
        .dataType = SA_BOOLEAN,
        .success = true
    };
}

SaComputationResult notBooleanOperator(SaComputationResult left) {
    logDebugging(_logger, "Performing boolean operation ...");
    if (!left.success) {
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) {
        .dataType = SA_BOOLEAN,
        .success = true
    };
}

SaComputationResult computeProgram(Program * program) {
    logDebugging(_logger, "Computing program (ADDR: %p)...", program);
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
        SaComputationResult tempSacr = computeSentence(program->sentence);
        if (symbolTableHasUnititializedTypes()) {
            logError(_logger, "There are symbols with uninitialized types");
            return generateInvalidComputationResult();
        }
        return tempSacr;
    }
}

SaComputationResult computeSentence(Sentence * sentence) {
    if (sentence == NULL) { return (SaComputationResult) { .dataType = SA_VOID, .success = true }; };
    if (!computeSentence(sentence->nextSentence).success) { return generateInvalidComputationResult(); }
    logDebugging(_logger, "Computing sentence (ADDR: %p)...", sentence);
    switch (sentence->type){
        case EXPRESSION_SENTENCE:
            logDebugging(_logger, "...of expression type %d", sentence->expression->type);
            return computeExpression(sentence->expression);
        case BLOCK_SENTENCE:
            logDebugging(_logger, "...of code block type %d", sentence->type);
            return computeBlock(sentence->block);
        // TODO: implement the rest of the sentence types
        case VARIABLE_SENTENCE:
            logDebugging(_logger, "...of variable declaration type");
            return computeVariableDeclaration(sentence->variable);
        case RETURN_SENTENCE:
            logDebugging(_logger, "...of return expression type %d", sentence->expression->type);
            if (sentence->nextSentence != NULL) {
                logError(_logger, "but Return statement must be the last statement in the block");
                return generateInvalidComputationResult();
            }
            return computeExpression(sentence->expression);
        default:
            logError(_logger, "The specified sentence type is not supported: %d", sentence->type);
            return generateInvalidComputationResult();
    }
}

SaComputationResult computeExpression(Expression * expression) {
    logDebugging(_logger, "Computing expression (ADDR: %p)...", expression);
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
        case COMPARISON_EXPRESSION:
            if (expression->leftExpression->type == VARIABLE_CALL_EXPRESSION){
                markArith(expression->leftExpression->variableCall->variableName);
                logDebugging(_logger, expression->leftExpression->variableCall->variableName);
            }
            if (expression->rightExpression->type == VARIABLE_CALL_EXPRESSION){
                markArith(expression->rightExpression->variableCall->variableName);
                logDebugging(_logger, expression->rightExpression->variableCall->variableName);
            }
            logDebugging(_logger, "...of an arithmetic operator (type: %d)", expression->type);
            return (_expressionTypeToBinaryOperator(expression->type))
                (computeExpression(expression->leftExpression), computeExpression(expression->rightExpression));
        case LOGIC_AND:
        case LOGIC_OR:
            if (expression->leftExpression->type == VARIABLE_CALL_EXPRESSION){
                markBoolean(expression->leftExpression->variableCall->variableName);
            }
            if (expression->rightExpression->type == VARIABLE_CALL_EXPRESSION){
                markBoolean(expression->rightExpression->variableCall->variableName);
            }
            logDebugging(_logger, "...of an arithmetic operator (type: %d)", expression->type);
            return (_expressionTypeToBinaryOperator(expression->type))
                (computeExpression(expression->leftExpression), computeExpression(expression->rightExpression));
        case LOGIC_NOT:
            return notBooleanOperator(computeExpression(expression->leftExpression));
        case VARIABLE_CALL_EXPRESSION:
            logDebugging(_logger, "...of a variable call (id: %s)", expression->variableCall->variableName);
            return computeVariableCall(expression->variableCall);
        case FUNCTION_CALL_EXPRESSION:
            logDebugging(_logger, "...of a function call (id: %s)", expression->functionCall->functionName);
            return computeFunctionCall(expression->functionCall);
        default:
            logError(_logger, "The specified expression type is not supported: %d", expression->type);
            return generateInvalidComputationResult();
    }
}

SaComputationResult computeVariableCall(VariableCall * vCall) {
    if (vCall == NULL) {
        logError(_logger, "Invalid variable call");
        return generateInvalidComputationResult();
    }
    logDebugging(_logger, "Computing variable call (ADDR: %p)...", vCall);
    tValue retVal = _getFromSymbolTable(vCall->variableName);
    // if (retVal.type == SA_ERROR) {
    //     logError(_logger, "Undeclared variable");
    //     return generateInvalidComputationResult();
    // }
    return (SaComputationResult) {
        .dataType = retVal.type,
        .success = true
    };
}

SaComputationResult computeFunctionCall(FunctionCall * fCall) {
    if (fCall == NULL) {
        logError(_logger, "Invalid function call");
        return generateInvalidComputationResult();
    }
    logDebugging(_logger, "Computing function call (ADDR: %p)...", fCall);
    tValue retVal = _getFromSymbolTable(fCall->functionName);
    return (SaComputationResult) {
        .dataType = retVal.type,
        .success = true
    };
}

SaComputationResult computeBlock(Block * block) {
    logDebugging(_logger, "Computing code block (ADDR: %p)...", block);
    if (!computeSentence(block->nextSentence).success) {
        logError(_logger, "The code block body is invalid");
        return generateInvalidComputationResult();
    }
    switch (block->type) {
        case BT_FUNCTION_DEFINITION:
            logDebugging(_logger, "...of function definition type");
            return computeFunctionDefinition(block->functionDefinition, block->nextSentence);
        case BT_CONDITIONAL:
            logDebugging(_logger, "...of conditional type");
            return computeConditionalBlock(block->conditional);
        case BT_FOR:
            logDebugging(_logger, "...of for loop type");
            return computeForLoopBlock(block->forBlock);
        case BT_WHILE:
            logDebugging(_logger, "...of while loop type");
            return computeWhileLoopBlock(block->whileBlock);
        case BT_CLASS_DEFINITION:
        default:
            logError(_logger, "The specified block type is not supported: %d", block->type);
            return generateInvalidComputationResult();
    }
}

SaComputationResult computeForLoopBlock(ForBlock * forLoop) {
    logDebugging(_logger, "Computing for loop block (ADDR: %p)...", forLoop);
    SaComputationResult leftCompute = computeExpression(forLoop->left);
    SaComputationResult rightCompute = computeExpression(forLoop->right);
    if (forLoop->left == NULL || forLoop->left->type != VARIABLE_CALL_EXPRESSION) {
        logError(_logger, "Invalid for loop initialization");
        return generateInvalidComputationResult();
    }
    if (!leftCompute.success || !rightCompute.success) {
        logError(_logger, "Invalid for loop bounds");
        return generateInvalidComputationResult();
    }
    _addToSymbolTable(forLoop->left->variableCall->variableName,
        (SaComputationResult) { .dataType = SA_OBJECT, .success = true });
    return (SaComputationResult) {
        .dataType = SA_VOID,
        .success = true
    };
}

SaComputationResult computeWhileLoopBlock(WhileBlock * whileLoop) {
    logDebugging(_logger, "Computing while loop block (ADDR: %p)...", whileLoop);
    SaComputationResult conditionCompute = computeExpression(whileLoop->expression);
    if (!conditionCompute.success || conditionCompute.dataType == SA_VOID) {
        logError(_logger, "Invalid condition for while loop");
        return generateInvalidComputationResult();
    }
    return (SaComputationResult) {
        .dataType = SA_VOID,
        .success = true
    };
}

SaComputationResult computeConditionalBlock(ConditionalBlock * conditional) {
    logDebugging(_logger, "Computing conditional block (ADDR: %p)...", conditional);
    if (conditional->type == CB_ELSE) {
        logDebugging(_logger, "...of else type");
        return (SaComputationResult) {
            .dataType = SA_VOID,
            .success = true
        };
    }
    SaComputationResult exprCompute = computeExpression(conditional->expression);
    if (!exprCompute.success || exprCompute.dataType == SA_VOID) {
        logError(_logger, "Condition for if/else if must be a valid boolean expression");
        return generateInvalidComputationResult();
    }
    logDebugging(_logger, "...of if/else if type");
    return (SaComputationResult) {
        .dataType = SA_VOID,
        .success = true
    };
}

boolean _findReturn(Sentence * first, SaDataType * returnType) {
    if (first == NULL) {
        logDebugging(_logger, "This function returns void");
        return false;
    } else if (first->type == RETURN_SENTENCE) {
        // Inefficient, but works for now
        *returnType = computeExpression(first->expression).dataType;
        logDebugging(_logger, "This function returns type %d", *returnType);
        return true;
    } else {
        return _findReturn(first->nextSentence, returnType);
    }
}

SaComputationResult computeFunctionDefinition(FunctionDefinition * fdef, Sentence * body) {
    if (!computeSentence(body).success) { return generateInvalidComputationResult(); }
    logDebugging(_logger, "Computing function definition (ADDR: %p)...", fdef);
    if (_hasDefinition(body)) {
        logError(_logger, "Definition of classes or functions inside a function is not allowed");
        return generateInvalidComputationResult();
    }
    switch (fdef->type) {
        case FD_GENERIC:
            logDebugging(_logger, "...without explicitely typed return (name: %s)", fdef->functionName);
            SaDataType returnType;
            boolean hasReturn = _findReturn(body, &returnType);
            SaComputationResult paramComputation = computeParameters(fdef->parameters);
            if (!paramComputation.success) {
                logError(_logger, "Invalid parameters for function %s", fdef->functionName);
                return generateInvalidComputationResult();
            }
            SaComputationResult sacr = {
                .dataType = hasReturn? returnType : SA_VOID,
                .success = true
            };
            _addToSymbolTable(fdef->functionName, sacr);
            // hacky, change whenever possible
            sacr.dataType = SA_VOID;
            return sacr;
        case FD_OBJECT_TYPE:
        case FD_VARIABLE_CALL_TYPE:
        case FD_LIST_TYPE:
        case FD_TUPLE_TYPE:
        case FD_BUILTIN_TYPE:
        default:
            logError(_logger, "The specified function definition type is not supported: %d", fdef->type);
            return generateInvalidComputationResult();
    }
}

SaComputationResult computeParameters(Parameters * params) {
    logDebugging(_logger, "Computing parameters (ADDR: %p)...", params);
    if (params == NULL || params->leftExpression == NULL) {
        logDebugging(_logger, "...no parameters");
        return (SaComputationResult) {
            .dataType = SA_VOID,
            .success = true
        };
    }
    if (!computeParameters(params->rightParameters).success) {
        logError(_logger, "...invalid parameters");
        return generateInvalidComputationResult();
    }
    if (params->leftExpression->type != VARIABLE_CALL_EXPRESSION) {
        logError(_logger, "...invalid parameter");
        return generateInvalidComputationResult();
    }
    SaComputationResult thisComputation = {
        .dataType = SA_OBJECT,
        .success = true
    };
    _addToSymbolTable(params->leftExpression->variableCall->variableName, thisComputation);
    return thisComputation;
}

SaComputationResult computeVariableDeclaration(Variable * var) {
    logDebugging(_logger, "Computing variable declaration (ADDR: %p)...", var);
    SaComputationResult exprResult = computeExpression(var->expression);
    if (!exprResult.success) {
        logError(_logger, "...invalid expression");
        return generateInvalidComputationResult();
    }

    boolean wasAdded = _addToSymbolTable(var->identifier, exprResult);
    if (!wasAdded) {
        logError(_logger, "The variable declared type mismatches its uses");
        return generateInvalidComputationResult();
    }
    // This may change should we support assignments other than '='
    return (SaComputationResult) {
        .dataType = SA_VOID,
        .success = true
    };
}

SaComputationResult computeConstant(Constant * constant) {
    logDebugging(_logger, "Computing constant (ADDR: %p)...", constant);
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
            logDebugging(_logger, "...of string type (ADDR: %p)", constant->string);
            return (SaComputationResult) {
                .dataType = SA_STRING,
                .success = true
            };
        default:
            logError(_logger, "The specified constant type is not supported: %d", constant->type);
            return generateInvalidComputationResult();
    }
}
