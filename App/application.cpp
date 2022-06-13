#include <stdbool.h>

#include "config.h"
#include "application.h"
#include "cli_handle.h"
#include "log_libs.h"
// #include "usbd_cdc_if.h"
#include "system.hpp"
//#include "core407.hpp"
//#include "green_pill.hpp"

bool host_com_port_open = false;
// Core407 sys = Core407();
//GreenPill sys = GreenPill();
System sys = System();

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