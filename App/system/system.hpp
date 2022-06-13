
#ifndef SYSTEM_H
#define SYSTEM_H

#include "io_bus.hpp"

typedef enum
{
    kTIMEOUT = -3,
    kBUSY = -2,
    kERR = -1,
    kOK
} SystemError;

class System
{
  public:
    virtual SystemError Initialize(void *ctx);
    static void Delay(int ms);
    IOBus *GetI2CBus();
    static const char *ErrStringify(SystemError err);

  private:
    IOBus i2c_bus_;
};

#endif // SYSTEM_H