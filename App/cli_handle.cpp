#include "cli_handle.h"

#include <cstdlib>
#include <cstring>
#include <inttypes.h>

#include "config.h"
#include "main.h"
#include <stdio.h>
#include <inttypes.h>
#include "application.h"

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
static char buff[INPUT_BUFFER_MAX_SIZE] = {0};
static uint8_t pos = 0;
static void ShellHelpCmd(void);

static const textToCmd_t textToCmdList[] =
    {
        {"-h", "Print this help", [](const char *text) -> bool
         { ShellHelpCmd(); return true; }},
        {"-led", "[on/off] led ctrl", [](const char *text) -> bool
         {
             bool result = false;
             if(strstr(text, "on")){
                 LED_set(true);
                 result = true;
             }
             else if(strstr(text, "off")){
                 LED_set(false);
                 result = true;
             }
             return result;
         }}};

void CliReadTaskFunc(void)
{
    int8_t key = buff[pos];
    if (key > 0)
    {
        if (((char)key == '\n') && (pos != 0))
        {
            // new string
            buff[pos] = '\0';
            pos = 0;
            if (!CliParse(buff, textToCmdList, sizeof(textToCmdList) / sizeof(*textToCmdList)))
            {
                LOG_WARNING("Wrong cmd! Help: -h");
            }
        }
        else if (pos < (sizeof(buff) - 1))
        {
            buff[pos++] = key;
        }
        else
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
    LOG_INFO("Shell commands:");

    for (size_t i = 0; i < sizeof(textToCmdList) / sizeof(*textToCmdList); ++i)
    {
        LOG_RAW_INFO("%s %s\n\r", textToCmdList[i].cmdTextP, textToCmdList[i].cmdDecrP);
    }
}

void CliPutToBuf(const uint8_t data)
{
    if (pos >= INPUT_BUFFER_MAX_SIZE)
        return;
    buff[pos++] = data;
}