#include "RCC.h"

/**
 * @brief  RCC_Operate-构造方法
 * @retval None
 */
RCC_Operate::RCC_Operate()
{
}

/**
 * @brief  RCC_Operate-析构方法
 * @retval None
 */
RCC_Operate::~RCC_Operate()
{
}

/**
 * @brief  RCC_Operate-获取RCC时钟信息方法
 * @param  None
 * @retval RCC时钟信息
 */
RCC_ClocksTypeDef RCC_Operate::Get_ClocksFreq()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks;
}

/**
 * @brief  RCC_Operate-获取系统时钟方法
 * @param  None
 * @retval 系统时钟频率
 */
uint32_t RCC_Operate::Get_SYSCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.SYSCLK_Frequency;
}

/**
 * @brief  RCC_Operate-获取AHB总线时钟方法
 * @param  None
 * @retval AHB总线时钟频率
 */
uint32_t RCC_Operate::Get_HCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.HCLK_Frequency;
}

/**
 * @brief  RCC_Operate-获取APB1外设时钟方法
 * @param  None
 * @retval APB1外设时钟频率
 */
uint32_t RCC_Operate::Get_PCLK1_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.PCLK1_Frequency;
}

/**
 * @brief  RCC_Operate-获取APB2外设时钟方法
 * @param  None
 * @retval APB2外设时钟频率
 */
uint32_t RCC_Operate::Get_PCLK2_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.PCLK2_Frequency;
}

/**
 * @brief  RCC_Operate-获取ADC时钟方法
 * @param  None
 * @retval ADC时钟频率
 */
uint32_t RCC_Operate::Get_ADCCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.ADCCLK_Frequency;
}

/**
 * @brief  RCC_Operate-获取系统时钟源
 * @param  None
 * @retval 时钟源
 */
Clock_Source RCC_Operate::Get_SYSCLKSource()
{
  switch (RCC_GetSYSCLKSource())
  {
  case 0x00:
    return HSI;
  case 0x04:
    return HSE;
  case 0x08:
    return PLL;
  default:
    return HSI;
  }
}

/**
 * @brief  RCC_Operate-备份域复位
 *         复位的对象包括BKP的数据寄存器,RTC的CNT,PRL,ALR寄存器,以及RCC的RCC_BDCR寄存器
 * @param  None
 * @retval
 */
void RCC_Operate::Backup_Reset()
{
  BKP_DeInit();
}

/**
 * @brief  RCC_Operate-外部高速时钟HSE配置系统时钟方法
 * @param  pllmul       PLL寄存器倍频因子(2-16,一般为9)
 * @retval None
 */
void RCC_Operate::HSE_SetSysClock(uint32_t pllmul)
{
  __IO uint32_t HSEStartUpStatus = 0;
  //复位rcc外设
  RCC_DeInit();
  //使能HSE，开启外部晶振
  RCC_HSEConfig(RCC_HSE_ON);
  //等待HSE稳定启动
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  // HSE稳定后继续设置
  if (HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    // AHB预分频因子设置位1分频
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    // APB2预分频因子设置为1分频
    RCC_PCLK2Config(RCC_HCLK_Div1);
    // APB1预分频因子设置位2分频
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //设置PLL时钟零来源为HSE,设置PLL倍频因子
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
    //开启pll
    RCC_PLLCmd(ENABLE);
    //等待PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    //当PLL稳定之后，吧pll时钟切换为系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //读取时钟切换状态位，确保PLLCLK被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
      ;
  }
  else
  {
    while (1)
    {
    }
  }
}

/**
 * @brief  RCC_Operate-内部高速时钟HSI配置系统时钟方法
 * @param  pllmul       PLL寄存器倍频因子(2-16)
 * @retval None
 */
