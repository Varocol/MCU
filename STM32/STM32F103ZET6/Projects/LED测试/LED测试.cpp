#include "System.h"

void Setup();
void Test();
void End();

int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    system_delay_ms(500);
    LED_1.Init();
    GPIO pwr(PB7);
    pwr.Init();
    pwr.Pin_High();
}
void Test()
{
    while (1)
    {
        LED_1.Toggle();
        SysTick_Operate::Delay_ms(500);
    }
}
void End()
{
}