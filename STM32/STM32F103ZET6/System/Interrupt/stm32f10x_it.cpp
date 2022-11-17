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
  // PWR电源管理项目
  // if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  // {
  //   EXTI_ClearITPendingBit(EXTI_Line0);
  // }
  // EXTI中断项目
  // if (EXTI_GetITStatus(EXTI_Line0) != RESET)
  // {
  //   LED_1.Toggle();
  //   printf("按下\n");
  //   EXTI_ClearITPendingBit(EXTI_Line0);
  // }
  EXTI0_Handler();
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
void USART1_IRQHandler(void)
{
  // if (USART_GetITStatus(USART1, USART_IT_RXNE))
  // {
  // 实验二
  // receivedata = USART_1.ReceiveByte();
  // USART_1.SendByte(receivedata);
  // 实验三
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
  USART1_Handler();
}
void WWDG_IRQHandler(void)
{
}
void PVD_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line16) != RESET)
  {
    if (PWR_GetFlagStatus(PWR_FLAG_PVDO) == RESET) // 高于阈值
    {
      printf("进入PVD中断,电压高于阈值\r\n");
    }
    else // 低于阈值
    {
      printf("进入PVD中断,电压低于阈值\r\n");
    }
    EXTI_ClearITPendingBit(EXTI_Line16);
  }
}
void TAMPER_IRQHandler(void)
{
  // 入侵检测项目
  if (BKP_GetITStatus() != RESET)
  {
    printf("入侵事件触发!\n");
    BKP_ClearFlag();
    BKP_ClearITPendingBit();
  }
}
void RTC_IRQHandler(void)
{
  // RTC实时时钟项目
  // if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
  // {
  //   timeinfo = RTC_Operate::Get_Time();
  //   strftime(timestr, sizeof(timestr) / sizeof(char), "%Y/%m/%d %p %H:%M:%S %A %Z ", &timeinfo);
  //   printf("%s\r", timestr);
  //   LED_1.Toggle();
  //   RTC_WaitForLastTask();
  //   RTC_ClearITPendingBit(RTC_IT_SEC);
  // }
  // else if (RTC_GetITStatus(RTC_IT_ALR) != RESET)
  // {
  //   printf("闹钟事件触发!\n");
  //   RTC_WaitForLastTask();
  //   RTC_ClearITPendingBit(RTC_IT_ALR);
  // }
  RTC_Handler();
}
void FLASH_IRQHandler(void)
{
}
void RCC_IRQHandler(void)
{
}
void EXTI1_IRQHandler(void)
{
  EXTI1_Handler();
}
void EXTI2_IRQHandler(void)
{
  EXTI2_Handler();
}
void EXTI3_IRQHandler(void)
{
  EXTI3_Handler();
}
void EXTI4_IRQHandler(void)
{
  EXTI4_Handler();
}
void DMA1_Channel1_IRQHandler(void)
{
  DMA1_Channel1_Handler();
}
void DMA1_Channel2_IRQHandler(void)
{
  DMA1_Channel2_Handler();
}
void DMA1_Channel3_IRQHandler(void)
{
  // if (DMA_GetITStatus(DMA1_IT_TC3))
  // {
  //   printf("123\n");
  //   DMA_ClearITPendingBit(DMA1_IT_TC3);
  // }
  DMA1_Channel3_Handler();
}
void DMA1_Channel4_IRQHandler(void)
{
  DMA1_Channel4_Handler();
}
void DMA1_Channel5_IRQHandler(void)
{
  // DMA串口通信项目
  // if (DMA_GetITStatus(DMA1_IT_TC5))
  // {
  //   // 一般发送
  //   //  for (int i = 0; i < sizeof(ReceiveBuffer) / sizeof(char); i++)
  //   //  {
  //   //    USART_1.Send_Data(ReceiveBuffer[i]);
  //   //  }
  //   //  DMA发送
  //   USART1_TX_DMA.Init();
  //   USART_1.DMACmd(USART_DMA_TX, ENABLE);
  //   DMA_ClearITPendingBit(DMA1_IT_TC5);
  // }
  DMA1_Channel5_Handler();
}

