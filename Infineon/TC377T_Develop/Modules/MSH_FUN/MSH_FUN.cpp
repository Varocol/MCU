#include "MSH_FUN.h"
#include "Libraries.h"
#include "Modules.h"
//�������OJ_Library.h����Ϊ��Ҫ�õ�����Ŀ⣬ͬʱҲ������MSH_FUN.h
long LED_Test (void)
{
    LED led1 = LED(P20_8, Low_level_lighting);
    led1.Init();
    led1.Pin_Toggle();
    return 0;
}

long Car_Run_Test (void)
{
    //������־
    run_flag = 1;
    //�����źŵƳ�ʼ��
    Sinal_Light_Init();
    platform_printf("�����źŵ��ѳ�ʼ��\n");
    //��Ļ��ʼ��
    Screen_Init();
    platform_printf("��Ļ�ѳ�ʼ��\n");
    //����ͷ��ʼ��
    MT9V03x_Init();
    platform_printf("����ͷ�ѳ�ʼ��\n");
    //��������ʼ��
    Encoder_Init();
    platform_printf("�������ѳ�ʼ��\n");
    //�����ʼ��
    Motor_Init();
    platform_printf("����ѳ�ʼ��\n");
    //�����ʼ��
    Servo_Init();
    platform_printf("����ѳ�ʼ��\n");
    //PID��ʼ��
    PID_Init();
    platform_printf("PID�ѳ�ʼ��\n");
    //��ȡCDF��
    Get_CDF_Table();
    //��ȡ���������ͷ������Ϣ
    MT9V03x_Get_Conf();
    //ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ
    MT9V03x_Show_Info();
    return 0;
}
