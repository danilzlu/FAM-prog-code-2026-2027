#include <stdio.h>

int main(void)
{
    int c;
    int words = 0;

    /*
     * in_word == 0:
     * сейчас находимся между словами.
     *
     * in_word == 1:
     * сейчас читаем слово.
     */
    int in_word = 0;

    while ((c = getchar()) != '\n' && c != EOF) {

        if (c == ' ') {
            /*
             * Пробел означает, что слово закончилось.
             */
            in_word = 0;
        } else {
            /*
             * Если раньше мы были не внутри слова,
             * а теперь встретили непробельный символ,
             * значит началось новое слово.
             */
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }

    printf("%d\n", words);

    return 0;
}