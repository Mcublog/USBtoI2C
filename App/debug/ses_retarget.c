/**
 * @file stdin_retarget.c
 * @author Viacheslav (slava.k@ks2corp.com)
 * @brief
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright KS2 Copyright (c) 2022
 *
 */
#include <stdio.h>

#include "RTT/SEGGER_RTT.h"
#include "__SEGGER_RTL_Int.h"
#include "ses_retarget.h"
//>>---------------------- Local declaration
struct __SEGGER_RTL_FILE_impl
{
    int handle;
};

// static FILE __SEGGER_RTL_stdin_file = {0};  // stdin reads from RTT buffer #0
// static FILE __SEGGER_RTL_stdin_file = {0};  // stdin reads from RTT buffer #0
// static FILE __SEGGER_RTL_stdout_file = {0}; // stdout writes to RTT buffer #0
// static FILE __SEGGER_RTL_stderr_file = {0}; // stdout writes to RTT buffer #0
static int __SEGGER_RTL_stdin_ungot = EOF;
//<<----------------------

//>>---------------------- Public data
// FILE *stdin = &__SEGGER_RTL_stdin_file;
// FILE *stdin = &__SEGGER_RTL_stdin_file;
// FILE *stdout = &__SEGGER_RTL_stdout_file;
// FILE *stderr = &__SEGGER_RTL_stderr_file;
//<<----------------------

/**
 * @brief Get file status
 *
 * Additional information
 * Low-overhead test to determine if stream is valid. If stream
 * is a valid pointer and the stream is open, this function must
 * succeed. If stream is a valid pointer and the stream is closed,
 * this function must fail.
 *
 * The implementation may optionally determine whether stream is
 * a valid pointer: this may not always be possible and is not
 * required, but may assist debugging when clients provide wild
 * pointers.
 * @param stream Pointer to file
 * @return int
 * < 0 - Failure, stream is not a valid file
 * >= 0 - Success, stream is a valid file
 */
int __SEGGER_RTL_X_file_stat(__SEGGER_RTL_FILE *stream)
{
    if (stream == stdin || stream == stdout || stream == stderr)
    {
        return 0;
    }
    else
    {
        return EOF;
    }
}

/**
 * @brief Get stream buffer size.
 *
 * Additional information
 * Returns the number of characters to use for buffered I/O on
 * the file stream. The I/O buffer is allocated on the stack
 * for the duration of the I/O call, therefore this value should
 * not be set arbitrarily large.
 * For unbuffered I/O, return 1.
 * @param stream Pointer to file.
 * @return int
 * Nonzero number of characters to use for buffered I/O; for
 * unbuffered I/O, return 1.
 */
int __SEGGER_RTL_X_file_bufsize(__SEGGER_RTL_FILE *stream)
{
    return 64;
}

/**
 * @brief Get character from standard input.
 * Additional information
 * This function never fails to deliver a character.
 * @return char Character received.
 *
 */
static char __SEGGER_RTL_stdin_getc(void)
{
    int r;
    char c;
    //
    if (__SEGGER_RTL_stdin_ungot != EOF)
    {
        c = __SEGGER_RTL_stdin_ungot;
        __SEGGER_RTL_stdin_ungot = EOF;
    }
    do
    {
        r = SEGGER_RTT_Read(stdin->handle, &c, 1);
    } while (r == 0);
    //
    return c;
}

/**
 * @brief Read data from file.
 *
 * Additional information
 * Reading from any stream other than stdin results in an error.
 *
 * @param stream Pointer to file to read from
 * @param s Pointer to object that receives the input
 * @param len Number of characters to read from file
 * @return int
 * >= 0 - Success.
 * < 0 - Failure.
 */
int __SEGGER_RTL_X_file_read(__SEGGER_RTL_FILE *stream, char *s, unsigned len)
{
    int c;
    //
    if (stream == stdin)
    {
        c = 0;
        while (len > 0)
        {
            *s++ = __SEGGER_RTL_stdin_getc();
            --len;
        }
    }
    else
    {
        c = EOF;
    }
    //
    return c;
}


/**
 * @brief  Flush unwritten data to file.
 *
 * @param stream Pointer to file
 * @return int
 * < 0 - Failure, file cannot be flushed or was not successfully flushed.
 * == 0 - Success, unwritten data is flushed.
 */
int __SEGGER_RTL_X_file_flush(__SEGGER_RTL_FILE *stream)
{
    return 0;
}

int __SEGGER_RTL_X_file_write(__SEGGER_RTL_FILE *stream, const char *s, unsigned len) {
return SEGGER_RTT_Write(stream->handle, s, len);
}

int __SEGGER_RTL_X_file_unget(__SEGGER_RTL_FILE *stream, int c)
{
    if (stream == stdin)
    {
        if (c != EOF && __SEGGER_RTL_stdin_ungot == EOF)
        {
            __SEGGER_RTL_stdin_ungot = c;
        }
        else
        {
            c = EOF;
        }
    }
    else
    {
        c = EOF;
    }
    //
    return c;
}
