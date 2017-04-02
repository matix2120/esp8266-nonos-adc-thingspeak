/* Created by matix21
 * MIT License
 */

#ifndef TCP_H
#define TCP_H

#include "user_interface.h"

void ICACHE_FLASH_ATTR tcp_connected(void *arg);
void ICACHE_FLASH_ATTR tcp_disconnected(void *arg);
void ICACHE_FLASH_ATTR get_thingspeak_ip();

struct espconn thingspeak_connection;
ip_addr_t thingspeak_ip;
esp_tcp thingspeak_tcp;

#define THINGSPEAK_HOST "api.thingspeak.com"
#define THINGSPEAK_API_KEY ""

#endif
