idf_component_register(SRCS "socket_client.c"
        INCLUDE_DIRS "." "../../managed_components/espressif__esp_websocket_client/include"
        REQUIRES esp_event esp-tls nvs_flash esp_http_client esp_http_server tcp_transport json camera gpio_custom)