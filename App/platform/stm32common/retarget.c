/**
 * @file retarget.c
 * @author Viacheslav (viacheslav@mcublog.ru)
 * @brief Retarget stdio for Core407
 * @version 0.1
 * @date 2022-06-18
 *
 * @copyright Mcublog Copyright (c) 2022
 *
 */
#include "retarget.h"

#include "config.h"

#if STDIO_STREAM == STDIO_RTT
#include "RTT/SEGGER_RTT.h"
#elif STDIO_STREAM == STDIO_USB_CDC
#include "ringbuffer.h"
#include "usbd_cdc_if.h"
//>>---------------------- Exported Variables
extern ring_buffer_t input_ring;
//<<----------------------
#else
#pragma error("Undefined stdio stream")
#endif

/**
 * @brief Read data from RTT or USB VCOM
 *
 * @param handle
 * @param c
 * @param len
 * @return int
 */
int rt_get_char(void *handle, char *c, int len) {
#if STDIO_STREAM == STDIO_USB_CDC
    (void)len;
    (void)handle;
    return ring_buffer_dequeue(&input_ring, c);
#elif STDIO_STREAM == STDIO_RTT
    return SEGGER_RTT_Read((unsigned)handle, c, len);
#endif
}

/**
 * @brief
 *
 * @param handle
 * @param c
 * @param len
 * @return int
 */
int rt_put_char(void *handle, char *c, int len) {
#if STDIO_STREAM == STDIO_USB_CDC
    (void)handle;
    return CDC_Transmit_FS((uint8_t *)c, len);
#elif STDIO_STREAM == STDIO_RTT
    return SEGGER_RTT_Write((unsigned)handle, c, len);
#endif
}