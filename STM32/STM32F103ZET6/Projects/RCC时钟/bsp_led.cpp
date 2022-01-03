#include"bsp_led.h"
GPIO LED;
void    LED_GPIO_Init(void)
{
        GPIO_InitTypeDef GPIO_InitStructure = 
        {
                LED_GPIO_PIN,
                GPIO_Speed_50MHz,
                GPIO_Mode_Out_PP
        };
        LED = GPIO(LED_GPIO_PORT,GPIO_InitStructure);
        LED.Init();
}
void    LED_Shine(void)
{
        while(1) 
        {
              LED.Set_Pin((BitAction)!LED.Get_Output_Pin());
              delay(5000);
        }
}
void    delay(int x)
{
        for(int i=0;i<1000;i++)
        for(int j=0;j<x;j++)
        __NOP();
}