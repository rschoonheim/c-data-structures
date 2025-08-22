#include <stdio.h>

#include "src/skip-list.h"

int main() {
    skip_list_t *skipList = skip_list_create();

    int res = skip_list_create_express_layer(
        skipList,
        "layer1",
        (int[]){1, 2, 3, 4, 5}
    );
    printf("Result of creating express layer: %d\n", res);

    int res2 = skip_list_create_express_layer(
        skipList,
        "layer2",
        (int[]){6, 7, 8, 9, 10}
    );
    printf("Result of creating express layer: %d\n", res2);

    skip_list_layer_t * layer1 = skip_list_get_express_layer(skipList, "layer1");
    printf("Address of retrieved layer1: %p\n", (void*)layer1);

    skip_list_layer_t * layer2 = skip_list_get_express_layer(skipList, "layer2");
    printf("Address of retrieved layer2: %p\n", (void*)layer2);
}
