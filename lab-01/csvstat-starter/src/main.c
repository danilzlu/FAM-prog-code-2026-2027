#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "common.h"

int main(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        cli_print_help();
        return CSVSTAT_EXIT_OK;
    }

    /*
     * TODO:
     *
     * 1. Разобрать командную строку.
     * 2. Выбрать режим работы.
     * 3. Вызвать соответствующий модуль.
     * 4. Преобразовать внутреннюю ошибку в код завершения 0 / 1 / 2.
     *
     * Старайтесь не реализовывать здесь CSV-парсер или статистики:
     * main.c быстро становится неудобным для сопровождения.
     */

    fprintf(stderr,
            "csvstat: starter project; command handling is not implemented yet\n");
    return CSVSTAT_EXIT_BAD_CLI;
}
