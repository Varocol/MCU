#include "System.h"
int main()
{
    double LED_Frequency = 500; // LEDƵ��,100Hz,���ܳ���500Hz,�Ҳ��ܴ���PWM��ʼ�������е�Ƶ��
    double LED_Cycle = 2;       // LEDһ��������,2s
    PWM pwm = PWM(TIM3_Channel3_PartialRemap, 1000, 0.5);
    pwm.Init();
    int flag = 1;
    for (int i = 0;; i += flag)
    {
        if (i == LED_Frequency) // 100��ˢ��Ƶ��
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