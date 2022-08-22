#include "Variable_Space.h"
// I2C
#define STM32_OWN_ADDR7 0xB0
I2C_InitTypeDef I2C1_InitStructure = {
    400000,
    I2C_Mode_I2C,
    I2C_DutyCycle_16_9,
    STM32_OWN_ADDR7,
    I2C_Ack_Enable,
    I2C_AcknowledgedAddress_7bit};
I2C_InitTypeDef I2C2_InitStructure = {
    400000,
    I2C_Mode_I2C,
    I2C_DutyCycle_16_9,
    STM32_OWN_ADDR7,
    I2C_Ack_Enable,
    I2C_AcknowledgedAddress_7bit};
// I2C1 �����ж�
NVIC_InitTypeDef I2C1_ER_NVIC_InitStructure = {
    I2C1_ER_IRQn,
    0,
    6,
    ENABLE};
// I2C1 �¼��ж�
NVIC_InitTypeDef I2C1_EV_NVIC_InitStructure = {
    I2C1_EV_IRQn,
    0,
    7,
    ENABLE};
// I2C2 �����ж�
NVIC_InitTypeDef I2C2_ER_NVIC_InitStructure = {
    I2C2_ER_IRQn,
    0,
    8,
    ENABLE};
// I2C2 �¼��ж�
NVIC_InitTypeDef I2C2_EV_NVIC_InitStructure = {
    I2C2_EV_IRQn,
    0,
    9,
    ENABLE};
I2C_Param I2C1_Param = {
    I2C1,
    I2C1_InitStructure,
    NVIC_Operate(I2C1_ER_NVIC_InitStructure),
    NVIC_Operate(I2C1_EV_NVIC_InitStructure),
    I2C_Default,
    DISABLE,
    I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR};
I2C_Param I2C2_Param = {
    I2C2,
    I2C2_InitStructure,
    NVIC_Operate(I2C2_ER_NVIC_InitStructure),
    NVIC_Operate(I2C2_EV_NVIC_InitStructure),
    I2C_Default,
    DISABLE,
    I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR};

// I2C1 400KHz ��������
I2C I2C_1 = I2C(I2C1_Param);

// I2C2 400KHz ��������
I2C I2C_2 = I2C(I2C2_Param);

// USART
USART_InitTypeDef USART1_InitStructure = {
    USART_BAUDRATE_115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx,
    USART_HardwareFlowControl_None};
USART_InitTypeDef USART2_InitStructure = {
    USART_BAUDRATE_115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx,
    USART_HardwareFlowControl_None};
USART_InitTypeDef USART3_InitStructure = {
    USART_BAUDRATE_115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx,
    USART_HardwareFlowControl_None};
USART_InitTypeDef UART4_InitStructure = {
    USART_BAUDRATE_115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx,
    USART_HardwareFlowControl_None};
USART_InitTypeDef UART5_InitStructure = {
    USART_BAUDRATE_115200,
    USART_WordLength_8b,
    USART_StopBits_1,
    USART_Parity_No,
    USART_Mode_Rx | USART_Mode_Tx,
    USART_HardwareFlowControl_None};
USART_ClockInitTypeDef USART_Default_InitStructure = {
    USART_Clock_Disable,
    USART_CPOL_Low,
    USART_CPHA_1Edge,
    USART_LastBit_Disable};
NVIC_InitTypeDef USART1_NVIC_InitStructure = {
    USART1_IRQn,
    0,
    0,
    ENABLE};
NVIC_InitTypeDef USART2_NVIC_InitStructure = {
    USART2_IRQn,
    0,
    1,
    ENABLE};
NVIC_InitTypeDef USART3_NVIC_InitStructure = {
    USART3_IRQn,
    0,
    2,
    ENABLE};
NVIC_InitTypeDef UART4_NVIC_InitStructure = {
    UART4_IRQn,
    0,
    3,
    ENABLE};
NVIC_InitTypeDef UART5_NVIC_InitStructure = {
    UART5_IRQn,
    0,
    4,
    ENABLE};
USART_Param USART1_Param = {
    USART1,
    USART1_InitStructure,
    USART_Default_InitStructure,
    NVIC_Operate(USART1_NVIC_InitStructure),
    USART1_Default,
    DISABLE,
    USART_IT_RXNE};
USART_Param USART2_Param = {
    USART2,
    USART2_InitStructure,
    USART_Default_InitStructure,
    NVIC_Operate(USART2_NVIC_InitStructure),
    USART2_Default,
    DISABLE,
    USART_IT_RXNE};
USART_Param USART3_Param = {
    USART3,
    USART3_InitStructure,
    USART_Default_InitStructure,
    NVIC_Operate(USART3_NVIC_InitStructure),
    USART3_Default,
    DISABLE,
    USART_IT_RXNE};
USART_Param UART4_Param = {
    UART4,
    UART4_InitStructure,
    USART_Default_InitStructure,
    NVIC_Operate(UART4_NVIC_InitStructure),
    UART4_Default,
    DISABLE,
    USART_IT_RXNE};
