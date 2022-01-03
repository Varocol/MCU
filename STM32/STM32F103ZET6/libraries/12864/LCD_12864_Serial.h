#ifndef __OJ_LCD_12864_SERIAL_H
#define __OJ_LCD_12864_SERIAL_H
#include "GPIO.h"
#include "SysTick.h"
#include "LCD_12864.h"
//12864串行参数
typedef struct
{
    GPIO_TypeDef *GPIO_CS_PORT;  //CS(RS)端口
    GPIO_TypeDef *GPIO_SID_PORT; //SID(RW)端口
    GPIO_TypeDef *GPIO_SCK_PORT; //SCK(EN)端口
    uint16_t CS_PIN;             //CS(RS)引脚
    uint16_t SID_PIN;            //SID(RW)引脚
    uint16_t SCK_PIN;            //SCK(EN)引脚
} LCD_12864_Param_Serial;

class LCD_12864_Serial : public LCD_12864
{
private:
    LCD_12864_Param_Serial Param;
    GPIO CS;  //片选
    GPIO SID; //数据口
    GPIO SCK; //时钟线
public:
    LCD_12864_Serial();
    LCD_12864_Serial(LCD_12864_Param_Serial Param);                                    //构造函数,传参
    void Set_Param(LCD_12864_Param_Serial Param);                                      //设置参数
    void Update(LCD_12864_Param_Serial Param);                                         //更新
    virtual void Clear_DDRAM();                                                        //清屏并归址
    virtual void Send_Byte(uchar);                                                     //发送字节,从高到低(串行模
    virtual void Write_Cmd(uchar cmd);                                                 //写指令,RS=L,RW=L
    virtual void Write_Data(uchar data);                                               //写数据,RS=H,RW=L
    virtual void Pos(uchar x, uchar y);                                                //字符位置,以中文字符16*16
    virtual void Init();                                                               //初始化,设置并口(有些型号
    virtual void Pin_Init();                                                           //GPIO初始化
    virtual void Check_Busy();                                                         //判断12864是否在忙,一定要
    virtual void Set_CGRAM(uchar num, uchar *p);                                       //写入CGRAM
    virtual void Display_CGRAM(uchar num, uchar x, uchar y);                           //显示CGRAM
    virtual void Show_String(uchar *p, uint16_t row, uint16_t col);                    //在指定位置显示字符串,不能
    virtual void Display_Image(uchar *p);                                              //GDRAM绘图模式
    virtual void Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag);   //以两个字节绘制矩形(可能效
    virtual void Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag); //以点绘制矩形
    virtual void Draw_Point(uchar x, uchar y, uchar flag);                             //画点
    virtual void Clear_GDRAM();                                                        //清空GDRAM
    virtual void Read_GDRAM(uchar x, uchar y);                                         //读取GDRAM数据
    virtual void Set_GDRAMadd(uchar x, uchar y);                                       //设置GDRAM的地址
    virtual uchar Read_Data();                                                         //读数据,RS=H,RW=H(串行不支
    virtual uchar Receive_Byte();                                                      //读取字节,从高到低(串行模
    virtual uchar Read_Status();                                                       //读状态,RS=L,RW=H
};

#endif /*__OJ_LCD_12864_SERIAL_H*/