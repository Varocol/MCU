#include "bsp_conf.h"
#include "bsp_led.h"
int main()
{
     // HSE_SetSysClock(RCC_PLLMul_9);
     LED_GPIOInit();
     LED.Pin_Off();
     while(1)
     {
          if(TIM::Delay_Complete())
          {
               TIM::Delay_ms(2000);
               LED.Set_Pin(flag);
          }
     }
}