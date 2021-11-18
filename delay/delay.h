#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h>
#include "stm32l4xx_hal.h"

void delay(uint32_t ms){
 HAL_Delay(ms);
}

#endif /* __DELAY_H__ */
