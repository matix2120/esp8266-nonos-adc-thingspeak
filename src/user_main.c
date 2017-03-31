#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "os_type.h"
#include "user_interface.h"

#define user_procTaskPrio        0
#define user_procTaskQueueLen    1
os_event_t    user_procTaskQueue[user_procTaskQueueLen];
static void loop(os_event_t *events);

//Main code function
static void ICACHE_FLASH_ATTR
loop(os_event_t *events)
{
    os_printf("Hello\n\r");
    os_delay_us(1000000);
    system_os_post(user_procTaskPrio, 0, 0 );
}

//Init function 
void ICACHE_FLASH_ATTR
user_init()
{
    uart_div_modify( 0, UART_CLK_FREQ / ( UART_SPEED ) );
    
    //Start os task
    system_os_task (loop, user_procTaskPrio,user_procTaskQueue, user_procTaskQueueLen);

    system_os_post (user_procTaskPrio, 0, 0 );
}