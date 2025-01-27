#include <stdio.h>
#include "esp_system.h"
#include "esp_event.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"

#include "esp_log.h"
#include "esp_websocket_client.h"
#include "esp_event.h"
#include "socket_client.h"

#include "camera.h"

static const char *TAG = "WEBSOCKET";

void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id) {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        break;
    case WEBSOCKET_EVENT_DATA:
        ESP_LOGW(TAG, "Received=%.*s\n", data->data_len, (char *)data->data_ptr);
        break;
    }
}

void websocket_connect_and_stream(const char* uri)
{
    // Define the websocket connection
    esp_websocket_client_config_t websocket_cfg = {
        .uri = uri
    };
    ESP_LOGI(TAG, "Connecting to %s ...", websocket_cfg.uri);

    // Connect to WebSocket Server
    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    // Attempt to connect to the WebSocket server
    esp_err_t err = esp_websocket_client_start(client);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Connection failed: %s", esp_err_to_name(err));
        return;  // Exit if connection failed
    }

    // Wait until WebSocket is connected
    while (!esp_websocket_client_is_connected(client)) {
        vTaskDelay(pdMS_TO_TICKS(100)); // Small delay to prevent locking up the system
    }

    ESP_LOGI(TAG, "WebSocket connected, sending message...");

    const char *message = "{\"type\":\"setType\",\"value\":\"esp32\"}";
    size_t len = strlen(message);

    // Send message
    if (esp_websocket_client_send_text(client, message, len, portMAX_DELAY) < 0) {
        ESP_LOGE(TAG, "Failed to send message");
    } else {
        ESP_LOGI(TAG, "Message sent successfully: %s", message);
    }

    // Start streaming frames
    while (1) {
        camera_fb_t* fb = capture_frame();  // Capture a frame from the camera
        if (!fb) {
            ESP_LOGE(TAG, "Failed to capture frame");
            vTaskDelay(100 / portTICK_PERIOD_MS);  // Retry delay
            continue;
        }

        // Send the frame over WebSocket
        int send_result = esp_websocket_client_send_bin(client, (const char*)fb->buf, fb->len, portMAX_DELAY);
        if (send_result < 0) {
            ESP_LOGE(TAG, "Failed to send frame data, error code: %d", send_result);
        } else {
            ESP_LOGI(TAG, "Successfully sent frame to server, size: %d bytes", fb->len);
        }

        esp_camera_fb_return(fb);  // Return the frame buffer to the camera driver

//        // Simulate frame rate, adjust the delay if necessary
        vTaskDelay(33.33 / portTICK_PERIOD_MS); // Frame rate control (e.g., 20 FPS)
		if(!esp_websocket_client_is_connected(client)){
        	while (!esp_websocket_client_is_connected(client)) {
        		vTaskDelay(pdMS_TO_TICKS(2000));
    		}
                
            ESP_LOGI(TAG, "WebSocket connected, sending message...");
    		const char *message = "{\"type\":\"setType\",\"value\":\"esp32\"}";
    		size_t len = strlen(message);

    		if (esp_websocket_client_send_text(client, message, len, portMAX_DELAY) < 0) {
        		ESP_LOGE(TAG, "Failed to send message");
    		} else {
        		ESP_LOGI(TAG, "Message sent successfully: %s", message);
    		}
        }
    }

    // Cleanup after streaming
    ESP_LOGI(TAG, "Closing WebSocket connection...");

    esp_websocket_client_stop(client);       // Stop the WebSocket client
    esp_websocket_client_destroy(client); // Free resources associated with the WebSocket client
}
