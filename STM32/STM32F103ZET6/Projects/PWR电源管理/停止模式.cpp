#include "System.h"
/*
    实验：
        验证停止模式。使用按键中断唤醒芯片，并配置唤醒后的时钟。
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
    //初始化灯
    LED_1.Init();
    //初始化串口
    USART_1.Init();
    //初始化KEY1引脚及中断
    GPIO KEY1 = GPIO(PA0, GPIO_Mode_IN_FLOATING);
    KEY1.Init();
    NVIC_InitTypeDef EXTI_KEY1_NVIC_InitStructure = {
        .NVIC_IRQChannel = EXTI0_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 2,
        .NVIC_IRQChannelCmd = ENABLE};
    EXTI_InitTypeDef EXTI_KEY1_InitStructure = {
        .EXTI_Line = EXTI_Line0,
        .EXTI_Mode = EXTI_Mode_Interrupt,
        .EXTI_Trigger = EXTI_Trigger_Rising,
        .EXTI_LineCmd = ENABLE};
    EXTI_Operate EXTI_KEY1 = EXTI_Operate(EXTI_KEY1_InitStructure, EXTI_KEY1_NVIC_InitStructure, GPIOA);
    EXTI_KEY1.Init();
    //开启PWR时钟
    RCC_Operate::RCC_Config(PWR, ENABLE);
    //通过闹钟中断(EXTI17)或事件唤醒
    NVIC_InitTypeDef RTCALR_NVIC_InitStructure = {
        .NVIC_IRQChannel = RTCAlarm_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 3,
        .NVIC_IRQChannelCmd = ENABLE};
    //闹钟事件的上升沿
    EXTI_InitTypeDef RTCALR_InitStructure = {
        .EXTI_Line = EXTI_Line17,
        .EXTI_Mode = EXTI_Mode_Interrupt,
        .EXTI_Trigger = EXTI_Trigger_Rising,
        .EXTI_LineCmd = ENABLE};
    EXTI_Operate EXTI_RTCALR = EXTI_Operate(RTCALR_InitStructure, RTCALR_NVIC_InitStructure);
    EXTI_RTCALR.Init();
    RTC_x.Init();
    RTC_x.SetAlarm(RTC_Operate::GetCounter() + 60);
}
void Test()
{
    while (1)
    {
        printf("程序正在运行...\n");
        LED_1.Toggle();
        SysTick_Operate::Delay_ms(500);
        LED_1.Toggle();
        SysTick_Operate::Delay_ms(500);
        printf("进入停止模式\n");
        PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
        RCC_ClocksTypeDef wakeup_config = RCC_Operate::Get_ClocksFreq();
        Clock_Source wakeup_source = RCC_Operate::Get_SYSCLKSource();
        RCC_Operate::HSE_SetSysClock(RCC_PLLMul_9);
        RCC_ClocksTypeDef normal_config = RCC_Operate::Get_ClocksFreq();
        Clock_Source normal_source = RCC_Operate::Get_SYSCLKSource();
        printf("唤醒后时钟频率:\n"
               "SYSTICK:%d\n"
               "HCLK:%d\n"
               "PCLK1:%d\n"
               "PCLK2:%d\n"
               "时钟源(0:HSI,1:HSE,2:PLL):%d\n",
               wakeup_config.SYSCLK_Frequency,
               wakeup_config.HCLK_Frequency,
               wakeup_config.PCLK1_Frequency,
               wakeup_config.PCLK2_Frequency,
               wakeup_source);
        printf("配置后时钟频率:\n"
               "SYSTICK:%d\n"
               "HCLK:%d\n"
               "PCLK1:%d\n"
               "PCLK2:%d\n"
               "时钟源(0:HSI,1:HSE,2:PLL):%d\n",
               normal_config.SYSCLK_Frequency,
               normal_config.HCLK_Frequency,
               normal_config.PCLK1_Frequency,
               normal_config.PCLK2_Frequency,
               normal_source);
    }
}
void End()
{
}