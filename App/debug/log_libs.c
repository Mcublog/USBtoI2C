#include "log_libs.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_DEBUG_BUFF_SIZE (128)

static char _buffer[MAX_DEBUG_BUFF_SIZE];  // PLACE_IN_COMMON_RAM;

void log_printf(const char *prefix, const char *module, const char *sFormat, ...) {
    printf("%s> %s: ", prefix, module);
    va_list ParamList;
    va_start(ParamList, sFormat);
    vsnprintf(_buffer, sizeof(_buffer), sFormat, ParamList);
    va_end(ParamList);
    printf(_buffer);
    printf("\n");
}
