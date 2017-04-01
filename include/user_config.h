#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include "ip_addr.h"
#include "espconn.h"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASS"

#define UART_SPEED 115200

struct espconn thingspeak_connection;
ip_addr_t thingspeak_ip;

#define THINGSPEAK_HOST "thingspeak.com"

#endif
