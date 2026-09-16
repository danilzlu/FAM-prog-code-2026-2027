#include <stdio.h>


int main(void) {

    printf("Table of multiplication\n * ");

    for (int i = 1; i != 10; ++i) {
        printf("| %2d ", i);
    }

    printf("\n------------------------------------------------\n");

    for (int i = 1; i != 10; ++i) {
        printf(" %d ", i);
        for (int j = 1; j != 10; ++j) {
            printf("| %2d ", i * j);
        }
        printf("\n------------------------------------------------\n");
    }

    printf("\n\n\nMilitary time: ");

    int hours = 2;
    int minutes = 59;
    int seconds = 5;

    printf("%.2d:%.2d:%.2d\n\n\n\n", hours, minutes, seconds);
}