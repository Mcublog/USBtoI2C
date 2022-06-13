/**
 * @file green_pill.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Stm32 Green Pill I2C implementation
 *
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "green_pill.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME gp
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
SystemError GreenPill::Initialize(void* ctx)
{
    LOG_INFO("Green Pill init");
    io_.Initialize(nullptr);
    i2c_bus_.Initialize(nullptr);
    return SystemError::kOK;
}

/**
 * @brief Get I2C bus instance pointer
 *
 * @return IOBus*
 */
IOBus *GreenPill::GetI2CBus()
{
    return (IOBus*)&i2c_bus_;
}

/**
 * @brief
 *
 * @return SysGpio*
 */
SysGpio *GreenPill::GetIo()
{
    return (SysGpio*)&io_;
}

