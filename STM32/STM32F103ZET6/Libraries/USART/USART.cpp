#include "USART.h"
#include "stdio.h"
// C++的static静态成员需要在其他地方初始化,记住在.h文件不支持赋值,所以不要在.h内初始化

queue<vector<uint8_t>> USART::USART1_DMA_Data_Queue; // USART1消息队列
queue<vector<uint8_t>> USART::USART2_DMA_Data_Queue; // USART2消息队列
queue<vector<uint8_t>> USART::USART3_DMA_Data_Queue; // USART3消息队列
queue<vector<uint8_t>> USART::UART4_DMA_Data_Queue;  // UART4 消息队列

USART_DMA_Queue_Status USART1_DMA_Queue_Status = STOP; // USART1消息队列状态
USART_DMA_Queue_Status USART2_DMA_Queue_Status = STOP; // USART2消息队列状态
USART_DMA_Queue_Status USART3_DMA_Queue_Status = STOP; // USART3消息队列状态
USART_DMA_Queue_Status UART4_DMA_Queue_Status = STOP;  // UART4 消息队列状态

// 内置DMA默认配置参数
// USART1_DMA 通道中断子优先级 0
// USART2_DMA 通道中断子优先级 1
// USART3_DMA 通道中断子优先级 2
// UART4_DMA  通道中断子优先级 3

// 默认DMA初始化结构体(公用)
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

NVIC_InitTypeDef USART1_TX_DMA_Default_NVIC_InitStructure = {
    .NVIC_IRQChannel = DMA1_Channel4_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 0,
    .NVIC_IRQChannelCmd = ENABLE};
// NVIC_InitTypeDef USART1_TX_DMA_Default_NVIC_InitStructure = {
//     .NVIC_IRQChannel = DMA1_Channel4_IRQn,
//     .NVIC_IRQChannelPreemptionPriority = 0,
//     .NVIC_IRQChannelSubPriority = 0,
//     .NVIC_IRQChannelCmd = ENABLE};
// NVIC_InitTypeDef USART1_TX_DMA_Default_NVIC_InitStructure = {
//     .NVIC_IRQChannel = DMA1_Channel4_IRQn,
//     .NVIC_IRQChannelPreemptionPriority = 0,
//     .NVIC_IRQChannelSubPriority = 0,
//     .NVIC_IRQChannelCmd = ENABLE};
// NVIC_InitTypeDef USART1_TX_DMA_Default_NVIC_InitStructure = {
//     .NVIC_IRQChannel = DMA1_Channel4_IRQn,
//     .NVIC_IRQChannelPreemptionPriority = 0,
//     .NVIC_IRQChannelSubPriority = 0,
//     .NVIC_IRQChannelCmd = ENABLE};
// NVIC_InitTypeDef USART1_TX_DMA_Default_NVIC_InitStructure = {
//     .NVIC_IRQChannel = DMA1_Channel4_IRQn,
//     .NVIC_IRQChannelPreemptionPriority = 0,
//     .NVIC_IRQChannelSubPriority = 0,
//     .NVIC_IRQChannelCmd = ENABLE};

DMA_Param USART_TX_DMA_Default_Param = {
    .DMA_Channelx = NULL,
    .DMA_InitStructure = USART_TX_DMA_Default_InitStructure,
    .DMA_NVIC_InitStructure = USART1_TX_DMA_Default_NVIC_InitStructure,
    .DMA_IT_Selection = DMA_IT_TC | DMA_IT_TE, // DMA_IT_HT | DMA_IT_TC | DMA_IT_TE
    .DMA_IT_State = ENABLE};

void (*USART1_Handler)(void);
void (*USART2_Handler)(void);
void (*USART3_Handler)(void);
void (*UART4_Handler)(void);
void (*UART5_Handler)(void);

/**
 * @brief  USART1_TX对应的DMA通道的中断处理
 *         用于维护消息队列
 * @param  None
 * @retval None
 */
void USART1_TX_DMA_Handler()
{
  // DMA1_Channel4
  if (USART::DMA_Config_Check(USART1))
  {
    if (DMA_GetITStatus(DMA1_IT_HT4))
    {
      DMA_ClearITPendingBit(DMA1_IT_HT4);
    }
    else if (DMA_GetITStatus(DMA1_IT_TC4))
    {
      USART::DMA_Queue_Remove(USART1);
      USART::DMA_Queue_Start(USART1);
      DMA_ClearITPendingBit(DMA1_IT_TC4);
    }
    else if (DMA_GetITStatus(DMA1_IT_TE4))
    {
      printf("[USART1]:DMA消息队列传输错误!\n");
      USART::DMA_Queue_Stop(USART1);
      DMA_ClearITPendingBit(DMA1_IT_TE4);
    }
  }
}