void RCC_Operate::HSI_SetSysClock(uint32_t pllmul)
{
  __IO uint32_t HSIStartUpStatus = 0;
  //复位rcc外设
  RCC_DeInit();
  //使能HSI
  RCC_HSICmd(ENABLE);
  //等待HSI稳定启动
  HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;
  // HSI稳定后继续设置
  if (HSIStartUpStatus == RCC_CR_HSIRDY)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    // AHB预分频因子设置位1分频
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    // APB2预分频因子设置为1分频
    RCC_PCLK2Config(RCC_HCLK_Div1);
    // APB1预分频因子设置位2分频
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //设置PLL时钟零来源为HSI,设置PLL倍频因子
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
    //开启pll
    RCC_PLLCmd(ENABLE);
    //等待PLL稳定
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    //当PLL稳定之后，吧pll时钟切换为系统时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //读取时钟切换状态位，确保PLLCLK被选为系统时钟
    while (RCC_GetSYSCLKSource() != 0x08)
      ;
  }
  else
  {
    while (1)
    {
    }
  }
}

/**
 * @brief  RCC_Operate-ADC的RCC时钟分频配置方法
 * @param  RCC_PCLK2    ADC分频系数
 *                      RCC_PCLK2_Div2
 *                      RCC_PCLK2_Div4
 *                      RCC_PCLK2_Div6
 *                      RCC_PCLK2_Div8
 * @retval None
 */
void RCC_Operate::ADC_CLKConfig(uint32_t RCC_PCLK2)
{
  RCC_ADCCLKConfig(RCC_PCLK2);
}

/**
 * @brief  RCC_Operate-ADC的RCC时钟一键配置方法
 * @param  ADCX         ADC外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(ADC_TypeDef *ADCX, FunctionalState NewState)
{
  assert_param(IS_ADC_ALL_PERIPH(ADCX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(ADCX_Convert_RCC(ADCX), NewState);
}

/**
 * @brief  RCC_Operate-AFIO的RCC时钟一键配置方法
 * @param  AFIOX        AFIO外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(AFIO_TypeDef *AFIOX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(AFIO_Convert_RCC(AFIOX), NewState);
}

/**
 * @brief  RCC_Operate-BKP的RCC时钟一键配置方法
 * @param  BKPX         BKP外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(BKP_TypeDef *BKPX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(BKP_Convert_RCC(BKPX), NewState);
}

/**
 * @brief  RCC_Operate-CAN的RCC时钟一键配置方法
 * @param  CANX         CAN外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(CAN_TypeDef *CANX, FunctionalState NewState)
{
  assert_param(IS_CAN_ALL_PERIPH(CANX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(CAN_Convert_RCC(CANX), NewState);
}

/**
 * @brief  RCC_Operate-CRC的RCC时钟一键配置方法
 * @param  CRCX         CRC外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(CRC_TypeDef *CRCX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(CRC_Convert_RCC(CRCX), NewState);
}

/**
 * @brief  RCC_Operate-DAC的RCC时钟一键配置方法
 * @param  DACX         DAC外设
 * @param  NewState:    状态
 * @retval None
 */
void RCC_Operate::RCC_Config(DAC_TypeDef *DACX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(DAC_Convert_RCC(DACX), NewState);
}

