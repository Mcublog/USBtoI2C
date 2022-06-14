
#ifndef APP_SYSTEM_HPP_
#define APP_SYSTEM_HPP_

#include "errors.h"
#include "io_bus.hpp"
#include "sys_gpio.hpp"

class System {
   public:
    virtual SystemError Initialize(void *ctx);
    virtual IOBus *GetI2CBus();
    virtual SysGpio *GetIo();
    virtual void Delay(int ms);

    static const char *ErrStringify(SystemError err);

   private:
    IOBus i2c_bus_;
    SysGpio io_;
};

#endif  // APP_SYSTEM_HPP_
