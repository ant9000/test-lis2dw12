#include <stdio.h>
#include "periph/gpio.h"
#include "lis2dw12.h"

void callback(void *arg) {
  printf("CALLBACK %p\n", arg);
}

int main(void)
{
  //lis2dw12_read_data_polling();
  //lis2dw12_single_tap();

  gpio_init_int(GPIO_PIN(PA, 6), GPIO_IN_PU, GPIO_FALLING, callback, (void *)1);
  gpio_init_int(GPIO_PIN(PA, 7), GPIO_IN_PU, GPIO_FALLING, callback, (void *)2);
  lis2dw12_wake_up();
  return 0;
}
