
#ifndef CORE407_BUS_H
#define CORE407_BUS_H

#include "i2c.h"
#include "io_bus.hpp"

class Core407Bus : public IOBus {
   public:
    IOError Initialize(void *ctx);

    IOError IsReady(uint8_t adr);
    IOError Write(uint8_t adr, uint8_t reg, uint8_t regsize,
                  uint8_t *data, uint8_t len);
    IOError Read(uint8_t adr, uint8_t reg, uint8_t regsize, uint8_t *data,
                 uint8_t len);

   private:
    I2C_HandleTypeDef *i2c_handle_;

    static IOError to_iobus_error(int err);
};

#endif  // CORE407_BUS_H