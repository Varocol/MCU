#include  "bsp_conf.h"
#include  "bsp_led.h"
int main()
{
     LED_GPIOInit();
     Key_GPIOInit();
     EXTI_GPIO_Config(KEY_GPIO_PORT,KEY_GPIO_PIN);
     while(1)
     {
          LED_FLOW(flag);
     }
}