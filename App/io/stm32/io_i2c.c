/**
 * @file io_i2c.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief STM32 i2c bus handling
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "io_i2c.h"
#include "i2c.h"
//>>---------------------- Local declaration
static I2C_HandleTypeDef *_i2c_handle = NULL;
//<<----------------------

/**
 * @brief Init I2C peripheral
 *
 * @param pv
 * @return int
 */
int io_i2c_init(void *pv)
{
    _i2c_handle = (I2C_HandleTypeDef *)pv;
    return IO_I2C_OK;
}

/**
 * @brief Try to get ACK from address
 *
 * @param adr
 * @return int
 */
int io_i2c_is_ready(uint8_t adr)
{
    if (HAL_I2C_IsDeviceReady(_i2c_handle, (adr << 1), 1, 1) == HAL_OK)
        return IO_I2C_OK;
    return IO_I2C_ERR;
}

/**
 * @brief write to i2c device
 *
 * @param adr address as in datasheet no need to shift
 * @param data
 * @param len
 * @return int
 */
int io_i2c_write(uint8_t adr, uint8_t *data, uint8_t len)
{
    return IO_I2C_ERR;
}

/**
 * @brief reading data from I2C device
 *
 * @param adr address as in datasheet no need to shift
 * @param data
 * @param len
 * @return int
 */
int io_i2c_read(uint8_t adr, uint8_t *data, uint8_t len)
{
    return IO_I2C_ERR;
}