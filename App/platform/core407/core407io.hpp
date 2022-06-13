
#ifndef CORE407IO_H
#define CORE407IO_H

#include "sys_gpio.hpp"
#include "errors.h"

class Core407IO : public SysGpio
{
  public:
    IOError Initialize(void *pv);
    IOError LedWrite(bool state);
};

#endif // CORE407IO_H
