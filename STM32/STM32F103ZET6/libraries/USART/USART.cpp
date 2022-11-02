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
 * @brief  USART-发送字节
 * @param  data             数据
 * @retval None
 */
void USART::Send_Data(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  // 这个地方一定要同时使用,为了防止串口发送第一个数据时丢失以及最后一个数据时间不够丢失。
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
 * @brief  USART-使用DMA单次发送字节
 * @param  data             数据(UART5无法使用)
 * @retval None
 */
void USART::Send_Data_DMA(uint8_t data)
{
  if (USARTx_Param.USARTx != UART5)
  {
    // 申请堆栈存储消息
    uint8_t *ptr = new uint8_t;
    *ptr = data;
    // 插入队列
    USART_DMA_Data_Queue.push(ptr);
    
    DMACmd(USART_DMA_TX, ENABLE);
    DMA(USART_TX_DMA_Param).Init();
  }
}

/**
 * @brief  USART-使用DMA单次发送字符数组
 * @param  buffer           字符数组
 * @param  cnt              字符数组大小
 * @retval None
 */
void USART::Send_Buffer_DMA(uint8_t *buffer, uint32_t cnt)
{
  if (USARTx_Param.USARTx != UART5)
  {

    // 配置DMA
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
 * @brief  USART-使用DMA单次发送字符串
 * @param  str              字符串
 * @retval None
 */
void USART::Send_String_DMA(const char *str)
{
  if (USARTx_Param.USARTx != UART5)
  {
    // 将内存置空,释放内存,同时重定向

    // 复制str
    uint32_t cnt;
    for (cnt = 0; cnt < tmp.length(); cnt++)
    {
      USART_DMA_Data_ptr.get()[cnt] = str[cnt];
    }
    // 配置DMA
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
  // 开启USART时钟
  RCC_Enable();
  // USARTx寄存器复位
  USART_DeInit(USARTx_Param.USARTx);
  // 引脚初始化
  Pin_Init();
  // 配置串口
  USART_Init(USARTx_Param.USARTx, &USARTx_Param.USART_InitStructure);
  // 配置时钟
  USART_ClockInit(USARTx_Param.USARTx, &USARTx_Param.USART_ClockInitStructure);
  // 配置串口中断
  ITConfig(USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  // 配置DMA
  DMACmd(USARTx_Param.USART_DMA_enum, USARTx_Param.USART_DMA_State);
  // 使能串口
  Enable();
}

/**
 * @brief  USART-中断方法
 * @param  USART_IT         中断标志的选择
 * @param  NewState         使能或失能
 * @retval None
 */
void USART::ITConfig(uint16_t USART_IT, FunctionalState NewState)
{
  // 配置串口中断优先级
  USARTx_Param.USART_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Operate(USARTx_Param.USART_NVIC_InitStructure).Init();
  USART_ITConfig(USARTx_Param.USARTx, USART_IT, NewState);
}

/**
 * @brief  USART-使用DMA传输功能(UART5不支持)
 * @param  USART_DMA_enum   使用DMA传输的引脚
 * @param  NewState         是否使能DMA
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
 * @brief  USART-开启USART方法(USART使能)
 * @param  None
 * @retval None
 */
void USART::Enable()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-关闭USART方法(USART失能)
 * @param  None
 * @retval None
 */
void USART::Disable()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}

/**
 * @brief  USART-开启USART时钟方法
 * @param  None
 * @retval None
 */
void USART::RCC_Enable()
{
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, ENABLE);
}

/**
 * @brief  USART-关闭USART时钟方法
 * @param  None
 * @retval None
 */
void USART::RCC_Disable()
{
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, DISABLE);
}

/**
 * @brief  USART-开启USART时钟方法
 * @param  USARTx     USARTx
 * @retval None
 */
void USART::RCC_Enable(USART_TypeDef *USARTx)
{
  RCC_Operate::RCC_Config(USARTx, ENABLE);
}

/**
 * @brief  USART-关闭USART时钟方法
 * @param  USARTx     USARTx
 * @retval None
 */
void USART::RCC_Disable(USART_TypeDef *USARTx)
{
  RCC_Operate::RCC_Config(USARTx, DISABLE);
}

/**
 * @brief  USART-获取DR寄存器的地址
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
 * @brief  USART-获取USART对应的DMA通道
 * @param  USARTx             USARTx
 * @param  USART_DMA_enum     USART_DMA_enum枚举
 * @retval USART对应的DMA通道
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