/**
 * @file gp_bus.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Implementation of I2c bus for Green Pill platform
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "gp_bus.hpp"

#include "i2c.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME gpbus
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
/**
 * @brief Convert to IOError
 *
 * @param err
 * @return IOError
 */
IOError GpBus::to_iobus_error(int err) {
    if (err == HAL_ERROR)
        return kIO_ERR;
    else if (err == HAL_BUSY)
        return kIO_BUSY;
    else if (err == HAL_TIMEOUT)
        return kIO_TIMEOUT;
    return kIO_OK;
}

/**
 * @brief
 *
 * @param ctx
 * @return IOBusError
 */
IOError GpBus::Initialize(void *ctx) {
    i2c_handle_ = &hi2c1;
    return kIO_OK;
}

/**
 * @brief
 *
 * @param adr
 * @return IOBusError
 */
IOError GpBus::IsReady(uint8_t adr) {
    HAL_StatusTypeDef err =
        HAL_I2C_IsDeviceReady(i2c_handle_, (adr << 1), 1, kI2CTimeoutMs);
    return GpBus::to_iobus_error(err);
}

/**
 * @brief
 *
 * @param adr
 * @param reg
 * @param regsize
 * @param data
 * @param len
 * @return IOBusError
 */
IOError GpBus::Write(uint8_t adr, uint8_t reg, uint8_t regsize,
                     uint8_t *data, uint8_t len) {
    HAL_StatusTypeDef err = HAL_I2C_Mem_Write(
        i2c_handle_, (adr << 1), reg, regsize, data, len, kI2CTimeoutMs);
    return GpBus::to_iobus_error(err);
}

/**
 * @brief
 *
 * @param adr
 * @param reg
 * @param regsize
 * @param data
 * @param len
 * @return IOBusError
 */
IOError GpBus::Read(uint8_t adr, uint8_t reg, uint8_t regsize,
                    uint8_t *data, uint8_t len) {
    HAL_StatusTypeDef err = HAL_I2C_Mem_Read(i2c_handle_, (adr << 1), reg,
                                             regsize, data, len, kI2CTimeoutMs);
    return GpBus::to_iobus_error(err);
}
