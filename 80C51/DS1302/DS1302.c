#include"DS1302.h"
#include"12864libs.h"
#include"string.h"
#include"delay.h"
uchar str[21],str1[21];
uchar temp;
uchar code str2 []=
{
0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00/*"三"*/
};
void main()
{
     LCD12864_init();
     //设置XX年,XX月,XX日,XX时,XX分,XX秒,星期X,12/24
     DS1302_init();
     //设置2021年
     DS1302_Write_Data(YearWrite,0x21);
     //设置1月份
     DS1302_Write_Data(MonthWrite,0x01);
     //设置23号
     DS1302_Write_Data(DateWrite,0x23);
     //设置星期五
     DS1302_Write_Data(DayWrite,0x06);
     //设置10时,12小时制
     DS1302_Write_Data(HourWrite,0x90);
     //设置52分
     DS1302_Write_Data(MinuteWrite,0x52);
     //设置00秒
     DS1302_Write_Data(SecondWrite,0x00);
     //锁定1302
     DS1302_Write_Data(ProtectWrite,0x80);
     LCD12864_SET_CGRAM(0,str2);  
     while(1)
     {    
          //LCD12864_clear_DDRAM();刷新屏幕
          //合成"20XX年"字符串
          String_numtostring(2000+DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead)),str);
          String_mergestring(str,"年",String_strlen(str),String_strlen("年"),str);
          LCD12864_showstring(str,0,0);
          //合成"01月"字符串
          String_numtostring(DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead)),str);
          String_mergestring(str,"月",String_strlen(str),String_strlen("月"),str);
          LCD12864_showstring(str,0,4);
          //合成"20日"字符串
          String_numtostring(DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead)),str);
          String_mergestring(str,"日",String_strlen(str),String_strlen("日"),str);
          LCD12864_showstring(str,0,6);

          temp=DS1302_Read_Data(HourRead);
          if(temp>>7)
          {
               if((temp>>5)%2)
               {
                   LCD12864_showstring("PM",2,1);
               }
               else 
               {
                   LCD12864_showstring("AM",2,1);
               }
          }
          
          temp=DS1302_Read_Data(DayRead);
          switch (temp)
          {
          case 1:LCD12864_showstring("星期一",1,3);
                 break;
          case 2:LCD12864_showstring("星期二",1,3);
                 break;
          case 3:LCD12864_showstring("星期",1,3);
                 LCD12864_display_CGRAM(0,1,5);
                 break;
          case 4:LCD12864_showstring("星期四",1,3);
                 break;
          case 5:LCD12864_showstring("星期五",1,3);
                 break;
          case 6:LCD12864_showstring("星期六",1,3);
                 break; 
          case 7:LCD12864_showstring("星期日",1,3);
                 break;     
          }

          String_numtostring(DS1302_convert_Data(HourRead,DS1302_Read_Data(HourRead)),str);
          String_mergestring(str,":",String_strlen(str),String_strlen(":"),str);
          String_numtostring(DS1302_convert_Data(MinuteRead,DS1302_Read_Data(MinuteRead)),str1);
          String_mergestring(str,str1,String_strlen(str),String_strlen(str1),str);
          LCD12864_showstring(str,2,3);

          temp=DS1302_Read_Data(SecondRead);
          String_numtostring(DS1302_convert_Data(SecondRead,temp),str);
          LCD12864_showstring(str,3,7);
          delay1ms(900);
          while(temp==DS1302_Read_Data(SecondRead));
     }
     
}