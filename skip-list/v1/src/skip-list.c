#include "skip-list.h"

#include <stdlib.h>

typedef struct skip_list_layer {
    int *elements;
} skip_list_layer_t;

typedef struct skip_list_express_layers {
    skip_list_layer_t *layers;
} skip_list_express_layers_t;

typedef struct skip_list {
    skip_list_layer_t *base_layer;
    skip_list_express_layers_t *express_layers;
} skip_list_t;

/**
 * @brief Hash function for the express layers hash table. Use jdb2 algorithm.
 *
 * @param {const char*} key - The key to be hashed.
 *
 * @return {int} - The hash value.
 */
static int express_layers_hash_function(const char *key) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % 1024; // Assuming a hash table size of 1024
}

/**
 * @brief Create the base layer of the skip list.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list.
 *
 * @return {void}
 */
static void skip_list_create_base_layer(skip_list_t *sl) {
    sl->base_layer = malloc(sizeof(skip_list_layer_t));
}

/**
 * @brief Create the express layers of the skip list.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list.
 *
 * @return {void}
 */
static void skip_list_create_express_layers(skip_list_t *sl) {
    sl->express_layers = malloc(sizeof(skip_list_express_layers_t));
    sl->express_layers->layers = malloc(sizeof(skip_list_layer_t));
}

/**
 * @brief Free the memory allocated for the skip list.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list to be freed.
 *
 * @return {void}
 */
static void free_skip_list(skip_list_t *sl) {
    if (sl->base_layer) {
        free(sl->base_layer);
    }
    if (sl->express_layers) {
        free(sl->express_layers);
    }

    // Free the skip list itself.
    //
    free(sl);
}

skip_list_t *skip_list_create() {
    skip_list_t *skipList = malloc(sizeof(skip_list_t));

    // Initialize the layers of the skip list.
    //
    skip_list_create_base_layer(skipList);
    skip_list_create_express_layers(skipList);

    return skipList;
}

int skip_list_create_express_layer(
    skip_list_t *sl,
    const char *layer_name,
    int *elements
) {
    if (!sl || !layer_name || !elements) {
        return -1; // Error: Null pointer
    }

    // Create a new express layer.
    //
    skip_list_layer_t *new_layer = malloc(sizeof(skip_list_layer_t));
    new_layer->elements = elements;

    // Insert the new layer into the express layers hash table.
    //
    int hash_index = express_layers_hash_function(layer_name);
    sl->express_layers->layers[hash_index] = *new_layer;

    return 0; // Success
}

skip_list_layer_t *skip_list_get_express_layer(skip_list_t *sl, const char *layer_name) {
    if (!sl || !layer_name) {
        return NULL; // Error: Null pointer
    }

    int hash_index = express_layers_hash_function(layer_name);
    return &sl->express_layers->layers[hash_index];
}

int skip_list_delete(skip_list_t *sl) {
    if (!sl) {
        return -1; // Error: Null pointer
    }

    free_skip_list(sl);

    return 0; // Success
}
