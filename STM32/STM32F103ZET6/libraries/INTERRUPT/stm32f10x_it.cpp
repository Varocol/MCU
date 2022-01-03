/**
  ******************************************************************************
  * @file    USART/Printf/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
BitAction flag = Bit_SET;
uint8_t receivedata;
uint32_t time_ms = 0;
uint32_t current_time_ms = 0;
/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup USART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{

}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
    
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {

  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {

  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {

  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{

}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{

}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  
}

void EXTI0_IRQHandler(void)
{
  //  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  //  {
  //      if(flag == Bit_SET)
  //      {
  //        flag = Bit_RESET;
  //      }
  //      else
  //      {
  //        flag = Bit_SET;
  //      }
  //  }
  //  KEY_IN_MODE;
  //  while(!KEY_IN);
  //  EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void)
{
}
void EXTI2_IRQHandler(void)
{
}
void EXTI3_IRQHandler(void)
{
}
void EXTI4_IRQHandler(void)
{
}
void EXTI9_5_IRQHandler(void)
{
}
void EXTI15_10_IRQHandler(void)
{
}
void TIM1_IRQHandler(void)
{
}
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    current_time_ms++;
    if (current_time_ms == time_ms)
    {
      if (flag == Bit_SET)
      {
        flag = Bit_RESET;
      }
      else
      {
        flag = Bit_SET;
      }
      current_time_ms = 0;
      TIM_Cmd(TIM2, DISABLE);
    }
    TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
  }
}
void TIM3_IRQHandler(void)
{
}
void TIM4_IRQHandler(void)
{
}
void TIM5_IRQHandler(void)
{
}
void TIM6_IRQHandler(void)
{
}
void TIM7_IRQHandler(void)
{
}
void TIM8_IRQHandler(void)
{
}
void USART1_IRQHandler(void)
{
  // if (USART_GetITStatus(USART1, USART_IT_RXNE))
  // {
    //实验二
    // receivedata = USART_1.ReceiveByte();
    // USART_1.SendByte(receivedata);
    //实验三
    // if((uint8_t)receivedata == '1')
    // {
    // PBout(12) = 0;
    // }
    // else if((uint8_t)receivedata == '0')
    // {
    // PBout(12) = 1;
    // }
    // USART_ClearITPendingBit(USART1, USART_IT_RXNE);
  // }
}
void USART2_IRQHandler(void)
{
}
void USART3_IRQHandler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
