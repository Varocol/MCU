#include "USART.h"
#include "stdio.h"
// C++��static��̬��Ա��Ҫ�������ط���ʼ��,��ס��.h�ļ���֧�ָ�ֵ,���Բ�Ҫ��.h�ڳ�ʼ��

queue<vector<uint8_t>> USART::USART1_DMA_Data_Queue; // USART1��Ϣ����
queue<vector<uint8_t>> USART::USART2_DMA_Data_Queue; // USART2��Ϣ����
queue<vector<uint8_t>> USART::USART3_DMA_Data_Queue; // USART3��Ϣ����
queue<vector<uint8_t>> USART::UART4_DMA_Data_Queue;  // UART4 ��Ϣ����

// ����DMAĬ�����ò���
// USART1_DMA ͨ���ж������ȼ� 15
// USART2_DMA ͨ���ж������ȼ� 14
// USART3_DMA ͨ���ж������ȼ� 13
// UART4_DMA  ͨ���ж������ȼ� 12
DMA_InitTypeDef USART_TX_DMA_Default_InitStructure = {
    .DMA_PeripheralBaseAddr = NULL,
    .DMA_MemoryBaseAddr = NULL,
    .DMA_DIR = DMA_DIR_PeripheralDST,
    .DMA_BufferSize = NULL,
    .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Normal,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Disable};
NVIC_InitTypeDef USART_TX_DMA_Default_NVIC_InitStructure = {
    .NVIC_IRQChannel = NULL,
    .NVIC_IRQChannelPreemptionPriority = NULL,
    .NVIC_IRQChannelSubPriority = NULL,
    .NVIC_IRQChannelCmd = ENABLE};
DMA_Param USART_TX_DMA_Default_Param = {
    .DMA_Channelx = NULL,
    .DMA_InitStructure = USART_TX_DMA_Default_InitStructure,
    .DMA_NVIC_InitStructure = USART_TX_DMA_Default_NVIC_InitStructure,
    .DMA_IT_Selection = DMA_IT_TC | DMA_IT_TE, // DMA_IT_HT | DMA_IT_TC | DMA_IT_TE
    .DMA_IT_State = ENABLE};

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
    // ��ȡDMA��Ϣ����
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // ����DMA��Ϣ����
    Data_Queue->push(vector<uint8_t>{data});
    // ���DMAͨ���Ƿ��ڹ���
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // ������ڹ��������乤��
      DMA_Queue_Start(USARTx_Param.USARTx);
    }
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
    // ��ȡDMA��Ϣ����
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // ����DMA��Ϣ����
    Data_Queue->push(vector<uint8_t>(buffer, buffer + cnt));
    // ���DMAͨ���Ƿ��ڹ���
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // ������ڹ��������乤��
      DMA_Queue_Start(USARTx_Param.USARTx);
    }
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
    // ��ȡDMA��Ϣ����
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // ����DMA��Ϣ����
    Data_Queue->push(vector<uint8_t>(str, str + strlen(str)));
    printf("%d", strlen(str));
    // ���DMAͨ���Ƿ��ڹ���
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // ������ڹ��������乤��
      DMA_Queue_Start(USARTx_Param.USARTx);
    }
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
 * @brief  USART-����DMA�������
 * @param  None
 * @retval DMA�����Ƿ���ȷ
 */
bool USART::DMA_Config_Check(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  // ���USART��ӦDMA�Ƿ��ڿ���״̬
  bool flag1 = DMA::Check_DMAx_Channelx(Get_DMA_Channel(USARTx, USART_DMA_TX));
  // ���USART��ӦDMAͨ���������ַԴ�Ƿ���ȷ
  bool flag2 = Get_DMA_Channel(USARTx, USART_DMA_TX)->CPAR == Get_DR_ADDR(USARTx);
  // ���USART DMA_TXλ�Ƿ��
  bool flag3 = USARTx->CR3 & USART_DMAReq_Tx;
  return flag1 && flag2 && flag3;
}

