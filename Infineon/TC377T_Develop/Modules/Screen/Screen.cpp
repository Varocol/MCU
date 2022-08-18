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
void Screen_Show_Running_Info ()
{
    Screen_Draw_Line();
    Screen_Show_FPS ();
}

/*
 * @brief       屏幕显示图像
 * @param       null
 * @return      null
 */
void Screen_Show_Img ()
{
    Screen.Displayimage_032(Screen_IMG, Screen_IMG_W, Screen_IMG_H);
}

/*
 * @brief       屏幕显示帧率
 * @param       null
 * @return      null
 */
void Screen_Show_FPS ()
{
    uint16 FPS_X = 100;
    uint16 FPS_Y = 10;
    Screen.Show_Num(FPS_X, FPS_Y, end - start ? 1000 / (end - start) : 0);
}

/*
 * @brief       屏幕显示辅助线
 * @param       null
 * @return      null
 */
void Screen_Draw_Line ()
{
    if (left_findflag)  //如果左边界线存在，则画出左边界线
    {
        for (int i = 0; i < L_edge_count; i++)
        {
            Screen.Draw_Point(L_edge[i].col, L_edge[i].row, IPS_BLUE);
        }
    }
    if (right_findflag)  //如果右边界线存在，则画出右边界线
    {
        for (int i = 0; i < R_edge_count; i++)
        {
            Screen.Draw_Point(R_edge[i].col, R_edge[i].row, IPS_RED);
        }
    }
    if (Mid_count > 0)
    {
        for (int i = 0; i < Mid_count; i++)
            Screen.Draw_Point(Mid_Line[i].col, Mid_Line[i].row, IPS_BLACK);
    }
    if (L_corner_flag)   //画出左拐点
    {
        if (L_corner_col - 2 > 0 && L_corner_row - 2 > 0 && L_corner_row + 2 < Image_W && L_corner_col + 2 < Image_W)
        {
            Screen.Draw_Point(L_corner_col - 2, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 1, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 1, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 1, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 1, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row + 1, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row - 1, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row - 1, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row + 1, IPS_RED);
        }
    }
    if (R_corner_flag)   //画出右拐点
    {
        if (R_corner_col - 2 > 0 && R_corner_row - 2 > 0 && R_corner_row + 2 < Image_W && R_corner_col + 2 < Image_W)
        {
            Screen.Draw_Point(R_corner_col - 2, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 1, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 1, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 1, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 1, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row + 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row - 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row - 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row + 1, IPS_BLUE);
        }
    }
}

