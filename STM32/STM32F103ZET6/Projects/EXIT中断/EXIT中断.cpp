#include "Libraries.h"
/*
    测试：
        使用板载KEY1改变LED状态(注意！！！按键的引脚一定要配置过)
        效果并不佳
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
    USART_1.Init();
    LED_1.Init();
    //将按键所在的引脚配置成不同的模式
    GPIO KEY1 = GPIO(PA0, GPIO_Mode_IN_FLOATING);
    KEY1.Init();
    NVIC_InitTypeDef EXTI_KEY1_NVIC_InitStructure = {
        EXTI0_IRQn,
        0,
        2,
        ENABLE};
    EXTI_InitTypeDef EXTI_KEY1_InitStructure = {
        EXTI_Line0,
        EXTI_Mode_Interrupt,
        EXTI_Trigger_Rising,
        ENABLE};
    EXTI_Operate EXTI_KEY1 = EXTI_Operate(EXTI_KEY1_InitStructure, NVIC_Operate(EXTI_KEY1_NVIC_InitStructure), GPIOA);
    EXTI_KEY1.Init();
    printf("已初始化完成!\n");
}
void Test()
{
    while (1)
        ;
}
void End()
{
}