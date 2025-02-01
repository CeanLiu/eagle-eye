#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "gpio_custom.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void gpio_custom_init(void) {
    // Reset and configure GPIO pins
    gpio_reset_pin(LED);
    gpio_reset_pin(MOTION_1);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(MOTION_1, GPIO_MODE_INPUT);
	gpio_set_pull_mode(MOTION_1, GPIO_PULLDOWN_ONLY); //
    // Set initial LED state
    gpio_set_level(LED, 0); // Turn off LED initially
//
//     Main loop for motion detection
//    while (1) {
//        // Read the PIR sensor status
//        int status = gpio_get_level(MOTION_1);
//
//        // Log the current status
//        ESP_LOGI("gpio_custom_init", "Motion sensor status: %d", status);
//
//        if (status == 1) {
//            // Motion detected
//            ESP_LOGI("gpio_custom_init", "Motion detected!");
//        } else {
//        }
//
//        // Delay for 500 ms
//        vTaskDelay(100 / portTICK_PERIOD_MS);
//    }
}


void lightOn(void){
  gpio_set_level(LED, 0);
  ESP_LOGI("gpio_custom_init", "LED ON");
 }

void lightOff(void){
   gpio_set_level(LED, 1);
   ESP_LOGI("gpio_custom_init", "LED OFF");
}
