#include <stdio.h>
#include <stdlib.h>

#include "src/hash-table.h"

typedef struct person {
    char *name;
} person_t;

int main() {

    // Create a new hash table that can hold up to 10 buckets.
    //
    hash_table_t * hash_table = hash_table_new(10);
    printf("Address of hash table: %p\n", (void *)hash_table);

    // Add a person structure to the hash table.
    //
    person_t *person = malloc(sizeof(person_t));
    person->name = "John Doe";
    hash_table_bucket_t * bucket = hash_table_bucket_new(hash_table, person);

    // Add another person structure to the hash table.
    //
    person_t *person2 = malloc(sizeof(person_t));
    person2->name = "Jane Doe";
    hash_table_bucket_t * bucket2 = hash_table_bucket_new(hash_table, person2);

    // Add a third person structure to the hash table this time with
    // a hash collision.
    //
    person_t *person3 = malloc(sizeof(person_t));
    person3->name = "John Smith";
    hash_table_bucket_t * bucket3 = hash_table_bucket_new(hash_table, person3);
    hash_table_bucket_t * bucket4 = hash_table_bucket_new(hash_table, person3);

    // Find the bucket for the third person structure.
    //
    hash_table_bucket_t * found_bucket = hash_table_find(hash_table, person3);
    printf("Found bucket address for person3: %p\n", (void *)found_bucket);
}