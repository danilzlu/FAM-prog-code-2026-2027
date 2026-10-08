#include "options.h"

struct CsvOptions csv_options_default(void)
{
    struct CsvOptions options = {
        .scientific = false,
        .multiline = false,
        .delimiter = ','
    };

    return options;
}
