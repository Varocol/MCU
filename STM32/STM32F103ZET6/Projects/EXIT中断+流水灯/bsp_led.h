#ifndef  __BSP_LED_H
#define  __BSP_LED_H
#include "bsp_conf.h"
#define  LED_GPIO_PORT GPIOB
#define  LED_GPIO_PIN  GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15
#define  LED_GPIO_BASE GPIOB_BASE
#define  LED_GPIO_ODR_Addr (LED_GPIO_BASE + 12)
#define  LED_GPIO_IDR_Addr (LED_GPIO_BASE + 8)
#define  LED_OUT_MODE  GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                       GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                       GPIO_Common_Out_Struct.GPIO_Pin = LED_GPIO_PIN;\
                       GPIO_config(LED_GPIO_PORT,GPIO_Common_Out_Struct)           
void     LED_GPIOInit();
void     LED_SHINE(GPIO_TypeDef* GPIOx,uint16_t GPIOpin);
void     LED_FLOW(uint8_t flag);
#endif   /*__BSP_LED_H*/