#include "System.h"
/*
    ʵ��:
        ����PVD��ع���,ʵ��PVD�ж�(�����Ҫʹ��PVD�¼�,���Կ���AFIO�Ĵ�����EVENTOUT,��������������ź�)��
        �����ʵ��ֻ��ʹ�ô��ڹ���,Ȼ���������ɶ�һ�´���,�������TFT��ʾ��,���������������,������ѹ�Ͳ�����,
        ��Ȼ��ѹ��ֵ�����������
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
    //�����ǿ�PWRʱ��
    RCC_Operate::RCC_Config(PWR, ENABLE);
    //����PVD��ֵ�ȼ�
    PWR_PVDLevelConfig(PWR_PVDLevel_2V9);
    //����PVD��Դ����
    PWR_PVDCmd(ENABLE);
    //����EXTI16�ߵ��ж�
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