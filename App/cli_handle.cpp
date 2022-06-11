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
#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "cli_handle.h"
#include "config.h"
#include "io.h"
#include "io_i2c.h"
#include "main.h"
#include "ses_retarget.h"
//---------------------- Log control -------------------------------------------
#define LOG_MODULE_NAME cli
#if defined(NDEBUG)
#define LOG_MODULE_LEVEL (3)
#else
#define LOG_MODULE_LEVEL (3)
#endif
#include "log_libs.h"
//------------------------------------------------------------------------------
#define INPUT_BUFFER_MAX_SIZE (32)
static std::array<char, INPUT_BUFFER_MAX_SIZE> buff;

static uint8_t pos = 0;
static void ShellHelpCmd(void);
static void Print_HAL_err(HAL_StatusTypeDef err)
{
    switch (err)
    {
    case HAL_OK:
        LOG_RAW_INFO("OK");
        break;
    case HAL_ERROR:
        LOG_RAW_INFO("ERROR");
        break;
    case HAL_BUSY:
        LOG_RAW_INFO("BUSY");
        break;
    case HAL_TIMEOUT:
        LOG_RAW_INFO("TIMEOUT");
        break;
    }
    LOG_RAW_INFO("\r\n");
}

template<typename T, size_t N>
static void Print_hex_array(std::array<T, N> const &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        if(data[i])
            LOG_RAW_INFO("%#x ", data[i]);
        break;
    }
    LOG_RAW_INFO("\r\n");
}

static void Print_hex_array(uint8_t *data, size_t size)
{
    for (int i = 0; i < size; ++i)
    {
        LOG_RAW_INFO("%#x ", data[i]);
    }
    LOG_RAW_INFO("\r\n");
}

static const textToCmd_t textToCmdList[] = {
    {"-h", "Print this help",
     [](const char *text) -> bool {
         ShellHelpCmd();
         return true;
     }},
    {"-led", "[on/off] led ctrl",
     [](const char *text) -> bool {
         bool result = true;
         if (strstr(text, "on"))
             io_led_write(true);
         else if (strstr(text, "off"))
             io_led_write(false);
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
         uint32_t Timeout = 1000;
         HAL_StatusTypeDef err;
         int sscanf_res = sscanf(text, "%hx %hx %hd %hd", &DevAddress,
                                 &MemAddress, &MemAddSize, &Size);
         if (sscanf_res < 4)
         {
             return false;
         }
         DevAddress =
             DevAddress
             << 1; // must be shifted to the left before calling the interface
         err = HAL_I2C_Mem_Read(&I2C_INSTANSE, DevAddress, MemAddress,
                                MemAddSize, data, Size, Timeout);
         if (err == HAL_OK)
         {
             // LOG_HEXDUMP_INFO(data, Size);
             Print_hex_array(data, Size);
         }
         else
         {
             Print_HAL_err(err);
         }
         return true;
     }},
    {"-w",
     "[DevAddress] [MemAddress] [MemAddSize] [Data] write one i2c register",
     [](const char *text) -> bool {
         uint16_t DevAddress;
         uint16_t MemAddress;
         uint16_t MemAddSize;
         uint8_t data[I2C_MAX_DATA_SIZE];
         uint16_t Size;
         uint32_t Timeout = 1000;
         HAL_StatusTypeDef err;
         int sscanf_res = sscanf(text, "%hx %hx %hd %hd", &DevAddress,
                                 &MemAddress, &MemAddSize, data);
         if (sscanf_res < 4)
         {
             return false;
         }
         DevAddress =
             DevAddress
             << 1; // must be shifted to the left before calling the interface
         err = HAL_I2C_Mem_Write(&I2C_INSTANSE, DevAddress, MemAddress,
                                 MemAddSize, data, 1, Timeout);
         Print_HAL_err(err);
         return true;
     }},
    {"-s", "[Trials] [Timeout] scan i2c bus",
     [](const char *text) -> bool {
         uint32_t Trials;
         uint32_t Timeout;
         std::array<uint8_t, I2C_MAX_DATA_SIZE> data;
         if (sscanf(text, "%d %d", &Trials, &Timeout) < 2)
             return false;
         for (uint8_t addr, i = 0; addr <= I2C_MAX_DATA_SIZE; ++addr)
         {
             for (int i = 0; i < Trials; ++i)
             {
                 if (io_i2c_is_ready(addr) == IO_I2C_OK)
                 {
                     data[i++] = addr;
                     break;
                 }
                 // delay (timeout)
             }
         }
         if (data.front())
             Print_hex_array(data);
         else
             LOG_RAW_INFO("not found!\r\n");
         return true;
     }},
};

static const uint32_t CMD_LIST_SIZE = sizeof(textToCmdList) / sizeof(*textToCmdList);

void CliReadTaskFunc(void)
{
    static bool first = true;
    if (first)
    {
        first = false;
        uint32_t Trials = 2;
        uint32_t Timeout = 50;
        std::array<uint8_t, I2C_MAX_DATA_SIZE> data;
        int data_index = 0;
        for (uint16_t addr, i = 0; addr <= I2C_MAX_DATA_SIZE; ++addr)
        {
            if (io_i2c_is_ready(addr) == IO_I2C_OK)
                data[i++] = addr;
        }
        if (data.front())
        {
            for (auto a : data)
            {
                if (a)
                    LOG_RAW_INFO("%#x ", a);
                else
                    break;
            }
            LOG_RAW_INFO("\r\n");
        }
        else
        {
            LOG_RAW_INFO("not found!\r\n");
        }
    }
    int d = scanf("%[^\n]", buff.data());
    if (buff.front() != 0)
    {
        if (!CliParse(buff.data(), textToCmdList, CMD_LIST_SIZE))
        {
            LOG_WARNING("Wrong cmd! Help: -h");
        }
    }
    fflush(stdin);
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
bool CliParse(const char *msgP, const textToCmd_t *table, size_t tableLen)
{
    for (size_t i = 0; i < tableLen; ++i)
    {
        size_t len_cmd = strlen(table[i].cmdTextP);
        if (!strncmp(msgP, table[i].cmdTextP, len_cmd))
        {
            if ((msgP[len_cmd] == ' ') || (strlen(msgP) == len_cmd))
                /*get command from table*/
                if (table[i].func)
                {
                    return table[i].func(&msgP[strlen(table[i].cmdTextP)]);
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
void ShellHelpCmd(void)
{
    LOG_INFO("Shell commands: %d:  %d", sizeof(textToCmdList),
             sizeof(*textToCmdList));

    for (int i = 0; i < CMD_LIST_SIZE; ++i)
    {
        LOG_RAW_INFO("%s %s\n\r", textToCmdList[i].cmdTextP,
                     textToCmdList[i].cmdDecrP);
    }
}

void CliPutToBuf(const uint8_t data)
{
    if (pos >= INPUT_BUFFER_MAX_SIZE)
        return;
    buff[pos++] = data;
}