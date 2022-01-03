#include "bsp_led.h"
GPIO LED;
void    LED_GPIOInit()
{
        GPIO_InitTypeDef LED_GPIOInitStructure = 
        {
            LED_GPIO_PIN,
            GPIO_Speed_50MHz,
            GPIO_Mode_Out_PP
        };
        LED = GPIO(LED_GPIO_PORT, LED_GPIOInitStructure); 
        LED.Init();
}

 