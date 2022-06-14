/**
 * @file cli_handle.cpp
 * @author Viacheslav (slava.k@ks2corp.com)
 * @brief
 * @version 0.1
 * @date 2022-06-10
 *
 * @copyright KS2 Copyright (c) 2022
 *
 */

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>

#include "config.h"
#include "cli_handle.h"
#include "system.hpp"
//>>---------------------- Log control
#define LOG_MODULE_NAME cli
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//<<----------------------
#define INPUT_BUFFER_MAX_SIZE (32)
static std::array<char, INPUT_BUFFER_MAX_SIZE> buff;

static System *sys = nullptr;
static IOBus *i2c = nullptr;
static SysGpio *io = nullptr;
static uint8_t pos = 0;
static void ShellHelpCmd(void);

template <typename T, size_t N>
static void Print_hex_array(std::array<T, N> const &data) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == 0)
            break;
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\r\n");
}

static void Print_hex_array(uint8_t *data, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\r\n");
}

bool _i2c_write(uint8_t adr, uint8_t regadr, uint8_t regsize, uint8_t *data,
                size_t size) {
    IOError err = i2c->Write(adr, regadr, regsize, data, size);
    LOG_ERROR("%s", IOBus::ErrStringify(err));
    return false;
}

static bool _i2c_read(uint8_t adr, uint8_t regadr, uint8_t regsize,
                      uint8_t *data, size_t size) {
    IOError err = i2c->Read(adr, regadr, regsize, data, size);
    if (err == IOError::kIO_OK)
        Print_hex_array(data, size);
    else
        LOG_ERROR("%s", IOBus::ErrStringify(err));
    return false;
}

static const textToCmd_t textToCmdList[] = {
    {"-h", "Print this help",
     [](const char *text) -> bool {
         UNUSED(text);
         ShellHelpCmd();
         return true;
     }},
    {"-led", "[on/off] led ctrl",
     [](const char *text) -> bool {
         bool result = true;
         if (strstr(text, "on"))
             io->LedWrite(true);
         else if (strstr(text, "off"))
             io->LedWrite(false);
         else
             result = false;
         return result;
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
         _i2c_read(DevAddress, MemAddress, MemAddSize, data, Size);
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
         _i2c_write(DevAddress, MemAddress, MemAddSize, data, Size);
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
                 if (i2c->IsReady(addr) == kIO_OK) {
                     data[i++] = addr;
                     break;
                 }
                 //  sys->Delay(5);
             }
         }
         if (data.front())
             Print_hex_array(data);
         else
             LOG_RAW_INFO("not found!\r\n");
         return true;
     }},
};

static const uint32_t CMD_LIST_SIZE =
    sizeof(textToCmdList) / sizeof(*textToCmdList);

void CliReadTaskFunc(void *context) {
    if (sys == nullptr) {
        sys = reinterpret_cast<System *>(context);
        i2c = sys->GetI2CBus();
        io = sys->GetIo();
    }
    scanf("%[^\n]", buff.data());
    if (!CliParse(buff.data(), textToCmdList, CMD_LIST_SIZE))
        LOG_WARNING("Wrong cmd! Help: -h");
    getchar();  // Clear from buffer last char (flush stdin)
}

/**
 * @brief
 *
 * @param msgP
 * @param table
 * @param tableLen
 * @return true
 * @return false
 */
bool CliParse(const char *msgP, const textToCmd_t *table, size_t tableLen) {
    for (size_t i = 0; i < tableLen; ++i) {
        size_t len_cmd = strlen(table[i].cmdTextP);
        if (!strncmp(msgP, table[i].cmdTextP, len_cmd)) {
            if ((msgP[len_cmd] == ' ') || (strlen(msgP) == len_cmd)) {
                /*get command from table*/
                if (table[i].func) {
                    return table[i].func(&msgP[strlen(table[i].cmdTextP)]);
                }
            }
        }
    }
    /*unknown command*/
    return false;
}

/**
 * @brief
 *
 */
void ShellHelpCmd(void) {
    LOG_INFO("Shell commands: %d:  %d", sizeof(textToCmdList),
             sizeof(*textToCmdList));

    for (uint32_t i = 0; i < CMD_LIST_SIZE; ++i) {
        LOG_RAW_INFO("%s %s\n\r", textToCmdList[i].cmdTextP,
                     textToCmdList[i].cmdDecrP);
    }
}

void CliPutToBuf(const uint8_t data) {
    if (pos >= INPUT_BUFFER_MAX_SIZE)
        return;
    buff[pos++] = data;
}
