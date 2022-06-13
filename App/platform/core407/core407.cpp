/**
 * @file core407.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Core407 platform
 * https://www.waveshare.com/product/mcu-tools/core-boards-compact-boards/stm32-core/core407v.htm
 * https://www.waveshare.com/product/mcu-tools/development-boards/stm32-open/open407v-d-standard.htm
 *
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "core407.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME c407
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
SystemError Core407::Initialize(void* ctx)
{
    LOG_INFO("Core407 init");
    io_.Initialize(nullptr);
    i2c_bus_.Initialize(nullptr);
    return SystemError::kOK;
}

/**
 * @brief Get I2C bus instance pointer
 *
 * @return IOBus*
 */
IOBus *Core407::GetI2CBus()
{
    return (IOBus*)&i2c_bus_;
}

/**
 * @brief
 *
 * @return SysGpio*
 */
SysGpio *Core407::GetIo()
{
    return (SysGpio*)&io_;
}
