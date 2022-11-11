#include "Variable_Space.h"
// I2C
#define STM32_OWN_ADDR7 0xB0
I2C_InitTypeDef I2C1_InitStructure = {
    .I2C_ClockSpeed = 100000,
    .I2C_Mode = I2C_Mode_I2C,
    .I2C_DutyCycle = I2C_DutyCycle_16_9,
    .I2C_OwnAddress1 = STM32_OWN_ADDR7,
    .I2C_Ack = I2C_Ack_Enable,
    .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
I2C_InitTypeDef I2C2_InitStructure = {
    .I2C_ClockSpeed = 100000,
    .I2C_Mode = I2C_Mode_I2C,
    .I2C_DutyCycle = I2C_DutyCycle_16_9,
    .I2C_OwnAddress1 = STM32_OWN_ADDR7,
    .I2C_Ack = I2C_Ack_Enable,
    .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
// I2C1 错误中断
NVIC_InitTypeDef I2C1_ER_NVIC_InitStructure = {
    .NVIC_IRQChannel = I2C1_ER_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 6,
    .NVIC_IRQChannelCmd = ENABLE};
// I2C1 事件中断
NVIC_InitTypeDef I2C1_EV_NVIC_InitStructure = {
    .NVIC_IRQChannel = I2C1_EV_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 7,
    .NVIC_IRQChannelCmd = ENABLE};
// I2C2 错误中断
NVIC_InitTypeDef I2C2_ER_NVIC_InitStructure = {
    .NVIC_IRQChannel = I2C2_ER_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 8,
    .NVIC_IRQChannelCmd = ENABLE};
// I2C2 事件中断
NVIC_InitTypeDef I2C2_EV_NVIC_InitStructure = {
    .NVIC_IRQChannel = I2C2_EV_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 9,
    .NVIC_IRQChannelCmd = ENABLE};
I2C_Param I2C1_Param = {
    .I2Cx = I2C1,
    .I2C_InitStructure = I2C1_InitStructure,
    .I2C_ER_NVIC_InitStructure = I2C1_ER_NVIC_InitStructure,
    .I2C_EV_NVIC_InitStructure = I2C1_EV_NVIC_InitStructure,
    .I2C_Pin_Remap = I2C_Default,
    .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
    .I2C_IT_State = DISABLE,
    .I2C_DMA_State = DISABLE};
I2C_Param I2C2_Param = {
    .I2Cx = I2C2,
    .I2C_InitStructure = I2C2_InitStructure,
    .I2C_ER_NVIC_InitStructure = I2C2_ER_NVIC_InitStructure,
    .I2C_EV_NVIC_InitStructure = I2C2_EV_NVIC_InitStructure,
    .I2C_Pin_Remap = I2C_Default,
    .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
    .I2C_IT_State = DISABLE,
    .I2C_DMA_State = DISABLE};

// I2C1 400KHz 主发送器
I2C I2C_1(I2C1_Param);

// I2C2 400KHz 主发送器
I2C I2C_2(I2C2_Param);

// USART
USART_InitTypeDef USART1_InitStructure = {
    .USART_BaudRate = USART_BAUDRATE_115200,
    .USART_WordLength = USART_WordLength_8b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_No,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None};
USART_InitTypeDef USART2_InitStructure = {
    .USART_BaudRate = USART_BAUDRATE_115200,
    .USART_WordLength = USART_WordLength_8b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_No,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None};
USART_InitTypeDef USART3_InitStructure = {
    .USART_BaudRate = USART_BAUDRATE_115200,
    .USART_WordLength = USART_WordLength_8b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_No,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None};
USART_InitTypeDef UART4_InitStructure = {
    .USART_BaudRate = USART_BAUDRATE_115200,
    .USART_WordLength = USART_WordLength_8b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_No,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None};
USART_InitTypeDef UART5_InitStructure = {
    .USART_BaudRate = USART_BAUDRATE_115200,
    .USART_WordLength = USART_WordLength_8b,
    .USART_StopBits = USART_StopBits_1,
    .USART_Parity = USART_Parity_No,
    .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
    .USART_HardwareFlowControl = USART_HardwareFlowControl_None};
USART_ClockInitTypeDef USART_Default_InitStructure = {
    .USART_Clock = USART_Clock_Disable,
    .USART_CPOL = USART_CPOL_Low,
    .USART_CPHA = USART_CPHA_1Edge,
    .USART_LastBit = USART_LastBit_Disable};
NVIC_InitTypeDef USART1_NVIC_InitStructure = {
    .NVIC_IRQChannel = USART1_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 0,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef USART2_NVIC_InitStructure = {
    .NVIC_IRQChannel = USART2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 1,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef USART3_NVIC_InitStructure = {
    .NVIC_IRQChannel = USART3_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 2,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef UART4_NVIC_InitStructure = {
    .NVIC_IRQChannel = UART4_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 3,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef UART5_NVIC_InitStructure = {
    .NVIC_IRQChannel = UART5_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 4,
    .NVIC_IRQChannelCmd = ENABLE};
USART_Param USART1_Param = {
    .USARTx = USART1,
    .USART_InitStructure = USART1_InitStructure,
    .USART_ClockInitStructure = USART_Default_InitStructure,
    .USART_NVIC_InitStructure = USART1_NVIC_InitStructure,
    .USARTx_Pin_Remap = USART1_Default,
    .USART_IT_Selection = USART_IT_RXNE,
    .USART_DMA_enum = USART_DMA_BOTH,
    .USART_IT_State = DISABLE,
    .USART_DMA_State = DISABLE};
USART_Param USART2_Param = {
    .USARTx = USART2,
    .USART_InitStructure = USART2_InitStructure,
    .USART_ClockInitStructure = USART_Default_InitStructure,
    .USART_NVIC_InitStructure = USART2_NVIC_InitStructure,
    .USARTx_Pin_Remap = USART2_Default,
    .USART_IT_Selection = USART_IT_RXNE,
    .USART_DMA_enum = USART_DMA_BOTH,
    .USART_IT_State = DISABLE,
    .USART_DMA_State = DISABLE};
USART_Param USART3_Param = {
    .USARTx = USART3,
    .USART_InitStructure = USART3_InitStructure,
    .USART_ClockInitStructure = USART_Default_InitStructure,
    .USART_NVIC_InitStructure = USART3_NVIC_InitStructure,
    .USARTx_Pin_Remap = USART3_Default,
    .USART_IT_Selection = USART_IT_RXNE,
    .USART_DMA_enum = USART_DMA_BOTH,
    .USART_IT_State = DISABLE,
    .USART_DMA_State = DISABLE};
USART_Param UART4_Param = {
    .USARTx = UART4,
    .USART_InitStructure = UART4_InitStructure,
    .USART_ClockInitStructure = USART_Default_InitStructure,
    .USART_NVIC_InitStructure = UART4_NVIC_InitStructure,
    .USARTx_Pin_Remap = UART4_Default,
    .USART_IT_Selection = USART_IT_RXNE,
    .USART_DMA_enum = USART_DMA_BOTH,
    .USART_IT_State = DISABLE,
    .USART_DMA_State = DISABLE};
USART_Param UART5_Param = {
    .USARTx = UART5,
    .USART_InitStructure = UART5_InitStructure,
    .USART_ClockInitStructure = USART_Default_InitStructure,
    .USART_NVIC_InitStructure = UART5_NVIC_InitStructure,
    .USARTx_Pin_Remap = UART5_Default,
    .USART_IT_Selection = USART_IT_RXNE,
    .USART_DMA_enum = USART_DMA_BOTH,
    .USART_IT_State = DISABLE,
    .USART_DMA_State = DISABLE};

// USART1 波特率115200 能收能发
USART USART_1(USART1_Param);
// USART2 波特率115200 能收能发
USART USART_2(USART2_Param);
// USART3 波特率115200 能收能发
USART USART_3(USART3_Param);
// USART4 波特率115200 能收能发(实际上应该是UART4)
USART UART_4(UART4_Param);
// USART5 波特率115200 能收能发(实际上应该是UART5)
USART UART_5(UART5_Param);

// TIM
// TIM基本参数初始化结构体
TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure = {
    .TIM_Prescaler = (uint16_t)(RCC_Operate::Get_SYSCLK_Frequency() / 1000000), // 72
    .TIM_CounterMode = TIM_CounterMode_Up,
    .TIM_Period = 999,                 //计1000次,这样每次1ms
    .TIM_ClockDivision = TIM_CKD_DIV1, //输入信号滤波频率
    .TIM_RepetitionCounter = 0         //重复次数,只用通用和高级定时器才有
};
// TIM通道初始化结构体
TIM_OCInitTypeDef TIM2_OCStructure = {
    .TIM_OCMode = TIM_OCMode_PWM1,                //通道模式
    .TIM_OutputState = TIM_OutputState_Enable,    //输入/捕获使能(OCx)
    .TIM_OutputNState = TIM_OutputNState_Disable, //输入/互补输出使能,只有高级定时器才有(OCxN)
    .TIM_Pulse = 500,                             // CCRx的值,用来设置占空比
    .TIM_OCPolarity = TIM_OCPolarity_High,        //输入/捕获极性,高电平有效(OCx)
    .TIM_OCNPolarity = TIM_OCNPolarity_High,      //输入/捕获互补输出极性,高电平有效(OCNx)
    .TIM_OCIdleState = TIM_OCIdleState_Reset,     //输出空闲状态(OCx)
    .TIM_OCNIdleState = TIM_OCNIdleState_Reset    //输出空闲状态(OCxN)
};
TIM_ICInitTypeDef TIM2_ICSturcture = {
    .TIM_Channel = TIM_Channel_1,
    .TIM_ICPolarity = TIM_ICPolarity_Rising,
    .TIM_ICSelection = TIM_ICSelection_DirectTI,
    .TIM_ICPrescaler = TIM_ICPSC_DIV1,
    .TIM_ICFilter = 0x00};
// NVIC中断初始化结构体
NVIC_InitTypeDef TIM2_NVIC_Structure = {
    .NVIC_IRQChannel = TIM2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 5,
    .NVIC_IRQChannelCmd = ENABLE};

// TIM2初始化参数
TIM_Parma TIM2_Parma = {
    .TIMx = TIM2,
    .TIM_TimeBaseStructure = TIM2_TimeBaseStructure,
    .TIM_OCStructure = TIM2_OCStructure,
    .TIM_ICStructure = TIM2_ICSturcture,
    .TIM_NVIC_InitStructure = TIM2_NVIC_Structure,
    .TIM_IT_Selection = TIM_IT_Update,
    .OCx = OC1,
    .TIM_IT_State = ENABLE};

// TIM2
TIM TIM_2(TIM2_Parma);

// DMA
//以USART示范DMA
#define USART_DR_ADDR (USART1_BASE + 0x04)
#define USART_TX_DMA_Channel DMA1_Channel4
#define USART_RX_DMA_Channel DMA1_Channel5
#define Flash_SRAM_DMA_Channel DMA1_Channel1
#define USART_TX_DMA_IRQN DMA1_Channel4_IRQn
#define USART_RX_DMA_IRQN DMA1_Channel5_IRQn
#define Flash_SRAM_DMA_IRQN DMA1_Channel1_IRQn
NVIC_InitTypeDef USART_RX_DMA_NVIC_InitStructure = {
    .NVIC_IRQChannel = USART_RX_DMA_IRQN,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 10,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure = {
    .NVIC_IRQChannel = USART_TX_DMA_IRQN,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 11,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef Flash_SRAM_DMA_NVIC_InitStructure = {
    .NVIC_IRQChannel = Flash_SRAM_DMA_IRQN,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 11,
    .NVIC_IRQChannelCmd = ENABLE};
DMA_InitTypeDef USART_RX_DMA_InitStructure = {
    .DMA_PeripheralBaseAddr = USART_DR_ADDR,
    .DMA_MemoryBaseAddr = (uint32_t)ReceiveBuffer,
    .DMA_DIR = DMA_DIR_PeripheralSRC,
    .DMA_BufferSize = sizeof(ReceiveBuffer) / sizeof(char),
    .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Circular,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Disable};
DMA_InitTypeDef USART_TX_DMA_InitStructure = {
    .DMA_PeripheralBaseAddr = USART_DR_ADDR,
    .DMA_MemoryBaseAddr = (uint32_t)SendBuffer, // (uint32_t)ReceiveBuffer,
    .DMA_DIR = DMA_DIR_PeripheralDST,
    .DMA_BufferSize = strlen(SendBuffer) + 1, // sizeof(ReceiveBuffer) / sizeof(char),
    .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Normal,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Disable};
DMA_InitTypeDef Flash_SRAM_DMA_InitStructure = {
    .DMA_PeripheralBaseAddr = (uint32_t)FlashBuffer,
    .DMA_MemoryBaseAddr = (uint32_t)SRAMBuffer,
    .DMA_DIR = DMA_DIR_PeripheralSRC,
    .DMA_BufferSize = strlen(FlashBuffer),
    .DMA_PeripheralInc = DMA_PeripheralInc_Enable,
    .DMA_MemoryInc = DMA_MemoryInc_Enable,
    .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
    .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
    .DMA_Mode = DMA_Mode_Normal,
    .DMA_Priority = DMA_Priority_High,
    .DMA_M2M = DMA_M2M_Enable};
DMA_Param USART1_RX_DMA_Param = {
    .DMA_Channelx = USART_RX_DMA_Channel,
    .DMA_InitStructure = USART_RX_DMA_InitStructure,
    .DMA_NVIC_InitStructure = USART_RX_DMA_NVIC_InitStructure,
    .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
    .DMA_IT_State = DISABLE};
DMA_Param USART1_TX_DMA_Param = {
    .DMA_Channelx = USART_TX_DMA_Channel,
    .DMA_InitStructure = USART_TX_DMA_InitStructure,
    .DMA_NVIC_InitStructure = USART_TX_DMA_NVIC_InitStructure,
    .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
    .DMA_IT_State = DISABLE};
DMA_Param Flash_SRAM_DMA_Param = {
    .DMA_Channelx = Flash_SRAM_DMA_Channel,
    .DMA_InitStructure = Flash_SRAM_DMA_InitStructure,
    .DMA_NVIC_InitStructure = Flash_SRAM_DMA_NVIC_InitStructure,
    .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
    .DMA_IT_State = DISABLE};
DMA USART1_RX_DMA = DMA(USART1_RX_DMA_Param);
DMA USART1_TX_DMA = DMA(USART1_TX_DMA_Param);
DMA Flash_SRAM_DMA = DMA(Flash_SRAM_DMA_Param);
//由于SPI的DMA需要做5个实验所以参数会有变化,这里就不写参数配置了,详细见spi的测试
DMA SPI2_RX_DMA;
DMA SPI1_TX_DMA;

// SPI
NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
    .NVIC_IRQChannel = SPI1_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 13,
    .NVIC_IRQChannelCmd = ENABLE};
NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
    .NVIC_IRQChannel = SPI2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 14,
    .NVIC_IRQChannelCmd = ENABLE};
SPI_InitTypeDef SPI1_InitStructure = {
    .SPI_Direction = SPI_Direction_2Lines_FullDuplex,
    .SPI_Mode = SPI_Mode_Master,
    .SPI_DataSize = SPI_DataSize_8b,
    .SPI_CPOL = SPI_CPOL_Low,
    .SPI_CPHA = SPI_CPHA_1Edge,
    .SPI_NSS = SPI_NSS_Soft,
    .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2,
    .SPI_FirstBit = SPI_FirstBit_MSB,
    .SPI_CRCPolynomial = 3};
SPI_InitTypeDef SPI2_InitStructure = {
    .SPI_Direction = SPI_Direction_2Lines_FullDuplex,
    .SPI_Mode = SPI_Mode_Slave,
    .SPI_DataSize = SPI_DataSize_8b,
    .SPI_CPOL = SPI_CPOL_Low,
    .SPI_CPHA = SPI_CPHA_1Edge,
    .SPI_NSS = SPI_NSS_Hard,
    .SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2,
    .SPI_FirstBit = SPI_FirstBit_MSB,
    .SPI_CRCPolynomial = 3};
SPI_Param SPI1_Param = {
    .SPIx = SPI1,
    .SPI_InitStructure = SPI1_InitStructure,
    .SPI_NSS = SPI_NSS_Master_Soft,
    .SPI_NVIC_InitStructure = SPI1_NVIC_InitStructure,
    .SPI_IT_Selection = SPI_I2S_IT_TXE | SPI_I2S_IT_ERR | SPI_I2S_IT_RXNE,
    .SPI_DMA_enum = SPI_DMA_BOTH,
    .SPI_IT_State = DISABLE,
    .SPI_DMA_State = DISABLE};
SPI_Param SPI2_Param = {
    .SPIx = SPI2,
    .SPI_InitStructure = SPI2_InitStructure,
    .SPI_NSS = SPI_NSS_Slave_Hard,
    .SPI_NVIC_InitStructure = SPI2_NVIC_InitStructure,
    .SPI_IT_Selection = SPI_I2S_IT_TXE | SPI_I2S_IT_ERR | SPI_I2S_IT_RXNE,
    .SPI_DMA_enum = SPI_DMA_BOTH,
    .SPI_IT_State = DISABLE,
    .SPI_DMA_State = DISABLE};

// SPI1 主模式
SPI SPI_1(SPI1_Param);
// SPI2 从模式
SPI SPI_2(SPI2_Param);

// RTC
NVIC_InitTypeDef RTC_NVIC_InitStructure = {
    .NVIC_IRQChannel = RTC_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 5,
    .NVIC_IRQChannelCmd = ENABLE};
RTC_Param RTCx_Param = {
    .PrescalerValue = 32768,
    .CounterValue = 1660705805,
    .AlarmValue = 1660705865,
    .RTC_CLK = RTC_CLK_LSE,
    .RTC_NVIC_InitStructure = RTC_NVIC_InitStructure,
    .RTC_IT_Selection = RTC_IT_ALR | RTC_IT_SEC,
    .RTC_IT_State = DISABLE};
RTC_Operate RTC_x = RTC_Operate(RTCx_Param);

// EXTI
NVIC_InitTypeDef EXTI_PC6_NVIC_InitStructure = {
    .NVIC_IRQChannel = EXTI9_5_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 15,
    .NVIC_IRQChannelCmd = ENABLE};
EXTI_InitTypeDef EXTI_PC6_InitStructure = {
    .EXTI_Line = EXTI_Line6,
    .EXTI_Mode = EXTI_Mode_Interrupt,
    .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
    .EXTI_LineCmd = ENABLE};
EXTI_Operate EXTI_PC6 = EXTI_Operate(EXTI_PC6_InitStructure, EXTI_PC6_NVIC_InitStructure, GPIOC);

// LED
// LED1_RED     PB5(没用)
// LED1_GREEN   PB0
// LED1_BLUE    PB1(没用)
// LED2         PF7
// LED3         PF8
LED LED_1_R(PB5, Low_level_lighting);
LED LED_1_G(PB0, Low_level_lighting);
LED LED_1_B(PB1, Low_level_lighting);
LED LED_1(PB0, Low_level_lighting);
LED LED_2(PF7, Low_level_lighting);
LED LED_3(PF8, Low_level_lighting);

// ADC
NVIC_InitTypeDef ADC1_NVIC_InitStructure = {
    .NVIC_IRQChannel = ADC1_2_IRQn,
    .NVIC_IRQChannelPreemptionPriority = 0,
    .NVIC_IRQChannelSubPriority = 5,
    .NVIC_IRQChannelCmd = DISABLE};
ADC_Base_InitTypeDef ADC1_Base_InitStructure = {
    .RCC_PCLK2_Divx = RCC_PCLK2_Div6,
    .ADC_DiscModeNumber = 1,
    .ADC_DataAlign = ADC_DataAlign_Right,
    .ADC_Mode = ADC_Mode_Independent,
    .ADC_JAuto = DISABLE,
    .ADC_ContinuousConvMode = ENABLE,
    .ADC_ScanConvMode = ENABLE};
vector<ADC_Channel_ConInfo> ADC1_RegularChannellist = {
    {ADC_Channel_10,
     1,
     ADC_SampleTime_1Cycles5},
    {ADC_Channel_11,
     2,
     ADC_SampleTime_1Cycles5},
    {ADC_Channel_12,
     3,
     ADC_SampleTime_1Cycles5}};
vector<ADC_Channel_ConInfo> ADC1_InjectedChannellist = {
    {ADC_Channel_13,
     1,
     ADC_SampleTime_1Cycles5}};
ADC_Channel_InitTypeDef ADC1_RegularChannel_InitStructure = {
    .ADC_Channellist = ADC1_RegularChannellist,
    .ADC_ExternalTrigConv = ADC_ExternalTrigConv_None,
    .ADC_DiscMode = DISABLE,
    .ADC_ExternalTrig = DISABLE};
ADC_Channel_InitTypeDef ADC1_InjectedChannel_InitStructure = {
    .ADC_Channellist = ADC1_InjectedChannellist,
    .ADC_ExternalTrigConv = ADC_ExternalTrigInjecConv_None, //如果用软件开启则直接使用none
    .ADC_DiscMode = DISABLE,
    .ADC_ExternalTrig = DISABLE};
ADC_Param ADC1_Param = {
    .ADCx = ADC1,
    .ADC_Base_InitStructure = ADC1_Base_InitStructure,
    .ADC_RegularChannel_InitStructure = ADC1_RegularChannel_InitStructure,
    .ADC_InjectedChannel_InitStructure = ADC1_InjectedChannel_InitStructure,
    .ADC_NVIC_InitStructure = ADC1_NVIC_InitStructure,
    .ADC_IT_Selection = ADC_IT_EOC,
    .ADC_IT_State = ENABLE,
    .ADC_DMA_State = DISABLE};
ADC ADC_1(ADC1_Param);

//  Button
Button Key1(PA0, false);

// Buzzer
Buzzer Beep(TIM1_Channel1_Default);

//系统变量
time_t system_start_time;
time_t timestamp;
tm timeinfo;
char timestr[80];

//普通变量区
BitAction flag = Bit_SET;
uint8_t receivedata;
uint32_t time_ms = 0;
uint32_t current_time_ms = 0;
const char SendBuffer1[] = "1235678910\n"; //为了验证spidmaCRC污染问题所以第一个字符随便写
const char SendBuffer[] =
    "-------------------金辰星我爱你------------------\n"
    "$$$_____$$$$$$$$$$$$$$$_$$$_______$$$_$$$$$$$$$$\n"
    "$$$____$$$____$$$____$$$_$$$_____$$$__$$$_______\n"
    "$$$____$$$___________$$$_$$$_____$$$__$$$_______\n"
    "$$$_____$$$_________$$$___$$$___$$$___$$$$$$$$__\n"
    "$$$______$$$_______$$$_____$$$_$$$____$$$_______\n"
    "$$$_______$$$_____$$$______$$$_$$$____$$$_______\n"
    "$$$$$$$$$___$$$_$$$_________$$$$$_____$$$$$$$$$$\n";
char ReceiveBuffer[500];
const char FlashBuffer[] =
    "NFBZMOMGEYGJSDWTDYHHCXLGOREVYXGOGPAWTSULKQSFQHHYSQOSWZTUNXDZTZZDRQFWJLFGGNAOJNLLBTWXTSFOALZDYGYUMTHZQTGBEQPPFGYACDPFKVWQWBCPZH";
char SRAMBuffer[127];

