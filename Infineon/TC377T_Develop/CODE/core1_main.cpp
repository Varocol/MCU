#include "core1_main.h"
void core1_setup ()
{
}
void core1_loop ()
{
    //使用图像时不要同时使用Buffer_image,mt9v03x_image,Result_image,temp_image
    if (MT9V03x_IMG_Complete() && run_flag)
    {
        //计时开始
        FPS_Start();
        //图像处理
        Image_Process();
        //计时结束
        FPS_End();
        //显示二值化图像
        Screen_Show_Img();
        //将辅助信息输出到屏幕上
        //包括帧率,电机速度,舵机方向,中线偏移量等
        Screen_Show_Running_Info();
        MT9V03x_Clear_Flag();
    }
}

