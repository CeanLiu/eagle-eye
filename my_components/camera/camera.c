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

#include "camera.h"

static const char *CAM_TAG = "camera";
static const char *TAG = "SD_CARD";

static camera_config_t cam_config = {
    .pin_d0 = Y2_GPIO_NUM,
    .pin_d1 = Y3_GPIO_NUM,
    .pin_d2 = Y4_GPIO_NUM,
    .pin_d3 = Y5_GPIO_NUM,
    .pin_d4 = Y6_GPIO_NUM,
    .pin_d5 = Y7_GPIO_NUM,
    .pin_d6 = Y8_GPIO_NUM,
    .pin_d7 = Y9_GPIO_NUM,
    .pin_xclk = XCLK_GPIO_NUM,
    .pin_pclk = PCLK_GPIO_NUM,
    .pin_vsync = VSYNC_GPIO_NUM,
    .pin_href = HREF_GPIO_NUM,
    .pin_sccb_sda = SIOD_GPIO_NUM,
    .pin_sccb_scl = SIOC_GPIO_NUM,
    .pin_pwdn = PWDN_GPIO_NUM,
    .pin_reset = RESET_GPIO_NUM,

    .xclk_freq_hz = 20000000,
    .ledc_channel = LEDC_CHANNEL_0,
    .ledc_timer = LEDC_TIMER_0,

    .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_SVGA, // Change to desired resolution

    .jpeg_quality = 12,       // Adjust quality (lower = better quality)
    .fb_count = 2,
    .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY
};

esp_err_t save_to_sd(void)
{
  	camera_fb_t *pic = esp_camera_fb_get();
    ESP_LOGI(CAM_TAG, "Picture taken! Its size was: %zu bytes", pic->len);
    ESP_LOGI(TAG, "Opening file /sdcard/example.jpg");
    FILE *f = fopen("/sdcard/example.jpg", "w");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
        return ESP_FAIL;
    }
    fwrite(pic->buf, 1, pic->len, f);
    fclose(f);
    ESP_LOGI(TAG, "File written");

    return ESP_OK;
}

void init_camera(void) {
    // Initialize the camera
    esp_err_t err = esp_camera_init(&cam_config);
    if (err != ESP_OK) {
        ESP_LOGE(CAM_TAG,"Camera init failed with error 0x%d",err);
    }
}

camera_fb_t* capture_frame(void) {
    camera_fb_t *fb = esp_camera_fb_get();  // Capture a frame from the camera
    if (!fb) {
        ESP_LOGE(TAG, "Camera capture failed");
        return NULL;
    }
    return fb;
}



void init_sd(void) {
    const char base_path []= "/sdcard";

	sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1;
    slot_config.clk = SD_MMC_CLK;
    slot_config.cmd = SD_MMC_CMD;
    slot_config.d0 = SD_MMC_D0;

    sdmmc_host_t host = SDMMC_HOST_DEFAULT();

    esp_vfs_fat_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16*2024,
        .disk_status_check_enable = false
    };
	sdmmc_card_t* card;
    ESP_LOGI(TAG, "Mounting filesystem");
    esp_err_t ret = esp_vfs_fat_sdmmc_mount(base_path, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set the EXAMPLE_FORMAT_IF_MOUNT_FAILED menuconfig option.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card lines have pull-up resistors in place.", esp_err_to_name(ret));
        }
        return;
    }
    ESP_LOGI(TAG, "Filesystem mounted");
    sdmmc_card_print_info(stdout, card);

	save_to_sd();

    esp_vfs_fat_sdcard_unmount(base_path, card);
    ESP_LOGI(TAG, "Card unmounted");
}
