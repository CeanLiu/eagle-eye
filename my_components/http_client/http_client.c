#include "esp_log.h"
#include "esp_err.h"
#include "lwip/sockets.h"
#include "esp_http_client.h"
#include "http_client.h"
#include "camera.h"
#include <string.h>

#define TAG "HTTP_CLIENT"

esp_err_t http_event_handler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
        break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
        break;
        case HTTP_EVENT_ON_DATA:
            if (evt->data_len > 0) {
                ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
                printf("%.*s\n", evt->data_len, (char *)evt->data);
            }
        break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
        break;
        case HTTP_EVENT_REDIRECT:
            ESP_LOGI(TAG, "HTTP_EVENT_REDIRECT");
        break; // Add handling if needed for redirects
        default:
            ESP_LOGW(TAG, "Unhandled event ID: %d", evt->event_id);
        break;
    }
    return ESP_OK;
}

esp_err_t send_mjpeg_frame(esp_http_client_config_t *config, uint8_t *data, size_t len) {
    esp_http_client_handle_t client = esp_http_client_init(config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Failed to initialize HTTP client");
        return ESP_ERR_NO_MEM;
    }

    // Set correct headers for JPEG data
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "image/jpeg");
    char content_length[32];
    snprintf(content_length, sizeof(content_length), "%zu", len);
    esp_http_client_set_header(client, "Content-Length", content_length);

    // Open connection with the correct content length
    esp_err_t err = esp_http_client_open(client, len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open HTTP connection: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        return err;
    }

    // Write the JPEG data directly
    int written = esp_http_client_write(client, (char*)data, len);
    if (written < 0 || (size_t)written != len) {
        ESP_LOGE(TAG, "Failed to write JPEG data");
        esp_http_client_cleanup(client);
        return ESP_FAIL;
    }

    // Complete the request
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Successfully sent frame to server");
        ESP_LOGI(TAG, "HTTP Status = %d, content_length = %lld",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "Failed to send frame: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    return err;
}

void http_stream_task(void *pvParameters) {

    esp_http_client_config_t config = {
        .event_handler = http_event_handler,
        .url = STREAM_URL,
        .timeout_ms = 5000,     // Timeout for the entire HTTP request in milliseconds
        .buffer_size = 512,     // Size of buffer to hold the request body (e.g., MJPEG data)
    };

    // Configure HTTP client
    esp_err_t err = ESP_FAIL;
//    while (err != ESP_OK) {
//        // If the connection failed, log the error and attempt to reconnect
//        ESP_LOGW(TAG, "HTTP request failed: %s. Reconnecting...", esp_err_to_name(err));
//        // Optionally, wait before retrying
//        vTaskDelay(5000 / portTICK_PERIOD_MS); // Delay for 1 second
//        camera_fb_t* fb = capture_frame();  // Capture a frame from the camera
//        if (fb) {
//            err = send_mjpeg_frame(&config, fb->buf, fb->len);
//            esp_camera_fb_return(fb);
//        } else {
//            ESP_LOGE(TAG, "Failed to capture frame");
//        }
//    }
    while (1) {
        camera_fb_t* fb = capture_frame();  // Capture a frame from the camera
        if (fb) {
            err = send_mjpeg_frame(&config, fb->buf, fb->len);
            if (err == ESP_OK) {
                ESP_LOGI(TAG, "Successfully sent frame to server");
            } else {
                ESP_LOGE(TAG, "Failed to send frame: %s", esp_err_to_name(err));
            }
            esp_camera_fb_return(fb);  // Return the frame buffer to the camera driver
        } else {
            ESP_LOGE(TAG, "Failed to capture frame");
        }

        vTaskDelay(50 / portTICK_PERIOD_MS); // Adjust the delay between frames if needed
    }

    // Delete the task
    vTaskDelete(NULL);
}
