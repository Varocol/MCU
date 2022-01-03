#ifndef __BSP_LED
#define __BSP_LED
#include "stm32f10x.h"
#include "bsp_conf.h"
#define LED_GPIO_PORT GPIOB
#define LED_GPIO_PIN  GPIO_Pin_12
extern  GPIO LED;
void    LED_GPIO_Init(void);
void    LED_Shine(void);
void    delay(int);
#endif