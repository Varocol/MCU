#include "bsp_led.h"
uint16_t LED_GPIO_Pin;
void    LED_GPIOInit()
{
        LED_OUT_MODE;
        LED_GPIO_Pin = GPIO_Pin_12;
}
void    LED_SHINE(GPIO_TypeDef* GPIOx,uint16_t GPIOpin)
{
        GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_All);
        GPIO_ResetBits(LED_GPIO_PORT,GPIOpin);
}
void    LED_FLOW(uint8_t flag)
{
        if(flag)
        {
            if(LED_GPIO_Pin < GPIO_Pin_15)
            {
                LED_GPIO_Pin <<= 1;
            }
            else
            {
                LED_GPIO_Pin = GPIO_Pin_12;   
            }
        }
        else
        {
            if(LED_GPIO_Pin > GPIO_Pin_12)
            {
                LED_GPIO_Pin >>= 1;
            }
            else
            {
                LED_GPIO_Pin = GPIO_Pin_15;   
            }
        }
        LED_SHINE(LED_GPIO_PORT,LED_GPIO_Pin);
        SysTick_Delay_ms(500);
}
 