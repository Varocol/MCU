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
}

/**
 * @brief  USART-�����ֽ�
 * @param  data             ����
 * @retval None
 */
void USART::Send_Data(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  //����ط�һ��Ҫͬʱʹ��,Ϊ�˷�ֹ���ڷ��͵�һ������ʱ��ʧ�Լ����һ������ʱ�䲻����ʧ��
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
  //����USARTʱ��
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, ENABLE);
  // USARTx�Ĵ�����λ
  USART_DeInit(USARTx_Param.USARTx);
  //���ų�ʼ��
  Pin_Init();
  //���ô���
  USART_Init(USARTx_Param.USARTx, &USARTx_Param.USART_InitStructure);
  //����ʱ��
  USART_ClockInit(USARTx_Param.USARTx, &USARTx_Param.USART_ClockInitStructure);
  //���ô����ж����ȼ�
  USARTx_Param.USART_NVIC_Operate.Init();
  //���ô����ж�
  ITConfig(USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  //ʹ�ܴ���
  Start();
}

/**
 * @brief  USART-�жϷ���
 * @param  USART_IT         �жϱ�־��ѡ��
 * @param  NewState         ʹ�ܻ�ʧ��
 * @retval None
 */
void USART::ITConfig(uint16_t USART_IT, FunctionalState NewState)
{
  USART_ITConfig(USARTx_Param.USARTx, USART_IT, NewState);
}

/**
 * @brief  USART-ʹ��DMA���书��
 * @param  USART_DMA_enum   ʹ��DMA���������
 * @param  state            �Ƿ�ʹ��DMA
 * @retval None
 */
void USART::Use_DMA(USART_DMA_enum USART_DMA_enum, FunctionalState state)
{
  switch (USART_DMA_enum)
  {
  case USART_DMA_TX:
    USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Tx, state);
    break;
  case USART_DMA_RX:
    USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Rx, state);
    break;
  case USART_DMA_BOTH:
    USART_DMACmd(USARTx_Param.USARTx, USART_DMAReq_Tx | USART_DMAReq_Rx, state);
    break;
  }
}

/**
 * @brief  USART-����USART����(USARTʹ��)
 * @param  None
 * @retval None
 */
void USART::Start()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-�ر�USART����(USARTʧ��)
 * @param  None
 * @retval None
 */
void USART::ShutUp()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}
