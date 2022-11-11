#ifndef __OJ_USART_H
#define __OJ_USART_H
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"
#include "DMA.h"
#include <queue>
using namespace std;
// TODO USART需要补充
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

中断标志位列表
USART_IT_CTS:   //CTS标志
USART_IT_LBD    //断开标志
USART_IT_TXE    //发送数据寄存器空标志
USART_IT_TC     //发送完成标志
USART_IT_RXNE   //接收数据就绪可读标志
USART_IT_IDLE   //检测到空闲线路标志
USART_IT_PE     //奇偶检验错标志
USART_IT_ERR    //错误中断标志
*/
// 波特率枚举
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

// USART引脚枚举
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

// USART参数列表结构体
typedef struct
{
        USART_TypeDef *USARTx;                           // USARTx
        USART_InitTypeDef USART_InitStructure;           // USART初始化结构体
        USART_ClockInitTypeDef USART_ClockInitStructure; // USART时钟初始化结构体
        NVIC_InitTypeDef USART_NVIC_InitStructure;       // USART中断初始化结构体
        USART_Remap_enum USARTx_Pin_Remap;               // USART引脚选择
        uint16_t USART_IT_Selection;                     // USART中断位选择
        USART_DMA_enum USART_DMA_enum;                   // USARTDMA选择
        FunctionalState USART_IT_State;                  // USART中断使(失)能
        FunctionalState USART_DMA_State;                 // USARTDMA使(失)能
} USART_Param;

class USART
{
private:
        USART_Param USARTx_Param;

        // DMA 消息队列 UART5不支持
        static queue<vector<uint8_t>> USART1_DMA_Data_Queue; // USART1消息队列
        static queue<vector<uint8_t>> USART2_DMA_Data_Queue; // USART2消息队列
        static queue<vector<uint8_t>> USART3_DMA_Data_Queue; // USART3消息队列
        static queue<vector<uint8_t>> UART4_DMA_Data_Queue;  // UART4 消息队列

        static queue<vector<uint8_t>> *Get_USART_DMA_Data_Queue(USART_TypeDef *USARTx);
        static void DMA_Setup(USART_TypeDef *USARTx);

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

        static void RCC_Enable(USART_TypeDef *USARTx);
        static void RCC_Disable(USART_TypeDef *USARTx);

        // DMA管理
        static bool DMA_Config_Check(USART_TypeDef *USARTx);
        static void DMA_Queue_Stop(USART_TypeDef *USARTx);
        static void DMA_Queue_Start(USART_TypeDef *USARTx);
        static void DMA_Queue_Remove(USART_TypeDef *USARTx);
        static void DMA_MAP_FUNC(USART_TypeDef *USARTx);

        // DMA专用
        static uint32_t Get_DR_ADDR(USART_TypeDef *USARTx);
        static DMA_Channel_TypeDef *Get_DMA_Channel(USART_TypeDef *USARTx, USART_DMA_enum USART_DMA);
};

extern void (*USART1_Handler)(void);
extern void (*USART2_Handler)(void);
extern void (*USART3_Handler)(void);
extern void (*UART4_Handler)(void);
extern void (*UART5_Handler)(void);

#endif /*__OJ_USART_H*/
