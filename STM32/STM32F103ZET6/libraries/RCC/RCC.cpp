#include "RCC.h"

/**
 * @brief  RCC_Operate-���췽��
 * @retval None
 */
RCC_Operate::RCC_Operate()
{
}

/**
 * @brief  RCC_Operate-��������
 * @retval None
 */
RCC_Operate::~RCC_Operate()
{
}

/**
 * @brief  RCC_Operate-��ȡRCCʱ����Ϣ����
 * @param  None
 * @retval RCCʱ����Ϣ
 */
RCC_ClocksTypeDef RCC_Operate::Get_ClocksFreq()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks;
}

/**
 * @brief  RCC_Operate-��ȡϵͳʱ�ӷ���
 * @param  None
 * @retval ϵͳʱ��Ƶ��
 */
uint32_t RCC_Operate::Get_SYSCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.SYSCLK_Frequency;
}

/**
 * @brief  RCC_Operate-��ȡAHB����ʱ�ӷ���
 * @param  None
 * @retval AHB����ʱ��Ƶ��
 */
uint32_t RCC_Operate::Get_HCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.HCLK_Frequency;
}

/**
 * @brief  RCC_Operate-��ȡAPB1����ʱ�ӷ���
 * @param  None
 * @retval APB1����ʱ��Ƶ��
 */
uint32_t RCC_Operate::Get_PCLK1_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.PCLK1_Frequency;
}

/**
 * @brief  RCC_Operate-��ȡAPB2����ʱ�ӷ���
 * @param  None
 * @retval APB2����ʱ��Ƶ��
 */
uint32_t RCC_Operate::Get_PCLK2_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.PCLK2_Frequency;
}

/**
 * @brief  RCC_Operate-��ȡADCʱ�ӷ���
 * @param  None
 * @retval ADCʱ��Ƶ��
 */
uint32_t RCC_Operate::Get_ADCCLK_Frequency()
{
  RCC_ClocksTypeDef RCC_Clocks;
  RCC_GetClocksFreq(&RCC_Clocks);
  return RCC_Clocks.ADCCLK_Frequency;
}

/**
 * @brief  RCC_Operate-��ȡϵͳʱ��Դ
 * @param  None
 * @retval ʱ��Դ
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
 * @brief  RCC_Operate-������λ
 *         ��λ�Ķ������BKP�����ݼĴ���,RTC��CNT,PRL,ALR�Ĵ���,�Լ�RCC��RCC_BDCR�Ĵ���
 * @param  None
 * @retval
 */
void RCC_Operate::Backup_Reset()
{
  BKP_DeInit();
}

/**
 * @brief  RCC_Operate-�ⲿ����ʱ��HSE����ϵͳʱ�ӷ���
 * @param  pllmul       PLL�Ĵ�����Ƶ����(2-16,һ��Ϊ9)
 * @retval None
 */
