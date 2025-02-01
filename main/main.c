#include "wifi_sta.h"
#include "http_client.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "camera.h"
#include "socket_client.h"
#include "gpio_custom.h"

static const char *TAG = "main";

#define WIFI_SSID "Pixel 7"
#define WIFI_PASSWORD "big L on you"
#define REMOTE_URL "ws://10.255.233.58:80"

void app_main(void) {
    // Initialize NVS (non-volatile storage)
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // Initialize Wi-Fi
    if (init_wifi_sta(WIFI_SSID, WIFI_PASSWORD) == ESP_OK) {
        ESP_LOGI(TAG, "Wi-Fi initialization started.");
    } else {
        ESP_LOGE(TAG, "Wi-Fi initialization failed.");
        return;
    }
    //initialize camera
    init_camera();
	gpio_custom_init();
    //start http server after a delay(ensures wifi is connected)
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    //set the client parameters
    websocket_connect_and_stream(REMOTE_URL);
//    xTaskCreate(http_stream_task, "http_stream_task", 8000, NULL, 5, NULL);

    //start http server after a delay(ensures wifi is connected)
    vTaskDelay(1000 / portTICK_PERIOD_MS);


}
