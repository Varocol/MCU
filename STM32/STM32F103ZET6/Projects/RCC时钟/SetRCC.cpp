#include"stm32f10x.h"
#include"bsp_led.h"
#include"bsp_conf.h"
int main()
{
      // RCC_Operate::HSE_SetSysClock(RCC_PLLMul_9);
      RCC_Operate::HSI_SetSysClock(RCC_PLLMul_2);
      LED_GPIO_Init();
      LED_Shine();
}
