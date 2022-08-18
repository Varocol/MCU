#ifndef __OJ_LCD_12864_PARALLEL_H
#define __OJ_LCD_12864_PARALLEL_H
#include "LCD_12864.h"
#include "GPIO.h"
//12864���в���
typedef struct
{
  PIN_enum IO_PIN;            //����8λ���ݶ˿�
  PIN_enum RS_PIN;            //RS����
  PIN_enum RW_PIN;            //RW����
  PIN_enum EN_PIN;            //EN����
} LCD_12864_Param_Parallel;

class LCD_12864_Parallel : public LCD_12864
{
private:
  LCD_12864_Param_Parallel Param;
  GPIO RS; //���������ѡ��
  GPIO RW; //��дѡ��
  GPIO EN; //ʱ����s
  GPIO IO; //IO���ݿ�
  uchar temp, Hbit, Lbit;

public:
  LCD_12864_Parallel();
  LCD_12864_Parallel(LCD_12864_Param_Parallel Param);                                //���췽��,����
  void Set_Param(LCD_12864_Param_Parallel Param);                                    //���ò���
  void Update(LCD_12864_Param_Parallel Param);                                       //����
  virtual void Clear_DDRAM();                                                        //��������ַ
  virtual void Send_Byte(uchar byte);                                                //�����ֽ�,�Ӹߵ���(����ģʽ)
  virtual void Write_Cmd(uchar cmd);                                                 //дָ��,RS=L,RW=L
  virtual void Write_Data(uchar data);                                               //д����,RS=H,RW=L
  virtual void Pos(uchar x, uchar y);                                                //�ַ�λ��,�������ַ�16*16����Ϊ��λ
  virtual void Init();                                                               //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
  virtual void Pin_Init();                                                           //GPIO��ʼ��
  virtual void Check_Busy();                                                         //�ж�12864�Ƿ���æ,һ��Ҫ��,������ܵ������ݶ�ʧ
  virtual void Set_CGRAM(uchar num, uchar *p);                                       //д��CGRAM
  virtual void Display_CGRAM(uchar num, uchar x, uchar y);                           //��ʾCGRAM
  virtual void Show_String(uchar *p, uint16_t row, uint16_t col);                    //��ָ��λ����ʾ�ַ���,���ܰ�vscode������ʾ�ĺ�����ռλ������ʵ��λ�����������ľ���ռ2���ֽڵ�
  virtual void Display_Image(uchar *p);                                              //GDRAM��ͼģʽ
  virtual void Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag);   //�������ֽڻ��ƾ���(����Ч���Ը�)
  virtual void Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag); //�Ե���ƾ���
  virtual void Draw_Point(uchar x, uchar y, uchar flag);                             //����
  virtual void Clear_GDRAM();                                                        //���GDRAM
  virtual void Read_GDRAM(uchar x, uchar y);                                         //��ȡGDRAM����
  virtual void Set_GDRAMadd(uchar x, uchar y);                                       //����GDRAM�ĵ�ַ
  virtual uchar Read_Data();                                                         //������,RS=H,RW=H(���в�֧�ֶ�ȡ��Ļ����)
  virtual uchar Receive_Byte();                                                      //��ȡ�ֽ�,�Ӹߵ���(����ģʽ)
  virtual uchar Read_Status();                                                       //��״̬,RS=L,RW=H
};

#endif /*__OJ_LCD_12864_PARALLEL_H*/