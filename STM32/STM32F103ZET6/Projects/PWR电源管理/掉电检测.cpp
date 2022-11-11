#include "System.h"
/*
    实验:
        配置PVD监控功能,实现PVD中断(如果想要使用PVD事件,可以看看AFIO寄存器的EVENTOUT,用于输出高脉冲信号)。
        做这个实验只需使用串口供电,然后作死地松动一下串口,最好配上TFT显示屏,提升串口输出功率,这样电压就不稳了,
        当然电压阈值最好往上升。
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
    //别忘记开PWR时钟
    RCC_Operate::RCC_Config(PWR, ENABLE);
    //配置PVD阈值等级
    PWR_PVDLevelConfig(PWR_PVDLevel_2V9);
    //开启PVD电源管理
    PWR_PVDCmd(ENABLE);
    //配置EXTI16线的中断
    NVIC_InitTypeDef EXTI_PVD_NVIC_InitStructure = {
        .NVIC_IRQChannel = PVD_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority= 2,
        .NVIC_IRQChannelCmd = ENABLE};
    EXTI_InitTypeDef EXTI_PVD_InitStructure = {
        .EXTI_Line = EXTI_Line16,
        .EXTI_Mode = EXTI_Mode_Interrupt,
        .EXTI_Trigger = EXTI_Trigger_Rising_Falling,
        .EXTI_LineCmd = ENABLE};
    EXTI_Operate EXTI_PVD = EXTI_Operate(EXTI_PVD_InitStructure, EXTI_PVD_NVIC_InitStructure);
    EXTI_PVD.Init();
}
void Test()
{
    while (1)
        ;
}
void End()
{
}