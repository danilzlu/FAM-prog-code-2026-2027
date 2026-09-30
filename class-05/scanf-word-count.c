#include <stdio.h>

int main(void)
{
    char c;
    int words = 0;
    int in_word = 0;

    /*
     * %c читает ровно один следующий символ,
     * включая пробел и '\n'.
     */

    while (scanf("%c", &c) == 1 && c != '\n') {

        if (c == ' ') {
            in_word = 0;
        } else {
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    printf("%d\n", words);

    return 0;
}