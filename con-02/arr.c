#include <stdio.h>


int main(void) {

    int array[100] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};

    int *ptr = array + 5;


    printf("%d ", *(ptr-1));
    printf("%d ", *(ptr-2));

    printf("%d ", *(ptr+10));




    return 0;
}