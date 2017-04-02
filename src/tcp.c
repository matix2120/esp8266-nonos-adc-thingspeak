#include "osapi.h"
#include "tcp.h"

static void ICACHE_FLASH_ATTR host_ip_found(const char *name, ip_addr_t *ipaddr, void *arg)
{
    if (ipaddr == NULL)
    {
        os_printf("Unable to find IP for %s\nDisconnecting wifi\n", THINGSPEAK_HOST);
        wifi_station_disconnect();
    }

    os_printf("host %s found %d.%d.%d.%d\n", THINGSPEAK_HOST, *((uint8 *)&ipaddr->addr), *((uint8 *)&ipaddr->addr + 1),
             *((uint8 *)&ipaddr->addr + 2), *((uint8 *)&ipaddr->addr + 3));

    struct espconn *pespconn = (struct espconn *)arg;
    pespconn->type = ESPCONN_TCP;
    pespconn->state = ESPCONN_NONE;
    pespconn->proto.tcp=&thingspeak_tcp;
    pespconn->proto.tcp->local_port = espconn_port();
    pespconn->proto.tcp->remote_port = 80;
    os_memcpy (pespconn->proto.tcp->remote_ip, &ipaddr->addr, 4);

    espconn_regist_connectcb (pespconn, tcp_connected);
    espconn_regist_disconcb (pespconn, tcp_disconnected);

    if (espconn_connect(pespconn) != ESPCONN_OK)
    {
        os_printf("Unable to connect to %s\nDisconnecting wifi\n", THINGSPEAK_HOST);
        wifi_station_disconnect();
    }
}

void ICACHE_FLASH_ATTR get_thingspeak_ip()
{
	espconn_gethostbyname (&thingspeak_connection, THINGSPEAK_HOST, &thingspeak_ip, host_ip_found);
}

static void ICACHE_FLASH_ATTR data_received(void *arg, char *pdata, unsigned short len)
{
    os_printf("Received %d bytes: %s", len, pdata);
}

void ICACHE_FLASH_ATTR tcp_connected(void *arg)
{
    os_printf("Connected to: %s\n", THINGSPEAK_HOST);

    espconn_regist_recvcb(&thingspeak_connection, data_received); 
}

void ICACHE_FLASH_ATTR tcp_disconnected(void *arg)
{
    os_printf("Disconnected from: %s\n", THINGSPEAK_HOST);
}
