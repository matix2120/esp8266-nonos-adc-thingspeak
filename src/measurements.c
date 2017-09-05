/* Created by matix21
 * MIT License
 */

#include "measurements.h"
#include "user_interface.h"

uint16_t ICACHE_FLASH_ATTR get_adc_measurement(void)
{
    uint16 result = 0;
    uint8 i;
    for (i = 0; i < ADC_MEASURES_NUM; ++i)
    {
        result += system_adc_read();
    }
    return result/ADC_MEASURES_NUM;
}

void ICACHE_FLASH_ATTR prepare_measurements(measurements *meas)
{
    meas->temp = BME280_GetTemperature();
    meas->press = BME280_GetPressure();
    meas->hum = BME280_GetHumidity();
    meas->voltage = get_adc_measurement();
    meas->voltage *= 416;
    meas->voltage /= 1024;
}
