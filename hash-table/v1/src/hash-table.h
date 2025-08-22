#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

typedef struct hash_table_bucket hash_table_bucket_t;
typedef struct hash_table hash_table_t;

/**
 * @brief Creates a new hash table instance
 *
 * @param {@code size_t} table_size - The size of the hash table (number of buckets).
 *
 * @return {@code hash_table_t*} - Pointer to the newly created hash table.
 */
hash_table_t * hash_table_new(size_t table_size);

/**
 * @brief Add a new bucket to the hash table.
 *
 * @param {@code hash_table_t*} hash_table - Pointer to the hash table.
 * @param {@code void *} structure - Pointer to the structure for which to create a bucket.
 *
 * @return {@code hash_table_bucket_t*} - Pointer to the newly created bucket, or NULL if the operation failed.
 */
hash_table_bucket_t * hash_table_bucket_new(hash_table_t *hash_table, void * structure);

/**
 * @brief Find a structure in the hash table.
 *
 * @param {@code hash_table_t*} hash_table - Pointer to the hash table.
 * @param {@code void *} structure - Pointer to the structure to find.
 *
 * @return {@code hash_table_bucket_t*} - Pointer to the bucket containing the structure, or NULL if not found.
 */
hash_table_bucket_t * hash_table_find(hash_table_t *hash_table, void * structure);

#endif //DATA_STRUCTURES_HASH_TABLE_H
