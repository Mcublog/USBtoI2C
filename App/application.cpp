#include "application.h"

#include <stdbool.h>

#include "cli_handle.h"
#include "config.h"
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
bool host_com_port_open = false;
ring_buffer_t input_ring;

void application(void) {
    ring_buffer_init(&input_ring);
    sys.Initialize(nullptr);
    sys.GetIo()->LedWrite(true);
    CliInit(&sys);
    while (1) {
        CliReadTaskFunc();
    }
}