#include "Libraries.h"
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
    //ʹ��RTC���ʼ��
    RTC_x.Init();
}
void Test()
{
    // uint32_t timestamp;
    // uint8_t flag = 0;
    // while (!flag)
    // {
    //     RTC_x.ITConfig(RTC_IT_SEC, DISABLE);
    //     printf("����ʱ��У׼:\n");
    //     scanf("%ld", &timestamp);
    //     RTC_x.SetCounter(timestamp);
    //     RTC_x.ITConfig(RTC_IT_SEC, ENABLE);
    //     printf("У׼�ɹ�������1,��������0:\n");
    //     scanf("%d", &flag);
    // }
    // RTC_x.ITConfig(RTC_IT_SEC, DISABLE);
    // printf("��������ʱ��:\n");
    // scanf("%ld", &timestamp);
    // RTC_x.SetAlarm(timestamp);
    // printf("���óɹ���\n");
    // RTC_x.ITConfig(RTC_IT_SEC, ENABLE);
    // printf("���������ɹ���\n");
    // if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET && PWR_GetFlagStatus(PWR_FLAG_WU) == SET)
    // {
    //     printf("�������ѻ����Ӹ�λ\n");
    //     RTC_x.Init();
    // }
    // else
    // {
    //     printf("�������ģʽ\n");
    //     PWR_ClearFlag(PWR_FLAG_SB);
    //     PWR_ClearFlag(PWR_FLAG_WU);
    //     PWR_WakeUpPinCmd(ENABLE);
    //     PWR_EnterSTANDBYMode();
    // }
    while (1)
        ;
}
void End()
{
}