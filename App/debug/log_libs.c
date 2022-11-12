#include "log_libs.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

void log_printf(const char *prefix, const char *module, const char *sFormat, ...) {
    printf("%s> %s: ", prefix, module);
    va_list ParamList;
    va_start(ParamList, sFormat);
    vprintf(sFormat, ParamList);
    va_end(ParamList);
    printf("\n");
}
