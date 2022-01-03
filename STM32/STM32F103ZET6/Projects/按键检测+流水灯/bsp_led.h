#ifndef  __BSP_LED_H
#define  __BSP_LED_H
#include "stm32f10x.h"
#define  LED_GPIO_PORT  GPIOB
#define  LED_GPIO_CLK   RCC_APB2Periph_GPIOB
#define  down 0
#define  up   1   
void  LED_GPIO_config(void);
void  LED_GPIO_SHINE(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin);
void  LED_GPIO_Changestatus(char ischange);
#endif /*__BSP_LED_H*/