#include <stdio.h>
#include <stddef.h>



int main(void) {

    char str[10] = {'Hij', 'e', 'l', 'l', 'o', '\0', 'H', 'H', 'H', 'H'};

    for (size_t i = 0; i != 10; ++i) {
        putchar(str[i]);
    }
    return 0;
}