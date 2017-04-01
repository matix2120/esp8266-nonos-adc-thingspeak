#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"
#include "user_config.h"

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

    os_printf("%s\n\r", __FUNCTION__);
    return wifi_station_set_config(&stationConf);
}

LOCAL void ICACHE_FLASH_ATTR host_ip_found (const char *name, ip_addr_t *ipaddr, void *arg)
{
    struct espconn *pespconn = (struct espconn *)arg;
    if (ipaddr == NULL)
    {
        os_printf("Unable to find IP for %s\nDisconnecting wifi\n", THINGSPEAK_HOST);
        wifi_station_disconnect();
    }

    os_printf("host %s found %d.%d.%d.%d\n", THINGSPEAK_HOST, *((uint8 *)&ipaddr->addr), *((uint8 *)&ipaddr->addr + 1),
             *((uint8 *)&ipaddr->addr + 2), *((uint8 *)&ipaddr->addr + 3));
}

void wifi_handle_event_cb(System_Event_t *evt)
{
    switch (evt->event)
    {
        case EVENT_STAMODE_CONNECTED:
        os_printf("connect to ssid %s, channel %d\n", evt->event_info.connected.ssid, evt->event_info.connected.channel);
        break;

        case EVENT_STAMODE_DISCONNECTED:
        os_printf("disconnect from ssid %s, reason %d\n", evt->event_info.disconnected.ssid, evt->event_info.disconnected.reason);
        break;

        case EVENT_STAMODE_AUTHMODE_CHANGE:
        os_printf("authmode change: %d -> %d\n", evt->event_info.auth_change.old_mode, evt->event_info.auth_change.new_mode);
        break;

        case EVENT_STAMODE_GOT_IP:
        espconn_gethostbyname (&thingspeak_connection, THINGSPEAK_HOST, &thingspeak_ip, host_ip_found);
        break;

        default:
        os_printf("Unknown event: %x", evt->event);
        break;
    }
}

void ICACHE_FLASH_ATTR user_init()
{
    uart_div_modify(0, UART_CLK_FREQ / (UART_SPEED));

    wifi_set_opmode(STATION_MODE);

    // Uncoment bellow line when you want to set new wifi settings
    // user_set_station_config(WIFI_SSID, WIFI_PASSWORD);

    //Start os task
    // system_os_task (loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);
    // system_os_post (user_procTaskPrio, 0, 0 );

    wifi_set_event_handler_cb (wifi_handle_event_cb);
}