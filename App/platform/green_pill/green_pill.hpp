
#ifndef GREEN_PILL_H
#define GREEN_PILL_H

#include "gp_bus.hpp"
#include "gp_io.hpp"
#include "system.hpp"

class GreenPill : public System {
   public:
    SystemError Initialize(void *ctx);
    IOBus *GetI2CBus();
    SysGpio *GetIo();

   private:
    GpBus i2c_bus_;
    GpIO io_;
};

#endif  // CORE407_H