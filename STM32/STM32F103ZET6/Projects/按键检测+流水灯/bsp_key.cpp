#include"bsp_key.h"
uint8_t  KEY_Status;
void  KEY_GPIO_config(void)
{
      GPIO_InitTypeDef GPIO_InitStruture;
      RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);
      GPIO_InitStruture.GPIO_Mode  = GPIO_Mode_IN_FLOATING; 
      GPIO_InitStruture.GPIO_Speed = GPIO_Speed_50MHz;
      GPIO_InitStruture.GPIO_Pin   = KEY_GPIO_Pin;
      GPIO_Init(GPIOB,&GPIO_InitStruture);
      KEY_Status=KEY_ON;
}
uint8_t KEY_Scan(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin)
{
      if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)
      {
           return KEY_ON;
      }
      else
      {
           return KEY_OFF;
      }
}
uint8_t  KEY_Status_Ischange(void)
{
      if(KEY_Scan(KEY_GPIO_PORT,KEY_GPIO_Pin)==KEY_Status)
      {
            return KEY_NCHG;
      }
      else
      {
            return KEY_CHG;
      }

}
void   KEY_Updata_key_status(uint8_t Status)
{
      KEY_Status=Status;
}
uint8_t  KEY_Return_status(void)
{
         return KEY_Status;
}
