#include "Libraries.h"
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
    //��ʼ������
    USART_1.Init();
    //��ʼ���źŵ�
    LED_1.Init();
    //������Դ�ͺ󱸼Ĵ���ʱ��
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);

    //���ź󱸼Ĵ���
    PWR_BackupAccessCmd(ENABLE);
    //�ر�����������
    BKP_TamperPinCmd(DISABLE);
    //�������ŵ�ƽ
    BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low);
    //�����־λ(���������ſ����ڲ���ҪVDD��ʱ����,�����п��������ڼ���������¼�,��Ҫ�ֶ����)
    BKP_ClearFlag();
    //�����ж�
    NVIC_InitTypeDef Tamper_InitStructure =
        {
            TAMPER_IRQn,
            0,
            1,
            ENABLE};
    NVIC_Operate Tamper_NVIC = NVIC_Operate(Tamper_InitStructure);
    Tamper_NVIC.Init();
    BKP_ITConfig(ENABLE);
    //�������ּ������
    BKP_TamperPinCmd(ENABLE);
}
void Test()
{
    //��ȡ�ϵ����
    printf("�ϵ����:%d\n", BKP_ReadBackupRegister(BKP_DR1));
    //д���ϵ����
    BKP_WriteBackupRegister(BKP_DR1, BKP_ReadBackupRegister(BKP_DR1) + 1);
    while (1)
        ;
}
void End()
{
}