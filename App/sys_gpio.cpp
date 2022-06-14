/**
 * @file sys_gpio.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Base class for IO
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "sys_gpio.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME io
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
/**
 * @brief Init IO port
 *
 * @param pv
 * @return IOError
 */
IOError SysGpio::Initialize(void *pv) {
    UNUSED(pv);
    LOG_INFO("IO initialized");
    return IOError::kIO_OK;
}

/**
 * @brief Write to LED output
 *
 * @param state
 * @return IOError
 */
IOError SysGpio::LedWrite(bool state) {
    LOG_INFO("LED write: %d", state);
    return IOError::kIO_OK;
}