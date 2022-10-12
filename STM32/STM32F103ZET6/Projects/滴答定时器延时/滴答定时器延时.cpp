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
     LED_1.Init();
}
void Test()
{
     while (1)
     {
          LED_1.Toggle();
          SysTick_Operate::Delay_ms(250);
     }
}
void End()
{
}