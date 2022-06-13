#ifndef IO_BUS_HPP
#define IO_BUS_HPP

#include <stdint.h>

typedef enum
{
    kIO_TIMEOUT = -3,
    kIO_BUSY = -2,
    kIO_ERR = -1,
    kIO_OK
} IOBusError;

class IOBus
{
  public:
    virtual IOBusError Initialize(void *ctx);

    virtual IOBusError IsReady(uint8_t adr);
    virtual IOBusError Write(uint8_t adr, uint8_t reg, uint8_t regsize,
                              uint8_t const *data, uint8_t len);
    virtual IOBusError Read(uint8_t adr, uint8_t reg, uint8_t regsize,
                             uint8_t *data, uint8_t len);

    static const char *ErrStringify(IOBusError err);

  private:
     static const uint8_t kVirtualI2CDeviceAddress = 0x0C;

};

#endif // IO_BUS_HPP
