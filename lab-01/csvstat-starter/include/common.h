#ifndef CSVSTAT_COMMON_H
#define CSVSTAT_COMMON_H

/*
 * Внешние коды завершения программы заданы условием лабораторной.
 * Внутри программы вы можете использовать другие enum/структуры ошибок.
 */
enum CsvstatExitCode {
    CSVSTAT_EXIT_OK = 0,
    CSVSTAT_EXIT_ERROR = 1,
    CSVSTAT_EXIT_BAD_CLI = 2
};

#endif
