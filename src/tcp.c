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
	struct espconn *conn = arg;
	char *status = strstr(pdata, "Status");
	os_printf("Received %d bytes\n%s\n", len, strtok(status, "\r"));
	espconn_disconnect(conn);
}

void ICACHE_FLASH_ATTR tcp_connected(void *arg)
{
    os_printf("Connected to: %s\n", THINGSPEAK_HOST);

    espconn_regist_recvcb(&thingspeak_connection, data_received); 

    static int temperature = 20;   // test data
    struct espconn *conn = arg;
	char buffer[256];
	char value_buf[100];

	os_sprintf(value_buf, "field1=%d\r\n", temperature);
    os_sprintf(buffer, "POST /update HTTP/1.1\r\nHost: %s\r\nConnection: close\r\nX-THINGSPEAKAPIKEY: %s\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %d\r\n\r\n%s",
			   THINGSPEAK_HOST, THINGSPEAK_API_KEY, os_strlen(value_buf), value_buf);

    int result = espconn_send(conn, buffer, os_strlen(buffer));

    if(result == ESPCONN_OK)
    {
		os_printf("Sent value: %d\n", temperature);
	}
	else
	{
		os_printf("Send error: %d\n", result);
	}
    temperature++;
}

void ICACHE_FLASH_ATTR tcp_disconnected(void *arg)
{
    os_printf("Disconnected from: %s\n", THINGSPEAK_HOST);
    wifi_station_disconnect();
}
