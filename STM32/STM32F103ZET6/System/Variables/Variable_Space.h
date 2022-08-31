#ifndef __OJ_VARIBALE_SPACE_H
#define __OJ_VARIBALE_SPACE_H
#include "Libraries.h"

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
extern DMA Flash_SRAM_DMA;
extern DMA SPI2_RX_DMA;
extern DMA SPI1_TX_DMA;
// SPI
extern SPI SPI_1;
extern SPI SPI_2;

// RTC
extern RTC_Operate RTC_x;

// EXTI
extern EXTI_Operate EXTI_PC6;

// LED
extern LED LED_1;
extern LED LED_2;
extern LED LED_3;

// Button
extern Button Key1;

// Buzzer
extern Buzzer Beep;

//系统变量
extern time_t timestamp;
extern time_t system_start_time;
extern tm timeinfo;
extern char timestr[80];

// 普通变量
extern BitAction flag;
extern uint8_t receivedata;
extern uint32_t time_ms;
extern uint32_t current_time_ms;
extern const char SendBuffer[];
extern char ReceiveBuffer[500];
extern const char FlashBuffer[];
extern char SRAMBuffer[127];
#endif /*__OJ_VARIBALE_SPACE_H*/
