
#ifndef CORE407IO_H
#define CORE407IO_H

#include "errors.h"
#include "sys_gpio.hpp"

class Core407IO : public SysGpio {
   public:
    IOError Initialize(void *pv);
    IOError LedWrite(bool state);
};

#endif  // CORE407IO_H
