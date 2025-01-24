#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_camera.h"
#include "camera_pins.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "esp_vfs_fat.h"

#define SD_MMC_CMD 15 //Please do not modify it.
#define SD_MMC_CLK 14 //Please do not modify it.
#define SD_MMC_D0  2

#define SDMMC_FREQ_DEFAULT 20000

esp_err_t save_to_sd(void);
void init_camera(void);
void init_sd(void);
camera_fb_t* capture_frame(void);
#endif /* CAMERA_H */
