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
    platform_printf("\n");
    platform_printf("***********����ͷ������Ϣ***********\n");
    platform_printf("�Զ��ع⣺               \t%d\n", GET_CFG[0][1]);
    platform_printf("�ع�ʱ�䣺               \t%d\n", GET_CFG[1][1]);
    platform_printf("ͼ��֡�ʣ�               \t%d\n", GET_CFG[2][1]);
    platform_printf("ͼ����������           \t%d\n", GET_CFG[3][1]);
    platform_printf("ͼ����������           \t%d\n", GET_CFG[4][1]);
    platform_printf("ͼ������ƫ������    \t%d\n", GET_CFG[5][1]);
    platform_printf("ͼ������ƫ������    \t%d\n", GET_CFG[6][1]);
    platform_printf("ͼ�����棺               \t%d\n", GET_CFG[7][1]);
    platform_printf("����ͷ�Ƿ��ʼ��:��\t%s\n", MT9V03X_CFG[8][1] ? "��" : "��");
}

//ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ(�����ʽ�Ѿ�������,����Ķ�,cpu1,cpu2�޷�ʹ��)
void MT9V03x_Show_Info ()
{
    //��ʾ�����̼��汾
    platform_printf("\n");
    platform_printf("�����̼��汾��\t%d\n", MT9V03x_Get_Version());
    //��ʾ�������������
    platform_printf("\n");
    platform_printf("***********����������Ϣ***********\n");
    platform_printf("���ڣ�                 \tUART0\n");
    platform_printf("UART TX��            \tP02_2\n");
    platform_printf("UART RX��            \tP02_3\n");
    platform_printf("���ж����ţ�          \tP02_0\n");
    platform_printf("D0���ţ�               \tP02_0\n");
    platform_printf("����ʱ�����ţ�         \tP02_1\n");
    platform_printf("DMAͨ����              \tDMA5\n");
    //��ʾ���������ͷ������Ϣ
    platform_printf("\n");
    platform_printf("***********����ͷ������Ϣ***********\n");
    platform_printf("�Զ��ع⣺              \t%d\n", GET_CFG[0][1]);
    platform_printf("�ع�ʱ�䣺              \t%d\n", GET_CFG[1][1]);
    platform_printf("ͼ��֡�ʣ�              \t%d\n", GET_CFG[2][1]);
    platform_printf("ͼ����������          \t%d\n", GET_CFG[3][1]);
    platform_printf("ͼ����������          \t%d\n", GET_CFG[4][1]);
    platform_printf("ͼ������ƫ������        \t%d\n", GET_CFG[5][1]);
    platform_printf("ͼ������ƫ������        \t%d\n", GET_CFG[6][1]);
    platform_printf("ͼ�����棺              \t%d\n", GET_CFG[7][1]);
    platform_printf("����ͷ�Ƿ��ʼ����       \t%s\n", MT9V03X_CFG[8][1] ? "��" : "��");
    //��ʾ���������ͷָ���б�
    platform_printf("\n");
    platform_printf("***********����ͷָ���б�***********\n");
    platform_printf("����ͷ��ʼ�����       \t%d\n", INIT);
    platform_printf("�Զ��ع����              \t%d\n", AUTO_EXP);
    platform_printf("�ع�ʱ�����              \t%d\n", EXP_TIME);
    platform_printf("����ͷ֡�����          \t%d\n", FPS);
    platform_printf("ͼ�������          \t%d\n", SET_COL);
    platform_printf("ͼ�������          \t%d\n", SET_ROW);
    platform_printf("ͼ������ƫ�����       \t%d\n", LR_OFFSET);
    platform_printf("ͼ������ƫ�����       \t%d\n", UD_OFFSET);
    platform_printf("ͼ��ƫ�����              \t%d\n", GAIN);
    platform_printf("���������ع�ʱ�����     \t%d\n", SET_EXP_TIME);
    platform_printf("��ȡ����ͷ�������   \t%d\n", GET_STATUS);
    platform_printf("�̼��汾�����          \t%d\n", GET_VERSION);
    platform_printf("�Ĵ�����ַ���          \t%d\n", SET_ADDR);
    platform_printf("�Ĵ����������          \t%d\n", SET_DATA);
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
