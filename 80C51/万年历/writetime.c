#include"DS1302.h"

void main()
{
     DS1302_init();
     //����2021��
     DS1302_Write_Data(YearWrite,0x21);
     //����2�·�
     DS1302_Write_Data(MonthWrite,0x02);
     //����21��
     DS1302_Write_Data(DateWrite,0x21);
     //����������
     DS1302_Write_Data(DayWrite,0x07);
     //��������8��
     DS1302_Write_Data(HourWrite,0xB0);
     //����40��
     //DS1302_Write_Data(MinuteWrite,0x15);
     //����00��
     //DS1302_Write_Data(SecondWrite,0x00);
     DS1302_Write_Data(ProtectWrite,0x80);
}