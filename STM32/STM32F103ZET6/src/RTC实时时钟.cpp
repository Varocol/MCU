#include "Libraries.h"
#define RTC_CLKSELECT 0
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
    //复位备份域(将整个备份域复位,包括bkp数据以及RTC计数器等)
    BKP_DeInit();
    //开启PWR和BKP时钟
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);
    //允许访问BKP区域(复位后整个备份域被锁,需要开启访问)
    PWR_BackupAccessCmd(ENABLE);
#if RTC_CLKSELECT == 0
    //开启需要给RTC提供信号源的时钟
    RCC_LSEConfig(RCC_LSE_ON);
    //等待时钟源就绪
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        ;
    //配置RTC时钟源选择(一般选择LSE,因为LSE处在备份域中,由VBat供电,所以可以持续提供信号)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#elif RTC_CLKSELECT == 1
    //开启需要给RTC提供信号源的时钟
    RCC_LSICmd(ENABLE);
    //等待时钟源就绪
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
        ;
    //配置RTC时钟源选择(一般选择LSE,因为LSE处在备份域中,由VBat供电,所以可以持续提供信号)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#endif
    //使能RTC时钟
    RCC_RTCCLKCmd(ENABLE);
    //等待RTC时钟同步
    RTC_WaitForSynchro();
    //等待上次任务完成
    RTC_WaitForLastTask();
    //配置相关中断
    RTC_ITConfig(RTC_IT_SEC | RTC_IT_ALR, ENABLE);
    //等待上次任务完成
    RTC_WaitForLastTask();
    //进入配置模式
    RTC_EnterConfigMode();
    //等待上次任务完成
    RTC_WaitForLastTask();
    //设置RTC分频
    RTC_SetPrescaler(32768);
    //等待上次任务完成
    RTC_WaitForLastTask();
    //设置RTC计数
    RTC_SetCounter(1660705805);
    //等待上次任务完成
    RTC_WaitForLastTask();
    //设置报警
    RTC_SetAlarm(1660705865);
    //退出配置模式
    RTC_ExitConfigMode();
    //配置NVIC
    NVIC_InitTypeDef RTC_NVIC_InitStructure = {
        RTC_IRQn,
        0,
        7,
        ENABLE};
    NVIC_Operate RTC_NVIC = NVIC_Operate(RTC_NVIC_InitStructure);
    RTC_NVIC.Init();
}
void Test()
{
    while (1)
        ;
}
void End()
{
}