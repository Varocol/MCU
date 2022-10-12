#ifndef __OJ_PLATFORM_H
#define __OJ_PLATFORM_H
#include "Variable_Space.h"
#include "stm32f10x_it.h"
#include <cstdio>
using namespace std;

//平台指定的外设(用于重定向C底层函数)
#define PLATFORM_USART USART_1
#define PLATFORM_LED LED_1
#define PLATFORM_RTC RTC_x

void tzset(uint8_t);

void record_start_time();
void usart_init();
void led_init();
void rtc_init();
void system_init();

uint32_t system_time();
uint32_t system_time_ms();

void system_delay(uint32_t s);
void system_delay_ms(uint32_t ms);

#endif /*__OJ_PLATFORM_H*/