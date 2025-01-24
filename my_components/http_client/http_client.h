#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "esp_http_client.h"

#define MAIN_URL "http://10.146.5.58/esp32"
#define STREAM_URL "http://10.146.5.58/esp32/frameData"

// Structure to pass HTTP client parameters
typedef enum {
  STATUS = 0,
  STREAM = 1,
  RECORD = 2,
  OTHER = 3,
} http_client_post_type_t;


// Function to start the HTTP client task
void http_stream_task(void *pvParameters);

#endif // HTTP_CLIENT_H
