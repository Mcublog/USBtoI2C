/**
 * @file io_bus.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief I2C bus base class
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "io_bus.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME i2c
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
/**
 * @brief Initialize I2C bus by default
 *
 */
IOError IOBus::Initialize(void *ctx) {
    UNUSED(ctx);
    LOG_INFO("I2C bus init");
    return IOError::IO_OK;
}

/**
 * @brief Reset bus
 *
 * @return IOError
 */
IOError IOBus::Reset()
{
    LOG_INFO("I2C bus reset");
    return IOError::IO_OK;
}

/**
 * @brief Default I2C device ready
 *
 * @param adr
 * @return I2CBusError
 */
IOError IOBus::IsReady(uint8_t adr) {
    if (adr != kVirtualI2CDeviceAddress)
        return IOError::IO_ERR;
    LOG_INFO("Find I2C virtual: %#x", adr);
    return IOError::IO_OK;
}

/**
 * @brief Write data to I2C bus
 *
 * @param adr Device address as in datasheet no need to shift
 * @param reg Device register number
 * @param regsize Size of the register
 * @param data Pointer to data
 * @param len Size of data
 * @return I2CBusError
 */
IOError IOBus::Write(uint8_t adr, uint8_t reg, uint8_t regsize,
                     uint8_t *data, uint8_t len) {
    LOG_INFO("Write I2C bus: ADR: %#x REG: %#x REGSIZE: %d", adr, reg, regsize);
    LOG_RAW_INFO("DATA[%d]: ", len);
    for (int32_t i = 0; i < len; ++i)
        LOG_RAW_INFO("%#x ", data[i]);
    LOG_RAW_INFO("\n");
    return IOError::IO_OK;
}

/**
 * @brief
 *
 * @param adr Device address as in datasheet no need to shift
 * @param reg Device register number
 * @param regsize Size of the register
 * @param data Pointer to data
 * @param len Size of data
 * @return I2CBusError
 * @return I2CBusError
 */
IOError IOBus::Read(uint8_t adr, uint8_t reg, uint8_t regsize,
                    uint8_t *data, uint8_t len) {
    LOG_INFO("Read I2C bus: ADR: %#x REG: %#x REGSIZE: %d", adr, reg, regsize);
    LOG_RAW_INFO("DATA[%d]: ", len);
    for (int32_t i = 0; i < len; ++i) {
        data[i] = i;
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\n");
    return IOError::IO_OK;
}

/**
 * @brief Convert to string i2c bus error
 *
 * @param err
 * @return const char*
 */
const char *IOBus::ErrStringify(IOError err) {
    if (err == IO_TIMEOUT)
        return "IO_I2C_TIMEOUT";
    else if (err == IO_BUSY)
        return "IO_I2C_BUSY";
    else if (err == IO_ERR)
        return "IO_I2C_ERR";
    return "IO_I2C_OK";
}
