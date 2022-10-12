#include "System.h"
/*
    ���ԣ�
        ʹ�ð���KEY1�ı�LED״̬(ע�⣡��������������һ��Ҫ���ù�)
        Ч��������
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
    //���������ڵ��������óɲ�ͬ��ģʽ
    GPIO KEY1 = GPIO(PA0, GPIO_Mode_IN_FLOATING);
    KEY1.Init();
    NVIC_InitTypeDef EXTI_KEY1_NVIC_InitStructure = {
        .NVIC_IRQChannel = EXTI0_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 2,
        .NVIC_IRQChannelCmd = ENABLE};
    EXTI_InitTypeDef EXTI_KEY1_InitStructure = {
        .NVIC_IRQChannel = EXTI_Line0,
        .NVIC_IRQChannelPreemptionPriority = EXTI_Mode_Interrupt,
        .NVIC_IRQChannelSubPriority = EXTI_Trigger_Rising,
        .NVIC_IRQChannelCmd = ENABLE};
    EXTI_Operate EXTI_KEY1 = EXTI_Operate(EXTI_KEY1_InitStructure, EXTI_KEY1_NVIC_InitStructure, GPIOA);
    EXTI_KEY1.Init();
    printf("�ѳ�ʼ�����!\n");
}
void Test()
{
    while (1)
        ;
}
void End()
{
}