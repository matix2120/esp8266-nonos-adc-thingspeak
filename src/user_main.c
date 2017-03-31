#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];

//Main code function
static void ICACHE_FLASH_ATTR loop(os_event_t *events)
{
    system_os_post(user_procTaskPrio, 0, 0);
}

bool ICACHE_FLASH_ATTR user_set_station_config(char *ssid, char *password)
{
    struct station_config stationConf;
    stationConf.bssid_set = 0;      //need not check MAC address of AP

    os_memset(&stationConf.ssid, 0, sizeof(stationConf.ssid));
    os_memset(&stationConf.password, 0, sizeof(stationConf.password));

    os_memcpy(&stationConf.ssid, ssid, os_strlen(ssid));
    os_memcpy(&stationConf.password, password, os_strlen(password));

    s_printf("%s\n\r", __FUNCTION__);
    return wifi_station_set_config(&stationConf);
}

//Init function 
void ICACHE_FLASH_ATTR user_init()
{
    uart_div_modify(0, UART_CLK_FREQ / (UART_SPEED));

    wifi_set_opmode(STATION_MODE);

    // Uncoment bellow line when you want to set new wifi settings
    // user_set_station_config(WIFI_SSID, WIFI_PASSWORD);

    //Start os task
    system_os_task (loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    system_os_post (user_procTaskPrio, 0, 0 );
}