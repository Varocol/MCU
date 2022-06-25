//���ڸ�Ӳ���������жϺ��������Բ��÷�װ��ֻ������д
#ifndef __OJ_MT9V03X_H
#define __OJ_MT9V03X_H
#include "OJ_Library.h"
#include "headfile.h"

//��ȡ���������ͷ������Ϣ
void MT9V03x_Get_Conf ();
//��ȡ�����汾��
uint16 MT9V03x_Get_Version ();
//���������������Ϣ
void MT9V03x_Set_Conf ();
//����������ع�ʱ��
void MT9V03x_Set_exposure_time (uint16 light);
//ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ,cpu1,cpu2�޷�ʹ��
void MT9V03x_Show_Conf ();
//ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ,cpu1,cpu2�޷�ʹ��
void MT9V03x_Show_Info ();
//������ʼ��
void MT9V03x_Init ();
//����һ֡ͼ������λ��
void MT9V03x_Sendimg_To_PC (uint8 *image, uint16 width, uint16 height);
//����һ֡ͼ����IPS114��Ļ
void MT9V03x_Sendimg_To_IPS114 (IPS_114 &Screen, uint8 *image, uint16 width, uint16 height);
//�жϻ������Ƿ���ͼ��
bool MT9V03x_IMG_Complete ();
//��־λ����
void MT9V03x_Clear_Flag ();

#endif  /*__OJ_MT9V03X_H*/
