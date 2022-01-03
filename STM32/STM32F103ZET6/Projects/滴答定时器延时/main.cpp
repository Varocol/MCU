#include"stm32f10x.h"
#include"bsp_led.h"
int main()
{
     LED_GPIO_config();
     LED_GPIO_SHINE(0.4);
}