/**
 * @brief  USART-����DMA��Ϣ����ֹͣ����
 * @param  None
 * @retval DMA�����Ƿ���ȷ
 */
void USART::DMA_Queue_Stop(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  // �ر�DMAλ
  USART_DMACmd(USARTx, USART_DMAReq_Tx, DISABLE);
  // �ر�DMAͨ��
  DMA_Cmd(Get_DMA_Channel(USARTx, USART_DMA_TX), DISABLE);
}

/**
 * @brief  USART-����DMA��Ϣ���п�ʼ����,ͬʱװ������
 * @param  None
 * @retval DMA�����Ƿ���ȷ
 */
void USART::DMA_Queue_Start(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // ������д���
  if (Data_Queue != nullptr)
  {
    // �������Ϊ��,����DMA��Ϣ����Ϊ����
    if (Data_Queue->empty())
    {
      DMA_Queue_Stop(USARTx);
    }
    // ��������DMA
    else
    {
      DMA_Setup(USARTx);
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

/**
 * @brief  USART-��ȡUSART��Ӧ��DMA��Ϣ����
 * @param  None
 * @retval USART��Ӧ��DMA��Ϣ����
 */
queue<vector<uint8_t>> *USART::Get_USART_DMA_Data_Queue(USART_TypeDef *USARTx)
{
  if (USARTx == USART1)
  {
    return &USART1_DMA_Data_Queue;
  }
  else if (USARTx == USART2)
  {
    return &USART2_DMA_Data_Queue;
  }
  else if (USARTx == USART3)
  {
    return &USART3_DMA_Data_Queue;
  }
  else if (USARTx == UART4)
  {
    return &UART4_DMA_Data_Queue;
  }
  return nullptr;
}

/**
 * @brief  USART-����DMA
 * @param  USARTx             USARTx
 * @retval None
 */
void USART::DMA_Setup(USART_TypeDef *USARTx)
{
  // ��ȡDMA��Ϣ����
  queue<vector<uint8_t>> *USART_DMA_Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // �����Ϣ���в����ڻ�����Ϣ����Ϊ���򷵻�
  if (USART_DMA_Data_Queue == nullptr || USART_DMA_Data_Queue->empty())
  {
    return;
  }
  DMA_Param DMA_Param = USART_TX_DMA_Default_Param;
  DMA_Param.DMA_Channelx = Get_DMA_Channel(USARTx, USART_DMA_TX);
  DMA_Param.DMA_InitStructure.DMA_PeripheralBaseAddr = Get_DR_ADDR(USARTx);
  DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannel = DMA::Get_DMAx_Channelx_IRQn(Get_DMA_Channel(USARTx, USART_DMA_TX));
  DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  if (USARTx == USART1)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
  }
  else if (USARTx == USART2)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 14;
  }
  else if (USARTx == USART3)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 13;
  }
  else if (USARTx == UART4)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 12;
  }
  DMA_Param.DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) & *(USART_DMA_Data_Queue->front().begin());
  DMA_Param.DMA_InitStructure.DMA_BufferSize = USART_DMA_Data_Queue->front().size();
  // ����DMAλ
  USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);
  // ��ʼ��DMA
  DMA(DMA_Param).Init();
}

/**
 * @brief  USART-�Ƴ������ѷ��͵�����
 * @param  USARTx             USARTx
 * @retval USART��Ӧ��DMA��Ϣ����
 */
void USART::DMA_Queue_Remove(USART_TypeDef *USARTx)
{
  // ��ȡDMA��Ϣ����
  queue<vector<uint8_t>> *USART_DMA_Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // �����Ϣ���в����ڻ�����Ϣ����Ϊ���򷵻�
  if (USART_DMA_Data_Queue == nullptr || USART_DMA_Data_Queue->empty())
  {
    return;
  }
  // �Ƴ�����Ԫ��
  USART_DMA_Data_Queue->pop();
}