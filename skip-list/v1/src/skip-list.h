#ifndef DATA_STRUCTURES_SKIP_LIST_H
#define DATA_STRUCTURES_SKIP_LIST_H

typedef struct skip_list_layer skip_list_layer_t;
typedef struct skip_list skip_list_t;

/**
 * @brief Create a new skip list.
 *
 * @return {skip_list_t*} - A pointer to a newly created skip list.
 */
skip_list_t *skip_list_create();

/**
 * @brief Create a express layer in the skip list.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list.
 * @param {const char*} layer_name - The name of the express layer to be created.
 * @param {int * elements} elements - An array of integers to be added to the express layer.
 *
 * @return {int} - Status code (0 for success, non-zero for failure).
 */
int skip_list_create_express_layer(
    skip_list_t *sl,
    const char *layer_name,
    int *elements
);

/**
 * @brief Get a express layer from the skip list by its name.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list.
 * @param {const char*} layer_name - The name of the express layer to be
 *
 * @return {skip_list_layer_t*} - A pointer to the express layer, or NULL if not found.
 */
skip_list_layer_t *skip_list_get_express_layer(
    skip_list_t *sl,
    const char *layer_name
);

/**
 * @brief Delete a skip list.
 *
 * @param {skip_list_t*} sl - A pointer to the skip list to be deleted.
 *
 * @return {int} - Status code (0 for success, non-zero for failure).
 */
int skip_list_delete(skip_list_t *sl);

#endif //DATA_STRUCTURES_SKIP_LIST_H
