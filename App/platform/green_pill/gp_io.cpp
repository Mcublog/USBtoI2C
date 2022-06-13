/**
 * @file gp_io.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief GPIO instance for Green Pill
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "gp_io.hpp"
#include "gpio.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME gp_io
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
/**
 * @brief
 *
 * @param ctx
 * @return IOError
 */
IOError GpIO::Initialize(void * ctx)
{
    LOG_INFO("Green Pill init");
    return IOError::kIO_OK;
}
/**
 * @brief Write to LED output
 *
 * @param state
 * @return IOError
 */
IOError GpIO::LedWrite(bool state)
{
    GPIO_PinState out = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, out);
    return IOError::kIO_OK;
}