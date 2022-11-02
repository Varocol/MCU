#ifndef __OJ_USART_H
#define __OJ_USART_H
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"
#include "DMA.h"
#include <queue>
// TODO USART��Ҫ����
/*
                TX      RX      SCLK    nCTS    nRTS
USART1:
        Default:
                PA9     PA10    PA8     PA11    PA12
        Remap:
                PB6     PB7
USART2:
        Default:
                PA2     PA3     PA4     PA0     PA1
        Remap:
                PD5     PD6     PD7     PD3     PD4
USART3:
        Default:
                PB10    PB11    PB12    PB13    PB14
        PartialRemap:
                PC10    PC11    PC12    PB13    PB14
        FullRemap:
                PD8     PD9     PD10    PD11    PD12
UART4:
        Default:
                PC10    PC11
UART5:
        Default:
                PC12    PD2

�жϱ�־λ�б�
USART_IT_CTS:   //CTS��־
USART_IT_LBD    //�Ͽ���־
USART_IT_TXE    //�������ݼĴ����ձ�־
USART_IT_TC     //������ɱ�־
USART_IT_RXNE   //�������ݾ����ɶ���־
USART_IT_IDLE   //��⵽������·��־
USART_IT_PE     //��ż������־
USART_IT_ERR    //�����жϱ�־
*/
// ������ö��
typedef enum
{
        USART_BAUDRATE_110 = 110,
        USART_BAUDRATE_300 = 300,
        USART_BAUDRATE_600 = 600,
        USART_BAUDRATE_1200 = 1200,
        USART_BAUDRATE_2400 = 2400,
        USART_BAUDRATE_4800 = 4800,
        USART_BAUDRATE_9600 = 9600,
        USART_BAUDRATE_14400 = 14400,
        USART_BAUDRATE_19200 = 19200,
        USART_BAUDRATE_38400 = 38400,
        USART_BAUDRATE_57600 = 57600,
        USART_BAUDRATE_115200 = 115200,
        USART_BAUDRATE_230400 = 230400,
        USART_BAUDRATE_460800 = 460800,
        USART_BAUDRATE_921600 = 921600,
        USART_BAUDRATE_1843200 = 1843200,
        USART_BAUDRATE_3686400 = 3686400,
        USART_BAUDRATE_7812500 = 7812500
} USART_BAUDRATE;

// USART����ö��
typedef enum
{
        USART1_Default,
        USART1_Remap,
        USART2_Default,
        USART2_Remap,
        USART3_Default,
        USART3_PartialRemap,
        USART3_FullRemap,
        UART4_Default,
        UART5_Default
} USART_Remap_enum;

typedef enum
{
        USART_DMA_RX,
        USART_DMA_TX,
        USART_DMA_BOTH
} USART_DMA_enum;

// USART�����б�ṹ��
typedef struct
{
        USART_TypeDef *USARTx;                           // USARTx
        USART_InitTypeDef USART_InitStructure;           // USART��ʼ���ṹ��
        USART_ClockInitTypeDef USART_ClockInitStructure; // USARTʱ�ӳ�ʼ���ṹ��
        NVIC_InitTypeDef USART_NVIC_InitStructure;       // USART�жϳ�ʼ���ṹ��
        USART_Remap_enum USARTx_Pin_Remap;               // USART����ѡ��
        uint16_t USART_IT_Selection;                     // USART�ж�λѡ��
        USART_DMA_enum USART_DMA_enum;                   // USARTDMAѡ��
        FunctionalState USART_IT_State;                  // USART�ж�ʹ(ʧ)��
        FunctionalState USART_DMA_State;                 // USARTDMAʹ(ʧ)��
} USART_Param;

class USART
{
private:
        USART_Param USARTx_Param;

        // DMA ��Ϣ���� UART5��֧��
        static queue<uint8_t *> USART1_DMA_Data_Queue; // USART1��Ϣ����
        static queue<uint8_t *> USART2_DMA_Data_Queue; // USART2��Ϣ����
        static queue<uint8_t *> USART3_DMA_Data_Queue; // USART3��Ϣ����
        static queue<uint8_t *> USART4_DMA_Data_Queue; // USART4��Ϣ����
        // ����Ĭ��DMA���ò���
        // USART1_DMA ͨ���ж������ȼ� 15
        // USART2_DMA ͨ���ж������ȼ� 14
        // USART3_DMA ͨ���ж������ȼ� 13
        // UART4_DMA  ͨ���ж������ȼ� 12
        DMA_InitTypeDef USART_TX_DMA_InitStructure = {
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
        NVIC_InitTypeDef USART_TX_DMA_NVIC_InitStructure = {
            .NVIC_IRQChannel = NULL,
            .NVIC_IRQChannelPreemptionPriority = NULL,
            .NVIC_IRQChannelSubPriority = NULL,
            .NVIC_IRQChannelCmd = ENABLE};
        DMA_Param USART_TX_DMA_Param = {
            .DMA_Channelx = NULL,
            .DMA_InitStructure = USART_TX_DMA_InitStructure,
            .DMA_NVIC_InitStructure = USART_TX_DMA_NVIC_InitStructure,
            .DMA_IT_Selection = DMA_IT_TC | DMA_IT_HT | DMA_IT_TE,
            .DMA_IT_State = ENABLE};

public:
        USART();
        ~USART();
        USART(USART_Param USARTx_Param);
        void Send_Data(uint8_t data);
        void Send_Buffer(uint8_t *buffer, uint32_t cnt);
        void Send_String(const char *str);
        void Send_Data_DMA(uint8_t data);
        void Send_Buffer_DMA(uint8_t *buffer, uint32_t cnt);
        void Send_String_DMA(const char *str);
        uint8_t Receive_Data();
        void Pin_Init();
        void Update(USART_Param USARTx_Param);
        void Set_USART_Param(USART_Param USARTx_Param);
        void DMACmd(USART_DMA_enum USART_DMA_enum, FunctionalState NewState);
        void ITConfig(uint16_t USART_IT, FunctionalState NewState);
        void Init();
        void Enable();
        void Disable();

        void RCC_Enable();
        void RCC_Disable();

        // DMA����
        void DMA_Init();
        void DMA_Disable();
        void DMA_Enable();

        static void RCC_Enable(USART_TypeDef *USARTx);
        static void RCC_Disable(USART_TypeDef *USARTx);

        // DMAר��
        static uint32_t Get_DR_ADDR(USART_TypeDef *USARTx);
        static DMA_Channel_TypeDef *Get_DMA_Channel(USART_TypeDef *USARTx, USART_DMA_enum USART_DMA);
};
#endif /*__OJ_USART_H*/
