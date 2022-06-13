
#ifndef SYS_GPIO_H
#define SYS_GPIO_H

#include <stdbool.h>

#include "errors.h"

class SysGpio
{
  public:
    virtual IOError Initialize(void *pv);
    virtual IOError LedWrite(bool state);
};

#endif // SYS_GPIO_H