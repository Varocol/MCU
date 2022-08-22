#include "USART.h"
/**
 * @brief  USART-空构造方法
 * @param  None
 * @retval None
 */
USART::USART()
{
}

/**
 * @brief  USART-析构方法
 * @param  None
 * @retval None
 */
USART::~USART()
{
}

/**
 * @brief  USART-构造方法
 * @param  USARTx_Param     USART的参数列表
 * @retval None
 */
USART::USART(USART_Param USARTx_Param)
{
  Set_USART_Param(USARTx_Param);
}

/**
 * @brief  USART-设置USART的参数列表
 * @param  USARTx_Param     USART的参数列表
 * @retval None
 */
void USART::Set_USART_Param(USART_Param USARTx_Param)
{
  this->USARTx_Param = USARTx_Param;
}

/**
 * @brief  USART-发送字节
 * @param  data             数据
 * @retval None
 */
void USART::Send_Data(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  //这个地方一定要同时使用,为了防止串口发送第一个数据时丢失以及最后一个数据时间不够丢失。
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TXE) == RESET)
    ;
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TC) == RESET)
    ;
}

/**
 * @brief  USART-发送字符数组
 * @param  buffer           字符数组
 * @param  cnt              字符数组大小
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
 * @brief  USART-发送字符串
 * @param  str              字符串
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
 * @brief  USART-接收字节
 * @param  None
 * @retval 接收缓冲器的值
 */
uint8_t USART::Receive_Data()
{
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_RXNE) == RESET)
    ;
  return USART_ReceiveData(USARTx_Param.USARTx);
}

/**
 * @brief  USART-GPIO引脚初始化
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
 * @brief  USART-参数列表更新
 * @param  USARTx_Param     USART的参数列表
 * @retval None
 */
void USART::Update(USART_Param USARTx_Param)
{
  USART_DeInit(this->USARTx_Param.USARTx);
  Set_USART_Param(USARTx_Param);
  Init();
}

/**
 * @brief  USART-初始化方法
 * @param  None
 * @retval None
 */
void USART::Init()
{
  //开启USART时钟
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, ENABLE);
  // USARTx寄存器复位
  USART_DeInit(USARTx_Param.USARTx);
  //引脚初始化
  Pin_Init();
  //配置串口
  USART_Init(USARTx_Param.USARTx, &USARTx_Param.USART_InitStructure);
  //配置时钟
  USART_ClockInit(USARTx_Param.USARTx, &USARTx_Param.USART_ClockInitStructure);
  //配置串口中断优先级
  USARTx_Param.USART_NVIC_Operate.Init();
  //配置串口中断
  ITConfig(USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  //使能串口
  Start();
}

/**
 * @brief  USART-中断方法
 * @param  USART_IT         中断标志的选择
 * @param  NewState         使能或失能
 * @retval None
 */
void USART::ITConfig(uint16_t USART_IT, FunctionalState NewState)
{
  USART_ITConfig(USARTx_Param.USARTx, USART_IT, NewState);
}

/**
 * @brief  USART-使用DMA传输功能
 * @param  USART_DMA_enum   使用DMA传输的引脚
 * @param  state            是否使能DMA
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
 * @brief  USART-开启USART方法(USART使能)
 * @param  None
 * @retval None
 */
void USART::Start()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-关闭USART方法(USART失能)
 * @param  None
 * @retval None
 */
void USART::ShutUp()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}
