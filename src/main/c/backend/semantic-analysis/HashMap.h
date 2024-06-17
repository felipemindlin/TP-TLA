#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <stdint.h>
#include <stdlib.h>
#include "../../shared/Type.h">
#include <string.h>


typedef void * tAny;
typedef uint64_t (*hashFp)(tAny);
typedef boolean (*keyEqualsFp)(tAny, tAny);
typedef struct hashMapCDT * hashMapADT;

/**
 * @brief Initializes a new hash map.
 * @param keySize The size of the key in bytes.
 * @param valueSize The size of the value in bytes.
 * @param prehash The prehash function to be used.
 * @param keyEquals The function used for key comparison.
 * @return A hash map with the given parameters.
 */
hashMapADT hashMapInit(uint64_t keySize, uint64_t valueSize, hashFp prehash, keyEqualsFp keyEquals);

/**
 * @brief Insert a key-value pair in the hash map, or update the value if the key is already present.
 * @param hm The hash map to be updated.
 * @param key The key to be inserted or updated.
 * @param value The value to be inserted or updated.
 */
void hashMapInsertOrUpdate(hashMapADT hm, tAny key, tAny value);

/**
 * @brief Remove a key-value pair from the hash map.
 * @param hm The hash map to be updated.
 * @param key The key of the pair to be removed.
 * @return True if the key was removed, false otherwise.
 */
boolean hashMapRemove(hashMapADT hm, tAny key);

/**
 * @brief Find the value for a given key in the hash map
 * @param hm The hash map to be searched.
 * @param key The hashing key.
 * @param value The address where the value will be stored if found.
 * @return True if the value was found, false otherwise.
 */
boolean hashMapFind(hashMapADT hm, tAny key, tAny value);

/**
 * @brief Get the used space of the hash map.
 * @param hm The hash map.
 * @return The size of the hash map.
 */
uint64_t hashMapSize(hashMapADT hm);

/**
 * @brief Destroy an initialized hash map.
 * @param hm The hash map to be freed.
 */
void hashMapDestroy(hashMapADT hm);

#endif