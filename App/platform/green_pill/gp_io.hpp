
#ifndef GP_IO_H
#define GP_IO_H

#include "errors.h"
#include "sys_gpio.hpp"

class GpIO : public SysGpio {
   public:
    IOError Initialize(void *pv);
    IOError LedWrite(bool state);
};

#endif  // GP_IO_H
