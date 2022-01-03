#ifndef __GETIRQN_H
#define __GETIRQN_H
#include "bsp_conf.h"
uint8_t  USART_GetIRQ(USART_TypeDef* USARTx);
uint8_t  EXTILine_convert_IRQChannel(uint16_t EXTILINE);
uint8_t  TIM_GetIRQ(TIM_TypeDef * TIMx);
#endif  /*__GETIRQN_H*/