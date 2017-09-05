/* Created by matix21
 * MIT License
 */

#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include "osapi.h"

#define ADC_MEASURES_NUM 10

typedef struct 
{
	int32_t temp;
    uint32_t press;
    uint32_t hum;
    uint32_t voltage;
} measurements;

uint16_t ICACHE_FLASH_ATTR get_adc_measurement(void);
void prepare_measurements(measurements *);



#endif
