#include "platform.h"

i2c_t bus = I2C_DEV(LIS2DW12_I2C_DEVICE);
#define SENSOR_ADDR LIS2DW12_I2C_ADDRESS

int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len)
{
    i2c_t bus = *(i2c_t *)handle;
    int error = i2c_write_regs(bus, SENSOR_ADDR, reg, (uint8_t*)bufp, len, 0);
/*
    printf("plaform_write %d:0x%02x reg:0x%02x len:%d\n", bus, SENSOR_ADDR, reg, len);
    printf("[ ");
    for(int i=0;i<len;i++){ printf("0x%02x ", bufp[i]); }
    printf("] error:%d\n", error);
*/
    return error;
}

int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len)
{
    i2c_t bus = *(i2c_t *)handle;
    int error = i2c_read_regs(bus, SENSOR_ADDR, reg, bufp, len, 0);
/*
    printf("plaform_read %d:0x%02x reg:0x%02x len:%d\n", bus, SENSOR_ADDR, reg, len);
    printf("[ ");
    for(int i=0;i<len;i++){ printf("0x%02x ", bufp[i]); }
    printf("] error:%d\n", error);
*/
    return error;
}

void platform_delay(uint32_t ms)
{
    ztimer_sleep(ZTIMER_MSEC, ms);
}

void platform_init(void)
{
}
