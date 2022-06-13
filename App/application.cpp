#include <stdbool.h>

#include "config.h"
#include "application.h"
#include "cli_handle.h"
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
bool host_com_port_open = false;

void LogLibsPrintCustom(char *buff, int n)
{
    if (!host_com_port_open) {
        return;
    }
    uint32_t attempts = 0;
    while (attempts++ < CDC_TRANSMIT_ATTEMPTS)
    {
        // if (CDC_Transmit_FS((uint8_t *)buff, n) == USBD_OK)
        // {
        //     return;
        // }
        return;
    }
}

void application(void)
{
    sys.Initialize(nullptr);
    sys.GetIo()->LedWrite(true);
    while (1)
    {
        CliReadTaskFunc((void*)&sys);
    }
}