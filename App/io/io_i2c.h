
#ifndef IO_I2C_H
#define IO_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    IO_I2C_ERR = -1,
    IO_I2C_OK
};

int io_i2c_init(void* pv);

int io_i2c_is_ready(uint8_t adr);
int io_i2c_write(uint8_t adr, uint8_t *data, uint8_t len);
int io_i2c_read(uint8_t adr, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif // HW_I2C_H