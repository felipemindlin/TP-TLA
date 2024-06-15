#ifndef _TEST_H_
#define _TEST_H_

#include "../../shared/Logger.h"
#include "../../frontend/syntactic-analysis/AbstractSyntaxTree.h"
#include "../../shared/Type.h"
#include <limits.h>


typedef enum { CRVT_BOOLEAN, CRVT_INTEGER, CRVT_FLOAT, CRVT_BOTTOM, CRVT_STRING } ComputationType;

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
 * @brief Generate a computation result for a constant.
 * @param constant The constant token
 * @return A successful computation result of the constant token
 */
ComputationResult computeConstant(Constant * constant);

#endif