/**
 * @brief  USART2_TX对应的DMA通道的中断处理
 *         用于维护消息队列
 * @param  None
 * @retval None
 */
void USART2_TX_DMA_Handler()
{
  // DMA1_Channel7
  if (USART::DMA_Config_Check(USART2))
  {
    if (DMA_GetITStatus(DMA1_IT_HT7))
    {
      DMA_ClearITPendingBit(DMA1_IT_HT7);
    }
    else if (DMA_GetITStatus(DMA1_IT_TC7))
    {
      USART::DMA_Queue_Remove(USART2);
      USART::DMA_Queue_Start(USART2);
      DMA_ClearITPendingBit(DMA1_IT_TC7);
    }
    else if (DMA_GetITStatus(DMA1_IT_TE7))
    {
      printf("[USART2]:DMA消息队列传输错误!\n");
      USART::DMA_Queue_Stop(USART2);
      DMA_ClearITPendingBit(DMA1_IT_TE7);
    }
  }
}

/**
 * @brief  USART3_TX对应的DMA通道的中断处理
 *         用于维护消息队列
 * @param  None
 * @retval None
 */
void USART3_TX_DMA_Handler()
{
  // DMA1_Channel2
  if (USART::DMA_Config_Check(USART3))
  {
    if (DMA_GetITStatus(DMA1_IT_HT2))
    {
      DMA_ClearITPendingBit(DMA1_IT_HT2);
    }
    else if (DMA_GetITStatus(DMA1_IT_TC2))
    {
      USART::DMA_Queue_Remove(USART3);
      USART::DMA_Queue_Start(USART3);
      DMA_ClearITPendingBit(DMA1_IT_TC2);
    }
    else if (DMA_GetITStatus(DMA1_IT_TE2))
    {
      printf("[USART3]:DMA消息队列传输错误!\n");
      USART::DMA_Queue_Stop(USART3);
      DMA_ClearITPendingBit(DMA1_IT_TE2);
    }
  }
}

/**
 * @brief  UART4_TX对应的DMA通道的中断处理
 *         用于维护消息队列
 * @param  None
 * @retval None
 */
void UART4_TX_DMA_Handler()
{
  // DMA2_Channel5
  // 注:DMA2_Channel4_5_IRQ
  if (USART::DMA_Config_Check(UART4))
  {
    if (DMA_GetITStatus(DMA2_IT_HT5))
    {
      DMA_ClearITPendingBit(DMA2_IT_HT5);
    }
    else if (DMA_GetITStatus(DMA2_IT_TC5))
    {
      USART::DMA_Queue_Remove(UART4);
      USART::DMA_Queue_Start(UART4);
      DMA_ClearITPendingBit(DMA2_IT_TC5);
    }
    else if (DMA_GetITStatus(DMA2_IT_TE5))
    {
      printf("[UART4]:DMA消息队列传输错误!\n");
      USART::DMA_Queue_Stop(UART4);
      DMA_ClearITPendingBit(DMA2_IT_TE5);
    }
  }
}

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
    // 获取DMA消息队列
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // 插入DMA消息队列
    Data_Queue->push(vector<uint8_t>{data});
    // 检测DMA通道是否在工作
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // 如果不在工作则初始化DMA
      DMA_Setup(USARTx_Param.USARTx);
    }
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
    // 获取DMA消息队列
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // 插入DMA消息队列
    Data_Queue->push(vector<uint8_t>(buffer, buffer + cnt));
    // 检测DMA通道是否在工作
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // 如果不在工作则让其工作
      DMA_Queue_Start(USARTx_Param.USARTx);
    }
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
    // 获取DMA消息队列
    queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx_Param.USARTx);
    // 插入DMA消息队列
    Data_Queue->push(vector<uint8_t>(str, str + strlen(str)));
    // 检测DMA通道是否在工作
    if (DMA_Config_Check(USARTx_Param.USARTx) == false)
    {
      // 如果不在工作则让其工作
      DMA_Queue_Start(USARTx_Param.USARTx);
    }
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
 * @brief  USART-内置DMA参数检查
 * @param  None
 * @retval DMA参数是否正确
 */
