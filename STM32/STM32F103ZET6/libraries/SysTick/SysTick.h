#ifndef __OJ_SYSTICK_H
#define __OJ_SYSTICK_H
#include "stm32f10x.h"
#include "core_cm3.h"
#include "RCC.h"
class SysTick_Operate
{
private:
public:
    SysTick_Operate();
    ~SysTick_Operate();
    static void Delay_ms(uint32_t ms);
    static void Delay_us(uint32_t us);
    static void Delay(uint32_t count, uint32_t ticks);
};
#endif