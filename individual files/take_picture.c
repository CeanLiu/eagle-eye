    #include <stdio.h>

    #include "esp_log.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "driver/gpio.h"


    #include "esp_mac.h"
    #include "esp_wifi.h"
    #include "esp_event.h"
    #include "esp_log.h"
    #include "nvs_flash.h"

    #include "lwip/err.h"
    #include "lwip/sys.h"

    #include "esp_camera.h"

    #define WIFI_SSID "esp-32"
    #define WIFI_PASSWORD "BIGLBIGLBIGL"
    #define MAX_STA_CONN  4

    #define CAMERA_MODEL_WROVER_KIT
    #include "camera_pins.h"
    #include "sdmmc_cmd.h"
    #include "driver/sdmmc_host.h"
    #include "esp_vfs_fat.h"


    static const char *TAG = "wifi softAP";
    static const char *CAM_TAG = "camera";


    static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
    {
    if(event_id == WIFI_EVENT_AP_STACONNECTED) {
    wifi_event_ap_staconnected_t *event= (wifi_event_ap_staconnected_t*) event_data;
    ESP_LOGI(TAG, "CONNECTED");
    ESP_LOGI(TAG, "Station "MACSTR" joined, AID=%d",
                    MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
      wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
      ESP_LOGI(TAG, "DISCONNECTED");
      ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d, reason=%d",
               MAC2STR(event->mac), event->aid, event->reason);
    }
    }

    void init_wifi_staap(void)
    {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t wifi_init = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init));
    //    esp_netif_set_default_wifi_sta();
    ESP_ERROR_CHECK(esp_event_handler_instance_register(
        WIFI_EVENT,
        ESP_EVENT_ANY_ID,
        &wifi_event_handler,
        NULL,
        NULL));
    wifi_config_t wifi_config = {
      .ap = {
          .ssid = WIFI_SSID,
          .password = WIFI_PASSWORD,
          .max_connection = MAX_STA_CONN
      },
    //      .sta = {
    //          .ssid = WIFI_SSID,
    //          .password = WIFI_PASSWORD,
    //      }
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    esp_wifi_start();
    ESP_LOGI(TAG, "SSID: %s, Password:/ %s", WIFI_SSID, WIFI_PASSWORD);

    }
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

    .pixel_format = PIXFORMAT_RGB565,
    .frame_size = FRAMESIZE_SVGA, // Change to desired resolution

    .jpeg_quality = 12,       // Adjust quality (lower = better quality)
    .fb_count = 2,
    .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY
    };
    void init_camera(void) {
    // Initialize the camera
    esp_err_t err = esp_camera_init(&cam_config);
    if (err != ESP_OK) {
        ESP_LOGE(CAM_TAG,"Camera init failed with error 0x%d",err);
    }
    }
    void save_to_sd(void)
    {
    const char *base_path = "/sdcard";
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    esp_vfs_fat_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 2048,
    };
    sdmmc_card_t *card;
    esp_vfs_fat_sdmmc_mount(base_path, &host, &slot_config, &mount_config, &card);
    camera_fb_t *pic = esp_camera_fb_get();
    ESP_LOGI(TAG, "Picture taken! Its size was: %zu bytes", pic->len);

    FILE *f = fopen("/sdcard/capture.jpeg", "wb");
    if (f == NULL) {
        ESP_LOGE(TAG,"Failed to open file for writing\n");
        esp_camera_fb_return(pic);
        esp_vfs_fat_sdcard_unmount(base_path, card);
        return;
    }
    size_t written = fwrite(pic->buf, 1, pic->len, f);
    if (written != pic->len) {
        ESP_LOGE(TAG, "Failed to write complete buffer to file");
    } else {
        ESP_LOGI(TAG,"Image saved successfully\n");
    }
    fclose(f);
    // Unmount the SD card
    esp_vfs_fat_sdcard_unmount(base_path, card);
    printf("SD card unmounted\n");
    esp_camera_fb_return(pic);
    }


    void app_main(void)
    {
    //    esp_err_t ret = nvs_flash_init();
    //    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
    //        ESP_ERROR_CHECK(nvs_flash_erase());
    //        ret = nvs_flash_init();
    //    }
    //    ESP_ERROR_CHECK(ret);
    //    init_wifi_staap();
      init_camera();
      save_to_sd();
    }