#include "System.h"
#define sleep_mode 1
/*
    KEY1 PA0
    KEY2 PC13
    实验:
        进入睡眠模式,流程:使用LED1指示程序正在运行,然后按下KEY2后进入睡眠,进入睡眠后LED1不再变化,按下KEY1唤醒内核重复执行上述操作。
        注：__WFI()指令不能放在中断函数内运行,否则会导致程序卡死,__WFE()可以。
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
    //初始化KEY1、KEY2以及对应的外部中断
    GPIO KEY1 = GPIO(PA0, GPIO_Mode_IN_FLOATING);
    GPIO KEY2 = GPIO(PC13, GPIO_Mode_IN_FLOATING);
    KEY1.Init();
    KEY2.Init();
#if sleep_mode == 0
    //使用__WFI()进入睡眠模式
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

#elif sleep_mode == 1
    //使用__WFE()进入睡眠模式
    EXTI_InitTypeDef EXTI_KEY1_InitStructure = {
        .EXTI_Line = EXTI_Line0,
        .EXTI_Mode = EXTI_Mode_Event,
        .EXTI_Trigger = EXTI_Trigger_Rising,
        .EXTI_LineCmd = ENABLE};
    EXTI_Operate EXTI_KEY1 = EXTI_Operate(EXTI_KEY1_InitStructure, GPIOA);

    NVIC_InitTypeDef EXTI_KEY2_NVIC_InitStructure = {
        .NVIC_IRQChannel = EXTI15_10_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 3,
        .NVIC_IRQChannelCmd = ENABLE};
    EXTI_InitTypeDef EXTI_KEY2_InitStructure = {
        .EXTI_Line = EXTI_Line13,
        .EXTI_Mode = EXTI_Mode_Interrupt,
        .EXTI_Trigger = EXTI_Trigger_Rising,
        .EXTI_LineCmd = ENABLE};
    EXTI_Operate EXTI_KEY2 = EXTI_Operate(EXTI_KEY2_InitStructure, EXTI_KEY2_NVIC_InitStructure, GPIOC);
    EXTI_KEY2.Init();
#endif
    EXTI_KEY1.Init();
}
void Test()
{
    while (1)
    {
        printf("\r\n程序正在运行...\r\n");
        LED_1.Toggle();
        SysTick_Operate::Delay_ms(1000);
        LED_1.Toggle();
        SysTick_Operate::Delay_ms(1000);
#if sleep_mode == 0
        __WFI();
#elif sleep_mode == 1
        // __WFE();
#endif
    }
}
void End()
{
}