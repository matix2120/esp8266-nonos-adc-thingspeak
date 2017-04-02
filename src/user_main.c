/* Created by matix21
 * MIT License
 */


#include "adc.h"
#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"
#include "os_type.h"
#include "user_interface.h"
#include "user_config.h"
#include "wifi.h"

void ICACHE_FLASH_ATTR user_init()
{
    uart_div_modify(0, UART_CLK_FREQ / (UART_SPEED));

    read_and_store_soil_moisture();

    wifi_set_opmode(STATION_MODE);

    // Uncoment bellow line when you want to set new wifi settings
    // user_set_station_config(WIFI_SSID, WIFI_PASSWORD);

    //Start os task
    // system_os_task (task, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    // system_os_post (user_procTaskPrio, 0, 0 );

    wifi_set_event_handler_cb (wifi_handle_event_cb);
}