void RCC_Operate::HSE_SetSysClock(uint32_t pllmul)
{
  __IO uint32_t HSEStartUpStatus = 0;
  //��λrcc����
  RCC_DeInit();
  //ʹ��HSE�������ⲿ����
  RCC_HSEConfig(RCC_HSE_ON);
  //�ȴ�HSE�ȶ�����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  // HSE�ȶ����������
  if (HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    // AHBԤ��Ƶ��������λ1��Ƶ
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    // APB2Ԥ��Ƶ��������Ϊ1��Ƶ
    RCC_PCLK2Config(RCC_HCLK_Div1);
    // APB1Ԥ��Ƶ��������λ2��Ƶ
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //����PLLʱ������ԴΪHSE,����PLL��Ƶ����
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, pllmul);
    //����pll
    RCC_PLLCmd(ENABLE);
    //�ȴ�PLL�ȶ�
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    //��PLL�ȶ�֮�󣬰�pllʱ���л�Ϊϵͳʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
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
 * @brief  RCC_Operate-�ڲ�����ʱ��HSI����ϵͳʱ�ӷ���
 * @param  pllmul       PLL�Ĵ�����Ƶ����(2-16)
 * @retval None
 */
void RCC_Operate::HSI_SetSysClock(uint32_t pllmul)
{
  __IO uint32_t HSIStartUpStatus = 0;
  //��λrcc����
  RCC_DeInit();
  //ʹ��HSI
  RCC_HSICmd(ENABLE);
  //�ȴ�HSI�ȶ�����
  HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;
  // HSI�ȶ����������
  if (HSIStartUpStatus == RCC_CR_HSIRDY)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    FLASH_SetLatency(FLASH_Latency_2);
    // AHBԤ��Ƶ��������λ1��Ƶ
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    // APB2Ԥ��Ƶ��������Ϊ1��Ƶ
    RCC_PCLK2Config(RCC_HCLK_Div1);
    // APB1Ԥ��Ƶ��������λ2��Ƶ
    RCC_PCLK1Config(RCC_HCLK_Div2);
    //����PLLʱ������ԴΪHSI,����PLL��Ƶ����
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, pllmul);
    //����pll
    RCC_PLLCmd(ENABLE);
    //�ȴ�PLL�ȶ�
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
      ;
    //��PLL�ȶ�֮�󣬰�pllʱ���л�Ϊϵͳʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    //��ȡʱ���л�״̬λ��ȷ��PLLCLK��ѡΪϵͳʱ��
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
 * @brief  RCC_Operate-ADC��RCCʱ�ӷ�Ƶ���÷���
 * @param  RCC_PCLK2    ADC��Ƶϵ��
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
 * @brief  RCC_Operate-ADC��RCCʱ��һ�����÷���
 * @param  ADCX         ADC����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(ADC_TypeDef *ADCX, FunctionalState NewState)
{
  assert_param(IS_ADC_ALL_PERIPH(ADCX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(ADCX_Convert_RCC(ADCX), NewState);
}

/**
 * @brief  RCC_Operate-AFIO��RCCʱ��һ�����÷���
 * @param  AFIOX        AFIO����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(AFIO_TypeDef *AFIOX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(AFIO_Convert_RCC(AFIOX), NewState);
}

/**
 * @brief  RCC_Operate-BKP��RCCʱ��һ�����÷���
 * @param  BKPX         BKP����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(BKP_TypeDef *BKPX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(BKP_Convert_RCC(BKPX), NewState);
}

/**
 * @brief  RCC_Operate-CAN��RCCʱ��һ�����÷���
 * @param  CANX         CAN����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(CAN_TypeDef *CANX, FunctionalState NewState)
{
  assert_param(IS_CAN_ALL_PERIPH(CANX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(CAN_Convert_RCC(CANX), NewState);
}

/**
 * @brief  RCC_Operate-CRC��RCCʱ��һ�����÷���
 * @param  CRCX         CRC����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(CRC_TypeDef *CRCX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(CRC_Convert_RCC(CRCX), NewState);
}

/**
 * @brief  RCC_Operate-DAC��RCCʱ��һ�����÷���
 * @param  DACX         DAC����
 * @param  NewState:    ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(DAC_TypeDef *DACX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(DAC_Convert_RCC(DACX), NewState);
}

/**
 * @brief  RCC_Operate-DMA��RCCʱ��һ�����÷���
 * @param  DMAX         DMA����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(DMA_TypeDef *DMAX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(DMA_Convert_RCC(DMAX), NewState);
}

/**
 * @brief  RCC_Operate-FLITF��RCCʱ��һ�����÷���
 * @param  FLITFX       FLITF����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FLITF_TypeDef *FLITFX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FLITF_Convert_RCC(FLITFX), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank1��RCCʱ��һ�����÷���
 * @param  FSMC_Bank1   FSMC��Bank1�����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank1_TypeDef *FSMC_Bank1X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank1_Convert_RCC(FSMC_Bank1X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank2��RCCʱ��һ�����÷���
 * @param  FSMC_Bank2   FSMC��Bank2�����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank2_TypeDef *FSMC_Bank2X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank2_Convert_RCC(FSMC_Bank2X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank3��RCCʱ��һ�����÷���
 * @param  FSMC_Bank3   FSMC��Bank3�����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank3_TypeDef *FSMC_Bank3X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank3_Convert_RCC(FSMC_Bank3X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank4��RCCʱ��һ�����÷���
 * @param  FSMC_Bank4   FSMC��Bank4�����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank4_TypeDef *FSMC_Bank4X, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank4_Convert_RCC(FSMC_Bank4X), NewState);
}

/**
 * @brief  RCC_Operate-FSMC_Bank1E��RCCʱ��һ�����÷���
 * @param  FSMC_Bank1E  FSMC��Bank1E�����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(FSMC_Bank1E_TypeDef *FSMC_Bank1EX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(FSMC_Bank1E_Convert_RCC(FSMC_Bank1EX), NewState);
}

/**
 * @brief  RCC_Operate-GPIO��RCCʱ��һ�����÷���
 * @param  GPIOX        GPIO����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(GPIO_TypeDef *GPIOX, FunctionalState NewState)
{
  assert_param(IS_GPIO_ALL_PERIPH(GPIOX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB2PeriphClockCmd(GPIOX_Convert_RCC(GPIOX), NewState);
}

/**
 * @brief  RCC_Operate-I2C��RCCʱ��һ�����÷���
 * @param  I2CX         I2C����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(I2C_TypeDef *I2CX, FunctionalState NewState)
{
  assert_param(IS_I2C_ALL_PERIPH(I2CX));
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(I2CX_Convert_RCC(I2CX), NewState);
}

/**
 * @brief  RCC_Operate-PWR��RCCʱ��һ�����÷���
 * @param  PWRX         PWR����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(PWR_TypeDef *PWRX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(PWRX_Convert_RCC(PWRX), NewState);
}

/**
 * @brief  RCC_Operate-SDIO��RCCʱ��һ�����÷���
 * @param  SDIOX        SDIO����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(SDIO_TypeDef *SDIOX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(SDIOX_Convert_RCC(SDIOX), NewState);
}

/**
 * @brief  RCC_Operate-SPI��RCCʱ��һ�����÷���
 * @param  SPIX         SPI����
 * @param  NewState     ״̬
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
 * @brief  RCC_Operate-SRAM��RCCʱ��һ�����÷���
 * @param  SRAMX        SRAM����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(SRAM_TypeDef *SRAMX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_AHBPeriphClockCmd(SRAMX_Convert_RCC(SRAMX), NewState);
}

/**
 * @brief  RCC_Operate-TIM��RCCʱ��һ�����÷���
 * @param  TIMX         TIM����
 * @param  NewState     ״̬
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
 * @brief  RCC_Operate-USART��RCCʱ��һ�����÷���
 * @param  USARTX       USART����
 * @param  NewState     ״̬
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
 * @brief  RCC_Operate-USB��RCCʱ��һ�����÷���
 * @param  USBX         USB����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(USB_TypeDef *USBX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(USBX_Convert_RCC(USBX), NewState);
}

/**
 * @brief  RCC_Operate-WWDG��RCCʱ��һ�����÷���
 * @param  WWDGX        WWDG����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(WWDG_TypeDef *WWDGX, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_APB1PeriphClockCmd(WWDGX_Convert_RCC(WWDGX), NewState);
}

/**
 * @brief  RCC_Operate-RTC��RCCʱ��һ�����÷���
 * @param  RTCx         RTC����
 * @param  NewState     ״̬
 * @retval None
 */
void RCC_Operate::RCC_Config(RTC_TypeDef *RTCx, FunctionalState NewState)
{
  assert_param(IS_FUNCTIONAL_STATE(NewState));
  RCC_RTCCLKCmd(NewState);
}

/**
 * @brief  RCC_Operate-ADCӳ��RCCʱ�ӷ���
 * @param  ADCX         �û������ADC
 * @retval ���������ȷ,�򷵻�RCC_APB2Periph_ADCX,���򷵻�0��
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
 * @brief  RCC_Operate-AFIOӳ��RCCʱ�ӷ���
 * @param  AFIOX        �û������AFIO
 * @retval ����RCC_APB2Periph_AFIO��
 */
uint32_t RCC_Operate::AFIO_Convert_RCC(AFIO_TypeDef *AFIOX)
{
  return RCC_APB2Periph_AFIO;
}

/**
 * @brief  RCC_Operate-BKPӳ��RCCʱ�ӷ���
 * @param  BKPX         �û������BKP
 * @retval ����RCC_APB1Periph_BKP��
 */
uint32_t RCC_Operate::BKP_Convert_RCC(BKP_TypeDef *BKPX)
{
  return RCC_APB1Periph_BKP;
}

/**
 * @brief  RCC_Operate-CANӳ��RCCʱ�ӷ���
 * @param  CANX         �û������CAN
 * @retval ���������ȷ,�򷵻�RCC_APB1Periph_CANX,���򷵻�0��
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
 * @brief  RCC_Operate-CRCӳ��RCCʱ�ӷ���
 * @param  CRCX         �û������CRC
 * @retval ����RCC_AHBPeriph_CRC��
 */
uint32_t RCC_Operate::CRC_Convert_RCC(CRC_TypeDef *CRCX)
{
  return RCC_AHBPeriph_CRC;
}

/**
 * @brief  RCC_Operate-DACӳ��RCCʱ�ӷ���
 * @param  DACX         �û������DAC
 * @retval ����RCC_APB1Periph_DAC��
 */
uint32_t RCC_Operate::DAC_Convert_RCC(DAC_TypeDef *DACX)
{
  return RCC_APB1Periph_DAC;
}

/**
 * @brief  RCC_Operate-DMAӳ��RCCʱ�ӷ���
 * @param  DMAX         �û������DMA
 * @retval ���������ȷ,�򷵻�RCC_AHBPeriph_DMAX,���򷵻�0��
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
 * @brief  RCC_Operate-FLITFӳ��RCCʱ�ӷ���
 * @param  FLITFX       �û������FLITF
 * @retval ����RCC_AHBPeriph_FLITF��
 */
uint32_t RCC_Operate::FLITF_Convert_RCC(FLITF_TypeDef *FLITFX)
{
  return RCC_AHBPeriph_FLITF;
}

/**
 * @brief  RCC_Operate-FSMC_Bank1ӳ��RCCʱ�ӷ���
 * @param  FSMC_Bank1X  �û������FSMC_Bank1
 * @retval ����RRCC_AHBPeriph_FSMC��
 */
uint32_t RCC_Operate::FSMC_Bank1_Convert_RCC(FSMC_Bank1_TypeDef *FSMC_Bank1X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank2ӳ��RCCʱ�ӷ���
 * @param  FSMC_Bank2X  �û������FSMC_Bank2
 * @retval ����RCC_AHBPeriph_FSMC��
 */
uint32_t RCC_Operate::FSMC_Bank2_Convert_RCC(FSMC_Bank2_TypeDef *FSMC_Bank2X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank3ӳ��RCCʱ�ӷ���
 * @param  FSMC_Bank3X  �û������FSMC_Bank3
 * @retval ����RCC_AHBPeriph_FSMC��
 */
uint32_t RCC_Operate::FSMC_Bank3_Convert_RCC(FSMC_Bank3_TypeDef *FSMC_Bank3X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank4ӳ��RCCʱ�ӷ���
 * @param  FSMC_Bank4X  �û������FSMC_Bank4
 * @retval ����RCC_AHBPeriph_FSMC��
 */
uint32_t RCC_Operate::FSMC_Bank4_Convert_RCC(FSMC_Bank4_TypeDef *FSMC_Bank4X)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-FSMC_Bank1Eӳ��RCCʱ�ӷ���
 * @param  FSMC_Bank1EX �û������FSMC_Bank1E
 * @retval ����RCC_AHBPeriph_FSMC��
 */
uint32_t RCC_Operate::FSMC_Bank1E_Convert_RCC(FSMC_Bank1E_TypeDef *FSMC_Bank1EX)
{
  return RCC_AHBPeriph_FSMC;
}

/**
 * @brief  RCC_Operate-GPIOӳ��RCCʱ�ӷ���
 * @param  GPIOX        �û������GPIO
 * @retval ���������ȷ,�򷵻�RCC_APB2Periph_GPIOX,���򷵻�0��
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
 * @brief  RCC_Operate-I2Cӳ��RCCʱ�ӷ���
 * @param  I2CX         �û������I2C
 * @retval ���������ȷ,�򷵻�RCC_APB1Periph_I2CX,���򷵻�0��
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
 * @brief  RCC_Operate-PWRӳ��RCCʱ�ӷ���
 * @param  PWRX         �û������PWR
 * @retval ����RCC_APB1Periph_PWR��
 */
uint32_t RCC_Operate::PWRX_Convert_RCC(PWR_TypeDef *PWRX)
{
  return RCC_APB1Periph_PWR;
}

/**
 * @brief  RCC_Operate-SDIOӳ��RCCʱ�ӷ���
 * @param  SDIOX        �û������SDIO
 * @retval ����RCC_AHBPeriph_SDIO��
 */
uint32_t RCC_Operate::SDIOX_Convert_RCC(SDIO_TypeDef *SDIOX)
{
  return RCC_AHBPeriph_SDIO;
}

/**
 * @brief  RCC_Operate-SPIӳ��RCCʱ�ӷ���
 * @param  SPIX         �û������SPI
 * @retval ���������ȷ,�򷵻�RCC_APB1Periph_SPIX|RCC_APB2Periph_SPIX���򷵻�0��
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
 * @brief  RCC_Operate-SRAMӳ��RCCʱ�ӷ���
 * @param  SRAMX        �û������SRAM
 * @retval ����RCC_AHBPeriph_SRAM��
 */
uint32_t RCC_Operate::SRAMX_Convert_RCC(SRAM_TypeDef *SRAMX)
{
  return RCC_AHBPeriph_SRAM;
}

/**
 * @brief  RCC_Operate-TIMӳ��RCCʱ�ӷ���
 * @param  TIMX         �û������TIM
 * @retval ���������ȷ,�򷵻�RCC_APB1Periph_TIMX|RCC_APB2Periph_TIMX,���򷵻�0��
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
 * @brief  RCC_Operate-USARTӳ��RCCʱ�ӷ���
 * @param  USARTX       �û������USART
 * @retval ���������ȷ,�򷵻�RCC_APB2Periph_USARTX|RCC_APB1Periph_USARTX,���򷵻�0��
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
 * @brief  RCC_Operate-USBӳ��RCCʱ�ӷ���
 * @param  USBX         �û������USB
 * @retval ����RCC_APB1Periph_USB��
 */
uint32_t RCC_Operate::USBX_Convert_RCC(USB_TypeDef *USBX)
{
  return RCC_APB1Periph_USB;
}

/**
 * @brief  RCC_Operate-WWDGӳ��RCCʱ�ӷ���
 * @param  WWDGX        �û������WWDG
 * @retval ����RCC_APB1Periph_WWDG��
 */
uint32_t RCC_Operate::WWDGX_Convert_RCC(WWDG_TypeDef *WWDGX)
{
  return RCC_APB1Periph_WWDG;
}
