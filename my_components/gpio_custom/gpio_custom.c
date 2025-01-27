#include <stdio.h>
#include "esp_log.h"
#include "driver/gpio.h"
#include "gpio_custom.h"

void gpio_custom_init(void){
  gpio_reset_pin(LED);
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);
  gpio_set_level(LED, 1);
  ESP_LOGI("gpio_custom_init", "GPIO_INIT_DONE");
}

void lightOn(void){
  gpio_set_level(LED, 0);
  ESP_LOGI("gpio_custom_init", "LED ON");
 }

void lightOff(void){
   gpio_set_level(LED, 1);
   ESP_LOGI("gpio_custom_init", "LED OFF");
}
