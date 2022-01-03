#ifndef __OJ_USART_DEBUG_H
#include "stm32f10x.h"
#include "stdio.h"
#define DEBUG_USARTx UART5
#define DEBUG_OUT_PUT 1
#define DEBUG_ERROR_INFO(fmt, arg...) \
    if (DEBUG_OUT_PUT)             \
    printf("<--- ERROR INFO --->\nFILE: [%s]\nLINE: [%d]\n<--- ERROR MESSAGE --->\n"fmt" \n", __FILE__, __LINE__, ##arg)
#define DEBUG_MESSAGE_INFO(fmt, arg...) \
    if (DEBUG_OUT_PUT)               \
    printf("<--- MESSAGE INFO --->\nFILE: [%s]\nLINE: [%d]\n<--- ERROR MESSAGE --->\n"fmt"\n", __FILE__, __LINE__, ##arg)
#endif /*__OJ_USART_DEBUG_H*/