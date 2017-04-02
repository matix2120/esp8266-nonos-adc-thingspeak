#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"
#include "user_config.h"
#include "wifi.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];

//Main code function
static void ICACHE_FLASH_ATTR task (os_event_t *events)
{
    system_os_post(user_procTaskPrio, 0, 0);
}

void ICACHE_FLASH_ATTR user_init()
{
    uart_div_modify(0, UART_CLK_FREQ / (UART_SPEED));

    wifi_set_opmode(STATION_MODE);

    // Uncoment bellow line when you want to set new wifi settings
    // user_set_station_config(WIFI_SSID, WIFI_PASSWORD);

    //Start os task
    // system_os_task (task, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    // system_os_post (user_procTaskPrio, 0, 0 );

    wifi_set_event_handler_cb (wifi_handle_event_cb);
}