/**
 * @brief  RCC_Operate-DMA的RCC时钟一键配置方法
 * @param  DMAX         DMA外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(DMA_TypeDef *DMAX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(DMA_Convert_RCC(DMAX), NewState);
}

/**
 * @brief  RCC_Operate-FLITF的RCC时钟一键配置方法
 * @param  FLITFX       FLITF外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FLITF_TypeDef *FLITFX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FLITF_Convert_RCC(FLITFX), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank1的RCC时钟一键配置方法
 * @param  FSMC_Bank1   FSMC的Bank1储存块
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank1_TypeDef *FSMC_Bank1X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank1_Convert_RCC(FSMC_Bank1X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank2的RCC时钟一键配置方法
 * @param  FSMC_Bank2   FSMC的Bank2储存块
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank2_TypeDef *FSMC_Bank2X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank2_Convert_RCC(FSMC_Bank2X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank3的RCC时钟一键配置方法
 * @param  FSMC_Bank3   FSMC的Bank3储存块
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank3_TypeDef *FSMC_Bank3X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank3_Convert_RCC(FSMC_Bank3X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank4的RCC时钟一键配置方法
 * @param  FSMC_Bank4   FSMC的Bank4储存块
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank4_TypeDef *FSMC_Bank4X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank4_Convert_RCC(FSMC_Bank4X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank1E的RCC时钟一键配置方法
 * @param  FSMC_Bank1E  FSMC的Bank1E储存块
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank1E_TypeDef *FSMC_Bank1EX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank1E_Convert_RCC(FSMC_Bank1EX), NewState);
}

/**
 * @brief  RCC_Operate-GPIO的RCC时钟一键配置方法
 * @param  GPIOX        GPIO外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(GPIO_TypeDef *GPIOX, FunctionalState NewState)
{
  assert_param(IS_GPIO_ALL_PERIPH(GPIOX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(GPIOX_Convert_RCC(GPIOX), NewState);
}

/**
 * @brief  RCC_Operate-I2C的RCC时钟一键配置方法
 * @param  I2CX         I2C外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(I2C_TypeDef *I2CX, FunctionalState NewState)
{
  assert_param(IS_I2C_ALL_PERIPH(I2CX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(I2CX_Convert_RCC(I2CX), NewState);
}

/**
 * @brief  RCC_Operate-PWR的RCC时钟一键配置方法
 * @param  PWRX         PWR外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(PWR_TypeDef *PWRX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(PWRX_Convert_RCC(PWRX), NewState);
}

/**
 * @brief  RCC_Operate-SDIO的RCC时钟一键配置方法
 * @param  SDIOX        SDIO外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(SDIO_TypeDef *SDIOX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(SDIOX_Convert_RCC(SDIOX), NewState);
}

/**
 * @brief  RCC_Operate-SPI的RCC时钟一键配置方法
 * @param  SPIX         SPI外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(SPI_TypeDef *SPIX, FunctionalState NewState)
{
  assert_param(IS_SPI_ALL_PERIPH(SPIX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (SPIX != SPI1)
  {
    RCC_APB1PeriphClockCmd(SPIX_Convert_RCC(SPIX), NewState);
  }
  else
  {
    RCC_APB2PeriphClockCmd(SPIX_Convert_RCC(SPIX), NewState);
  }
}

/**
 * @brief  RCC_Operate-SRAM的RCC时钟一键配置方法
 * @param  SRAMX        SRAM外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(SRAM_TypeDef *SRAMX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(SRAMX_Convert_RCC(SRAMX), NewState);
}

/**
 * @brief  RCC_Operate-TIM的RCC时钟一键配置方法
 * @param  TIMX         TIM外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(TIM_TypeDef *TIMX, FunctionalState NewState)
{
  assert_param(IS_TIM_ALL_PERIPH(TIMX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (TIMX != TIM1 && TIMX != TIM8)
  {
    RCC_APB1PeriphClockCmd(TIMX_Convert_RCC(TIMX), NewState);
  }
  else
  {
    RCC_APB2PeriphClockCmd(TIMX_Convert_RCC(TIMX), NewState);
  }
}

/**
 * @brief  RCC_Operate-USART的RCC时钟一键配置方法
 * @param  USARTX       USART外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(USART_TypeDef *USARTX, FunctionalState NewState)
{
  assert_param(IS_USART_ALL_PERIPH(USARTX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  if (USARTX != USART1)
  {
    RCC_APB1PeriphClockCmd(USARTX_Convert_RCC(USARTX), NewState);
  }
  else
  {
    RCC_APB2PeriphClockCmd(USARTX_Convert_RCC(USARTX), NewState);
  }
}

/**
 * @brief  RCC_Operate-USB的RCC时钟一键配置方法
 * @param  USBX         USB外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(USB_TypeDef *USBX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(USBX_Convert_RCC(USBX), NewState);
}

/**
 * @brief  RCC_Operate-WWDG的RCC时钟一键配置方法
 * @param  WWDGX        WWDG外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(WWDG_TypeDef *WWDGX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(WWDGX_Convert_RCC(WWDGX), NewState);
}

/**
 * @brief  RCC_Operate-RTC的RCC时钟一键配置方法
 * @param  RTCx         RTC外设
 * @param  NewState     状态
 * @retval None
 */
