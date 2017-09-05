/* Created by matix21
 * MIT License
 */

#ifndef WIFI_H
#define WIFI_H

#include "ip_addr.h"
#include "espconn.h"
#include "user_interface.h"

void wifi_handle_event_cb(System_Event_t *evt);
bool ICACHE_FLASH_ATTR user_set_station_config(void);

#endif
