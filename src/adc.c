/* Created by matix21
 * MIT License
 */

#include "adc.h"
#include "user_interface.h"

void ICACHE_FLASH_ATTR read_and_store_soil_moisture()
{
    uint8 old_state = wifi_get_opmode();
    wifi_set_opmode(NULL_MODE);
    ets_intr_lock( ); //lock interrupts
    uint16 adc_addr[10];
    uint16 adc_num = 10;
    uint8 adc_clk_div = 8;
    system_adc_read_fast(adc_addr, adc_num, adc_clk_div);
    ets_intr_unlock(); //unlock interrupts

    uint16 result = 0;
    uint8 i;
    for (i = 0; i < adc_num; ++i)
    {
        result += adc_addr[i];
    }
    result/=adc_num;
    soil_moisture=(1023-result)/10;

    wifi_set_opmode(old_state);
}
