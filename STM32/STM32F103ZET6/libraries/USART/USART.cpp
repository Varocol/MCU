#include "USART.h"
// USART_Default USART1_RX = PA10
GPIO_InitTypeDef U1_RX_Pin_1 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART_Default USART1_TX = PA9
GPIO_InitTypeDef U1_TX_Pin_1 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART1_Remap USART1_RX = PB7
GPIO_InitTypeDef U1_RX_Pin_2 =
    {
        GPIO_Pin_7,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART1_Remap USART1_TX = PB6
GPIO_InitTypeDef U1_TX_Pin_2 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART2_Default USART2_RX = PA3
GPIO_InitTypeDef U2_RX_Pin_1 =
    {
        GPIO_Pin_3,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART2_Default USART2_TX = PA2
GPIO_InitTypeDef U2_TX_Pin_1 =
    {
        GPIO_Pin_2,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART2_Remap USART2_RX = PD6
GPIO_InitTypeDef U2_RX_Pin_2 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART2_Remap USART2_TX = PD5
GPIO_InitTypeDef U2_TX_Pin_2 =
    {
        GPIO_Pin_5,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART3_Default USART3_RX = PB11
GPIO_InitTypeDef U3_RX_Pin_1 =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART3_Default USART3_TX = PB10
GPIO_InitTypeDef U3_TX_Pin_1 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART3_PartialRemap USART3_RX = PC11
GPIO_InitTypeDef U3_RX_Pin_2 =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART3_PartialRemap USART3_TX = PC10
GPIO_InitTypeDef U3_TX_Pin_2 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// USART3_FullRemap USART3_RX = PD9
GPIO_InitTypeDef U3_RX_Pin_3 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// USART3_FullRemap USART3_TX = PD8
GPIO_InitTypeDef U3_TX_Pin_3 =
    {
        GPIO_Pin_8,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// UART4_Default UART4_RX = PC11
GPIO_InitTypeDef U4_RX_Pin =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// UART4_Default UART4_TX = PC10
GPIO_InitTypeDef U4_TX_Pin =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

// UART5_Default UART4_RX = PD2
GPIO_InitTypeDef U5_RX_Pin =
    {
        GPIO_Pin_2,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

// UART5_Default UART4_TX = PC12
GPIO_InitTypeDef U5_TX_Pin =
    {
        GPIO_Pin_12,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};
/**
 * @brief  USART�չ��췽��
 * @param  None
 * @retval None
 */
USART::USART()
{
}

/**
 * @brief  USART��������
 * @param  None
 * @retval None
 */
USART::~USART()
{
}

/**
 * @brief  USART���췽��
 * @param  USARTx_Param:USART�Ĳ����б�
 * @retval None
 */
USART::USART(USART_Param USARTx_Param)
{
  Set_USART_Param(USARTx_Param);
}

/**
 * @brief  ����USART�Ĳ����б�
 * @param  USARTx_Param:USART�Ĳ����б�
 * @retval None
 */
void USART::Set_USART_Param(USART_Param USARTx_Param)
{
  this->USARTx_Param = USARTx_Param;
}

/**
 * @brief  USART�����ֽ�
 * @param  data:����
 * @retval None
 */
void USART::Send_Byte(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TXE) == RESET)
    ;
}

/**
 * @brief  USART�����ַ���l
 * @param  str:�ַ���
 * @retval None
 */
void USART::Send_String(uint8_t *str)
{
  for (int i = 0; str[i]; i++)
  {
    Send_Byte(str[i]);
  }
}

/**
 * @brief  USART�����ֽ�
 * @param  None
 * @retval None
 */
uint8_t USART::Receive_Byte()
{
  return USART_ReceiveData(USARTx_Param.USARTx);
}

/**
 * @brief  USART GPIO���ų�ʼ��
 * @param  None
 * @retval None
 */
void USART::Pin_Init()
{
  if (USARTx_Param.USARTx_Pin_Remap_Selection == USART_Default)
  {
    if (USARTx_Param.USARTx == USART1)
    {
      GPIO *USART1_RX_1 = new GPIO(GPIOA, U1_RX_Pin_1);
      USART1_RX_1->Init();
      delete USART1_RX_1;
      GPIO *USART1_TX_1 = new GPIO(GPIOA, U1_TX_Pin_1);
      USART1_TX_1->Init();
      delete USART1_TX_1;
    }
    else if (USARTx_Param.USARTx == USART2)
    {
      GPIO *USART2_RX_1 = new GPIO(GPIOA, U2_RX_Pin_1);
      USART2_RX_1->Init();
      delete USART2_RX_1;
      GPIO *USART2_TX_1 = new GPIO(GPIOA, U2_TX_Pin_1);
      USART2_TX_1->Init();
      delete USART2_TX_1;
    }
    else if (USARTx_Param.USARTx == USART3)
    {
      GPIO *USART3_RX_1 = new GPIO(GPIOB, U3_RX_Pin_1);
      USART3_RX_1->Init();
      delete USART3_RX_1;
      GPIO *USART3_TX_1 = new GPIO(GPIOB, U3_TX_Pin_1);
      USART3_TX_1->Init();
      delete USART3_TX_1;
    }
    else if (USARTx_Param.USARTx == UART4)
    {
      GPIO *UART4_RX = new GPIO(GPIOC, U4_RX_Pin);
      UART4_RX->Init();
      delete UART4_RX;
      GPIO *UART4_TX = new GPIO(GPIOC, U4_TX_Pin);
      UART4_TX->Init();
      delete UART4_TX;
    }
    else if (USARTx_Param.USARTx == UART5)
    {
      GPIO *UART5_RX = new GPIO(GPIOD, U5_RX_Pin);
      UART5_RX->Init();
      delete UART5_RX;
      GPIO *UART5_TX = new GPIO(GPIOC, U5_TX_Pin);
      UART5_TX->Init();
      delete UART5_TX;
    }
    return;
  }
  RCC_Operate::RCC_Config(AFIO, ENABLE);

  if (USARTx_Param.USARTx_Pin_Remap_Selection == USART1_Remap)
  {
    GPIO *USART1_RX_2 = new GPIO(GPIOB, U1_RX_Pin_2);
    USART1_RX_2->Init();
    delete USART1_RX_2;
    GPIO *USART1_TX_2 = new GPIO(GPIOB, U1_TX_Pin_2);
    USART1_TX_2->Init();
    delete USART1_TX_2;
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);
  }
  else if (USARTx_Param.USARTx_Pin_Remap_Selection == USART2_Remap)
  {
    GPIO *USART2_RX_2 = new GPIO(GPIOD, U2_RX_Pin_2);
    USART2_RX_2->Init();
    delete USART2_RX_2;
    GPIO *USART2_TX_2 = new GPIO(GPIOD, U2_TX_Pin_2);
    USART2_TX_2->Init();
    delete USART2_TX_2;
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);
  }
  else if (USARTx_Param.USARTx_Pin_Remap_Selection == USART3_PartialRemap)
  {
    GPIO *USART3_RX_2 = new GPIO(GPIOC, U3_RX_Pin_2);
    USART3_RX_2->Init();
    delete USART3_RX_2;
    GPIO *USART3_TX_2 = new GPIO(GPIOC, U3_TX_Pin_2);
    USART3_TX_2->Init();
    delete USART3_TX_2;
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
  }
  else if (USARTx_Param.USARTx_Pin_Remap_Selection == USART3_FullRemap)
  {
    GPIO *USART3_RX_3 = new GPIO(GPIOD, U3_RX_Pin_3);
    USART3_RX_3->Init();
    delete USART3_RX_3;
    GPIO *USART3_TX_3 = new GPIO(GPIOD, U3_TX_Pin_3);
    USART3_TX_3->Init();
    delete USART3_TX_3;
    GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);
  }
}

/**
 * @brief  USART�����б����
 * @param  USARTx_Param:USART�Ĳ����б�
 * @retval None
 */
void USART::Update(USART_Param USARTx_Param)
{
  USART_DeInit(this->USARTx_Param.USARTx);
  Set_USART_Param(USARTx_Param);
  Init();
}

/**
 * @brief  USART ��ʼ������
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
  //���ô����ж����ȼ�
  USARTx_Param.USART_NVIC_Operate.Init();
  //���ô����ж�
  USART_ITConfig(USARTx_Param.USARTx, USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  //ʹ�ܴ���
  Start();
}

/**
 * @brief  ʹ��DMA���书��
 * @param  USART_DMA_Selection:ʹ��DMA���������
 * @param  state:�Ƿ�ʹ��DMA
 * @retval None
 */
void USART::Use_DMA(USART_DMA_Selection USART_DMA_Selection, FunctionalState state)
{
  switch (USART_DMA_Selection)
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
 * @brief  ����USART����(USARTʹ��)
 * @param  None
 * @retval None
 */
void USART::Start()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  �ر�USART����(USARTʧ��)
 * @param  None
 * @retval None
 */
void USART::ShutUp()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}
