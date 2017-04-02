#include "wifi.h"
#include "tcp.h"
#include "osapi.h"


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
        get_thingspeak_ip();
        break;

        default:
        os_printf("Unknown event: %x", evt->event);
        break;
    }
}

bool ICACHE_FLASH_ATTR user_set_station_config()
{
    struct station_config stationConf;
    stationConf.bssid_set = 0;      //need not check MAC address of AP

    os_memset(&stationConf.ssid, 0, sizeof(stationConf.ssid));
    os_memset(&stationConf.password, 0, sizeof(stationConf.password));

    os_memcpy(&stationConf.ssid, WIFI_SSID, os_strlen(WIFI_SSID));
    os_memcpy(&stationConf.password, WIFI_PASSWORD, os_strlen(WIFI_PASSWORD));

    os_printf("%s\n\r", __FUNCTION__);
    return wifi_station_set_config(&stationConf);
}