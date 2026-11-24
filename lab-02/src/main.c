#include "avlset.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    AvlSet *set = avlset_create();

    if (!set) {
        fputs("avlset_create failed\n", stderr);
        return EXIT_FAILURE;
    }
    char cmd[32];

    int status = EXIT_SUCCESS;
    while (scanf("%31s", cmd) == 1) {
        /* TODO: написать обработку команд*/
    }
    avlset_destroy(set);
    return status;
}
