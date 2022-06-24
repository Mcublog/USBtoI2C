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

#include "cli_handle.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <array>
#include <cstdlib>
#include <cstring>

#include "config.h"
#include "cobsr.h"
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
//>>---------------------- Local Declaration
#define INPUT_BUFFER_MAX_SIZE (32)
static std::array<char, INPUT_BUFFER_MAX_SIZE> buff;
std::array<char, INPUT_BUFFER_MAX_SIZE> decoded = {0};

static const textToCmd_t *textToCmdList = nullptr;
static uint32_t cmd_list_size = 0;
static uint8_t pos = 0;

static const char kASCII_END_CHAR = '\n';
static const char kBINARY_END_CHAR = '\0';

static char end_char = kASCII_END_CHAR;
//<<----------------------
/**
 * @brief
 *
 */
void CliReadTaskFunc() {
    scanf("%c", &buff[pos]);
    if (buff[pos] == end_char) {
        // TODO: need refactoring code below
        bool binmode = end_char == kBINARY_END_CHAR;
        buff[pos] = '\0';
        if (binmode)
        {
            decoded.fill(0);
            cobsr_decode_result result = cobsr_decode(reinterpret_cast<void *>(decoded.data()), 64, buff.data(), pos);
            buff[result.out_len] = '\0';
            LOG_INFO("result: %d : size: %d", result.status, result.out_len);
            if (result.status != COBSR_DECODE_OK)
            {
                pos = 0;
                return;
            }
        }
        char *cmd = binmode ? decoded.data() : buff.data();
        if (!CliParse(cmd, textToCmdList, cmd_list_size))
            LOG_WARNING("Wrong cmd! Help: -h");
        pos = 0;
    } else {
        pos++;
        if (pos == buff.size())
            pos = 0;
    }
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
 * @brief Init cli interface
 *
 * @param command_list
 * @param list_size
 */
void CliInit(const textToCmd_t *command_list, uint32_t list_size) {
    textToCmdList = command_list;
    cmd_list_size = list_size;
}

/**
 * @brief Set parsing mode (Binary mode On/Off)
 *
 * @param binary_mode
 */
void CliSetParsingMode(const bool binary_mode) {
    end_char = binary_mode ? kBINARY_END_CHAR : kASCII_END_CHAR;
}

/**
 * @brief
 *
 */
void CliHelpCmd() {
    LOG_INFO("Shell commands");

    for (uint32_t i = 0; i < cmd_list_size; ++i) {
        LOG_RAW_INFO("%s %s\n\r", textToCmdList[i].cmdTextP,
                     textToCmdList[i].cmdDecrP);
    }
}