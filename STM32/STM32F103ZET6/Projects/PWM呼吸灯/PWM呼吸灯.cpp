#include "System.h"
int main()
{
    double LED_Frequency = 500; // LED频率,100Hz,不能超过500Hz,且不能大于PWM初始化参数中的频率
    double LED_Cycle = 2;       // LED一亮灭周期,2s
    PWM pwm = PWM(TIM3_Channel3_PartialRemap, 1000, 0.5);
    pwm.Init();
    int flag = 1;
    for (int i = 0;; i += flag)
    {
        if (i == LED_Frequency) // 100的刷新频率
        {
            flag = -1;
        }
        else if (i == 0)
        {
            flag = 1;
        }
        pwm.Update(TIM3_Channel3_PartialRemap, 1000, i / LED_Frequency);
        SysTick_Operate::Delay_ms(LED_Cycle * 500 / LED_Frequency);
    }
}