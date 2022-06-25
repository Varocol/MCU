#include "core1_main.h"
void core1_setup ()
{
    //工作信号灯初始化
    Sinal_Light_Init();
    //屏幕初始化
    Screen_Init();
    //摄像头初始化
    MT9V03x_Init();
    //获取总钻风摄像头配置信息
    MT9V03x_Get_Conf();
    //通过RT-Thread Finsh 显示总钻风摄像头所有信息
    MT9V03x_Show_Info();
}
void core1_loop ()
{
    //使用图像时不要同时使用Buffer_image,mt9v03x_image,Result_image,temp_image
    if (MT9V03x_IMG_Complete())
    {
        MT9V03x_Clear_Flag();
        //先复制一份图像
        DIP::Grayscale_Identity((uint8*) mt9v03x_image, (uint8*) Buffer_image, MT9V03X_H, MT9V03X_W);
        //计时开始
        DIP::FPS_Start();
        //Otsu二值化
        DIP::Global_Otsu_Better((uint8*) Buffer_image, (uint8*) Result_image, MT9V03X_H, MT9V03X_W);
        //赛道寻线以及识别元素
        DIP::Car_Img_Process((uint8*) Buffer_image, (uint8*) Result_image, MT9V03X_H, MT9V03X_W);
        //计时结束
        DIP::FPS_End();
        //测试帧率
        DIP::Show_FPS();
        //输出图像到屏幕上
        Screen_Show_Img((uint8*) Result_image, MT9V03X_W, MT9V03X_H);
    }
}

