#ifndef   __BSP_EXTI_H
#define   __BSP_EXTI_H
#include  "bsp_conf.h"
void    EXTI_GPIO_Config(GPIO_TypeDef* GPIOx,uint16_t GPIOPIN);
uint8_t GPIOPORT_convert_GPIOPORT_SRC(GPIO_TypeDef* GPIOx);
uint8_t GPIOPIN_convert_GPIOPIN_SRC(uint16_t GPIO_PIN);
#endif  /*__BSP_EXTI_H*/