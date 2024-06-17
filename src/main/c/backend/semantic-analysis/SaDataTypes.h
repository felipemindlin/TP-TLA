#ifndef _SA_DATA_TYPES_H_
#define _SA_DATA_TYPES_H_

#include "../../shared/Type.h"

/** 
 * @brief The data type of a subjacent symbol or expression.
 */
typedef enum {
    SA_INTEGER = 2,
    SA_FLOAT = 3,
    SA_BOOLEAN = 1,
    SA_STRING = 12,
    SA_OBJECT = 10,
    SA_VOID = 11,
    SA_ERROR = -1,
    SA_UNKNOWN = 13,
    /**
     * @brief Upper-most value for numeric type coercion
     */
    SA_META_NUMERIC_CEIL = 3,
    /**
     * @brief Lower-most value for numeric type coercion
     */
    SA_META_NUMERIC_FLOOR = 1,
} SaDataType;

typedef enum {
    SA_INT_INT_OP = SA_INTEGER*2 + SA_INTEGER*3,
    SA_INT_BOOL_OP = SA_INTEGER*2 + SA_BOOLEAN*3,
    SA_INT_FLT_OP = SA_INTEGER*2 + SA_FLOAT*3,
    SA_FLT_FLT_OP = SA_FLOAT*2 + SA_FLOAT*3,
    SA_FLT_BOOL_OP = SA_FLOAT*2 + SA_BOOLEAN*3,
    SA_FLT_INT_OP = SA_FLOAT*2 + SA_INTEGER*3,
    SA_BOOL_BOOL_OP = SA_BOOLEAN*2 + SA_BOOLEAN*3,
    SA_BOOL_INT_OP = SA_BOOLEAN*2 + SA_INTEGER*3,
    SA_BOOL_FLT_OP = SA_BOOLEAN*2 + SA_FLOAT*3,
    SA_STR_STR_OP = SA_STRING*2 + SA_STRING*3,
} SaValidBinaryArithmeticTypes;

/**
 * @brief The result of a semantic check, including data type for successful checks.
 */
typedef struct {
    SaDataType dataType;
    boolean success;
} SaComputationResult;

typedef SaComputationResult (*BinaryArithmeticOperation)(const SaComputationResult left, const SaComputationResult right);
#endif