#include"DS1302.h"

void main()
{
     DS1302_init();
     //设置2021年
     DS1302_Write_Data(YearWrite,0x21);
     //设置2月份
     DS1302_Write_Data(MonthWrite,0x02);
     //设置21号
     DS1302_Write_Data(DateWrite,0x21);
     //设置星期日
     DS1302_Write_Data(DayWrite,0x07);
     //设置上午8点
     DS1302_Write_Data(HourWrite,0xB0);
     //设置40分
     //DS1302_Write_Data(MinuteWrite,0x15);
     //设置00秒
     //DS1302_Write_Data(SecondWrite,0x00);
     DS1302_Write_Data(ProtectWrite,0x80);
}