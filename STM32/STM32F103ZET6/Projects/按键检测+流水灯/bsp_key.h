#ifndef __BSP_KEY_H
#define __BSP_KEY_H
#include "stm32f10x.h"
#define  KEY_GPIO_PORT  GPIOB
#define  KEY_GPIO_Pin   GPIO_Pin_1
#define  KEY_GPIO_CLK   RCC_APB2Periph_GPIOB
#define  KEY_ON         0
#define  KEY_OFF        1
#define  KEY_CHG        1
#define  KEY_NCHG       0
void     KEY_GPIO_config(void);
uint8_t  KEY_Scan(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin);
uint8_t  KEY_Status_Ischange(void);
void     KEY_Updata_key_status(uint8_t Status);
uint8_t  KEY_Return_status(void);
#endif /*__BSP_KEY_H*/