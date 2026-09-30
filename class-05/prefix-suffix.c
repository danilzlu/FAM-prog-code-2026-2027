#include <stdio.h>

int main(void)
{
    /*
     * Префикс определяет систему счисления.
     */

    int a = 42;          // decimal
    int b = 052;         // octal
    int c = 0x2A;        // hexadecimal
    int d = 0b101010;    // binary, C23

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", d);

    /*
     * Все четыре раза будет напечатано 42.
     */


    /*
     * Суффикс влияет на тип литерала.
     */

    unsigned int x = 42U;
    long y = 42L;
    unsigned long z = 42UL;

    long long p = 42LL;
    unsigned long long q = 42ULL;

    /*
     * Для float обычно используется F.
     * Без F вещественный литерал имеет тип double.
     */

    float f = 3.14F;
    double g = 3.14;

    return 0;
}