#include"bsp_exti.h"
/**
  * @brief  EXTI中断NVIC向量中断器配置
  * @param  EXTILINE:中断线
  * @retval None
  */
static void  EXTI_NVIC_Config(uint32_t NVIC_PriorityGroup,uint16_t EXTILINE)
{
       NVIC_Config(NVIC_PriorityGroup,EXTILine_convert_IRQChannel(EXTILINE),1,1);
}

/**
  * @brief  EXTI的AFIO配置
  * @param  GPIOx:GPIOX(X=A,B...,G)
  * @param  GPIOPIN:GPIO口
  * @retval None
  */
void    EXTI_GPIO_Config(GPIO_TypeDef* GPIOx,uint16_t GPIOPIN)
{
        //NVIC初始化
        EXTI_NVIC_Config(NVIC_PriorityGroup_1,GPIOPIN);
        //EXTI复用的GPIO口初始化 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//时钟使能
        GPIO_EXTILineConfig(GPIOPORT_convert_GPIOPORT_SRC(GPIOx),GPIOPIN_convert_GPIOPIN_SRC(GPIOPIN));//GPIOAFIO寄存器配置
        EXTI_Common_Interrupt_struct.EXTI_Line = GPIOPIN;//配置EXTILINEx
        EXTI_Init(&EXTI_Common_Interrupt_struct);//配置EXTI寄存器   
}

/**
  * @brief  GPIOPORT转换成GPIOPORT_SRC函数
  * @param  GPIOx:GPIOX(X=A,B...,G)
  * @retval GPIOPORT_SRC
  */
uint8_t GPIOPORT_convert_GPIOPORT_SRC(GPIO_TypeDef* GPIOx)
{
        if(GPIOx == GPIOA)
         {
             return GPIO_PortSourceGPIOA;
         }
         else if(GPIOx == GPIOB)
         {
             return GPIO_PortSourceGPIOB;
         }
         else if(GPIOx == GPIOC)
         {
             return GPIO_PortSourceGPIOC;
         }
         else if(GPIOx == GPIOD)
         {
             return GPIO_PortSourceGPIOD;
         }
         else if(GPIOx == GPIOE)
         {
             return GPIO_PortSourceGPIOE;
         }
         else if(GPIOx == GPIOF)
         {
             return GPIO_PortSourceGPIOF;
         }
         else if(GPIOx == GPIOG)
         {
             return GPIO_PortSourceGPIOG;
         }
         else
         {
             return 0;
         }
}

/**
  * @brief  GPIOPIN转换成GPIOPIN_SRC函数
  * @param  GPIO_PIN:GPIO口
  * @retval GPIOPIN_SRC
  */
uint8_t GPIOPIN_convert_GPIOPIN_SRC(uint16_t GPIO_PIN)
{
         switch (GPIO_PIN)
         {
         case GPIO_Pin_0:return GPIO_PinSource0;
         case GPIO_Pin_1:return GPIO_PinSource1;
         case GPIO_Pin_2:return GPIO_PinSource2;
         case GPIO_Pin_3:return GPIO_PinSource3;
         case GPIO_Pin_4:return GPIO_PinSource4;
         case GPIO_Pin_5:return GPIO_PinSource5;
         case GPIO_Pin_6:return GPIO_PinSource6;
         case GPIO_Pin_7:return GPIO_PinSource7;
         case GPIO_Pin_8:return GPIO_PinSource8;
         case GPIO_Pin_9:return GPIO_PinSource9;
         case GPIO_Pin_10:return GPIO_PinSource10;
         case GPIO_Pin_11:return GPIO_PinSource11;
         case GPIO_Pin_12:return GPIO_PinSource12;
         case GPIO_Pin_13:return GPIO_PinSource13;
         case GPIO_Pin_14:return GPIO_PinSource14;
         case GPIO_Pin_15:return GPIO_PinSource15;
         default:
             return 0;
         }
}
