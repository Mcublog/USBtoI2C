#include "application.h"

#include <stdbool.h>
#include <string.h>

#include <array>

#include "cli_handle.h"
#include "config.h"
#include "version.h"
#include "errors.h"
// #include "usbd_cdc_if.h"
#if defined(CORE407)
#include "core407.hpp"
Core407 sys = Core407();
#elif defined(GREEN_PILL)
#include "green_pill.hpp"
GreenPill sys = GreenPill();
#else
#include "system.hpp"
System sys = System();
#endif
//>>---------------------- Log control
#define LOG_MODULE_NAME app
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
//>>---------------------- Global variables
ring_buffer_t g_input_ring;
//<<----------------------
//>>---------------------- Local declaration
template <typename T, size_t N>
static void PrintHexArray(std::array<T, N> const &data);
static bool WriteI2C(uint8_t adr, uint8_t regadr, uint8_t regsize, uint8_t *data,
                     size_t size);
static bool ReadI2C(uint8_t adr, uint8_t regadr, uint8_t regsize,
                    uint8_t *data, size_t size);

static const textToCmd_t textToCmdList[] = {
    {"-h", "Print this help",
     [](const char *text) -> bool {
         UNUSED(text);
         CliHelpCmd();
         return true;
     }},
    {"-led", "[on/off] led ctrl",
     [](const char *text) -> bool {
         if (!(strstr(text, "on") || strstr(text, "off")))
             return false;
         bool state = strstr(text, "on") ? true : false;
         sys.GetIo()->LedWrite(state);
         return true;
     }},
    {"-r", "[DevAddress] [MemAddress] [MemAddSize] [Size] read i2c registers",
     [](const char *text) -> bool {
         uint16_t DevAddress;
         uint16_t MemAddress;
         uint16_t MemAddSize;
         uint8_t data[I2C_MAX_DATA_SIZE];
         uint16_t Size;
         if (sscanf(text, "%hx %hx %hd %hd", &DevAddress, &MemAddress,
                    &MemAddSize, &Size) < 4) {
             return false;
         }
         ReadI2C(DevAddress, MemAddress, MemAddSize, data, Size);
         return true;
     }},
    {"-w",
     "[DevAddress] [MemAddress] [MemAddSize] [DataSize] [Data] write one i2c "
     "register",
     [](const char *text) -> bool {
         uint16_t DevAddress;
         uint16_t MemAddress;
         uint16_t MemAddSize;
         uint8_t data[I2C_MAX_DATA_SIZE] = {0};
         uint16_t Size;
         int sscanf_res = sscanf(text, "%hx %hx %hd %hd %hd", &DevAddress,
                                 &MemAddress, &MemAddSize, &Size, data);
         if (sscanf_res < 5) {
             return false;
         }
         WriteI2C(DevAddress, MemAddress, MemAddSize, data, Size);
         return true;
     }},
    {"-s", "[Trials] [Timeout] scan i2c bus",
     [](const char *text) -> bool {
         uint32_t Trials;
         uint32_t Timeout;
         std::array<uint8_t, I2C_MAX_DATA_SIZE> data = {0};
         if (sscanf(text, "%d %d", &Trials, &Timeout) < 2)
             return false;
         for (uint8_t addr = 0, i = 0; addr <= I2C_MAX_DATA_SIZE; ++addr) {
             for (uint32_t j = 0; j < Trials; ++j) {
                 if (sys.GetI2CBus()->IsReady(addr) == IO_OK) {
                     data[i++] = addr;
                     break;
                 }
                 //  sys->Delay(5);
             }
         }
         if (data.front())
             PrintHexArray(data);
         else
             LOG_RAW_INFO("not found!\r\n");
         return true;
     }},
    {"-b", "switch to binary mode",
     [](const char *text) -> bool {
         (void)text;
         CliSetParsingMode(true);
         LOG_RAW_INFO("binary mode is ON\r\n");
         return true;
     }},
    {"-v", "get version",
     [](const char *text) -> bool {
         (void)text;
         LOG_RAW_INFO("%s\r\n", FW_VERSION);
         return true;
     }},
};

static const uint32_t CMD_LIST_SIZE =  sizeof(textToCmdList) / sizeof(*textToCmdList);
//<<----------------------
/**
 * @brief Print hex array
 *
 * @param data
 */
template <typename T, size_t N>
void PrintHexArray(std::array<T, N> const &data) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == 0)
            break;
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\r\n");
}

/**
 * @brief Overload print array
 *
 * @param data
 * @param size
 */
void PrintHexArray(uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\r\n");
}

/**
 * @brief Write to I2C bus
 *
 * @param adr
 * @param regadr
 * @param regsize
 * @param data
 * @param size
 * @return true
 * @return false
 */
bool WriteI2C(uint8_t adr, uint8_t regadr, uint8_t regsize, uint8_t *data,
              size_t size) {
    IOError err = sys.GetI2CBus()->Write(adr, regadr, regsize, data, size);
    LOG_ERROR("%s", IOBus::ErrStringify(err));
    return false;
}

/**
 * @brief Read from I2C bus
 *
 * @param adr
 * @param regadr
 * @param regsize
 * @param data
 * @param size
 * @return true
 * @return false
 */
bool ReadI2C(uint8_t adr, uint8_t regadr, uint8_t regsize,
             uint8_t *data, size_t size) {
    IOError err = sys.GetI2CBus()->Read(adr, regadr, regsize, data, size);
    if (err == IOError::IO_OK)
        PrintHexArray(data, size);
    else
        LOG_ERROR("%s", IOBus::ErrStringify(err));
    return false;
}

/**
 * @brief
 *
 */
void application(void) {
    LOG_INFO("Version: %s", FW_VERSION);
    ring_buffer_init(&g_input_ring);
    sys.Initialize(nullptr);
    sys.GetIo()->LedWrite(true);
    CliInit(textToCmdList, CMD_LIST_SIZE);
    while (1) {
        CliReadTaskFunc();
    }
}