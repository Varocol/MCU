//测试1302月份,平年闰年校正
#include"DS1302.h"

void main()
{

     /* 
     //测试2月份有几天
     DS1302_init();
     //设置2021年
     DS1302_Write_Data(YearWrite,0x21);
     //设置2月份
     DS1302_Write_Data(MonthWrite,0x02);
     //设置28号
     DS1302_Write_Data(DateWrite,0x28);
     //设置星期日
     DS1302_Write_Data(DayWrite,0x07);
     //设置晚上11点
     DS1302_Write_Data(HourWrite,0xB1);
     //设置59分
     DS1302_Write_Data(MinuteWrite,0x59);
     //设置00秒
     DS1302_Write_Data(SecondWrite,0x00);
     DS1302_Write_Data(ProtectWrite,0x80);
     
     //测试4月份有几天
     DS1302_init();
     //设置2021年
     DS1302_Write_Data(YearWrite,0x21);
     //设置4月份
     DS1302_Write_Data(MonthWrite,0x04);
     //设置30号
     DS1302_Write_Data(DateWrite,0x30);
     //设置星期五
     DS1302_Write_Data(DayWrite,0x05);
     //设置晚上11点
     DS1302_Write_Data(HourWrite,0xB1);
     //设置59分
     DS1302_Write_Data(MinuteWrite,0x59);
     //设置00秒
     DS1302_Write_Data(SecondWrite,0x00);
     DS1302_Write_Data(ProtectWrite,0x80);
     */
     //测试2020年2月份有几天
     DS1302_init();
     //设置2020年
     DS1302_Write_Data(YearWrite,0x20);
     //设置2月份
     DS1302_Write_Data(MonthWrite,0x02);
     //设置28号
     DS1302_Write_Data(DateWrite,0x28);
     //设置星期日
     DS1302_Write_Data(DayWrite,0x07);
     //设置晚上11点
     DS1302_Write_Data(HourWrite,0xB1);
     //设置59分
     DS1302_Write_Data(MinuteWrite,0x59);
     //设置00秒
     DS1302_Write_Data(SecondWrite,0x00);
     DS1302_Write_Data(ProtectWrite,0x80);
}