#ifndef __OJ_USART_H
#define __OJ_USART_H
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"
//波特率枚举
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

//USART引脚枚举
typedef enum
{
    USART_Default,
    USART1_Remap,
    USART2_Remap,
    USART3_PartialRemap,
    USART3_FullRemap
} USART_Pin_Selection;

//USART参数列表结构体
typedef struct
{
    USART_TypeDef *USARTx;                          //USARTx
    USART_InitTypeDef USART_InitStructure;          //USART初始化结构体
    NVIC_Operate USART_NVIC_Operate;                //USART中断对象
    USART_Pin_Selection USARTx_Pin_Remap_Selection; //USART引脚选择
    FunctionalState USART_IT_State;                 //USART中断使(失)能
    uint16_t USART_IT_Selection;                    //USART中断位选择
} USART_Param;

class USART
{
private:
    USART_Param USARTx_Param;

public:
    USART();
    ~USART();
    USART(USART_Param USARTx_Param);
    void Send_Byte(uint8_t data);
    void Send_String(uint8_t *str);
    uint8_t Receive_Byte();
    void Pin_Init();
    void Update(USART_Param USARTx_Param);
    void Set_USART_Param(USART_Param USARTx_Param);
    void Init();
    void Start();
    void ShutUp();
};

extern USART USART_1;
extern USART USART_2;
extern USART USART_3;
extern USART UART_4;
extern USART UART_5;

extern USART_Param USART1_Param;
extern USART_Param USART2_Param;
extern USART_Param USART3_Param;
#endif /*__OJ_USART_H*/
