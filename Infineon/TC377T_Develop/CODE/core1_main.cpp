#include "core1_main.h"
void core1_setup ()
{
}
void core1_loop ()
{
    //ʹ��ͼ��ʱ��Ҫͬʱʹ��Buffer_image,mt9v03x_image,Result_image,temp_image
    if (MT9V03x_IMG_Complete() && run_flag)
    {
        //��ʱ��ʼ
        FPS_Start();
        //ͼ����
        Image_Process();
        //��ʱ����
        FPS_End();
        //��ʾ��ֵ��ͼ��
        Screen_Show_Img();
        //��������Ϣ�������Ļ��
        //����֡��,����ٶ�,�������,����ƫ������
        Screen_Show_Running_Info();
        MT9V03x_Clear_Flag();
    }
}

