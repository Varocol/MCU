#include "USART.h"
/**
 * @brief  USART-�չ��췽��
 * @param  None
 * @retval None
 */
USART::USART()
{
}

/**
 * @brief  USART-��������
 * @param  None
 * @retval None
 */
USART::~USART()
{
}

/**
 * @brief  USART-���췽��
 * @param  USARTx_Param     USART�Ĳ����б�
 * @retval None
 */
USART::USART(USART_Param USARTx_Param)
{
  Set_USART_Param(USARTx_Param);
}

/**
 * @brief  USART-����USART�Ĳ����б�
 * @param  USARTx_Param     USART�Ĳ����б�
 * @retval None
 */
void USART::Set_USART_Param(USART_Param USARTx_Param)
{
  this->USARTx_Param = USARTx_Param;
  this->USART_TX_DMA_Param.DMA_Channelx = Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX);
  this->USART_TX_DMA_Param.DMA_InitStructure.DMA_PeripheralBaseAddr = Get_DR_ADDR(USARTx_Param.USARTx);
  this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannel = DMA::Get_DMAx_Channelx_IRQn(Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX));
  this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  if (this->USARTx_Param.USARTx == USART1)
  {
    this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
  }
  else if (this->USARTx_Param.USARTx == USART2)
  {
    this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;
  }
  else if (this->USARTx_Param.USARTx == USART3)
  {
    this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13;
  }
  else if (this->USARTx_Param.USARTx == UART4)
  {
    this->USART_TX_DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 12;
  }
}

/**
 * @brief  USART-�����ֽ�
 * @param  data             ����
 * @retval None
 */
void USART::Send_Data(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  // ����ط�һ��Ҫͬʱʹ��,Ϊ�˷�ֹ���ڷ��͵�һ������ʱ��ʧ�Լ����һ������ʱ�䲻����ʧ��
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TXE) == RESET)
    ;
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TC) == RESET)
    ;
}

/**
 * @brief  USART-�����ַ�����
 * @param  buffer           �ַ�����
 * @param  cnt              �ַ������С
 * @retval None
 */
void USART::Send_Buffer(uint8_t *buffer, uint32_t cnt)
{
  for (uint32_t i = 0; i < cnt; i++)
  {
    Send_Data(buffer[i]);
  }
}

/**
 * @brief  USART-�����ַ���
 * @param  str              �ַ���
 * @retval None
 */
void USART::Send_String(const char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    Send_Data(str[i]);
  }
}

/**
 * @brief  USART-ʹ��DMA���η����ֽ�
 * @param  data             ����(UART5�޷�ʹ��)
 * @retval None
 */
void USART::Send_Data_DMA(uint8_t data)
{
  if (USARTx_Param.USARTx != UART5)
  {
    // �����ջ�洢��Ϣ
    uint8_t *ptr = new uint8_t;
    *ptr = data;
    // �������
    USART_DMA_Data_Queue.push(ptr);
    
    DMACmd(USART_DMA_TX, ENABLE);
    DMA(USART_TX_DMA_Param).Init();
  }
}

/**
 * @brief  USART-ʹ��DMA���η����ַ�����
 * @param  buffer           �ַ�����
 * @param  cnt              �ַ������С
 * @retval None
 */
void USART::Send_Buffer_DMA(uint8_t *buffer, uint32_t cnt)
{
  if (USARTx_Param.USARTx != UART5)
  {

    // ����DMA
    DMA_InitTypeDef USART_TX_DMA_InitStructure = {
        .DMA_PeripheralBaseAddr = Get_DR_ADDR(USARTx_Param.USARTx),
        .DMA_MemoryBaseAddr = (uint32_t)USART_DMA_Data_ptr.get(),
        .DMA_DIR = DMA_DIR_PeripheralDST,
        .DMA_BufferSize = cnt,
        .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
        .DMA_MemoryInc = DMA_MemoryInc_Enable,
        .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
        .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
        .DMA_Mode = DMA_Mode_Normal,
        .DMA_Priority = DMA_Priority_High,
        .DMA_M2M = DMA_M2M_Disable};
    NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure = {
        .NVIC_IRQChannel = DMA::Get_DMAx_Channelx_IRQn(Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX)),
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 15,
        .NVIC_IRQChannelCmd = ENABLE};
    DMA_Param USART_TX_DMA_Param = {
        .DMA_Channelx = Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX),
        .DMA_InitStructure = USART_TX_DMA_InitStructure,
        .DMA_NVIC_InitStructure = USART_TX_DMA_NVIC_InitStructure,
        .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
        .DMA_IT_State = ENABLE};
    DMACmd(USART_DMA_TX, ENABLE);
    DMA(USART_TX_DMA_Param).Init();
  }
}

/**
 * @brief  USART-ʹ��DMA���η����ַ���
 * @param  str              �ַ���
 * @retval None
 */
