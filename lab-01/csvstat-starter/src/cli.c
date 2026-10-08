#include <stdio.h>

#include "cli.h"

void cli_print_help(void)
{
    puts("csvstat --help");
    puts("csvstat schema <csv-file> [options]");
    puts("csvstat stats <csv-file> [options]");
    puts("csvstat report <csv-file> <output-file> [options]");
    puts("");
    puts("Level 10:");
    puts("csvstat bin-import <csv-file> <binary-file> [options]");
    puts("csvstat bin-schema <binary-file>");
    puts("csvstat bin-stats <binary-file>");
    puts("csvstat bin-report <binary-file> <output-file>");
}
