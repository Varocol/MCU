#include"DS1302.h"
#include"12864libs.h"
#include"string.h"
#include"delay.h"
uchar str[21],str1[21];
uchar temp;
uchar code str2 []=
{
0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00/*"��"*/
};
void main()
{
     LCD12864_init();
     //����XX��,XX��,XX��,XXʱ,XX��,XX��,����X,12/24
     DS1302_init();
     //����2021��
     DS1302_Write_Data(YearWrite,0x21);
     //����1�·�
     DS1302_Write_Data(MonthWrite,0x01);
     //����23��
     DS1302_Write_Data(DateWrite,0x23);
     //����������
     DS1302_Write_Data(DayWrite,0x06);
     //����10ʱ,12Сʱ��
     DS1302_Write_Data(HourWrite,0x90);
     //����52��
     DS1302_Write_Data(MinuteWrite,0x52);
     //����00��
     DS1302_Write_Data(SecondWrite,0x00);
     //����1302
     DS1302_Write_Data(ProtectWrite,0x80);
     LCD12864_SET_CGRAM(0,str2);  
     while(1)
     {    
          //LCD12864_clear_DDRAM();ˢ����Ļ
          //�ϳ�"20XX��"�ַ���
          String_numtostring(2000+DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead)),str);
          String_mergestring(str,"��",String_strlen(str),String_strlen("��"),str);
          LCD12864_showstring(str,0,0);
          //�ϳ�"01��"�ַ���
          String_numtostring(DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead)),str);
          String_mergestring(str,"��",String_strlen(str),String_strlen("��"),str);
          LCD12864_showstring(str,0,4);
          //�ϳ�"20��"�ַ���
          String_numtostring(DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead)),str);
          String_mergestring(str,"��",String_strlen(str),String_strlen("��"),str);
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
          case 1:LCD12864_showstring("����һ",1,3);
                 break;
          case 2:LCD12864_showstring("���ڶ�",1,3);
                 break;
          case 3:LCD12864_showstring("����",1,3);
                 LCD12864_display_CGRAM(0,1,5);
                 break;
          case 4:LCD12864_showstring("������",1,3);
                 break;
          case 5:LCD12864_showstring("������",1,3);
                 break;
          case 6:LCD12864_showstring("������",1,3);
                 break; 
          case 7:LCD12864_showstring("������",1,3);
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