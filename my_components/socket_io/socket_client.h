#ifndef SOCKET_CLIENT_H
#define SOCKET_CLIENT_H

#include <stdio.h>
#include "esp_system.h"
#include "esp_event.h"
#include "esp_websocket_client.h"


// WebSocket Event Handler
void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);

// Start WebSocket Application
void websocket_connect_and_stream(const char* uri);

#endif // SOCKET_CLIENT_H