void RCC_Operate::RCC_Config(RTC_TypeDef *RTCx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_RTCCLKCmd(NewState);
}

/**
 * @brief  RCC_Operate-ADC映射RCC时钟方法
 * @param  ADCX         用户输入的ADC
 * @retval 如果参数正确,则返回RCC_APB2Periph_ADCX,否则返回0。
 */
uint32_t RCC_Operate::ADCX_Convert_RCC(ADC_TypeDef *ADCX)
{
  if (ADCX == ADC1)
  {
    return RCC_APB2Periph_ADC1;
  }
  else if (ADCX == ADC2)
  {
    return RCC_APB2Periph_ADC2;
  }
  else if (ADCX == ADC3)
  {
    return RCC_APB2Periph_ADC3;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-AFIO映射RCC时钟方法
 * @param  AFIOX        用户输入的AFIO
 * @retval 返回RCC_APB2Periph_AFIO。
 */
uint32_t RCC_Operate::AFIO_Convert_RCC(AFIO_TypeDef *AFIOX)
{
  return RCC_APB2Periph_AFIO;
}

/**
 * @brief  RCC_Operate-BKP映射RCC时钟方法
 * @param  BKPX         用户输入的BKP
 * @retval 返回RCC_APB1Periph_BKP。
 */
uint32_t RCC_Operate::BKP_Convert_RCC(BKP_TypeDef *BKPX)
{
  return RCC_APB1Periph_BKP;
}

/**
 * @brief  RCC_Operate-CAN映射RCC时钟方法
 * @param  CANX         用户输入的CAN
 * @retval 如果参数正确,则返回RCC_APB1Periph_CANX,否则返回0。
 */
uint32_t RCC_Operate::CAN_Convert_RCC(CAN_TypeDef *CANX)
{
  if (CANX == CAN1)
  {
    return RCC_APB1Periph_CAN1;
  }
  else if (CANX == CAN2)
  {
    return RCC_APB1Periph_CAN2;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-CRC映射RCC时钟方法
 * @param  CRCX         用户输入的CRC
 * @retval 返回RCC_AHBPeriph_CRC。
 */
uint32_t RCC_Operate::CRC_Convert_RCC(CRC_TypeDef *CRCX)
{
  return RCC_AHBPeriph_CRC;
}

/**
 * @brief  RCC_Operate-DAC映射RCC时钟方法
 * @param  DACX         用户输入的DAC
 * @retval 返回RCC_APB1Periph_DAC。
 */
uint32_t RCC_Operate::DAC_Convert_RCC(DAC_TypeDef *DACX)
{
  return RCC_APB1Periph_DAC;
}

/**
 * @brief  RCC_Operate-DMA映射RCC时钟方法
 * @param  DMAX         用户输入的DMA
 * @retval 如果参数正确,则返回RCC_AHBPeriph_DMAX,否则返回0。
 */
uint32_t RCC_Operate::DMA_Convert_RCC(DMA_TypeDef *DMAX)
{
  if (DMAX == DMA1)
  {
    return RCC_AHBPeriph_DMA1;
  }
  else if (DMAX == DMA2)
  {
    return RCC_AHBPeriph_DMA2;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-FLITF映射RCC时钟方法
 * @param  FLITFX       用户输入的FLITF
 * @retval 返回RCC_AHBPeriph_FLITF。
 */
uint32_t RCC_Operate::FLITF_Convert_RCC(FLITF_TypeDef *FLITFX)
{
  return RCC_AHBPeriph_FLITF;
}

/**
 * @brief  RCC_Operate-FSMC_Bank1映射RCC时钟方法
 * @param  FSMC_Bank1X  用户输入的FSMC_Bank1
 * @retval 返回RRCC_AHBPeriph_FSMC。
 */
uint32_t RCC_Operate::FSMC_Bank1_Convert_RCC(FSMC_Bank1_TypeDef *FSMC_Bank1X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank2映射RCC时钟方法
 * @param  FSMC_Bank2X  用户输入的FSMC_Bank2
 * @retval 返回RCC_AHBPeriph_FSMC。
 */
uint32_t RCC_Operate::FSMC_Bank2_Convert_RCC(FSMC_Bank2_TypeDef *FSMC_Bank2X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank3映射RCC时钟方法
 * @param  FSMC_Bank3X  用户输入的FSMC_Bank3
 * @retval 返回RCC_AHBPeriph_FSMC。
 */
uint32_t RCC_Operate::FSMC_Bank3_Convert_RCC(FSMC_Bank3_TypeDef *FSMC_Bank3X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank4映射RCC时钟方法
 * @param  FSMC_Bank4X  用户输入的FSMC_Bank4
 * @retval 返回RCC_AHBPeriph_FSMC。
 */
uint32_t RCC_Operate::FSMC_Bank4_Convert_RCC(FSMC_Bank4_TypeDef *FSMC_Bank4X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank1E映射RCC时钟方法
 * @param  FSMC_Bank1EX 用户输入的FSMC_Bank1E
 * @retval 返回RCC_AHBPeriph_FSMC。
 */
uint32_t RCC_Operate::FSMC_Bank1E_Convert_RCC(FSMC_Bank1E_TypeDef *FSMC_Bank1EX)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-GPIO映射RCC时钟方法
 * @param  GPIOX        用户输入的GPIO
 * @retval 如果参数正确,则返回RCC_APB2Periph_GPIOX,否则返回0。
 */
uint32_t RCC_Operate::GPIOX_Convert_RCC(GPIO_TypeDef *GPIOX)
{
  if (GPIOX == GPIOA)
  {
    return RCC_APB2Periph_GPIOA;
  }
  else if (GPIOX == GPIOB)
  {
    return RCC_APB2Periph_GPIOB;
  }
  else if (GPIOX == GPIOC)
  {
    return RCC_APB2Periph_GPIOC;
  }
  else if (GPIOX == GPIOD)
  {
    return RCC_APB2Periph_GPIOD;
  }
  else if (GPIOX == GPIOE)
  {
    return RCC_APB2Periph_GPIOE;
  }
  else if (GPIOX == GPIOF)
  {
    return RCC_APB2Periph_GPIOF;
  }
  else if (GPIOX == GPIOG)
  {
    return RCC_APB2Periph_GPIOG;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-I2C映射RCC时钟方法
 * @param  I2CX         用户输入的I2C
 * @retval 如果参数正确,则返回RCC_APB1Periph_I2CX,否则返回0。
 */
uint32_t RCC_Operate::I2CX_Convert_RCC(I2C_TypeDef *I2CX)
{
  if (I2CX == I2C1)
  {
    return RCC_APB1Periph_I2C1;
  }
  else if (I2CX == I2C2)
  {
    return RCC_APB1Periph_I2C2;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-PWR映射RCC时钟方法
 * @param  PWRX         用户输入的PWR
 * @retval 返回RCC_APB1Periph_PWR。
 */
uint32_t RCC_Operate::PWRX_Convert_RCC(PWR_TypeDef *PWRX)
{
  return RCC_APB1Periph_PWR;
}

/**
 * @brief  RCC_Operate-SDIO映射RCC时钟方法
 * @param  SDIOX        用户输入的SDIO
 * @retval 返回RCC_AHBPeriph_SDIO。
 */
uint32_t RCC_Operate::SDIOX_Convert_RCC(SDIO_TypeDef *SDIOX)
{
  return RCC_AHBPeriph_SDIO;
}

/**
 * @brief  RCC_Operate-SPI映射RCC时钟方法
 * @param  SPIX         用户输入的SPI
 * @retval 如果参数正确,则返回RCC_APB1Periph_SPIX|RCC_APB2Periph_SPIX否则返回0。
 */
uint32_t RCC_Operate::SPIX_Convert_RCC(SPI_TypeDef *SPIX)
{
  if (SPIX == SPI1)
  {
    return RCC_APB2Periph_SPI1;
  }
  else if (SPIX == SPI2)
  {
    return RCC_APB1Periph_SPI2;
  }
  else if (SPIX == SPI3)
  {
    return RCC_APB1Periph_SPI3;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-SRAM映射RCC时钟方法
 * @param  SRAMX        用户输入的SRAM
 * @retval 返回RCC_AHBPeriph_SRAM。
 */
uint32_t RCC_Operate::SRAMX_Convert_RCC(SRAM_TypeDef *SRAMX)
{
  return RCC_AHBPeriph_SRAM;
}

/**
 * @brief  RCC_Operate-TIM映射RCC时钟方法
 * @param  TIMX         用户输入的TIM
 * @retval 如果参数正确,则返回RCC_APB1Periph_TIMX|RCC_APB2Periph_TIMX,否则返回0。
 */
uint32_t RCC_Operate::TIMX_Convert_RCC(TIM_TypeDef *TIMX)
{
  if (TIMX == TIM1)
  {
    return RCC_APB2Periph_TIM1;
  }
  else if (TIMX == TIM2)
  {
    return RCC_APB1Periph_TIM2;
  }
  else if (TIMX == TIM3)
  {
    return RCC_APB1Periph_TIM3;
  }
  else if (TIMX == TIM4)
  {
    return RCC_APB1Periph_TIM4;
  }
  else if (TIMX == TIM5)
  {
    return RCC_APB1Periph_TIM5;
  }
  else if (TIMX == TIM6)
  {
    return RCC_APB1Periph_TIM6;
  }
  else if (TIMX == TIM7)
  {
    return RCC_APB1Periph_TIM7;
  }
  else if (TIMX == TIM8)
  {
    return RCC_APB2Periph_TIM8;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-USART映射RCC时钟方法
 * @param  USARTX       用户输入的USART
 * @retval 如果参数正确,则返回RCC_APB2Periph_USARTX|RCC_APB1Periph_USARTX,否则返回0。
 */
uint32_t RCC_Operate::USARTX_Convert_RCC(USART_TypeDef *USARTX)
{
  if (USARTX == USART1)
  {
    return RCC_APB2Periph_USART1;
  }
  else if (USARTX == USART2)
  {
    return RCC_APB1Periph_USART2;
  }
  else if (USARTX == USART3)
  {
    return RCC_APB1Periph_USART3;
  }
  else if (USARTX == UART4)
  {
    return RCC_APB1Periph_UART4;
  }
  else if (USARTX == UART5)
  {
    return RCC_APB1Periph_UART5;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief  RCC_Operate-USB映射RCC时钟方法
 * @param  USBX         用户输入的USB
 * @retval 返回RCC_APB1Periph_USB。
 */
uint32_t RCC_Operate::USBX_Convert_RCC(USB_TypeDef *USBX)
{
  return RCC_APB1Periph_USB;
}

/**
 * @brief  RCC_Operate-WWDG映射RCC时钟方法
 * @param  WWDGX        用户输入的WWDG
 * @retval 返回RCC_APB1Periph_WWDG。
 */
uint32_t RCC_Operate::WWDGX_Convert_RCC(WWDG_TypeDef *WWDGX)
{
  return RCC_APB1Periph_WWDG;
}
