#include"bsp_led.h"
uint32_t LED_GPIO_Pin  =GPIO_Pin_12;
uint8_t  flag;
void  LED_GPIO_config(void)
{
      GPIO_InitTypeDef GPIO_InitStruture;
      RCC_APB2PeriphClockCmd(LED_GPIO_CLK,ENABLE);
      GPIO_InitStruture.GPIO_Mode  = GPIO_Mode_Out_PP;
      GPIO_InitStruture.GPIO_Speed = GPIO_Speed_10MHz;
      GPIO_InitStruture.GPIO_Pin   = GPIO_Pin_12;
      GPIO_Init(GPIOB,&GPIO_InitStruture);
      GPIO_InitStruture.GPIO_Pin   = GPIO_Pin_13;
      GPIO_Init(GPIOB,&GPIO_InitStruture);
      GPIO_InitStruture.GPIO_Pin   = GPIO_Pin_14;
      GPIO_Init(GPIOB,&GPIO_InitStruture);
      GPIO_InitStruture.GPIO_Pin   = GPIO_Pin_15;
      GPIO_Init(GPIOB,&GPIO_InitStruture);
      flag=up;
}
void  LED_GPIO_SHINE(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin)
{
      GPIO_SetBits(LED_GPIO_PORT,GPIO_Pin_All);
      GPIO_ResetBits(LED_GPIO_PORT,GPIO_Pin);
}
void  LED_GPIO_Changestatus(char ischange)
{
      if(ischange)
      {
            flag = ~flag;
      }
      if(flag == up)
        {
            if(LED_GPIO_Pin==GPIO_Pin_15)
            {
                LED_GPIO_Pin = GPIO_Pin_12;
            }
            else
            {
                LED_GPIO_Pin <<=1;
            }
        }
        else
        {
            if(LED_GPIO_Pin==GPIO_Pin_12)
            {
                LED_GPIO_Pin = GPIO_Pin_15;
            }
            else
            {
                LED_GPIO_Pin >>=1;
            }
            
        }
       LED_GPIO_SHINE(LED_GPIO_PORT,LED_GPIO_Pin);
}