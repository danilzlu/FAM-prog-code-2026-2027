#ifndef CSVSTAT_OPTIONS_H
#define CSVSTAT_OPTIONS_H

#include <stdbool.h>

/*
 * Общие параметры интерпретации CSV.
 *
 * Это лишь возможное представление. Если вашей архитектуре удобнее хранить
 * параметры иначе, смело меняйте эту структуру.
 */
struct CsvOptions {
    bool scientific;
    bool multiline;
    char delimiter;
};

struct CsvOptions csv_options_default(void);

#endif
