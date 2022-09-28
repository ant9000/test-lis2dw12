#include "stdio_base.h"
#include "ztimer.h"
#include "periph/gpio.h"
#include "periph/i2c.h"

extern i2c_t bus;
#define SENSOR_BUS bus

int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp, uint16_t len);
int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp, uint16_t len);
void platform_delay(uint32_t ms);
void platform_init(void);
