#include "Test.h"

static Logger * _logger = NULL;

void initializeTestModule() {
    _logger = createLogger("Test");
}

void shutdownTestModule() {
    if (_logger != NULL) {
        destroyLogger(_logger);
    }
}

/** PRIVATE FUNCTIONS **/

/** PUBLIC FUNCTIONS **/
ComputationResult computeConstant(Constant * constant) {
    ComputationResult computationResult;
    computationResult.succeed = true;
    logDebugging(_logger, "Computing constant (ADDR: %x)", constant);
    switch (constant->type) {
        case CT_BOOLEAN:
            logDebugging(_logger, "Computing constant boolean: %d", constant->boolean);
            computationResult.booleanValue = constant->boolean;
            computationResult.type = CRVT_BOOLEAN;
            break;
        case CT_INTEGER:
            logDebugging(_logger, "Computing constant integer: %d", constant->integer);
            computationResult.integerValue = constant->integer;
            computationResult.type = CRVT_INTEGER;
            break;
        case CT_STRING:
            logDebugging(_logger, "Computing constant string: %s", constant->string);
            // TODO: should we copy or keep the ref?
            computationResult.stringValue = constant->string;
            computationResult.type = CRVT_STRING;
            break;
        case CT_FLOAT:
            logDebugging(_logger, "Computing constant float: %f", constant->decimal);
            computationResult.floatValue = constant->decimal;
            computationResult.type = CRVT_FLOAT;
            break;
        default:
            logError(_logger, "The specified constant type is not supported: %d", constant->type);
            computationResult.succeed = false;
            computationResult.type = CRVT_BOTTOM;
            break;
    }
    return computationResult;
}