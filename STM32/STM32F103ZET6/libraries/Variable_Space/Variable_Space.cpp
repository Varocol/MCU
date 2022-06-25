#include "Variable_Space.h"
// I2C
#define STM32_OWN_ADDR7 0xB0
I2C_InitTypeDef I2C1_InitStructure =
    {
        400000,
        I2C_Mode_I2C,
        I2C_DutyCycle_16_9,
        STM32_OWN_ADDR7,
        I2C_Ack_Enable,
        I2C_AcknowledgedAddress_7bit};

I2C_InitTypeDef I2C2_InitStructure =
    {
        400000,
        I2C_Mode_I2C,
        I2C_DutyCycle_16_9,
        STM32_OWN_ADDR7,
        I2C_Ack_Enable,
        I2C_AcknowledgedAddress_7bit};

// I2C1 错误中断
NVIC_InitTypeDef I2C1_ER_NVIC_InitStructure =
    {
        I2C1_ER_IRQn,
        0,
        6,
        ENABLE};
// I2C1 事件中断
NVIC_InitTypeDef I2C1_EV_NVIC_InitStructure =
    {
        I2C1_EV_IRQn,
        0,
        7,
        ENABLE};
// I2C2 错误中断
NVIC_InitTypeDef I2C2_ER_NVIC_InitStructure =
    {
        I2C2_ER_IRQn,
        0,
        8,
        ENABLE};
// I2C2 事件中断
NVIC_InitTypeDef I2C2_EV_NVIC_InitStructure =
    {
        I2C2_EV_IRQn,
        0,
        9,
        ENABLE};

/*
I2C 中断列表
I2C_IT_BUF
I2C_IT_EVT
I2C_IT_ERR
*/
I2C_Param I2C1_Param =
    {
        I2C1,
        I2C1_InitStructure,
        NVIC_Operate(&I2C1_ER_NVIC_InitStructure),
        NVIC_Operate(&I2C1_EV_NVIC_InitStructure),
        I2C_Default,
        DISABLE,
        I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR};

I2C_Param I2C2_Param =
    {
        I2C2,
        I2C2_InitStructure,
        NVIC_Operate(&I2C2_ER_NVIC_InitStructure),
        NVIC_Operate(&I2C2_EV_NVIC_InitStructure),
        I2C_Default,
        DISABLE,
        I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR};

// I2C1 400KHz 主发送器
I2C I2C_1 = I2C(I2C1_Param);

// I2C2 400KHz 主发送器
I2C I2C_2 = I2C(I2C2_Param);

// USART
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

// TIM
// TIM基本参数初始化结构体
TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure =
    {
        RCC_Operate::Get_SYSCLK_Frequency() / 1000000, // 72
        TIM_CounterMode_Up,
        999,          //计1000次,这样每次1ms
        TIM_CKD_DIV1, //输入信号滤波频率
        0,            //重复次数,只用通用和高级定时器才有
};
// TIM通道初始化结构体
TIM_OCInitTypeDef TIM2_OCStructure =
    {
        TIM_OCMode_PWM1,          //通道模式
        TIM_OutputState_Enable,   //输入/捕获使能(OCx)
        TIM_OutputNState_Disable, //输入/互补输出使能,只有高级定时器才有(OCxN)
        500,                      // CCRx的值,用来设置占空比
        TIM_OCPolarity_High,      //输入/捕获极性,高电平有效(OCx)
        TIM_OCNPolarity_High,     //输入/捕获互补输出极性,高电平有效(OCNx)
        TIM_OCIdleState_Reset,    //输出空闲状态(OCx)
        TIM_OCNIdleState_Reset    //输出空闲状态(OCxN)
};
// NVIC中断初始化结构体
NVIC_InitTypeDef TIM2_NVIC_Structure =
    {
        TIM2_IRQn,
        0,
        5,
        ENABLE};
// NVIC中断对象
NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(&TIM2_NVIC_Structure);

// TIM2初始化参数
TIM_Parma TIM2_Parma =
    {
        TIM2,
        TIM2_TimeBaseStructure,
        TIM2_OCStructure,
        TIM2_NVIC_Operate,
        ENABLE,
        TIM_IT_Update,
        OC1};

// TIM2对象
TIM TIM_2 = TIM(TIM2_Parma);

// DMA
//以USART示范DMA
#define USART_DR_ADDR (USART1_BASE + 0x04)
#define USART_TX_DMA_Channel DMA1_Channel4
#define USART_RX_DMA_Channel DMA1_Channel5
#define USART_TX_DMA_IRQN DMA1_Channel4_IRQn
#define USART_RX_DMA_IRQN DMA1_Channel5_IRQn
NVIC_InitTypeDef USART_RX_DMA_NVIC_InitStructure =
    {
        USART_RX_DMA_IRQN,
        0,
        10,
        ENABLE};
NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure =
    {
        USART_TX_DMA_IRQN,
        0,
        11,
        ENABLE};
DMA_InitTypeDef USART_RX_DMA_InitStructure = {
    USART_DR_ADDR,
    (uint32_t)ReceiveBuffer,
    DMA_DIR_PeripheralSRC,
    sizeof(ReceiveBuffer) / sizeof(char),
    DMA_PeripheralInc_Disable,
    DMA_MemoryInc_Enable,
    DMA_PeripheralDataSize_Byte,
    DMA_MemoryDataSize_Byte,
    DMA_Mode_Circular,
    DMA_Priority_High,
    DMA_M2M_Disable};
DMA_InitTypeDef USART_TX_DMA_InitStructure = {
    USART_DR_ADDR,
    (uint32_t)ReceiveBuffer,// (uint32_t)SendBuffer,
    DMA_DIR_PeripheralDST,
    sizeof(ReceiveBuffer) / sizeof(char),// strlen(SendBuffer),
    DMA_PeripheralInc_Disable,
    DMA_MemoryInc_Enable,
    DMA_PeripheralDataSize_Byte,
    DMA_MemoryDataSize_Byte,
    DMA_Mode_Normal,
    DMA_Priority_High,
    DMA_M2M_Disable};
DMA_Param USART1_RX_DMA_Param = {
    USART_RX_DMA_Channel,
    USART_RX_DMA_InitStructure,
    NVIC_Operate(&USART_RX_DMA_NVIC_InitStructure),
    ENABLE,
    DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
DMA_Param USART1_TX_DMA_Param = {
    USART_TX_DMA_Channel,
    USART_TX_DMA_InitStructure,
    NVIC_Operate(&USART_TX_DMA_NVIC_InitStructure),
    DISABLE,
    DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
DMA USART1_RX_DMA = DMA(USART1_RX_DMA_Param);
DMA USART1_TX_DMA = DMA(USART1_TX_DMA_Param);

//普通变量区
BitAction flag = Bit_SET;
uint8_t receivedata;
uint32_t time_ms = 0;
uint32_t current_time_ms = 0;
const char SendBuffer[] =
    "-------------------金辰星我爱你------------------\n$$$_____$$$$$$$$$$$$$$$_$$$_______$$$_$$$$$$$$$$\n$$$____$$$____$$$____$$$_$$$_____$$$__$$$_______\n$$$____$$$___________$$$_$$$_____$$$__$$$_______\n$$$_____$$$_________$$$___$$$___$$$___$$$$$$$$__\n$$$______$$$_______$$$_____$$$_$$$____$$$_______\n$$$_______$$$_____$$$______$$$_$$$____$$$_______\n$$$$$$$$$___$$$_$$$_________$$$$$_____$$$$$$$$$$\n";
char ReceiveBuffer[10];