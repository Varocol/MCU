#include"stm32f10x.h"
#include"bsp_led.h"
#include"bsp_key.h"
uint8_t flagt;
void  delay(uint16_t x)
{
      flagt=1;
      for(int i=0;i<x;i++)
      for(int j=0;j<1000;j++)
      {
          __NOP();    
          if(KEY_Status_Ischange()&flagt)
          {
              KEY_Updata_key_status(~KEY_Return_status());
              flagt=0;
          }
      }
}
int main()
{

    LED_GPIO_config();
    KEY_GPIO_config();
    GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_All);
    while(1)
    {
        LED_GPIO_Changestatus(KEY_Status_Ischange());
        delay(100);
    }
}