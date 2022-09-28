/*
 ******************************************************************************
 * @file    single_tap.c
 * @author  Sensors Software Solution Team
 * @brief   This file show the simplest way to detect single tap from sensor.
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
void lis2dw12_single_tap(void)
{
  /* Initialize mems driver interface. */
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
  lis2dw12_data_rate_set(&dev_ctx, LIS2DW12_XL_ODR_400Hz);
  /* Enable Tap detection on X, Y, Z */
  lis2dw12_tap_detection_on_z_set(&dev_ctx, PROPERTY_ENABLE);
  lis2dw12_tap_detection_on_y_set(&dev_ctx, PROPERTY_ENABLE);
  lis2dw12_tap_detection_on_x_set(&dev_ctx, PROPERTY_ENABLE);
  /* Set Tap threshold on all axis */
  lis2dw12_tap_threshold_x_set(&dev_ctx, 9);
  lis2dw12_tap_threshold_y_set(&dev_ctx, 9);
  lis2dw12_tap_threshold_z_set(&dev_ctx, 9);
  /* Configure Single Tap parameter */
  lis2dw12_tap_quiet_set(&dev_ctx, 1);
  lis2dw12_tap_shock_set(&dev_ctx, 2);
  /* Enable Single Tap detection only */
  lis2dw12_tap_mode_set(&dev_ctx, LIS2DW12_ONLY_SINGLE);
  /* Enable single tap detection interrupt */
  lis2dw12_pin_int1_route_get(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);
  int_route.ctrl4_int1_pad_ctrl.int1_single_tap = PROPERTY_ENABLE;
  lis2dw12_pin_int1_route_set(&dev_ctx, &int_route.ctrl4_int1_pad_ctrl);

  /* Wait Events */
  while (1) {
    lis2dw12_all_sources_t all_source;
    /* Check Single Tap events */
    lis2dw12_all_sources_get(&dev_ctx, &all_source);

    if (all_source.tap_src.single_tap) {
      printf("Tap Detected: Sign %s", all_source.tap_src.tap_sign ? "positive" : "negative");

      if (all_source.tap_src.x_tap) {
        puts(" on X axis");
      }

      if (all_source.tap_src.y_tap) {
        puts(" on Y axis");
      }

      if (all_source.tap_src.z_tap) {
        puts(" on Z axis");
      }
    }
  }
}
