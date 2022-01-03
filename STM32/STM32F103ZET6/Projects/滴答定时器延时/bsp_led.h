#ifndef  __BSP_LED_H
#define  __BSP_LED_H
#include "bsp_conf.h"
#define  LED_GPIO_PORT  GPIOB
#define  LED_GPIO_PIN   GPIO_Pin_12
void  LED_GPIO_config(void);
void  LED_GPIO_SHINE(double);
#endif /*__BSP_LED_H*/