#ifndef IO_BUS_HPP
#define IO_BUS_HPP

#include <stdint.h>

#include "errors.h"

class IOBus
{
  public:
    virtual IOError Initialize(void *ctx);
    virtual IOError Reset();
    virtual IOError IsReady(uint8_t adr);
    virtual IOError Write(uint8_t adr, uint8_t reg, uint8_t regsize,
                              uint8_t *data, uint8_t len);
    virtual IOError Read(uint8_t adr, uint8_t reg, uint8_t regsize,
                             uint8_t *data, uint8_t len);

    static const char *ErrStringify(IOError err);

  protected:
     static const uint32_t kI2CTimeoutMs = 1;

  private:
     static const uint8_t kVirtualI2CDeviceAddress = 0x0C;

};

#endif // IO_BUS_HPP
