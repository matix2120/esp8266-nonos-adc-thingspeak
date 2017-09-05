/* Created by matix21
 * MIT License
 */


#include "measurements.h"
#include "ets_sys.h"
#include "gpio.h"
#include "osapi.h"
#include "os_type.h"
#include "user_interface.h"
#include "user_config.h"
#include "wifi.h"
#include "i2c.h"
#include "i2c_bme280.h"

void ICACHE_FLASH_ATTR user_init()
{
    static bool initialized = 0;

    uart_div_modify(0, UART_CLK_FREQ / (UART_SPEED));
    if (initialized)
    {
        os_printf("BME280 already initialized.\r\n");
    }
    else
    {
        i2c_init();
        BME280_reset();
        os_printf("BME280 uninitialized, trying... ");
        initialized = BME280_Init(BME280_MODE_FORCED);
        if(initialized)
        {
            os_printf("Done.\r\n");
            user_set_station_config();
            wifi_set_opmode(STATION_MODE);
            wifi_set_event_handler_cb (wifi_handle_event_cb);
        }
        else
        {
            os_printf("\r\nBME280 init error. Going sleep for 1 minute.\r\n");
            system_deep_sleep_set_option(0);
            system_deep_sleep(SLEEP_BETWEEN_READ_FAILS_US);
        }
    }
}