void USART::Send_String_DMA(const char *str)
{
  if (USARTx_Param.USARTx != UART5)
  {
    // ���ڴ��ÿ�,�ͷ��ڴ�,ͬʱ�ض���

    // ����str
    uint32_t cnt;
    for (cnt = 0; cnt < tmp.length(); cnt++)
    {
      USART_DMA_Data_ptr.get()[cnt] = str[cnt];
    }
    // ����DMA
    DMA_InitTypeDef USART_TX_DMA_InitStructure = {
        .DMA_PeripheralBaseAddr = Get_DR_ADDR(USARTx_Param.USARTx),
        .DMA_MemoryBaseAddr = (uint32_t)USART_DMA_Data_ptr.get(),
        .DMA_DIR = DMA_DIR_PeripheralDST,
        .DMA_BufferSize = cnt,
        .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
        .DMA_MemoryInc = DMA_MemoryInc_Enable,
        .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
        .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
        .DMA_Mode = DMA_Mode_Normal,
        .DMA_Priority = DMA_Priority_High,
        .DMA_M2M = DMA_M2M_Disable};
    NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure = {
        .NVIC_IRQChannel = DMA::Get_DMAx_Channelx_IRQn(Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX)),
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 15,
        .NVIC_IRQChannelCmd = ENABLE};
    DMA_Param USART_TX_DMA_Param = {
        .DMA_Channelx = Get_DMA_Channel(USARTx_Param.USARTx, USART_DMA_TX),
        .DMA_InitStructure = USART_TX_DMA_InitStructure,
        .DMA_NVIC_InitStructure = USART_TX_DMA_NVIC_InitStructure,
        .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
        .DMA_IT_State = ENABLE};
    DMACmd(USART_DMA_TX, ENABLE);
    DMA(USART_TX_DMA_Param).Init();
  }
}

/**
 * @brief  USART-�����ֽ�
 * @param  None
 * @retval ���ջ�������ֵ
 */
uint8_t USART::Receive_Data()
{
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_RXNE) == RESET)
    ;
  return USART_ReceiveData(USARTx_Param.USARTx);
}

/**
 * @brief  USART-GPIO���ų�ʼ��
 * @param  None
 * @retval None
 */
void USART::Pin_Init()
{
  PIN_enum USART_RX_Pin;
  PIN_enum USART_TX_Pin;
  RCC_Operate::RCC_Config(AFIO, ENABLE);
  switch (USARTx_Param.USARTx_Pin_Remap)
  {
  case USART1_Default:
  {
    USART_RX_Pin = PA10;
    USART_TX_Pin = PA9;
  }
  break;
  case USART1_Remap:
  {
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
    USART_RX_Pin = PB7;
    USART_TX_Pin = PB6;
  }
  break;
  case USART2_Default:
  {
    USART_RX_Pin = PA3;
    USART_TX_Pin = PA2;
  }
  break;
  case USART2_Remap:
  {
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
    USART_RX_Pin = PD6;
    USART_TX_Pin = PD5;
  }
  break;
  case USART3_Default:
  {
    USART_RX_Pin = PB11;
    USART_TX_Pin = PB10;
  }
  break;
  case USART3_PartialRemap:
  {
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
    USART_RX_Pin = PC11;
    USART_TX_Pin = PC10;
  }
  break;
  case USART3_FullRemap:
  {
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
    USART_RX_Pin = PD9;
    USART_TX_Pin = PD8;
  }
  break;
  case UART4_Default:
  {
    USART_RX_Pin = PC11;
    USART_TX_Pin = PC10;
  }
  break;
  case UART5_Default:
  {
    USART_RX_Pin = PD2;
    USART_TX_Pin = PC12;
  }
  break;
  }
  GPIO USART_RX = GPIO(USART_RX_Pin, GPIO_Mode_IN_FLOATING);
  GPIO USART_TX = GPIO(USART_TX_Pin, GPIO_Mode_AF_PP);
  USART_RX.Init();
  USART_TX.Init();
}

/**
 * @brief  USART-�����б����
 * @param  USARTx_Param     USART�Ĳ����б�
 * @retval None
 */
void USART::Update(USART_Param USARTx_Param)
{
  USART_DeInit(this->USARTx_Param.USARTx);
  Set_USART_Param(USARTx_Param);
  Init();
}

/**
 * @brief  USART-��ʼ������
 * @param  None
 * @retval None
 */
