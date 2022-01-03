#ifndef __OJ_IPS_114_H
#define __OJ_IPS_114_H
#include "SPI.h"
#include "GPIO.h"
//常用颜色枚举，需要的可以自行加入
typedef enum
{
    IPS_RED = 0xF800,       //红色
    IPS_BLUE = 0x001F,      //蓝色
    IPS_YELLOW = 0xFFE0,    //黄色
    IPS_GREEN = 0x07E0,     //绿色
    IPS_WHITE = 0xFFFF,     //白色
    IPS_BLACK = 0x0000,     //黑色
    IPS_GRAY = 0x8430,      //灰色
    IPS_BROWN = 0xBC40,     //棕色
    IPS_PURPLE = 0xF81F,    //紫色
    IPS_PINK = 0xFE19       //粉色
} IPS_114_Color;

//IPS114显示方向
//0 竖屏模式
//1 竖屏模式  旋转180
//2 横屏模式
//3 横屏模式  旋转180
typedef enum
{
    Direction0,             //0 竖屏模式
    Direction1,             //1 竖屏模式  旋转180
    Direction2,             //2 横屏模式
    Direction3              //3 横屏模式  旋转180
} IPS_114_DISPLAY_DIR;

//IPS_114参数结构体
typedef struct
{
        PIN_enum IPS_114_BL_PIN;            //IPS_114 液晶背光引脚
        PIN_enum IPS_114_REST_PIN;          //IPS_114 液晶复位引脚
        PIN_enum IPS_114_DC_PIN;            //IPS_114 液晶命令位引脚
        IPS_114_Color IPS_114_PENCOLOR;     //IPS_114 写字笔颜色
        IPS_114_Color IPS_114_BGCOLOR;      //IPS_114 背景颜色
        uint16 IPS_114_Width;               //IPS_114 宽度
        uint16 IPS_114_Height;              //IPS_114 高度
        IPS_114_DISPLAY_DIR Dir;            //IPS_114 显示方向
} IPS_114_Param;

class IPS_114 : public SPI
{
    private:
        IPS_114_Param Param;
        GPIO *IPS_114_BL_PIN;
        GPIO *IPS_114_REST_PIN;
        GPIO *IPS_114_DC_PIN;
        uint16 IPS_114_X_MAX;
        uint16 IPS_114_Y_MAX;
        void Write_Index (uint8 dat);
        void Write_Data (uint8 dat);
        void Write_Data_16bit (uint16 dat);
        void Set_Region (uint16 x1, uint16 y1, uint16 x2, uint16 y2);
    public:
        IPS_114 ();
        ~IPS_114 ();
        IPS_114 (IPS_114_Param Param1, SPI_Param Param2);
        void Set_Param (IPS_114_Param Param, SPI_Param Param2);
        void Pin_Init ();
        void Init ();
        void Clear (IPS_114_Color Color);
        void Draw_Point (uint16 x, uint16 y, IPS_114_Color Color);
        void Show_Char (uint16 x, uint16 y, const int8 dat);
        void Show_String (uint16 x, uint16 y, const int8 dat[]);
        void Show_Num (uint16 x, uint16 y, int32 num);
        void Show_Float (uint16 x, uint16 y, double dat, uint8 num, uint8 pointnum);
        void Displayimage_032 (uint8 *p, uint16 width, uint16 height);
        void Displayimage_032_zoom (uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
        void Displayimage_032_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
                uint16 dis_width, uint16 dis_height);
        void Displayimage_8660_zoom (uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
        void Displayimage_8660_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
                uint16 dis_width, uint16 dis_height);
        void Displayimage_7725 (uint8 *p, uint16 width, uint16 height);
        void Display_Chinese (uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, IPS_114_Color color);
};

#endif /*__OJ_IPS_114_H*/
