#ifndef __OJ_LCD_12864_SERIAL_H
#define __OJ_LCD_12864_SERIAL_H
#include "GPIO.h"
#include "SysTick.h"
#include "LCD_12864.h"
//12864���в���
typedef struct
{
    GPIO_TypeDef *GPIO_CS_PORT;  //CS(RS)�˿�
    GPIO_TypeDef *GPIO_SID_PORT; //SID(RW)�˿�
    GPIO_TypeDef *GPIO_SCK_PORT; //SCK(EN)�˿�
    uint16_t CS_PIN;             //CS(RS)����
    uint16_t SID_PIN;            //SID(RW)����
    uint16_t SCK_PIN;            //SCK(EN)����
} LCD_12864_Param_Serial;

class LCD_12864_Serial : public LCD_12864
{
private:
    LCD_12864_Param_Serial Param;
    GPIO CS;  //Ƭѡ
    GPIO SID; //���ݿ�
    GPIO SCK; //ʱ����
public:
    LCD_12864_Serial();
    LCD_12864_Serial(LCD_12864_Param_Serial Param);                                    //���캯��,����
    void Set_Param(LCD_12864_Param_Serial Param);                                      //���ò���
    void Update(LCD_12864_Param_Serial Param);                                         //����
    virtual void Clear_DDRAM();                                                        //��������ַ
    virtual void Send_Byte(uchar);                                                     //�����ֽ�,�Ӹߵ���(����ģ
    virtual void Write_Cmd(uchar cmd);                                                 //дָ��,RS=L,RW=L
    virtual void Write_Data(uchar data);                                               //д����,RS=H,RW=L
    virtual void Pos(uchar x, uchar y);                                                //�ַ�λ��,�������ַ�16*16
    virtual void Init();                                                               //��ʼ��,���ò���(��Щ�ͺ�
    virtual void Pin_Init();                                                           //GPIO��ʼ��
    virtual void Check_Busy();                                                         //�ж�12864�Ƿ���æ,һ��Ҫ
    virtual void Set_CGRAM(uchar num, uchar *p);                                       //д��CGRAM
    virtual void Display_CGRAM(uchar num, uchar x, uchar y);                           //��ʾCGRAM
    virtual void Show_String(uchar *p, uint16_t row, uint16_t col);                    //��ָ��λ����ʾ�ַ���,����
    virtual void Display_Image(uchar *p);                                              //GDRAM��ͼģʽ
    virtual void Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag);   //�������ֽڻ��ƾ���(����Ч
    virtual void Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag); //�Ե���ƾ���
    virtual void Draw_Point(uchar x, uchar y, uchar flag);                             //����
    virtual void Clear_GDRAM();                                                        //���GDRAM
    virtual void Read_GDRAM(uchar x, uchar y);                                         //��ȡGDRAM����
    virtual void Set_GDRAMadd(uchar x, uchar y);                                       //����GDRAM�ĵ�ַ
    virtual uchar Read_Data();                                                         //������,RS=H,RW=H(���в�֧
    virtual uchar Receive_Byte();                                                      //��ȡ�ֽ�,�Ӹߵ���(����ģ
    virtual uchar Read_Status();                                                       //��״̬,RS=L,RW=H
};

#endif /*__OJ_LCD_12864_SERIAL_H*/