void USART::Init()
{
  // ����USARTʱ��
  RCC_Enable();
  // USARTx�Ĵ�����λ
  USART_DeInit(USARTx_Param.USARTx);
  // ���ų�ʼ��
  Pin_Init();
  // ���ô���
  USART_Init(USARTx_Param.USARTx, &USARTx_Param.USART_InitStructure);
  // ����ʱ��
  USART_ClockInit(USARTx_Param.USARTx, &USARTx_Param.USART_ClockInitStructure);
  // ���ô����ж�
  ITConfig(USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  // ����DMA
  DMACmd(USARTx_Param.USART_DMA_enum, USARTx_Param.USART_DMA_State);
  // ʹ�ܴ���
  Enable();
}

/**
 * @brief  USART-�жϷ���
 * @param  USART_IT         �жϱ�־��ѡ��
 * @param  NewState         ʹ�ܻ�ʧ��
 * @retval None
 */
void USART::ITConfig(uint16_t USART_IT, FunctionalState NewState)
{
  // ���ô����ж����ȼ�
  USARTx_Param.USART_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Operate(USARTx_Param.USART_NVIC_InitStructure).Init();
  USART_ITConfig(USARTx_Param.USARTx, USART_IT, NewState);
}

/**
 * @brief  USART-ʹ��DMA���书��(UART5��֧��)
 * @param  USART_DMA_enum   ʹ��DMA���������
 * @param  NewState         �Ƿ�ʹ��DMA
 * @retval None
 */
void USART::DMACmd(USART_DMA_enum USART_DMA_enum, FunctionalState NewState)
{
  if (USARTx_Param.USARTx != UART5)
  {
    switch (USART_DMA_enum)
    {
    case USART_DMA_TX:
      USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Tx, NewState);
      break;
    case USART_DMA_RX:
      USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Rx, NewState);
      break;
    case USART_DMA_BOTH:
      USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Tx | USART_DMAReq_Rx, NewState);
      break;
    }
  }
}

/**
 * @brief  USART-����USART����(USARTʹ��)
 * @param  None
 * @retval None
 */
void USART::Enable()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-�ر�USART����(USARTʧ��)
 * @param  None
 * @retval None
 */
void USART::Disable()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}

/**
 * @brief  USART-����USARTʱ�ӷ���
 * @param  None
 * @retval None
 */
void USART::RCC_Enable()
{
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-�ر�USARTʱ�ӷ���
 * @param  None
 * @retval None
 */
void USART::RCC_Disable()
{
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, DISABLE);
}

/**
 * @brief  USART-����USARTʱ�ӷ���
 * @param  USARTx     USARTx
 * @retval None
 */
void USART::RCC_Enable(USART_TypeDef *USARTx)
{
  RCC_Operate::RCC_Config(USARTx, ENABLE);
}

/**
 * @brief  USART-�ر�USARTʱ�ӷ���
 * @param  USARTx     USARTx
 * @retval None
 */
void USART::RCC_Disable(USART_TypeDef *USARTx)
{
  RCC_Operate::RCC_Config(USARTx, DISABLE);
}

/**
 * @brief  USART-��ȡDR�Ĵ����ĵ�ַ
 * @param  USARTx     USARTx
 * @retval USARTx_Base + 0x04
 */
uint32_t USART::Get_DR_ADDR(USART_TypeDef *USARTx)
{
  if (USARTx == USART1)
  {
    return USART1_BASE + 0x04;
  }
  else if (USARTx == USART2)
  {
    return USART2_BASE + 0x04;
  }
  else if (USARTx == USART3)
  {
    return USART3_BASE + 0x04;
  }
  else if (USARTx == UART4)
  {
    return UART4_BASE + 0x04;
  }
  else if (USARTx == UART5)
  {
    return UART5_BASE + 0x04;
  }
  return 0;
}

/**
 * @brief  USART-��ȡUSART��Ӧ��DMAͨ��
 * @param  USARTx             USARTx
 * @param  USART_DMA_enum     USART_DMA_enumö��
 * @retval USART��Ӧ��DMAͨ��
 */
DMA_Channel_TypeDef *USART::Get_DMA_Channel(USART_TypeDef *USARTx, USART_DMA_enum USART_DMA)
{
  if (USARTx == USART1)
  {
    if (USART_DMA == USART_DMA_TX || USART_DMA == USART_DMA_BOTH)
    {
      return DMA::Get_DMA_Channel(DMA_USART1_TX);
    }
    else if (USART_DMA == USART_DMA_RX)
    {
      return DMA::Get_DMA_Channel(DMA_USART1_RX);
    }
  }
  else if (USARTx == USART2)
  {
    if (USART_DMA == USART_DMA_TX || USART_DMA == USART_DMA_BOTH)
    {
      return DMA::Get_DMA_Channel(DMA_USART2_TX);
    }
    else if (USART_DMA == USART_DMA_RX)
    {
      return DMA::Get_DMA_Channel(DMA_USART2_RX);
    }
  }
  else if (USARTx == USART3)
  {
    if (USART_DMA == USART_DMA_TX || USART_DMA == USART_DMA_BOTH)
    {
      return DMA::Get_DMA_Channel(DMA_USART3_TX);
    }
    else if (USART_DMA == USART_DMA_RX)
    {
      return DMA::Get_DMA_Channel(DMA_USART3_RX);
    }
  }
  else if (USARTx == UART4)
  {
    if (USART_DMA == USART_DMA_TX || USART_DMA == USART_DMA_BOTH)
    {
      return DMA::Get_DMA_Channel(DMA_UART4_TX);
    }
    else if (USART_DMA == USART_DMA_RX)
    {
      return DMA::Get_DMA_Channel(DMA_UART4_RX);
    }
  }
  return 0;
}