bool USART::DMA_Config_Check(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  // 检测USART对应DMA是否处于开启状态
  bool flag1 = DMA::Check_DMAx_Channelx(Get_DMA_Channel(USARTx, USART_DMA_TX));
  // 检测USART对应DMA通道的外设地址源是否正确
  bool flag2 = Get_DMA_Channel(USARTx, USART_DMA_TX)->CPAR == Get_DR_ADDR(USARTx);
  // 检测USART DMA_TX位是否打开
  bool flag3 = USARTx->CR3 & USART_DMAReq_Tx;
  return flag1 && flag2 && flag3;
}

/**
 * @brief  USART-内置DMA消息队列停止工作
 * @param  None
 * @retval DMA参数是否正确
 */
void USART::DMA_Queue_Stop(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  // 关闭DMA位
  USART_DMACmd(USARTx, USART_DMAReq_Tx, DISABLE);
  // 关闭DMA通道
  DMA_Cmd(Get_DMA_Channel(USARTx, USART_DMA_TX), DISABLE);
}

/**
 * @brief  USART-内置DMA消息队列开始工作,同时装入数据
 * @param  None
 * @retval DMA参数是否正确
 */
void USART::DMA_Queue_Start(USART_TypeDef *USARTx)
{
  assert_param(IS_USART_ALL_PERIPH(USARTx));
  queue<vector<uint8_t>> *Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // 如果队列存在
  if (Data_Queue != nullptr)
  {
    // 如果队列为空,则置DMA消息队列为空闲
    if (Data_Queue->empty())
    {
      DMA_Queue_Stop(USARTx);
    }
    // 否则配置DMA
    else
    {
      DMA_Setup(USARTx);
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

/**
 * @brief  USART-获取USART对应的DMA消息队列
 * @param  None
 * @retval USART对应的DMA消息队列
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
 * @brief  USART-设置DMA
 * @param  USARTx             USARTx
 * @retval None
 */
void USART::DMA_Setup(USART_TypeDef *USARTx)
{
  // 获取DMA消息队列
  queue<vector<uint8_t>> *USART_DMA_Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // 如果消息队列不存在或者消息队列为空则返回
  if (USART_DMA_Data_Queue == nullptr || USART_DMA_Data_Queue->empty())
  {
    return;
  }
  // 挂载DMA中断函数
  DMA_MAP_FUNC(USARTx);
  DMA_Param DMA_Param = USART_TX_DMA_Default_Param;
  DMA_Param.DMA_Channelx = Get_DMA_Channel(USARTx, USART_DMA_TX);
  DMA_Param.DMA_InitStructure.DMA_PeripheralBaseAddr = Get_DR_ADDR(USARTx);
  DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannel = DMA::Get_DMAx_Channelx_IRQn(Get_DMA_Channel(USARTx, USART_DMA_TX));
  DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  if (USARTx == USART1)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  }
  else if (USARTx == USART2)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  }
  else if (USARTx == USART3)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  }
  else if (USARTx == UART4)
  {
    DMA_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  }
  DMA_Param.DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) & *(USART_DMA_Data_Queue->front().begin());
  DMA_Param.DMA_InitStructure.DMA_BufferSize = USART_DMA_Data_Queue->front().size();
  // 开启DMA位
  USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);
  // 初始化DMA
  DMA(DMA_Param).Init();
}

/**
 * @brief  USART-移除队首已发送的数据
 * @param  USARTx             USARTx
 * @retval None
 */
void USART::DMA_Queue_Remove(USART_TypeDef *USARTx)
{
  // 获取DMA消息队列
  queue<vector<uint8_t>> *USART_DMA_Data_Queue = Get_USART_DMA_Data_Queue(USARTx);
  // 如果消息队列不存在或者消息队列为空则返回
  if (USART_DMA_Data_Queue == nullptr || USART_DMA_Data_Queue->empty())
  {
    return;
  }
  // 移除队首元素
  USART_DMA_Data_Queue->pop();
}

/**
 * @brief  USART-挂载USART对应的DMA中断函数
 * @param  USARTx             USARTx
 * @retval None
 */
void USART::DMA_MAP_FUNC(USART_TypeDef *USARTx)
{
  if (USARTx == USART1)
  {
    DMA1_Channel4_Handler = USART1_TX_DMA_Handler;
  }
  else if (USARTx == USART2)
  {
    DMA1_Channel7_Handler = USART2_TX_DMA_Handler;
  }
  else if (USARTx == USART3)
  {
    DMA1_Channel2_Handler = USART3_TX_DMA_Handler;
  }
  else if (USARTx == UART4)
  {
    DMA2_Channel4_5_Handler = UART4_TX_DMA_Handler;
  }
}