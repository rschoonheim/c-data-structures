#include <stdio.h>
#include <stdlib.h>

#include "src/hash-table.h"

typedef struct person {
    char * name;
} person_t;

int main() {

    hash_table_t * hash_table = hash_table_new(0);
    printf("Hash table pointer: %p\n", (void *)hash_table);

    person_t * person = malloc(sizeof(person_t));
    person->name = "John Doe";
    hash_table_bucket_t * bucket = hash_table_bucket_new(hash_table, "person_1", person);
    printf("Bucket pointer: %p\n", (void *)bucket);

    person_t * person_2 = malloc(sizeof(person_t));
    person_2->name = "Jane Doe";
    hash_table_bucket_t * bucket_2 = hash_table_bucket_new(hash_table, "person_2", person_2);
    printf("Bucket 2 pointer: %p\n", (void *)bucket_2);


}