USART_Param UART5_Param = {
    UART5,
    UART5_InitStructure,
    USART_Default_InitStructure,
    NVIC_Operate(UART5_NVIC_InitStructure),
    UART5_Default,
    DISABLE,
    USART_IT_RXNE};

// USART1 ������115200 �����ܷ�
USART USART_1 = USART(USART1_Param);
// USART2 ������115200 �����ܷ�
USART USART_2 = USART(USART2_Param);
// USART3 ������115200 �����ܷ�
USART USART_3 = USART(USART3_Param);
// USART4 ������115200 �����ܷ�(ʵ����Ӧ����UART4)
USART UART_4 = USART(UART4_Param);
// USART5 ������115200 �����ܷ�(ʵ����Ӧ����UART5)
USART UART_5 = USART(UART5_Param);

// TIM
// TIM����������ʼ���ṹ��
TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure = {
    (uint16_t)(RCC_Operate::Get_SYSCLK_Frequency() / 1000000), // 72
    TIM_CounterMode_Up,
    999,          //��1000��,����ÿ��1ms
    TIM_CKD_DIV1, //�����ź��˲�Ƶ��
    0             //�ظ�����,ֻ��ͨ�ú͸߼���ʱ������
};
// TIMͨ����ʼ���ṹ��
TIM_OCInitTypeDef TIM2_OCStructure = {
    TIM_OCMode_PWM1,          //ͨ��ģʽ
    TIM_OutputState_Enable,   //����/����ʹ��(OCx)
    TIM_OutputNState_Disable, //����/�������ʹ��,ֻ�и߼���ʱ������(OCxN)
    500,                      // CCRx��ֵ,��������ռ�ձ�
    TIM_OCPolarity_High,      //����/������,�ߵ�ƽ��Ч(OCx)
    TIM_OCNPolarity_High,     //����/���񻥲��������,�ߵ�ƽ��Ч(OCNx)
    TIM_OCIdleState_Reset,    //�������״̬(OCx)
    TIM_OCNIdleState_Reset    //�������״̬(OCxN)
};
TIM_ICInitTypeDef TIM2_ICSturcture = {
    TIM_Channel_1,
    TIM_ICPolarity_Rising,
    TIM_ICSelection_DirectTI,
    TIM_ICPSC_DIV1,
    0x00};
// NVIC�жϳ�ʼ���ṹ��
NVIC_InitTypeDef TIM2_NVIC_Structure = {
    TIM2_IRQn,
    0,
    5,
    ENABLE};
// NVIC�ж϶���
NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(TIM2_NVIC_Structure);

// TIM2��ʼ������
TIM_Parma TIM2_Parma = {
    TIM2,
    TIM2_TimeBaseStructure,
    TIM2_OCStructure,
    TIM2_ICSturcture,
    TIM2_NVIC_Operate,
    ENABLE,
    TIM_IT_Update,
    OC1};

// TIM2
TIM TIM_2 = TIM(TIM2_Parma);

// DMA
//��USARTʾ��DMA
#define USART_DR_ADDR (USART1_BASE + 0x04)
#define USART_TX_DMA_Channel DMA1_Channel4
#define USART_RX_DMA_Channel DMA1_Channel5
#define Flash_SRAM_DMA_Channel DMA1_Channel1
#define USART_TX_DMA_IRQN DMA1_Channel4_IRQn
#define USART_RX_DMA_IRQN DMA1_Channel5_IRQn
#define Flash_SRAM_DMA_IRQN DMA1_Channel1_IRQn
NVIC_InitTypeDef USART_RX_DMA_NVIC_InitStructure = {
    USART_RX_DMA_IRQN,
    0,
    10,
    ENABLE};
NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure = {
    USART_TX_DMA_IRQN,
    0,
    11,
    ENABLE};
NVIC_InitTypeDef Flash_SRAM_DMA_NVIC_InitStructure = {
    Flash_SRAM_DMA_IRQN,
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
    (uint32_t)SendBuffer, // (uint32_t)ReceiveBuffer,
    DMA_DIR_PeripheralDST,
    strlen(SendBuffer) + 1, // sizeof(ReceiveBuffer) / sizeof(char),
    DMA_PeripheralInc_Disable,
    DMA_MemoryInc_Enable,
    DMA_PeripheralDataSize_Byte,
    DMA_MemoryDataSize_Byte,
    DMA_Mode_Normal,
    DMA_Priority_High,
    DMA_M2M_Disable};
DMA_InitTypeDef Flash_SRAM_DMA_InitStructure = {
    (uint32_t)FlashBuffer,
    (uint32_t)SRAMBuffer,
    DMA_DIR_PeripheralSRC,
    strlen(FlashBuffer),
    DMA_PeripheralInc_Enable,
    DMA_MemoryInc_Enable,
    DMA_PeripheralDataSize_Byte,
    DMA_MemoryDataSize_Byte,
    DMA_Mode_Normal,
    DMA_Priority_High,
    DMA_M2M_Enable};
