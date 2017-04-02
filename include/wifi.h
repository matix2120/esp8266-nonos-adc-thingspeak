#ifndef WIFI_H
#define WIFI_H

#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASS"

void wifi_handle_event_cb(System_Event_t *evt);
bool ICACHE_FLASH_ATTR user_set_station_config();

#endif
