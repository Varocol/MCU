#include "Libraries.h"
/*
    实验：
        正确配置RTC并输出时间,测试RTC的所有中断功能。
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
    //开启串口
    USART_1.Init();
    //开启信号灯
    LED_1.Init();
    //使用RTC类初始化
    RTC_x.Init();
}
void Test()
{
    // uint32_t timestamp;
    // uint8_t flag = 0;
    // while (!flag)
    // {
    //     RTC_x.ITConfig(RTC_IT_SEC, DISABLE);
    //     printf("输入时间校准:\n");
    //     scanf("%ld", &timestamp);
    //     RTC_x.SetCounter(timestamp);
    //     RTC_x.ITConfig(RTC_IT_SEC, ENABLE);
    //     printf("校准成功请输入1,否则输入0:\n");
    //     scanf("%d", &flag);
    // }
    // RTC_x.ITConfig(RTC_IT_SEC, DISABLE);
    // printf("输入闹钟时间:\n");
    // scanf("%ld", &timestamp);
    // RTC_x.SetAlarm(timestamp);
    // printf("设置成功！\n");
    // RTC_x.ITConfig(RTC_IT_SEC, ENABLE);
    // printf("程序启动成功！\n");
    // if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET && PWR_GetFlagStatus(PWR_FLAG_WU) == SET)
    // {
    //     printf("待机唤醒或闹钟复位\n");
    //     RTC_x.Init();
    // }
    // else
    // {
    //     printf("进入待机模式\n");
    //     PWR_ClearFlag(PWR_FLAG_SB);
    //     PWR_ClearFlag(PWR_FLAG_WU);
    //     PWR_WakeUpPinCmd(ENABLE);
    //     PWR_EnterSTANDBYMode();
    // }
    while (1)
        ;
}
void End()
{
}