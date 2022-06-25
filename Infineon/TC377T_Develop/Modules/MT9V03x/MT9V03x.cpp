#include "MT9V03x.h"

//��ȡ���������ͷ������Ϣ
void MT9V03x_Get_Conf ()
{
    get_config(MT9V03X_COF_UART, GET_CFG);
}

//��ȡ�����汾��
uint16 MT9V03x_Get_Version ()
{
    //��ȡ����
    return get_version(MT9V03X_COF_UART);
}

//���������������Ϣ
void MT9V03x_Set_Conf ()
{
    set_config(MT9V03X_COF_UART, MT9V03X_CFG);
}

//����������ع�ʱ��
void MT9V03x_Set_exposure_time (uint16 light)
{
    set_exposure_time(MT9V03X_COF_UART, light);
}

//ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ(cpu1,cpu2�޷�ʹ��)
void MT9V03x_Show_Conf ()
{
    rt_kprintf("\n");
    rt_kprintf("***********����ͷ������Ϣ***********\n");
    rt_kprintf("�Զ��ع⣺               \t%d\n", GET_CFG[0][1]);
    rt_kprintf("�ع�ʱ�䣺               \t%d\n", GET_CFG[1][1]);
    rt_kprintf("ͼ��֡�ʣ�               \t%d\n", GET_CFG[2][1]);
    rt_kprintf("ͼ����������           \t%d\n", GET_CFG[3][1]);
    rt_kprintf("ͼ����������           \t%d\n", GET_CFG[4][1]);
    rt_kprintf("ͼ������ƫ������    \t%d\n", GET_CFG[5][1]);
    rt_kprintf("ͼ������ƫ������    \t%d\n", GET_CFG[6][1]);
    rt_kprintf("ͼ�����棺               \t%d\n", GET_CFG[7][1]);
    rt_kprintf("����ͷ�Ƿ��ʼ��:��\t%s\n", MT9V03X_CFG[8][1] ? "��" : "��");
}

//ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ(�����ʽ�Ѿ�������,����Ķ�,cpu1,cpu2�޷�ʹ��)
void MT9V03x_Show_Info ()
{
    //��ʾ�����̼��汾
    rt_kprintf("\n");
    rt_kprintf("�����̼��汾��\t%d\n", MT9V03x_Get_Version());
    //��ʾ�������������
    rt_kprintf("\n");
    rt_kprintf("***********����������Ϣ***********\n");
    rt_kprintf("���ڣ�                 \tUART0\n");
    rt_kprintf("UART TX��            \tP02_2\n");
    rt_kprintf("UART RX��            \tP02_3\n");
    rt_kprintf("���ж����ţ�          \tP02_0\n");
    rt_kprintf("D0���ţ�               \tP02_0\n");
    rt_kprintf("����ʱ�����ţ�         \tP02_1\n");
    rt_kprintf("DMAͨ����              \tDMA5\n");
    //��ʾ���������ͷ������Ϣ
    rt_kprintf("\n");
    rt_kprintf("***********����ͷ������Ϣ***********\n");
    rt_kprintf("�Զ��ع⣺              \t%d\n", GET_CFG[0][1]);
    rt_kprintf("�ع�ʱ�䣺              \t%d\n", GET_CFG[1][1]);
    rt_kprintf("ͼ��֡�ʣ�              \t%d\n", GET_CFG[2][1]);
    rt_kprintf("ͼ����������          \t%d\n", GET_CFG[3][1]);
    rt_kprintf("ͼ����������          \t%d\n", GET_CFG[4][1]);
    rt_kprintf("ͼ������ƫ������        \t%d\n", GET_CFG[5][1]);
    rt_kprintf("ͼ������ƫ������        \t%d\n", GET_CFG[6][1]);
    rt_kprintf("ͼ�����棺              \t%d\n", GET_CFG[7][1]);
    rt_kprintf("����ͷ�Ƿ��ʼ����       \t%s\n", MT9V03X_CFG[8][1] ? "��" : "��");
    //��ʾ���������ͷָ���б�
    rt_kprintf("\n");
    rt_kprintf("***********����ͷָ���б�***********\n");
    rt_kprintf("����ͷ��ʼ�����       \t%d\n", INIT);
    rt_kprintf("�Զ��ع����              \t%d\n", AUTO_EXP);
    rt_kprintf("�ع�ʱ�����              \t%d\n", EXP_TIME);
    rt_kprintf("����ͷ֡�����          \t%d\n", FPS);
    rt_kprintf("ͼ�������          \t%d\n", SET_COL);
    rt_kprintf("ͼ�������          \t%d\n", SET_ROW);
    rt_kprintf("ͼ������ƫ�����       \t%d\n", LR_OFFSET);
    rt_kprintf("ͼ������ƫ�����       \t%d\n", UD_OFFSET);
    rt_kprintf("ͼ��ƫ�����              \t%d\n", GAIN);
    rt_kprintf("���������ع�ʱ�����     \t%d\n", SET_EXP_TIME);
    rt_kprintf("��ȡ����ͷ�������   \t%d\n", GET_STATUS);
    rt_kprintf("�̼��汾�����          \t%d\n", GET_VERSION);
    rt_kprintf("�Ĵ�����ַ���          \t%d\n", SET_ADDR);
    rt_kprintf("�Ĵ����������          \t%d\n", SET_DATA);
}

//������ʼ��
void MT9V03x_Init ()
{
    mt9v03x_init();
}

//����һ֡ͼ������λ��
void MT9V03x_Sendimg_To_PC (uint8 *image, uint16 width, uint16 height)
{
    seekfree_sendimg_03x(MT9V03X_COF_UART, image, width, height);
}

//����һ֡ͼ����IPS114��Ļ
void MT9V03x_Sendimg_To_IPS114 (IPS_114 &Screen, uint8 *image, uint16 width, uint16 height)
{
    Screen.Displayimage_032(image, width, height);
}

//�жϻ������Ƿ���ͼ��
bool MT9V03x_IMG_Complete ()
{
    return mt9v03x_finish_flag;
}

//�����־λ
void MT9V03x_Clear_Flag ()
{
    mt9v03x_finish_flag = 0;
}
