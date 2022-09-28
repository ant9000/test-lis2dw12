/*
 ******************************************************************************
 * @file    lis2dw12_wake_up.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to detect wake_up from sensor.
 *
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "lis2dw12_reg.h"

#include "platform.h"

/* Private macro -------------------------------------------------------------*/
#define    BOOT_TIME            20 //ms

/* Private variables ---------------------------------------------------------*/
static uint8_t whoamI, rst;

/* Main Example --------------------------------------------------------------*/
void lis2dw12_wake_up(void)
{
  /* Initialize mems driver interface */
  stmdev_ctx_t dev_ctx;
  lis2dw12_reg_t int_route;
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  dev_ctx.handle = &SENSOR_BUS;
  /* Initialize platform specific hardware */
  platform_init();
  /* Wait sensor boot time */
  platform_delay(BOOT_TIME);
  /* Check device ID */
  lis2dw12_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LIS2DW12_ID)
    while (1) {
      /* manage here device not found */
    }

  /* Restore default configuration */
  lis2dw12_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do {
    lis2dw12_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Set full scale */
  lis2dw12_full_scale_set(&dev_ctx, LIS2DW12_2g);
  /* Configure power mode */
  lis2dw12_power_mode_set(&dev_ctx,
                          LIS2DW12_CONT_LOW_PWR_LOW_NOISE_12bit);
  /* Set Output Data Rate */
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_200Hz);
  /* Apply high-pass digital filter on Wake-Up function */
  lis2dw12_filter_path_set(&dev_ctx, LIS2DW12_HIGH_PASS_ON_OUT);
  /* Apply high-pass digital filter on Wake-Up function
   * Duration time is set to zero so Wake-Up interrupt signal
   * is generated for each X,Y,Z filtered data exceeding the
   * configured threshold
   */
  lis2dw12_wkup_dur_set(&dev_ctx, 0);
  /* Set wake-up threshold
   * Set Wake-Up threshold: 1 LSb corresponds to FS_XL/2^6
   */
  lis2dw12_wkup_threshold_set(&dev_ctx, 2);
  /* Enable interrupt generation on Wake-Up INT1 pin */
  lis2dw12_pin_int1_route_get(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
  int_route.ctrl4_int1_pad_ctrl.int1_wu = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
  /* Enable interrupt generation on DRDY INT2 pin */
  lis2dw12_pin_int2_route_get(&dev_ctx, &int_route.ctrl5_int2_pad_ctrl);
  int_route.ctrl5_int2_pad_ctrl.int2_drdy = PROPERTY_ENABLE;
  lis2dw12_pin_int2_route_set(&dev_ctx, &int_route.ctrl5_int2_pad_ctrl);

  /* Wait Events */
  while (1) {
    lis2dw12_all_sources_t all_source;
    /* Check Wake-Up events */
    lis2dw12_all_sources_get(&dev_ctx, &all_source);

    if (all_source.wake_up_src.wu_ia) {
      printf("Wake-Up event on ");

      if (all_source.wake_up_src.x_wu) {
        printf("X");
      }

      if (all_source.wake_up_src.y_wu) {
        printf("Y");
      }

      if (all_source.wake_up_src.z_wu) {
        printf("Z");
      }

      puts(" direction");
    }
  }
}
