#include "core1_main.h"
void core1_setup ()
{
    //�����źŵƳ�ʼ��
    Sinal_Light_Init();
    //��Ļ��ʼ��
    Screen_Init();
    //����ͷ��ʼ��
    MT9V03x_Init();
    //��ȡ���������ͷ������Ϣ
    MT9V03x_Get_Conf();
    //ͨ��RT-Thread Finsh ��ʾ���������ͷ������Ϣ
    MT9V03x_Show_Info();
}
void core1_loop ()
{
    //ʹ��ͼ��ʱ��Ҫͬʱʹ��Buffer_image,mt9v03x_image,Result_image,temp_image
    if (MT9V03x_IMG_Complete())
    {
        MT9V03x_Clear_Flag();
        //�ȸ���һ��ͼ��
        DIP::Grayscale_Identity((uint8*) mt9v03x_image, (uint8*) Buffer_image, MT9V03X_H, MT9V03X_W);
        //��ʱ��ʼ
        DIP::FPS_Start();
        //Otsu��ֵ��
        DIP::Global_Otsu_Better((uint8*) Buffer_image, (uint8*) Result_image, MT9V03X_H, MT9V03X_W);
        //����Ѱ���Լ�ʶ��Ԫ��
        DIP::Car_Img_Process((uint8*) Buffer_image, (uint8*) Result_image, MT9V03X_H, MT9V03X_W);
        //��ʱ����
        DIP::FPS_End();
        //����֡��
        DIP::Show_FPS();
        //���ͼ����Ļ��
        Screen_Show_Img((uint8*) Result_image, MT9V03X_W, MT9V03X_H);
    }
}

