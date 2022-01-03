#include "bsp_led.h"
GPIO LED;
void LED_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure =
        {
            GPIO_Pin_12,
            GPIO_Speed_50MHz,
            GPIO_Mode_Out_PP};
    LED = GPIO(GPIOB, GPIO_InitStructure);
    LED.Init();
}