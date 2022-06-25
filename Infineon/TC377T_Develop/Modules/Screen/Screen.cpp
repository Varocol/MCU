#include "Screen.h"
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
IPS_114 Screen;

/*
 * @brief       屏幕初始化
 * @param       null
 * @return      null
 */
void Screen_Init ()
{
    Screen.Set_Param(IPS_114_param, SPI_param);
    Screen.Init();
}

/*
 * @brief       屏幕显示图像
 * @param       null
 * @return      null
 */
void Screen_Show_Img (uint8 *image, uint16 width, uint16 height)
{
    Screen.Displayimage_032(image, width, height);
}

