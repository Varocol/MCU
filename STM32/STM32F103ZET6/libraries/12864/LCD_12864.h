#ifndef __OJ_LCD_12864_H
#define __OJ_LCD_12864_H
#include "stm32f10x.h"
#include "String_CPP.h"
class LCD_12864
{
private:
public:
    virtual void Clear_DDRAM() = 0;                                                        //清屏并归址
    virtual void Send_Byte(uchar) = 0;                                                     //发送字节,从高到低(串行模式)
    virtual void Write_Cmd(uchar cmd) = 0;                                                 //写指令,RS=L,RW=L
    virtual void Write_Data(uchar data) = 0;                                               //写数据,RS=H,RW=L
    virtual void Pos(uchar x, uchar y) = 0;                                                //字符位置,以中文字符16*16点阵为单位
    virtual void Init() = 0;                                                               //初始化,设置并口(有些型号的12864分左右屏)
    virtual void Pin_Init() = 0;                                                           //GPIO初始化
    virtual void Check_Busy() = 0;                                                         //判断12864是否在忙,一定要有,否则可能导致数据丢失
    virtual void Set_CGRAM(uchar num, uchar *p) = 0;                                       //写入CGRAM
    virtual void Display_CGRAM(uchar num, uchar x, uchar y) = 0;                           //显示CGRAM
    virtual void Show_String(uchar *p, uint16_t row, uint16_t col) = 0;                    //在指定位置显示字符串,不能把vscode里面显示的汉字所占位数当作实际位数！！！中文就是占2个字节的
    virtual void Display_Image(uchar *p) = 0;                                              //GDRAM绘图模式
    virtual void Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag) = 0;   //以两个字节绘制矩形(可能效率略高)
    virtual void Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag) = 0; //以点绘制矩形
    virtual void Draw_Point(uchar x, uchar y, uchar flag) = 0;                             //画点
    virtual void Clear_GDRAM() = 0;                                                        //清空GDRAM
    virtual void Read_GDRAM(uchar x, uchar y) = 0;                                         //读取GDRAM数据
    virtual void Set_GDRAMadd(uchar x, uchar y) = 0;                                       //设置GDRAM的地址
    virtual uchar Read_Data() = 0;                                                         //读数据,RS=H,RW=H(串行不支持读取屏幕数据)
    virtual uchar Receive_Byte() = 0;                                                      //读取字节,从高到低(串行模式)
    virtual uchar Read_Status() = 0;                                                       //读状态,RS=L,RW=H
};

#endif /*__OJ_LCD_12864_H*/
