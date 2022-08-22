#include "Libraries.h"

/*
    ʵ�飺
        ��֤����ģʽ��
        ע�⣺�ٷ��ṩ�Ŀ���ֻ��ͨ��WFI�������ģʽ����ʵ��ѡһ���ɣ�
        ������ĸ����Ա������¼������жϣ������Դ����жϻ����¼���
        ����ʵ���ϴ���ģʽ�¹�������ֹͣ����ζ��CPU��ȫ��������
        ����WFE��WFI���ֽ��뷽ʽֻ��Ϊ����ϵͳ�������ģʽ��
        ���ѵĻ��Ͳ���Ҫ����ʹ�õ����������ֻ��ѷ�ʽ��
    ���ѷ�ʽ��
        WKUP���ŵ������ء�RTC�����¼��������ء�NRST�������ⲿ��λ��IWDG��λ
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
    //��ʼ��LED
    LED_1.Init();
    //��ʼ������
    USART_1.Init();
    //����RTC����
    RTC_x.Init();
    RTC_x.SetAlarm(RTC_Operate::GetCounter() + 10);
}
void Test()
{
    printf("���������ɹ���\n");
    if (PWR_GetFlagStatus(PWR_FLAG_SB) == SET && PWR_GetFlagStatus(PWR_FLAG_WU) == SET)
    {
        printf("�������ѻ����Ӹ�λ\n");
    }
    else
    {
        printf("�Ǵ��������ӻ��Ѹ�λ\n");
    }
    LED_1.Toggle();
    SysTick_Operate::Delay_ms(1000);
    LED_1.Toggle();
    SysTick_Operate::Delay_ms(1000);

    printf("�������ģʽ\n");
    PWR_ClearFlag(PWR_FLAG_SB);
    PWR_ClearFlag(PWR_FLAG_WU);
    PWR_WakeUpPinCmd(ENABLE);
    PWR_EnterSTANDBYMode();
}
void End()
{
}