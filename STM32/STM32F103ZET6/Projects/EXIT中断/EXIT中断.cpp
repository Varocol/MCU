#include "Libraries.h"
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