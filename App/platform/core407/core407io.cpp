/**
 * @file core407io.cpp
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief GPIO instance for Core407
 * @version 0.1
 * @date 2022-06-13
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "core407io.hpp"

#include "gpio.h"
//>>---------------------- Log control
#define LOG_MODULE_NAME c407io
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
IOError Core407IO::Initialize(void* ctx) {
    LOG_INFO("Core407IO init");
    return IOError::IO_OK;
}
/**
 * @brief Write to LED output
 *
 * @param state
 * @return IOError
 */
IOError Core407IO::LedWrite(bool state) {
    GPIO_PinState out = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, out);
    return IOError::IO_OK;
}