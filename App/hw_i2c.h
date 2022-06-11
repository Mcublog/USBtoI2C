
#ifndef HW_I2C_H
#define HW_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    IC_ERR = -1,
    IC_OK
};

int i2c_init(void* pv);

int i2c_is_ready(uint8_t adr);
int i2c_write(uint8_t adr, uint8_t *data, uint8_t len);
int i2c_read(uint8_t adr, uint8_t *data, uint8_t len);

#ifdef __cplusplus
}
#endif

#endif // HW_I2C_H