#ifndef _TEST_H_
#define _TEST_H_

#include "../../shared/Logger.h"
#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Type.h"
#include <limits.h>


typedef enum { CRVT_BOOLEAN, CRVT_INTEGER, CRVT_FLOAT, CRVT_BOTTOM, CRVT_STRING, CRVT_END } ComputationType;

/**
 * The result of a computation. It's considered valid only if "succeed" is
 * true.
 */
typedef struct {
	boolean succeed;
	union {
        int integerValue;
        boolean booleanValue;
        double floatValue;
        char * stringValue;
    };
    ComputationType type;
} ComputationResult;

/**
 * @brief Initialize the module's internal state.
 */
void initializeTestModule();

/**
 * @brief Shutdown the module's internal state.
 */
void shutdownTestModule();

/***
 * @brief Generate a computation result for a program, which might fail.
 * @param program The program token
 * @return A computation result of the program token
 */
ComputationResult computeProgram(Program * program);

/***
 * @brief Generate a computation result for a sentence, which might fail.
 * @param sentence The sentence token
 * @return A computation result of the sentence token
 */
ComputationResult computeSentence(Sentence * sentence);

/**
 * @brief Generate a computation result for an expression, which might fail.
 * @param expression The expression token
 * @return A computation result of the expression token.
 */
ComputationResult computeExpression(Expression * expression);


/***
 * @brief Generate a successful computation result for a constant.
 * @param constant The constant token
 * @return A computation result of the constant token
 */
ComputationResult computeConstant(Constant * constant);

#endif