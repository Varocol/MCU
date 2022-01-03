#include "GetIRQn.h"

/**
  * @brief  USART获取IRQ中断
  * @param  USARTX:串口
  * @retval None
  */
uint8_t USART_GetIRQ(USART_TypeDef *USARTX)
{
    if (USARTX == USART1)
    {
        return USART1_IRQn;
    }
    else if (USARTX == USART2)
    {
        return USART2_IRQn;
    }
    else if (USARTX == USART3)
    {
        return USART3_IRQn;
    }
    else if(USARTX == UART4)
    {
        return UART4_IRQn;
    }
    else if(USARTX == UART5)
    {
        return UART5_IRQn;
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  EXTILine转换成IRQChannel函数
  * @param  EXTILINE:中断线
  * @retval IRQChannel
  */
uint8_t EXTILine_convert_IRQChannel(uint16_t EXTILINE)
{
    switch (EXTILINE)
    {
    case EXTI_Line0:return EXTI0_IRQn;
    case EXTI_Line1:return EXTI1_IRQn;
    case EXTI_Line2:return EXTI2_IRQn;
    case EXTI_Line3:return EXTI3_IRQn;
    case EXTI_Line4:return EXTI4_IRQn;
    case EXTI_Line5:
    case EXTI_Line6:
    case EXTI_Line7:
    case EXTI_Line8:
    case EXTI_Line9:return EXTI9_5_IRQn;
    case EXTI_Line10:
    case EXTI_Line11:
    case EXTI_Line12:
    case EXTI_Line13:
    case EXTI_Line14:
    case EXTI_Line15:return EXTI15_10_IRQn;
    }
    return 0;
}

/**
  * @brief  TIM获取IRQ中断
  * @param  TIMX:定时器
  * @retval None
  */
uint8_t  TIM_GetIRQ(TIM_TypeDef * TIMX)
{
     
     if(TIMX == TIM2)
     {
        return TIM2_IRQn;
     }
     else if(TIMX == TIM3)
     {
        return TIM3_IRQn;
     }
     else if(TIMX == TIM4)
     {
        return TIM4_IRQn;
     }
     else if(TIMX == TIM5)
     {
        return TIM5_IRQn;
     }
     else if(TIMX == TIM6)
     {
        return TIM6_IRQn;
     }
     else if(TIMX == TIM7)
     {
        return TIM7_IRQn;
     }
     else
     {
        return 0;
     }
}