#include <core0_main.h>
//SPI参数列表
SPI_Param SPI_param = {SPI_2, //定义使用的SPI号
        SPI2_CS0_P15_2,  //定义SPI_CS引脚
        SPI2_SCLK_P15_3, //定义SPI_SCK引脚
        SPI2_MOSI_P15_5, //定义SPI_MOSI引脚
        SPI2_MISO_P15_4, //定义SPI_MISO引脚
        SPI_Mode_0,      //SPI模式(共4种)
        48 * 1000 * 1000 //SPI波特率
};
//IPS_114参数列表
IPS_114_Param IPS_114_param = {P15_4, //液晶背光引脚定义 由于实际通讯未使用P15_4因此 这里复用为GPIO
        P15_1, //液晶复位引脚定义
        P15_0, //液晶命令位引脚定义
        IPS_RED, //定义写字笔的颜色
        IPS_WHITE, //定义背景颜色
        IPS114_W, //定义IPS114最大宽度
        IPS114_H, //定义IPS114最大高度
        Direction3, //定义IPS114显示方向
        };
IPS_114 Screen = IPS_114(IPS_114_param, SPI_param);
void core0_setup ()
{
    //屏幕初始化
    Screen.Init();
    //摄像头初始化
    MT9V03x_Init();
    //获取总钻风摄像头配置信息
    MT9V03x_Get_Conf();
    //通过RT-Thread Finsh 显示总钻风摄像头所有信息
    MT9V03x_Show_Info();
}
void core0_loop ()
{
    if (MT9V03x_IMG_Complete())
    {
        MT9V03x_Clear_Flag();
        //先复制一份图像
        DIP::Grayscale_Identity((uint8*) mt9v03x_image, (uint8*) Buffer_image, MT9V03X_H, MT9V03X_W);
        //直方图均衡化
        DIP::Grayscale_Equalization((uint8*) Buffer_image, (uint8*) Result_image, MT9V03X_H, MT9V03X_W);
        //输出图像到屏幕上
        MT9V03x_Sendimg_To_IPS114(Screen, (uint8*) Result_image, MT9V03X_W, MT9V03X_H);
    }
}