void DMA1_Channel6_IRQHandler(void)
{
  DMA1_Channel6_Handler();
}
void DMA1_Channel7_IRQHandler(void)
{
  DMA1_Channel7_Handler();
}
void ADC1_2_IRQHandler(void)
{
  // ADC1_2_Handler();
  // JEOC会触发EOC,有重叠关系,所以使用if else
  if (ADC_GetITStatus(ADC1, ADC_IT_EOC))
  {
    PLATFORM_SERIAL.Send_String_DMA("[ADC1]:1v\n");
    if (ADC_GetITStatus(ADC1, ADC_IT_JEOC))
    {
      PLATFORM_SERIAL.Send_String_DMA("[ADC1]:2v\n");
      ADC_ClearITPendingBit(ADC1, ADC_IT_JEOC);
    }
    ADC_ClearITPendingBit(ADC1, ADC_IT_EOC);
  }
  else if (ADC_GetITStatus(ADC1, ADC_IT_AWD))
  {
    PLATFORM_SERIAL.Send_String_DMA("[ADC1]:AWD Waring!\n");
    ADC_ClearITPendingBit(ADC1, ADC_IT_AWD);
  }

  if (ADC_GetITStatus(ADC2, ADC_IT_EOC))
  {
    PLATFORM_SERIAL.Send_String_DMA("[ADC2]:1v\n");
    if (ADC_GetITStatus(ADC2, ADC_IT_JEOC))
    {
      PLATFORM_SERIAL.Send_String_DMA("[ADC2]:2v\n");
      ADC_ClearITPendingBit(ADC2, ADC_IT_JEOC);
    }
    ADC_ClearITPendingBit(ADC2, ADC_IT_EOC);
  }
  else if (ADC_GetITStatus(ADC2, ADC_IT_AWD))
  {
    PLATFORM_SERIAL.Send_String_DMA("[ADC2]:AWD Waring!\n");
    ADC_ClearITPendingBit(ADC2, ADC_IT_AWD);
  }
}
void USB_HP_CAN1_TX_IRQHandler(void)
{
}
void USB_LP_CAN1_RX0_IRQHandler(void)
{
}
void CAN1_RX1_IRQHandler(void)
{
}
void CAN1_SCE_IRQHandler(void)
{
}
void EXTI9_5_IRQHandler(void)
{
  // SPI通信测试项目
  // if (EXTI_GetITStatus(EXTI_Line6) != RESET)
  // {
  //   // USART_1.Send_String("已进入中断！\n");
  //   // 读取PC6
  //   if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == Bit_SET)
  //   {
  //     USART_1.Send_String("引脚已拉高\n");
  //     SPI_2.NSS_High();
  //   }
  //   else if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_6) == Bit_RESET)
  //   {
  //     USART_1.Send_String("引脚已拉低\n");
  //     SPI_2.NSS_Low();
  //   }
  //   EXTI_ClearITPendingBit(EXTI_Line6);
  // }
  EXTI9_5_Handler();
}
void TIM1_BRK_IRQHandler(void)
{
  TIM1_BRK_Handler();
}
void TIM1_UP_IRQHandler(void)
{
  TIM1_UP_Handler();
}
void TIM1_TRG_COM_IRQHandler(void)
{
  TIM1_TRG_COM_Handler();
}
void TIM1_CC_IRQHandler(void)
{
  TIM1_CC_Handler();
}
void TIM3_IRQHandler(void)
{
  TIM3_Handler();
}
void TIM4_IRQHandler(void)
{
  TIM4_Handler();
}
void I2C1_EV_IRQHandler(void)
{
  I2C1_EV_Handler();
}
void I2C1_ER_IRQHandler(void)
{
  I2C1_ER_Handler();
}
void I2C2_EV_IRQHandler(void)
{
  I2C2_EV_Handler();
}
void I2C2_ER_IRQHandler(void)
{
  I2C2_ER_Handler();
}
void SPI1_IRQHandler(void)
{
  // if (SPI_I2S_GetITStatus(SPI1, SPI_IT_MODF) != RESET)
  // {
  //   printf("MODF!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI1, SPI_IT_CRCERR) != RESET)
  // {
  //   printf("CRCERR!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_OVR) != RESET)
  // {
  //   printf("OVR!\n");
  // }
  SPI1_Handler();
}
void SPI2_IRQHandler(void)
{
  // if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET)
  // {
  //   printf("%c", SPI_I2S_ReceiveData(SPI2));
  //   // printf("RXNE!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) != RESET)
  // {
  //   printf("TXE!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI2, SPI_IT_CRCERR) != RESET)
  // {
  //   printf("CRCERR!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_OVR) != RESET)
  // {
  //   printf("OVR!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI2, SPI_IT_MODF) != RESET)
  // {
  //   printf("MODF!\n");
  // }
  // if (SPI_I2S_GetITStatus(SPI2, I2S_IT_UDR) != RESET)
  // {
  //   printf("UDR!\n");
  // }
  SPI2_Handler();
}
void USART2_IRQHandler(void)
{
  USART2_Handler();
}
void USART3_IRQHandler(void)
{
  USART3_Handler();
}
void EXTI15_10_IRQHandler(void)
{
  // PWR电源管理项目
  // if (EXTI_GetITStatus(EXTI_Line13) != RESET)
  // {
  //   printf("进入睡眠模式\n");
  //   __WFE();
  //   EXTI_ClearITPendingBit(EXTI_Line13);
  // }
  EXTI15_10_Handler();
}
void RTCAlarm_IRQHandler(void)
{
  // PWR电源管理项目
  // if (EXTI_GetITStatus(EXTI_Line17) != RESET)
  // {
  //   // 停止模式唤醒的时钟不足以发送串口
  //   // printf("闹钟60s唤醒\n");
  //   RTC_x.SetAlarm(RTC_Operate::GetCounter() + 60);
  //   EXTI_ClearITPendingBit(EXTI_Line17);
  // }
  RTCAlarm_Handler();
}
void USBWakeUp_IRQHandler(void)
{
}
void TIM8_BRK_IRQHandler(void)
{
  TIM8_BRK_Handler();
}
void TIM8_UP_IRQHandler(void)
{
  TIM8_UP_Handler();
}
void TIM8_TRG_COM_IRQHandler(void)
{
  TIM8_TRG_COM_Handler();
}
void TIM8_CC_IRQHandler(void)
{
  TIM8_CC_Handler();
}
void ADC3_IRQHandler(void)
{
  ADC3_Handler();
}
void FSMC_IRQHandler(void)
{
}
void SDIO_IRQHandler(void)
{
}
void TIM5_IRQHandler(void)
{
  TIM5_Handler();
}
void SPI3_IRQHandler(void)
{
  SPI3_Handler();
}
void UART4_IRQHandler(void)
{
  UART4_Handler();
}
void UART5_IRQHandler(void)
{
  UART5_Handler();
}
void TIM6_IRQHandler(void)
{
  TIM6_Handler();
}
void TIM7_IRQHandler(void)
{
  TIM7_Handler();
}
void DMA2_Channel1_IRQHandler(void)
{
  DMA2_Channel1_Handler();
}
void DMA2_Channel2_IRQHandler(void)
{
  DMA2_Channel2_Handler();
}
void DMA2_Channel3_IRQHandler(void)
{
  DMA2_Channel3_Handler();
}
void DMA2_Channel4_5_IRQHandler(void)
{
  DMA2_Channel4_5_Handler();
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
