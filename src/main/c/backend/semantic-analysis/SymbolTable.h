#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "HashMap.h"
#include "SaDataTypes.h"


struct key {
    char * varname;
};

struct value {
    SaDataType type;
};

void symbolTableInit();

int symbolTableFind(struct key * key, struct value * value);

void symbolTableInsert(struct key * key, struct value * value);

void symbolTableDestroy();
#endif