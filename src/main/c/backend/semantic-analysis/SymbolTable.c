#include "SymbolTable.h"
#include <stdint.h>
#include <string.h>
#include "../../shared/Logger.h"

#define SEED 0x13572468

static Logger * _logger = NULL;
static hashMapADT table = NULL;

// MurmurOAAT_32_Modified
static uint64_t symbolHashFunction(tAny key) {

    uint64_t h = SEED;
    struct key aux = *(struct key*) key;

    const char * str = aux.varname;
    // One-byte-at-a-time hash based on Murmur's mix
    // Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

static boolean symbolKeyEquals(tAny key1, tAny key2) {
    struct key aux1 = *(struct key *) key1;
    struct key aux2 = *(struct key *) key2;
    return strcmp(aux1.varname, aux2.varname) == 0;
}

void symbolTableInit() {
    if(table != NULL) {
        symbolTableDestroy();
    }
    _logger = createLogger("SymbolTable");
    table = hashMapInit(sizeof(struct key), sizeof(struct value), symbolHashFunction, symbolKeyEquals);
    logInformation(_logger, "Symbol table initialized.");
}

boolean symbolTableFind(tKey * key, tValue * value) {
    return hashMapFind(table, key, value);
}

void symbolTableInsert(struct key * key, struct value * value) {
    hashMapInsertOrUpdate(table, key, value);
}

void symbolTableDestroy() {
    hashMapDestroy(table);
    if (_logger != NULL) { 
        destroyLogger(_logger);
    }
    table = NULL;
}

boolean symbolTableHasUnititializedTypes() {
    logDebugging(_logger, "Checking for uninitialized types in the symbol table...");
    int valuesSize;
    tValue** values = (tValue**) hashMapValues(table, &valuesSize);
    logDebugging(_logger, "%d symbol%s found", valuesSize, valuesSize == 1 ? "" : "s");
    for (int i = 0; i < valuesSize; i++) {
        logDebugging(_logger, "Value in ADDR: %p");
        if ((values[i])->type == SA_UNDECLARED) {
            logWarning(_logger, "   Found symbol with uninitialized type", values[i]->type);
            free(values);
            return true;
        } else {
            logDebugging(_logger, "   Symbol PLACEHOLDER initialized with type %d", values[i]->type);
        }
    }
    logDebugging(_logger, "No symbols with uninitialized types found.");
    free(values);
    return false;
}