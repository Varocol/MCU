#ifndef __OJ_VARIBALE_SPACE_H
#define __OJ_VARIBALE_SPACE_H
#include "I2C.h"
#include "USART.h"
#include "TIM.h"
#include "DMA.h"
#include "String_CPP.h"
// I2C
extern I2C I2C_1;
extern I2C I2C_2;
// USART
extern USART USART_1;
extern USART USART_2;
extern USART USART_3;
extern USART UART_4;
extern USART UART_5;
// TIM
extern TIM TIM_2;
// DMA
extern DMA USART1_TX_DMA;
extern DMA USART1_RX_DMA;

// ∆’Õ®±‰¡ø
extern BitAction flag;
extern uint8_t receivedata;
extern uint32_t time_ms;
extern uint32_t current_time_ms;
extern const char SendBuffer[];
extern char ReceiveBuffer[10];
#endif /*__OJ_VARIBALE_SPACE_H*/
