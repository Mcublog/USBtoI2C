#ifndef CONFIG_H
#define CONFIG_H

#define STDIO_RTT                   0
#define STDIO_USB_CDC               1
#define STDIO_STREAM                STDIO_RTT

#define SYSTEM_LED_BLINK_PEROD      (500) // ms
#define I2C_MAX_DATA_SIZE           (0xff >> 1)

#endif // !CONFIG_Hs