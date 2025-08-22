#ifndef DATA_STRUCTURES_HASH_TABLE_H
#define DATA_STRUCTURES_HASH_TABLE_H

#ifndef DATA_STRUCTURES_HASH_TABLE_SIZE
#define DATA_STRUCTURES_HASH_TABLE_SIZE 512
#endif

#define DATA_STRUCTURES_HASH_TABLE_CREATION_ERROR_NONE 0
#define DATA_STRUCTURES_HASH_TABLE_CREATION_ERROR_MEMORY_ALLOCATION 1

typedef struct hash_table_bucket hash_table_bucket_t;
typedef struct hash_table hash_table_t;

/**
 * @brief Creates a new hash table.
 *
 * @param {int} size - size of the hash table. When size is 0 or `null` the
 *                     `DATA_STRUCTURES_HASH_TABLE_SIZE` is used.
 *
 * @return {hash_table_t*} - pointer to the newly created hash table
 */
hash_table_t * hash_table_new(int size);

/**
 * @brief Returns the last error code that occurred during hash table creation.
 *
 * @return {int} - error code (0 if no error occurred)
 */
int hash_table_get_last_creation_error();

/**
 * @brief Create a new hash table bucket.
 *
 * @param {hash_table_t} ht - pointer to the hash table
 * @param {char *} key - key for the bucket
 * @param {void *} value - value for the bucket
 *
 * @return {hash_table_bucket_t*} - pointer to the newly created bucket
 */
hash_table_bucket_t * hash_table_bucket_new(hash_table_t * ht, char * key, void * value);

/**
 * @brief Get a bucket from the hash table by key.
 *
 * @param {hash_table_t} ht  - pointer to the hash table
 * @param {char *} key - key to search for
 *
 * @return {hash_table_bucket_t*} - pointer to the bucket if found, NULL otherwise
 */
hash_table_bucket_t * hash_table_bucket_get(hash_table_t * ht, char * key);

#endif //DATA_STRUCTURES_HASH_TABLE_H
