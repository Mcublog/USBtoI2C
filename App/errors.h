
#ifndef ERRORS_H
#define ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    kTIMEOUT = -3,
    kBUSY = -2,
    kERR = -1,
    kOK
} SystemError;

typedef enum
{
    kIO_TIMEOUT = -3,
    kIO_BUSY = -2,
    kIO_ERR = -1,
    kIO_OK
} IOError;

#ifdef __cplusplus
}
#endif

#endif // ERRORS_H