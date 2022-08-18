#include "Libraries.h"
#define RTC_CLKSELECT 0
/*
    ʵ�飺
        ��ȷ����RTC�����ʱ��,����RTC�������жϹ��ܡ�
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
    //��������
    USART_1.Init();
    //�����źŵ�
    LED_1.Init();
    //��λ������(������������λ,����bkp�����Լ�RTC��������)
    BKP_DeInit();
    //����PWR��BKPʱ��
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);
    //�������BKP����(��λ��������������,��Ҫ��������)
    PWR_BackupAccessCmd(ENABLE);
#if RTC_CLKSELECT == 0
    //������Ҫ��RTC�ṩ�ź�Դ��ʱ��
    RCC_LSEConfig(RCC_LSE_ON);
    //�ȴ�ʱ��Դ����
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        ;
    //����RTCʱ��Դѡ��(һ��ѡ��LSE,��ΪLSE���ڱ�������,��VBat����,���Կ��Գ����ṩ�ź�)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
#elif RTC_CLKSELECT == 1
    //������Ҫ��RTC�ṩ�ź�Դ��ʱ��
    RCC_LSICmd(ENABLE);
    //�ȴ�ʱ��Դ����
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
        ;
    //����RTCʱ��Դѡ��(һ��ѡ��LSE,��ΪLSE���ڱ�������,��VBat����,���Կ��Գ����ṩ�ź�)
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
#endif
    //ʹ��RTCʱ��
    RCC_RTCCLKCmd(ENABLE);
    //�ȴ�RTCʱ��ͬ��
    RTC_WaitForSynchro();
    //�ȴ��ϴ��������
    RTC_WaitForLastTask();
    //��������ж�
    RTC_ITConfig(RTC_IT_SEC | RTC_IT_ALR, ENABLE);
    //�ȴ��ϴ��������
    RTC_WaitForLastTask();
    //��������ģʽ
    RTC_EnterConfigMode();
    //�ȴ��ϴ��������
    RTC_WaitForLastTask();
    //����RTC��Ƶ
    RTC_SetPrescaler(32768);
    //�ȴ��ϴ��������
    RTC_WaitForLastTask();
    //����RTC����
    RTC_SetCounter(1660705805);
    //�ȴ��ϴ��������
    RTC_WaitForLastTask();
    //���ñ���
    RTC_SetAlarm(1660705865);
    //�˳�����ģʽ
    RTC_ExitConfigMode();
    //����NVIC
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