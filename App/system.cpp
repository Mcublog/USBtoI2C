/**
 * @file system.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief System base class
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "system.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME sys
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------

/**
 * @brief System initialization
 *
 * @param ctx
 */
SystemError System::Initialize(void *ctx) {
    UNUSED(ctx);
    LOG_INFO("System init");
    i2c_bus_.Initialize(nullptr);
    io_.Initialize(nullptr);
    return SystemError::kOK;
}

/**
 * @brief Delay in ms
 *
 * @param ms
 */
void System::Delay(int ms) {
    LOG_INFO("waiting: %d ms", ms);
}

/**
 * @brief Get pointer to I2C bus
 *
 * @return IOBus*
 */
IOBus *System::GetI2CBus() {
    return &i2c_bus_;
}

/**
 * @brief Get the IO object
 *
 * @return IO*
 */
SysGpio *System::GetIo() {
    return &io_;
}

/**
 * @brief Convert to string system error codes
 *
 * @param err
 * @return const char*
 */
const char *System::ErrStringify(SystemError err) {
    if (err == kTIMEOUT)
        return "TIMEOUT";
    else if (err == kBUSY)
        return "BUSY";
    else if (err == kERR)
        return "ERR";
    return "OK";
}
