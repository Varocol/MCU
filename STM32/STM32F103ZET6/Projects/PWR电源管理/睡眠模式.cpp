#include "Libraries.h"
#define sleep_mode 1
/*
    KEY1 PA0
    KEY2 PC13
    ʵ��:
        ����˯��ģʽ,����:ʹ��LED1ָʾ������������,Ȼ����KEY2�����˯��,����˯�ߺ�LED1���ٱ仯,����KEY1�����ں��ظ�ִ������������
        ע��__WFI()ָ��ܷ����жϺ���������,����ᵼ�³�����,__WFE()���ԡ�
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
    //��ʼ����
    LED_1.Init();
    //��ʼ������
    USART_1.Init();
    //��ʼ��KEY1��KEY2�Լ���Ӧ���ⲿ�ж�
    GPIO KEY1 = GPIO(PA0, GPIO_Mode_IN_FLOATING);
    GPIO KEY2 = GPIO(PC13, GPIO_Mode_IN_FLOATING);
    KEY1.Init();
    KEY2.Init();
#if sleep_mode == 0
    //ʹ��__WFI()����˯��ģʽ
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

#elif sleep_mode == 1
    //ʹ��__WFE()����˯��ģʽ
    EXTI_InitTypeDef EXTI_KEY1_InitStructure = {
        EXTI_Line0,
        EXTI_Mode_Event,
        EXTI_Trigger_Rising,
        ENABLE};
    EXTI_Operate EXTI_KEY1 = EXTI_Operate(EXTI_KEY1_InitStructure, GPIOA);

    NVIC_InitTypeDef EXTI_KEY2_NVIC_InitStructure = {
        EXTI15_10_IRQn,
        0,
        3,
        ENABLE};
    EXTI_InitTypeDef EXTI_KEY2_InitStructure = {
        EXTI_Line13,
        EXTI_Mode_Interrupt,
        EXTI_Trigger_Rising,
        ENABLE};
    EXTI_Operate EXTI_KEY2 = EXTI_Operate(EXTI_KEY2_InitStructure, NVIC_Operate(EXTI_KEY2_NVIC_InitStructure), GPIOC);
    EXTI_KEY2.Init();
#endif
    EXTI_KEY1.Init();
}
void Test()
{
    while (1)
    {

        printf("\r\n������������...\r\n");
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