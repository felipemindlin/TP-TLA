#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "HashMap.h"
#include "SaDataTypes.h"



typedef struct key {
    char * varname;
} tKey;

typedef struct value {
    SaDataType type;
} tValue;

void symbolTableInit();

boolean symbolTableFind(struct key * key, struct value * value);

void symbolTableInsert(struct key * key, struct value * value);

/**
 * @brief Check if the symbol table has symbols with uninitialized types.
 * @returns true if there are symbols with uninitialized types, false otherwise.
 */
boolean symbolTableHasUnititializedTypes();

void symbolTableDestroy();
#endif