#include "USART.h"
//USART_Default USART1_RX = PA10
GPIO_InitTypeDef U1_RX_Pin_1 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART_Default USART1_TX = PA9
GPIO_InitTypeDef U1_TX_Pin_1 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART1_Remap USART1_RX = PB7
GPIO_InitTypeDef U1_RX_Pin_2 =
    {
        GPIO_Pin_7,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART1_Remap USART1_TX = PB6
GPIO_InitTypeDef U1_TX_Pin_2 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART2_Default USART2_RX = PA3
GPIO_InitTypeDef U2_RX_Pin_1 =
    {
        GPIO_Pin_3,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART2_Default USART2_TX = PA2
GPIO_InitTypeDef U2_TX_Pin_1 =
    {
        GPIO_Pin_2,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART2_Remap USART2_RX = PD6
GPIO_InitTypeDef U2_RX_Pin_2 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART2_Remap USART2_TX = PD5
GPIO_InitTypeDef U2_TX_Pin_2 =
    {
        GPIO_Pin_5,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART3_Default USART3_RX = PB11
GPIO_InitTypeDef U3_RX_Pin_1 =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART3_Default USART3_TX = PB10
GPIO_InitTypeDef U3_TX_Pin_1 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART3_PartialRemap USART3_RX = PC11
GPIO_InitTypeDef U3_RX_Pin_2 =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART3_PartialRemap USART3_TX = PC10
GPIO_InitTypeDef U3_TX_Pin_2 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//USART3_FullRemap USART3_RX = PD9
GPIO_InitTypeDef U3_RX_Pin_3 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//USART3_FullRemap USART3_TX = PD8
GPIO_InitTypeDef U3_TX_Pin_3 =
    {
        GPIO_Pin_8,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//UART4_Default UART4_RX = PC11
GPIO_InitTypeDef U4_RX_Pin =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//UART4_Default UART4_TX = PC10
GPIO_InitTypeDef U4_TX_Pin =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

//UART5_Default UART4_RX = PD2
GPIO_InitTypeDef U5_RX_Pin =
    {
        GPIO_Pin_2,
        GPIO_Speed_50MHz,
        GPIO_Mode_IN_FLOATING};

//UART5_Default UART4_TX = PC12
GPIO_InitTypeDef U5_TX_Pin =
    {
        GPIO_Pin_12,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

USART_InitTypeDef USART1_InitStructure =
    {
        USART_BAUDRATE_115200,
        USART_WordLength_8b,
        USART_StopBits_1,
        USART_Parity_No,
        USART_Mode_Rx | USART_Mode_Tx,
        USART_HardwareFlowControl_None};
USART_InitTypeDef USART2_InitStructure =
    {
        USART_BAUDRATE_115200,
        USART_WordLength_8b,
        USART_StopBits_1,
        USART_Parity_No,
        USART_Mode_Rx | USART_Mode_Tx,
        USART_HardwareFlowControl_None};
USART_InitTypeDef USART3_InitStructure =
    {
        USART_BAUDRATE_115200,
        USART_WordLength_8b,
        USART_StopBits_1,
        USART_Parity_No,
        USART_Mode_Rx | USART_Mode_Tx,
        USART_HardwareFlowControl_None};
USART_InitTypeDef UART4_InitStructure =
    {
        USART_BAUDRATE_115200,
        USART_WordLength_8b,
        USART_StopBits_1,
        USART_Parity_No,
        USART_Mode_Rx | USART_Mode_Tx,
        USART_HardwareFlowControl_None};
USART_InitTypeDef UART5_InitStructure =
    {
        USART_BAUDRATE_115200,
        USART_WordLength_8b,
        USART_StopBits_1,
        USART_Parity_No,
        USART_Mode_Rx | USART_Mode_Tx,
        USART_HardwareFlowControl_None};
NVIC_InitTypeDef USART1_NVIC_InitStructure =
    {
        USART1_IRQn,
        0,
        0,
        ENABLE};
NVIC_InitTypeDef USART2_NVIC_InitStructure =
    {
        USART2_IRQn,
        0,
        1,
        ENABLE};
NVIC_InitTypeDef USART3_NVIC_InitStructure =
    {
        USART3_IRQn,
        0,
        2,
        ENABLE};
NVIC_InitTypeDef UART4_NVIC_InitStructure =
    {
        UART4_IRQn,
        0,
        3,
        ENABLE};
NVIC_InitTypeDef UART5_NVIC_InitStructure =
    {
        UART5_IRQn,
        0,
        4,
        ENABLE};
// GPIO USART1_RX_1 = GPIO(GPIOA, U1_RX_Pin_1);
// GPIO USART1_RX_2 = GPIO(GPIOB, U1_RX_Pin_2);
// GPIO USART1_TX_1 = GPIO(GPIOA, U1_TX_Pin_1);
// GPIO USART1_TX_2 = GPIO(GPIOB, U1_TX_Pin_2);
// GPIO USART2_RX_1 = GPIO(GPIOA, U2_RX_Pin_1);
// GPIO USART2_RX_2 = GPIO(GPIOD, U2_RX_Pin_2);
// GPIO USART2_TX_1 = GPIO(GPIOA, U2_TX_Pin_1);
// GPIO USART2_TX_2 = GPIO(GPIOD, U2_TX_Pin_2);
// GPIO USART3_RX_1 = GPIO(GPIOB, U3_RX_Pin_1);
// GPIO USART3_RX_2 = GPIO(GPIOC, U3_RX_Pin_2);
// GPIO USART3_RX_3 = GPIO(GPIOD, U3_RX_Pin_3);
// GPIO USART3_TX_1 = GPIO(GPIOB, U3_TX_Pin_1);
// GPIO USART3_TX_2 = GPIO(GPIOC, U3_TX_Pin_2);
// GPIO USART3_TX_3 = GPIO(GPIOD, U3_TX_Pin_3);
// NVIC_Operate USART1_NVIC_Operate = NVIC_Operate(&USART1_NVIC_InitStructure);
// NVIC_Operate USART2_NVIC_Operate = NVIC_Operate(&USART2_NVIC_InitStructure);
// NVIC_Operate USART3_NVIC_Operate = NVIC_Operate(&USART3_NVIC_InitStructure);

/*
USART 中断位列表
USART_IT_CTS
USART_IT_LBD
USART_IT_TXE
USART_IT_TC
USART_IT_RXNE
USART_IT_IDLE
USART_IT_PE
USART_IT_ERR
*/
USART_Param USART1_Param =
    {
        USART1,
        USART1_InitStructure,
        NVIC_Operate(&USART1_NVIC_InitStructure),
        USART_Default,
        DISABLE,
        USART_IT_RXNE};

USART_Param USART2_Param =
    {
        USART2,
        USART2_InitStructure,
        NVIC_Operate(&USART2_NVIC_InitStructure),
        USART_Default,
        DISABLE,
        USART_IT_RXNE};

USART_Param USART3_Param =
    {
        USART3,
        USART3_InitStructure,
        NVIC_Operate(&USART3_NVIC_InitStructure),
        USART_Default,
        DISABLE,
        USART_IT_RXNE};

USART_Param UART4_Param =
    {
        UART4,
        UART4_InitStructure,
        NVIC_Operate(&UART4_NVIC_InitStructure),
        USART_Default,
        DISABLE,
        USART_IT_RXNE};

USART_Param UART5_Param =
    {
        UART5,
        UART5_InitStructure,
        NVIC_Operate(&UART5_NVIC_InitStructure),
        USART_Default,
        DISABLE,
        USART_IT_RXNE};

// USART1 波特率115200 能收能发
USART USART_1 = USART(USART1_Param);
// USART2 波特率115200 能收能发
USART USART_2 = USART(USART2_Param);
// USART3 波特率115200 能收能发
USART USART_3 = USART(USART3_Param);
// USART4 波特率115200 能收能发(实际上应该是UART4)
USART UART_4 = USART(UART4_Param);
// USART5 波特率115200 能收能发(实际上应该是UART5)
USART UART_5 = USART(UART5_Param);

/**
  * @brief  USART空构造方法
  * @param  None
  * @retval None
  */
USART::USART()
{
}

/**
  * @brief  USART析构函数
  * @param  None
  * @retval None
  */
USART::~USART()
{
}

/**
  * @brief  USART构造方法
  * @param  USARTx_Param:USART的参数列表
  * @retval None
  */
USART::USART(USART_Param USARTx_Param)
{
  Set_USART_Param(USARTx_Param);
}

/**
  * @brief  设置USART的参数列表
  * @param  USARTx_Param:USART的参数列表
  * @retval None
  */
void USART::Set_USART_Param(USART_Param USARTx_Param)
{
  this->USARTx_Param = USARTx_Param;
}

/**
  * @brief  USART发送字节
  * @param  data:数据
  * @retval None
  */
void USART::Send_Byte(uint8_t data)
{
  USART_SendData(USARTx_Param.USARTx, data);
  while (USART_GetFlagStatus(USARTx_Param.USARTx, USART_FLAG_TXE) == RESET)
    ;
}

/**
  * @brief  USART发送字符串l
  * @param  str:字符串
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
  * @brief  USART接收字节
  * @param  None
  * @retval None
  */
uint8_t USART::Receive_Byte()
{
  return USART_ReceiveData(USARTx_Param.USARTx);
}

/**
  * @brief  USART GPIO引脚初始化
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
  * @brief  USART参数列表更新
  * @param  USARTx_Param:USART的参数列表
  * @retval None
  */
void USART::Update(USART_Param USARTx_Param)
{
  USART_DeInit(this->USARTx_Param.USARTx);
  Set_USART_Param(USARTx_Param);
  Init();
}

/**
  * @brief  USART 初始化函数
  * @param  None
  * @retval None
  */
void USART::Init()
{
  //开启USART时钟
  RCC_Operate::RCC_Config(USARTx_Param.USARTx, ENABLE);
  //USARTx寄存器复位
  USART_DeInit(USARTx_Param.USARTx);
  //引脚初始化
  Pin_Init();
  //配置串口
  USART_Init(USARTx_Param.USARTx, &USARTx_Param.USART_InitStructure);
  //配置串口中断优先级
  USARTx_Param.USART_NVIC_Operate.Init();
  //配置串口中断
  USART_ITConfig(USARTx_Param.USARTx, USARTx_Param.USART_IT_Selection, USARTx_Param.USART_IT_State);
  //使能串口
  Start();
}

/**
  * @brief  开启USART函数(USART使能)
  * @param  None
  * @retval None
  */
void USART::Start()
{
  USART_Cmd(USARTx_Param.USARTx, ENABLE);
}

/**
  * @brief  关闭USART函数(USART失能)
  * @param  None
  * @retval None
  */
void USART::ShutUp()
{
  USART_Cmd(USARTx_Param.USARTx, DISABLE);
}
