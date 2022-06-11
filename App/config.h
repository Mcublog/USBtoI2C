#ifndef CONFIG_H
#define CONFIG_H

#define LOG_LIBS_PRINT_CUSTOM
#define LOG_LIBS_PRINT_UART
#define LOG_LIBS_USE_PRINTF 2

#define SYSTEM_LED_BLINK_PEROD      500 // ms
#define READ_COMMAND_BUF_LEN        200
#define CDC_TRANSMIT_ATTEMPTS       1000
#define LOG_LIBS_PRINT_LEN          1000
#define LOG_LIBS_TX_BUFFER_SIZE     0x400
#define LOG_LIBS_RX_BUFFER_SIZE     0x400

#define I2C_MAX_DATA_SIZE           (0xff >> 1)

#endif // !CONFIG_Hs