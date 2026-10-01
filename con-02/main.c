#include <stdlib.h>
#include <stdio.h>

int main(void)
{

    long  buffer = 0;

    long  *arr_ptr = malloc(sizeof(long ));
    size_t sz = 0;
    size_t cap = 1;
    
    do {
        scanf("%lld", &buffer);

        if (sz == cap) {
            arr_ptr = realloc(arr_ptr, (cap+1) * sizeof(long ));
            cap++;
        }

        arr_ptr[sz] = buffer;
        sz++;

    } while (buffer != 0);

    printf("%zu\n", sz-1);

    if (sz == 1) {
        free(arr_ptr);
        return 0;
    }

    for (long i = sz-2; i >= 0; i--) {
        printf("%lld ", arr_ptr[i]);
    }

    free(arr_ptr);
    return 0;
}