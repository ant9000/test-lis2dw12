#include "stdio_base.h"
#include "ztimer.h"
#include "periph/gpio.h"
#include "periph/i2c.h"

#ifndef LIS2DW12_I2C_DEVICE
#define LIS2DW12_I2C_DEVICE I2C_DEV(0)
#endif
#ifndef LIS2DW12_I2C_ADDRESS
#define LIS2DW12_I2C_ADDRESS   0x19
#endif

extern i2c_t bus;
#define SENSOR_BUS bus

int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
void platform_delay(uint32_t ms);
void platform_init(void);
