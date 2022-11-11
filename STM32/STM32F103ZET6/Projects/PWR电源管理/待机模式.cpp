#include "System.h"

/*
    实验：
        验证待机模式。
        注意：官方提供的库中只有通过WFI进入待机模式，其实二选一都可，
        下面的四个可以被认作事件或者中断，都可以触发中断或者事件，
        但是实际上待机模式下供电区域停止就意味着CPU完全不工作，
        所以WFE或WFI两种进入方式只是为了让系统进入待机模式，
        唤醒的话就不需要根据使用的命令来区分唤醒方式。
    唤醒方式：
        WKUP引脚的上升沿、RTC闹钟事件的上升沿、NRST引脚上外部复位、IWDG复位
*/

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
    //初始化LED
    LED_1.Init();
    //初始化串口
    USART_1.Init();
    //设置RTC唤醒
    RTC_x.Init();
    RTC_x.SetAlarm(RTC_Operate::GetCounter() + 10);
}
void Test()
{
    printf("程序启动成功！\n");
    if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET && PWR_GetFlagStatus(PWR_FLAG_WU) == SET)
    {
        printf("待机唤醒或闹钟复位\n");
    }
    else
    {
        printf("非待机或闹钟唤醒复位\n");
    }
    LED_1.Toggle();
    SysTick_Operate::Delay_ms(1000);
    LED_1.Toggle();
    SysTick_Operate::Delay_ms(1000);

    printf("进入待机模式\n");
    PWR_ClearFlag(PWR_FLAG_SB);
    PWR_ClearFlag(PWR_FLAG_WU);
    PWR_WakeUpPinCmd(ENABLE);
    PWR_EnterSTANDBYMode();
}
void End()
{
}