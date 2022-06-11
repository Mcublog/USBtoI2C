
#ifndef IO_I2C_H
#define IO_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    IO_I2C_TIMEOUT = -3,
    IO_I2C_BUSY = -2,
    IO_I2C_ERR = -1,
    IO_I2C_OK
}io_i2c_err_t;

io_i2c_err_t io_i2c_init(void* pv);

io_i2c_err_t io_i2c_is_ready(uint8_t adr);
io_i2c_err_t io_i2c_write(uint8_t adr, uint8_t reg, uint8_t regsize,
                          uint8_t *data, uint8_t len);
io_i2c_err_t io_i2c_read(uint8_t adr, uint8_t reg, uint8_t regsize,
                         uint8_t *data, uint8_t len);

inline const char* io_i2c_stringify_err(io_i2c_err_t err)
{
    if (err == IO_I2C_TIMEOUT)
        return "IO_I2C_TIMEOUT";
    else if (err == IO_I2C_BUSY)
        return "IO_I2C_BUSY";
    else if (err == IO_I2C_ERR)
        return "IO_I2C_ERR";
    return "IO_I2C_OK";
}

#ifdef __cplusplus
}
#endif

#endif // HW_I2C_H