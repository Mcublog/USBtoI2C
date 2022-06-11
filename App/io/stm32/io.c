/**
 * @file io.h
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief IO control
 * @version 0.1
 * @date 2022-06-11
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "io.h"
#include "main.h"

/**
 * @brief Init led pin
 *
 * @param pv
 */
void io_led_init(void *pv)
{

}

/**
 * @brief LED output control
 *
 * @param state
 */
void io_led_write(bool state)
{
    //TODO: need to invert for f401 board
    GPIO_PinState out = state ? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, out);
}