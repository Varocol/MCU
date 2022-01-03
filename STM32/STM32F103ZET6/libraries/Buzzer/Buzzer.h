#ifndef __OJ_BUZZER_H
#define __OJ_BUZZER_H
#include "stm32f10x.h"
#include "GPIO.h"
#include "SysTick.h"
class Buzzer
{
private:
    GPIO buzzer;
    void run(void);
    uint32_t BEEP_HZ_CONVERT(uint32_t HZ);
    void Systick_Special_Delay(uint32_t t, uint32_t count);
    void Systick_Delay_ms(uint32_t ms);

public:
    Buzzer();
    Buzzer(GPIO buzzer);
    ~Buzzer();
    void Init();
    void Music(uint32_t hz, double time,uint8_t Basespeed);
};

#endif /*__OJ_BUZZER_H*/