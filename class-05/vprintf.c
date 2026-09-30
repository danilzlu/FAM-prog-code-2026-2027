#include <stdio.h>

int main(void)
{
    /*
     * ЗНАКОВЫЕ ЦЕЛЫЕ
     */

    int a = -42;
    long b = 1000000L;
    long long c = 1000000000000LL;

    printf("int:       %d\n", a);
    printf("long:      %ld\n", b);
    printf("long long: %lld\n", c);


    /*
     * БЕЗЗНАКОВЫЕ ЦЕЛЫЕ
     */

    unsigned int u = 42U;
    unsigned long ul = 1000000UL;
    unsigned long long ull = 1000000000000ULL;

    printf("unsigned int:       %u\n", u);
    printf("unsigned long:      %lu\n", ul);
    printf("unsigned long long: %llu\n", ull);


    /*
     * ОДНО И ТО ЖЕ unsigned-ЧИСЛО
     * можно вывести в разных системах счисления.
     */

    unsigned int x = 255U;

    printf("decimal:     %u\n", x);   // 255
    printf("octal:       %o\n", x);   // 377
    printf("hex:         %x\n", x);   // ff
    printf("HEX:         %X\n", x);   // FF


    /*
     * ПРЕФИКСЫ ЦЕЛОЧИСЛЕННЫХ ЛИТЕРАЛОВ
     */

    int decimal = 42;        // десятичная запись
    int octal   = 052;       // начинается с 0: восьмеричная
    int hex     = 0x2A;      // 0x: шестнадцатеричная
    int binary  = 0b101010;  // 0b: двоичная, стандарт C23

    printf("%d %d %d %d\n",
           decimal, octal, hex, binary);

    /*
     * Все четыре переменные содержат одно и то же число 42.
     */


    /*
     * СУФФИКСЫ ЦЕЛОЧИСЛЕННЫХ ЛИТЕРАЛОВ
     *
     * U / u   — unsigned
     * L / l   — long
     * LL / ll — long long
     *
     * Их можно комбинировать.
     */

    unsigned int p = 1U;
    unsigned long q = 1UL;
    unsigned long long r = 1ULL;

    /*
     * Для битовых операций особенно важно писать 1U,
     * если работаем с unsigned int.
     */

    unsigned int mask = 1U << 31;

    printf("%u\n", mask);


    /*
     * СИМВОЛЫ
     */

    char ch = 'A';

    printf("character: %c\n", ch);

    /*
     * %c выводит символ,
     * а %d — его числовой код.
     */

    printf("code: %d\n", ch);


    /*
     * СТРОКИ
     */

    char text[] = "hello";

    printf("string: %s\n", text);


    /*
     * ВЕЩЕСТВЕННЫЕ ЧИСЛА
     */

    float f = 3.14F;
    double d = 3.1415926535;

    /*
     * В printf и float, и double выводятся через %f.
     * float при передаче в printf автоматически
     * преобразуется в double.
     */

    printf("float:  %f\n", f);
    printf("double: %f\n", d);

    /*
     * Можно задавать число знаков после точки.
     */

    printf("%.2f\n", d);   // 3.14
    printf("%.5f\n", d);   // 3.14159


    /*
     * НАУЧНАЯ ЗАПИСЬ
     */

    printf("%e\n", d);
    printf("%E\n", d);


    /*
     * АДРЕС
     */

    int value = 10;

    /*
     * %p используется для указателей.
     * Для %p указатель принято приводить к void *.
     */

    printf("address: %p\n", (void *)&value);


    /*
     * sizeof возвращает значение типа size_t.
     * Для size_t используется %zu.
     */

    printf("sizeof(int) = %zu\n", sizeof(int));


    /*
     * Чтобы вывести сам символ %, пишем %%.
     */

    printf("100%%\n");


    return 0;
}