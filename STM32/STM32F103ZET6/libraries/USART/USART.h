#ifndef __OJ_USART_H
#define __OJ_USART_H
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"
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
//������ö��
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
        NVIC_Operate USART_NVIC_Operate;                 // USART�ж϶���
        USART_Remap_enum USARTx_Pin_Remap;               // USART����ѡ��
        FunctionalState USART_IT_State;                  // USART�ж�ʹ(ʧ)��
        uint16_t USART_IT_Selection;                     // USART�ж�λѡ��
} USART_Param;

class USART
{
private:
        USART_Param USARTx_Param;

public:
        USART();
        ~USART();
        USART(USART_Param USARTx_Param);
        void Send_Data(uint8_t data);
        void Send_Buffer(uint8_t *buffer, uint32_t cnt);
        void Send_String(const char *str);
        uint8_t Receive_Data();
        void Pin_Init();
        void Update(USART_Param USARTx_Param);
        void Set_USART_Param(USART_Param USARTx_Param);
        void Use_DMA(USART_DMA_enum USART_DMA_enum, FunctionalState state);
        void ITConfig(uint16_t USART_IT, FunctionalState NewState);
        void Init();
        void Start();
        void ShutUp();
};
#endif /*__OJ_USART_H*/
