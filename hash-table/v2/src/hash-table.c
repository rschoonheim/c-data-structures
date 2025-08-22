#include <stdio.h>
#include <stdlib.h>

#include "hash-table.h"

#include <string.h>

typedef struct hash_table_bucket {
    char * key; // Key of the bucket
    void * value; // Value associated with the key
} hash_table_bucket_t;

typedef struct hash_table {
    hash_table_bucket_t *buckets; // Pointer to the array of buckets
    size_t capacity; // How many buckets the hash table can hold
    size_t bucket_count; // How many buckets are currently in use
} hash_table_t;

static int hash_table_creation_error = DATA_STRUCTURES_HASH_TABLE_CREATION_ERROR_NONE;

/**
 * @brief Generates a hash value for the given key using the DJB2 algorithm.
 *
 * @param {const char*} key - key to be hashed
 * @param {int} size - size of the hash table
 *
 * @return {int} - hash value
 */
static int hash_table_generate_hash(const char *key, int size) {
    unsigned long hash = 5381;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % size;
}

/**
 * @brief Detects if a collision occurs for the given key in the hash table.
 *
 * @param {hash_table_t} ht - pointer to the hash table
 * @param {const char*} key - key to be checked for collision
 *
 * @return {int} - 1 if collision detected, 0 otherwise
 */
static int hash_table_detect_collision(hash_table_t *ht, const char *key) {
    if (!ht || !key) {
        return 0;
    }

    if (ht->bucket_count == 0) {
        return 0; // No collision possible if table is empty
    }

    int index = hash_table_generate_hash(key, ht->capacity);
    if (ht->buckets[index].key != NULL) {
        // Collision detected
        printf("Collision detected for key '%s' at index %d\n", key, index);
        return 1;
    }

    if (ht->buckets[index].key == NULL) {
        return 0; // No collision if the slot is empty
    }

    if (strcmp(ht->buckets[index].key, key) == 0) {
        // Key already exists
        printf("Key '%s' already exists at index %d\n", key, index);
        return 1;
    }

    return 0;
}

/**
 * @brief Perform quadratic probing to find the next available index in case of a collision.
 *
 * @param {hash_table_t} ht - pointer to the hash table
 * @param {const char*} key - key to be hashed
 * @param {int} attempt - current attempt number (0 for first attempt)
 *
 * @return {int} - new index to try
 */
static int hash_table_quadratic_probing(hash_table_t *ht, const char *key, int attempt) {
    if (!ht || !key) {
        return -1;
    }

    int original_index = hash_table_generate_hash(key, ht->capacity);
    int new_index;
    for (int i = 1; i <= attempt; i++) {
        new_index = (original_index + i * i) % ht->capacity;
        if (ht->buckets[new_index].key == NULL) {
            return new_index; // Found an empty slot
        }
    }

    return -1;
}

hash_table_t * hash_table_new(int size) {
    hash_table_t *ht = malloc(sizeof(hash_table_t));
    if (!ht) {
        hash_table_creation_error = DATA_STRUCTURES_HASH_TABLE_CREATION_ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    if (size <= 0) {
        size = DATA_STRUCTURES_HASH_TABLE_SIZE;
    }
    ht->capacity = size;

    ht->buckets = malloc(sizeof(hash_table_bucket_t) * ht->capacity);
    ht->bucket_count = 0;

    return ht;
}

int hash_table_get_last_creation_error() {
    return hash_table_creation_error;
}

hash_table_bucket_t * hash_table_bucket_new(hash_table_t * ht, char * key, void * value) {
    if (!ht || !key) {
        return NULL;
    }

    if (ht->bucket_count >= ht->capacity) {
        // Hash table is full
        return NULL;
    }

    int index = hash_table_generate_hash(key, ht->capacity);
    printf("Index for key '%s': %d\n", key, index);

    // Handle collision using quadratic probing
    //
    if (hash_table_detect_collision(ht, key)) {
        index = hash_table_quadratic_probing(ht, key, 1); // Placeholder call
    }

    hash_table_bucket_t *bucket = &ht->buckets[index];
    bucket->key = key;
    bucket->value = value;

    ht->bucket_count++;

    return bucket;
}

hash_table_bucket_t * hash_table_bucket_get(hash_table_t * ht, char * key) {
    if (!ht || !key) {
        return NULL;
    }

    int index = hash_table_generate_hash(key, ht->capacity);

    hash_table_bucket_t *bucket = &ht->buckets[index];
    if (bucket->key != NULL && strcmp(bucket->key, key) == 0) {
        return bucket;
    }

    return NULL;
}