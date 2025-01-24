#ifndef WIFI_STA_H
#define WIFI_STA_H

#include "esp_err.h"

// Function to initialize Wi-Fi with the given SSID and password
esp_err_t init_wifi_sta(const char *ssid, const char *password);

#endif // WIFI_STA_H
