#ifndef APPLICATION_H
#define APPLICATION_H

#include "ringbuffer.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ring_buffer_t input_ring;

void application(void);

#ifdef __cplusplus
}
#endif
#endif // APPLICATION_H