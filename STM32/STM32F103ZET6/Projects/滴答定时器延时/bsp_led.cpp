#include "bsp_led.h"
GPIO LED;
void LED_GPIO_config(void)
{
      GPIO_InitTypeDef GPIO_InitStruture =
          {
              LED_GPIO_PIN,
              GPIO_Speed_50MHz,
              GPIO_Mode_Out_PP};
      LED = GPIO(LED_GPIO_PORT, GPIO_InitStruture);
      LED.Init();
}
void LED_GPIO_SHINE(double time)
{
      while (1)
      {
            LED.Set_Pin((BitAction)!LED.Get_Output_Pin());
            SysTick_Operate::Delay_ms(time * 1000);
      }
}