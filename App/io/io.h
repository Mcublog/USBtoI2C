
#ifndef IO_H
#define IO_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void io_led_init(void *pv);
void io_led_write(bool state);

#ifdef __cplusplus
}
#endif

#endif // IO_H