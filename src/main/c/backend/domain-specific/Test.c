// #include "Test.h"

// static Logger * _logger = NULL;

// void initializeTestModule() {
//     _logger = createLogger("Test");
// }

// void shutdownTestModule() {
//     if (_logger != NULL) {
//         destroyLogger(_logger);
//     }
// } 

// /** PRIVATE FUNCTIONS **/

// /** PUBLIC FUNCTIONS **/
// ComputationResult computeProgram(Program * program) {
//     logDebugging(_logger, "Computing program (ADDR: %lx)...", program);
//     if (program == NULL) {
//         logDebugging(_logger, "reached EOF");
//         return (ComputationResult) {
//             .succeed = true,
//             .type = CRVT_END
//         };
//     }

//     ComputationResult nextResult = computeProgram(program->nextProgram);
//     if (!nextResult.succeed) {
//         logDebugging(_logger, "INVALID");
//         return nextResult;
//     } else if (program->sentence == NULL) {
//         logDebugging(_logger, "empty line");
//         return nextResult;
//     } else {
//         logDebugging(_logger, "non-empty line");
//         return computeSentence(program->sentence);
//     }
// }

// ComputationResult computeSentence(Sentence * sentence) {
//     logDebugging(_logger, "Computing sentence (ADDR: %lx)...", sentence);
//     switch (sentence->type){
//         case EXPRESSION_SENTENCE:
//             logDebugging(_logger, "...of expression type %d", sentence->expression->type);
//             return computeExpression(sentence->expression);
//         default:
//             logError(_logger, "The specified sentence type is not supported: %d", sentence->type);
//             ComputationResult failedComputationResult = {
//                 .succeed = false,
//                 .type = CRVT_BOTTOM
//             };
//            return failedComputationResult;
//     }  
// }

// ComputationResult computeExpression(Expression * expression) {
//     logDebugging(_logger, "Computing expression (ADDR: %lx)...", expression);
//     switch (expression->type) {
//         case CONSTANT_EXPRESSION:
//             // TODO can it be null?
//             logDebugging(_logger, "...of constant type %d", expression->constant->type);
//             return computeConstant(expression->constant);
//         default:
//             logError(_logger, "The specified expression type is not supported: %d", expression->type);
//             ComputationResult failedComputationResult = {
//                 .succeed = false,
//                 .type = CRVT_BOTTOM
//             };
//            return failedComputationResult;
//     }
// }

// ComputationResult computeConstant(Constant * constant) {
//     ComputationResult computationResult;
//     computationResult.succeed = true;
//     logDebugging(_logger, "Computing constant (ADDR: %lx)...", constant);
//     switch (constant->type) {
//         case CT_BOOLEAN:
//             logDebugging(_logger, "...boolean = %d", constant->boolean);
//             computationResult.booleanValue = constant->boolean;
//             computationResult.type = CRVT_BOOLEAN;
//             break;
//         case CT_INTEGER:
//             logDebugging(_logger, "...integer = %d", constant->integer);
//             computationResult.integerValue = constant->integer;
//             computationResult.type = CRVT_INTEGER;
//             break;
//         case CT_STRING:
//             logDebugging(_logger, "...string = \"%s\"", constant->string);
//             // TODO: should we copy or keep the ref?
//             computationResult.stringValue = constant->string;
//             computationResult.type = CRVT_STRING;
//             break;
//         case CT_FLOAT:
//             logDebugging(_logger, "...float: %.3f", constant->decimal);
//             computationResult.floatValue = constant->decimal;
//             computationResult.type = CRVT_FLOAT;
//             break;
//         default:
//             logError(_logger, "The specified constant type is not supported: %d", constant->type);
//             computationResult.succeed = false;
//             computationResult.type = CRVT_BOTTOM;
//             break;
//     }
//     return computationResult;
// }