#include "System.h"
/*
    ���Զ���ģʽ
        ɨ��
        ���򴥷� (�������)
        ע�봥�� (�������)
        ������
        ע����
        �Զ�ע��
        ����ת��
        ���Ź�
        �ڲ��¶�
        DMA

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
    system_init();
    ADC_1.Init();
}
void Test()
{
}
void End()
{
}