#include <stdio.h>
#include <stdlib.h>

#include "hash-table.h"

typedef struct hash_table_bucket {
    int hash; // Hash value of the bucket.
    void * structure; // Pointer to the structure stored in this bucket.
    struct hash_table_bucket *next; // Pointer to the next bucket in case of collision.
} hash_table_bucket_t;

typedef struct hash_table {
    hash_table_bucket_t **buckets; // Array of pointers to hash table buckets.
    size_t count; // Number of buckets currently in use.
    size_t size; // Size of the hash table (max number of buckets).
} hash_table_t;

/**
 * @brief Generate a hash value using the address of a structure.
 *
 * @param {@code void*} structure - Pointer to the structure for which to generate a hash.
 * @param {@code size_t} hash_size - Size of the hash table.
 *
 * @return {@code int} - The generated hash value. Returns -1 if the structure
 *                       is NULL or if the hash size is invalid.
 */
static int hash_table_generate_hash_from_pointer(void *structure, size_t hash_size) {
    if (!structure || hash_size == 0) {
        return -1; // Invalid parameters
    }
    return ((size_t) structure % hash_size);
}

/**
 * @brief Detect if there is a collision in the hash table at a specific index.
 *
 * @param {@code hash_table_t*} hash_table - Pointer to the hash table.
 * @param {@code int} hash_index - The index in the hash table to check for collisions.
 *
 * @return {@code int} - Returns 1 if a collision is detected, 0 if no collision is detected,
 *                       and -1 if the parameters are invalid.
 */
static int hash_table_detect_collision(hash_table_t *hash_table, int hash_index) {
    if (!hash_table || hash_index < 0 || hash_index >= hash_table->size) {
        return -1; // Invalid parameters
    }

    if (hash_table->buckets[hash_index] != NULL) {
        return 1; // Collision detected
    }
    return 0; // No collision
}


hash_table_t * hash_table_new(size_t table_size) {
    hash_table_t *hash_table = malloc(sizeof(hash_table_t));
    if (!hash_table) {
        fprintf(stderr, "Failed to allocate memory for hash table.\n");
        return NULL; // Memory allocation failed
    }

    hash_table->count = 0;
    hash_table->size = table_size;
    hash_table->buckets = malloc(table_size * sizeof(hash_table_bucket_t *));

    return hash_table;
}

hash_table_bucket_t * hash_table_bucket_new(hash_table_t *hash_table, void * structure) {
    if (!hash_table || !structure) {
        fprintf(stderr, "Invalid hash table or structure pointer.\n");
        return NULL; // Invalid parameters
    }

    int hash_index = hash_table_generate_hash_from_pointer(structure, hash_table->size);
    if (hash_index < 0 || hash_index >= hash_table->size) {
        fprintf(stderr, "Invalid hash index: %d\n", hash_index);
        return NULL; // Invalid hash index
    }

    // Initialize new bucket.
    //
    hash_table_bucket_t * new_bucket = malloc(sizeof(hash_table_bucket_t));
    new_bucket->hash = hash_index;
    new_bucket->structure = structure;

    // Check if there is a collision at the calculated hash index.
    //
    int collision = hash_table_detect_collision(hash_table, hash_index);
    if (collision < 0) {
        fprintf(stderr, "Error detecting collision.\n");
        return NULL; // Error in collision detection
    }

    if (collision == 1) {
        hash_table_bucket_t *bucket = hash_table->buckets[hash_index];
        while (bucket->next != NULL) {
            bucket = bucket->next; // Traverse to the end of the linked list
        }
        printf("Hash index (with collision): %d\n", hash_index);
        bucket->next = new_bucket; // Add the new bucket to the end of the linked
        new_bucket->next = NULL; // Set the next pointer of the new bucket to NULL

        return new_bucket;
    }

    // No collision detected, add the new bucket directly to the hash table.
    //
    printf("Hash index (without collision): %d\n", hash_index);
    new_bucket->next = NULL; // Set the next pointer of the new bucket to NULL
    hash_table->buckets[hash_index] = new_bucket; // Add the new bucket
    hash_table->count++; // Increment the count of buckets in the hash table

    return new_bucket;
}

hash_table_bucket_t * hash_table_find(hash_table_t *hash_table, void * structure) {
    if (!hash_table || !structure) {
        fprintf(stderr, "Invalid hash table or structure pointer.\n");
        return NULL; // Invalid parameters
    }

    int hash_index = hash_table_generate_hash_from_pointer(structure, hash_table->size);
    if (hash_index < 0 || hash_index >= hash_table->size) {
        fprintf(stderr, "Invalid hash index: %d\n", hash_index);
        return NULL; // Invalid hash index
    }

    // Traverse the linked list at the calculated hash index to find the structure.
    //
    hash_table_bucket_t *bucket = hash_table->buckets[hash_index];
    while (bucket != NULL) {
        if (bucket->structure == structure) {
            return bucket; // Structure found in the bucket
        }
        bucket = bucket->next; // Move to the next bucket in case of collision
    }

    return NULL; // Structure not found in the hash table
}