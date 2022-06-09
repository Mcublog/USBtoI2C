#ifndef _CLI_HANDLE
#define _CLI_HANDLE

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    const char* cmdTextP;
    const char* cmdDecrP;
    bool (*func)(const char*);
} textToCmd_t;

void CliReadTaskFunc(void);
bool CliParse(const char *msg, const textToCmd_t *table, size_t tableLen);
void CliPutToBuf(const uint8_t data);

#ifdef __cplusplus
}
#endif

#endif /* _CLI_HANDLE */
