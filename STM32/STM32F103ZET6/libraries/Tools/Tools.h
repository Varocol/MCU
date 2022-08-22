#ifndef __OJ_TOOLS_H
#define __OJ_TOOLS_H
#include "stm32f10x.h"

uint32_t days_between_years(uint32_t, uint32_t);
uint8_t is_leapyear(uint32_t);
uint8_t days_in_months(uint32_t, uint8_t);
#endif /*__OJ_TOOLS_H*/