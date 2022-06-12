/**
 * @file sys_common.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Common utils and functions
 * @version 0.1
 * @date 2022-06-12
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "sys_common.h"
#include "stm32f4xx_hal.h"
#include "io_i2c.h"
#include "i2c.h"
/**
 * @brief Blocking delay function
 *
 * @param ms
 */
void sys_delay(int ms)
{
    HAL_Delay(ms);
}

void sys_init(void)
{
    io_i2c_init((void *)&hi2c1);
}