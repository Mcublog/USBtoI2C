
#ifndef ERRORS_H
#define ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    TIMEOUT = -3,
    BUSY = -2,
    ERR = -1,
    OK
} SystemError;

typedef enum
{
    IO_TIMEOUT = -3,
    IO_BUSY = -2,
    IO_ERR = -1,
    IO_OK
} IOError;

#define UNUSED(X) (void)X

#ifdef __cplusplus
}
#endif

#endif // ERRORS_H