DMA_Param USART1_RX_DMA_Param = {
    USART_RX_DMA_Channel,
    USART_RX_DMA_InitStructure,
    NVIC_Operate(USART_RX_DMA_NVIC_InitStructure),
    DISABLE,
    DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
DMA_Param USART1_TX_DMA_Param = {
    USART_TX_DMA_Channel,
    USART_TX_DMA_InitStructure,
    NVIC_Operate(USART_TX_DMA_NVIC_InitStructure),
    DISABLE,
    DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
DMA_Param Flash_SRAM_DMA_Param = {
    Flash_SRAM_DMA_Channel,
    Flash_SRAM_DMA_InitStructure,
    NVIC_Operate(Flash_SRAM_DMA_NVIC_InitStructure),
    DISABLE,
    DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
DMA USART1_RX_DMA = DMA(USART1_RX_DMA_Param);
DMA USART1_TX_DMA = DMA(USART1_TX_DMA_Param);
DMA Flash_SRAM_DMA = DMA(Flash_SRAM_DMA_Param);
//����SPI��DMA��Ҫ��5��ʵ�����Բ������б仯,����Ͳ�д����������,��ϸ��spi�Ĳ���
DMA SPI2_RX_DMA;
DMA SPI1_TX_DMA;

// SPI
NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
    SPI1_IRQn,
    0,
    13,
    ENABLE};
NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
    SPI2_IRQn,
    0,
    14,
    ENABLE};
SPI_InitTypeDef SPI1_InitStructure = {
    SPI_Direction_2Lines_FullDuplex,
    SPI_Mode_Master,
    SPI_DataSize_8b,
    SPI_CPOL_Low,
    SPI_CPHA_1Edge,
    SPI_NSS_Soft,
    SPI_BaudRatePrescaler_2,
    SPI_FirstBit_MSB,
    3};
SPI_InitTypeDef SPI2_InitStructure = {
    SPI_Direction_2Lines_FullDuplex,
    SPI_Mode_Slave,
    SPI_DataSize_8b,
    SPI_CPOL_Low,
    SPI_CPHA_1Edge,
    SPI_NSS_Hard,
    SPI_BaudRatePrescaler_2,
    SPI_FirstBit_MSB,
    3};
SPI_Param SPI1_Param = {
    SPI1,
    SPI1_InitStructure,
    SPI_NSS_Master_Soft,
    NVIC_Operate(SPI1_NVIC_InitStructure),
    DISABLE,
    SPI_I2S_IT_TXE | SPI_I2S_IT_ERR | SPI_I2S_IT_RXNE,
};
SPI_Param SPI2_Param = {
    SPI2,
    SPI2_InitStructure,
    SPI_NSS_Slave_Hard,
    NVIC_Operate(SPI2_NVIC_InitStructure),
    DISABLE,
    SPI_I2S_IT_TXE | SPI_I2S_IT_ERR | SPI_I2S_IT_RXNE,
};

// SPI1 ��ģʽ
SPI SPI_1 = SPI(SPI1_Param);
// SPI2 ��ģʽ
SPI SPI_2 = SPI(SPI2_Param);

// RTC
NVIC_InitTypeDef RTC_NVIC_InitStructure = {
    RTC_IRQn,
    0,
    5,
    ENABLE};
RTC_Param RTCx_Param = {
    32768,
    1660705805,
    1660705865,
    RTC_CLK_LSE,
    NVIC_Operate(RTC_NVIC_InitStructure),
    DISABLE,
    RTC_IT_ALR | RTC_IT_SEC};
RTC_Operate RTC_x = RTC_Operate(RTCx_Param);

// EXTI
NVIC_InitTypeDef EXTI_PC6_NVIC_InitStructure = {
    EXTI9_5_IRQn,
    0,
    15,
    ENABLE};
EXTI_InitTypeDef EXTI_PC6_InitStructure = {
    EXTI_Line6,
    EXTI_Mode_Interrupt,
    EXTI_Trigger_Rising_Falling,
    ENABLE};
EXTI_Operate EXTI_PC6 = EXTI_Operate(EXTI_PC6_InitStructure, NVIC_Operate(EXTI_PC6_NVIC_InitStructure), GPIOC);

// LED
// LED1_RED     PB5(û��)
// LED1_GREEN   PB0
// LED1_BLUE    PB1(û��)
// LED2         PF7
// LED3         PF8
LED LED_1_R = LED(PB5, Low_level_lighting);
LED LED_1_G = LED(PB0, Low_level_lighting);
LED LED_1_B = LED(PB1, Low_level_lighting);
LED LED_1 = LED(PB0, Low_level_lighting);
LED LED_2 = LED(PF7, Low_level_lighting);
LED LED_3 = LED(PF8, Low_level_lighting);

//  Button
Button Key1 = Button(PA0, false);

//ϵͳ����
time_t system_start_time;
time_t timestamp;
tm timeinfo;
char timestr[80];

//��ͨ������
BitAction flag = Bit_SET;
uint8_t receivedata;
uint32_t time_ms = 0;
uint32_t current_time_ms = 0;
const char SendBuffer1[] = "1235678910\n"; //Ϊ����֤spidmaCRC��Ⱦ�������Ե�һ���ַ����д
const char SendBuffer[] =
    "-------------------�����Ұ���------------------\n"
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