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

static const uint32_t _i2c_timeout_ms = 10;
io_i2c_err_t _to_i2c_err(int err);
//<<----------------------

//>>---------------------- Local defenition
io_i2c_err_t _to_i2c_err(int err)
{
    if (err == HAL_ERROR)
        return IO_I2C_ERR;
    else if (err == HAL_BUSY)
        return IO_I2C_BUSY;
    else if (err == HAL_TIMEOUT)
        return IO_I2C_TIMEOUT;
    return IO_I2C_OK;
}
//<<----------------------

/**
 * @brief Init I2C peripheral
 *
 * @param pv
 * @return io_i2c_err_t
 */
io_i2c_err_t io_i2c_init(void *pv)
{
    _i2c_handle = (I2C_HandleTypeDef *)pv;
    return IO_I2C_OK;
}

/**
 * @brief Try to get ACK from address
 *
 * @param adr
 * @return io_i2c_err_t
 */
io_i2c_err_t io_i2c_is_ready(uint8_t adr)
{
    if (HAL_I2C_IsDeviceReady(_i2c_handle, (adr << 1), 1, _i2c_timeout_ms) == HAL_OK)
        return IO_I2C_OK;
    return IO_I2C_ERR;
}

/**
 * @brief write to i2c device
 *
 * @param adr address as in datasheet no need to shift
 * @param data
 * @param len
 * @return io_i2c_err_t
 */
io_i2c_err_t io_i2c_write(uint8_t adr, uint8_t reg, uint8_t regsize,
                          uint8_t *data, uint8_t len)
{
    HAL_StatusTypeDef err = HAL_I2C_Mem_Write(
        _i2c_handle, (adr << 1), reg, regsize, data, len, _i2c_timeout_ms);
    return _to_i2c_err(err);
}

/**
 * @brief Reading data from I2C device
 *
 * @param adr Device address as in datasheet no need to shift
 * @param reg Device register number
 * @param regsize Size of the register
 * @param data Pointer to data
 * @param len Size of data
 * @return io_i2c_err_t
 */
io_i2c_err_t io_i2c_read(uint8_t adr, uint8_t reg, uint8_t regsize,
                         uint8_t *data, uint8_t len)
{
    HAL_StatusTypeDef err = HAL_I2C_Mem_Read(
        _i2c_handle, (adr << 1), reg, regsize, data, len, _i2c_timeout_ms);
    return _to_i2c_err(err);
}