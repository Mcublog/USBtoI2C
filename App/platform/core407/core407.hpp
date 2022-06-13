
#ifndef CORE407_H
#define CORE407_H

#include "core407bus.hpp"
// #include "sys_gpio.hpp"
#include "system.hpp"
#include "core407io.hpp"
class Core407 : public System
{
  public:
    SystemError Initialize(void *ctx);
    IOBus *GetI2CBus();
    SysGpio *GetIo();

  private:
    Core407Bus i2c_bus_;
    Core407IO io_;
};

#endif // CORE407_H