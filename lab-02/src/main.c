#include "avlset.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    AvlSet *set = avlset_create();
    if (!set) {
        fputs("avlset_create failed\n", stderr);
        return EXIT_FAILURE;
    }
    char cmd[32];
    int32_t x, y, result;
    uint32_t k;
    int status = EXIT_SUCCESS;
    while (scanf("%31s", cmd) == 1) {
        if (strcmp(cmd, "INSERT") == 0) {
            if (scanf("%" SCNd32, &x) != 1)
                break;
            avlset_insert(set, x);
        } else if (strcmp(cmd, "DELETE") == 0) {
            if (scanf("%" SCNd32, &x) != 1)
                break;
            avlset_delete(set, x);
        } else if (strcmp(cmd, "EXISTS") == 0) {
            if (scanf("%" SCNd32, &x) != 1)
                break;
            puts(avlset_exists(set, x) ? "true" : "false");
        } else if (strcmp(cmd, "NEXT") == 0 || strcmp(cmd, "PREV") == 0) {
            if (scanf("%" SCNd32, &x) != 1)
                break;
            bool found = strcmp(cmd, "NEXT") == 0 ? avlset_next(set, x, &result)
                                                  : avlset_prev(set, x, &result);
            if (found)
                printf("%" PRId32 "\n", result);
            else
                puts("none");
        } else if (strcmp(cmd, "KTH") == 0) {
            if (scanf("%" SCNu32, &k) != 1)
                break;
            if (avlset_kth(set, k, &result))
                printf("%" PRId32 "\n", result);
            else
                puts("none");
        } else if (strcmp(cmd, "RANK") == 0) {
            if (scanf("%" SCNd32, &x) != 1)
                break;
            printf("%" PRIu32 "\n", avlset_rank(set, x));
        } else if (strcmp(cmd, "RANGE_COUNT") == 0 || strcmp(cmd, "RANGE_SUM") == 0 ||
                   strcmp(cmd, "DELETE_RANGE") == 0) {
            if (scanf("%" SCNd32 " %" SCNd32, &x, &y) != 2)
                break;
            if (strcmp(cmd, "RANGE_COUNT") == 0)
                printf("%" PRIu32 "\n", avlset_range_count(set, x, y));
            else if (strcmp(cmd, "RANGE_SUM") == 0)
                printf("%" PRId64 "\n", avlset_range_sum(set, x, y));
            else
                avlset_delete_range(set, x, y);
        } else {
            fprintf(stderr, "unknown command: %s\n", cmd);
            status = EXIT_FAILURE;
            break;
        }
    }
    avlset_destroy(set);
    return status;
}
