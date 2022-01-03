#ifndef __OJ_LCD_12864_H
#define __OJ_LCD_12864_H
#include "stm32f10x.h"
#include "String_CPP.h"
class LCD_12864
{
private:
public:
    virtual void Clear_DDRAM() = 0;                                                        //��������ַ
    virtual void Send_Byte(uchar) = 0;                                                     //�����ֽ�,�Ӹߵ���(����ģʽ)
    virtual void Write_Cmd(uchar cmd) = 0;                                                 //дָ��,RS=L,RW=L
    virtual void Write_Data(uchar data) = 0;                                               //д����,RS=H,RW=L
    virtual void Pos(uchar x, uchar y) = 0;                                                //�ַ�λ��,�������ַ�16*16����Ϊ��λ
    virtual void Init() = 0;                                                               //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
    virtual void Pin_Init() = 0;                                                           //GPIO��ʼ��
    virtual void Check_Busy() = 0;                                                         //�ж�12864�Ƿ���æ,һ��Ҫ��,������ܵ������ݶ�ʧ
    virtual void Set_CGRAM(uchar num, uchar *p) = 0;                                       //д��CGRAM
    virtual void Display_CGRAM(uchar num, uchar x, uchar y) = 0;                           //��ʾCGRAM
    virtual void Show_String(uchar *p, uint16_t row, uint16_t col) = 0;                    //��ָ��λ����ʾ�ַ���,���ܰ�vscode������ʾ�ĺ�����ռλ������ʵ��λ�����������ľ���ռ2���ֽڵ�
    virtual void Display_Image(uchar *p) = 0;                                              //GDRAM��ͼģʽ
    virtual void Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag) = 0;   //�������ֽڻ��ƾ���(����Ч���Ը�)
    virtual void Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag) = 0; //�Ե���ƾ���
    virtual void Draw_Point(uchar x, uchar y, uchar flag) = 0;                             //����
    virtual void Clear_GDRAM() = 0;                                                        //���GDRAM
    virtual void Read_GDRAM(uchar x, uchar y) = 0;                                         //��ȡGDRAM����
    virtual void Set_GDRAMadd(uchar x, uchar y) = 0;                                       //����GDRAM�ĵ�ַ
    virtual uchar Read_Data() = 0;                                                         //������,RS=H,RW=H(���в�֧�ֶ�ȡ��Ļ����)
    virtual uchar Receive_Byte() = 0;                                                      //��ȡ�ֽ�,�Ӹߵ���(����ģʽ)
    virtual uchar Read_Status() = 0;                                                       //��״̬,RS=L,RW=H
};

#endif /*__OJ_LCD_12864_H*/
