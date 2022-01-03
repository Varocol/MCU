#include"万年历.h"
/*变量声明*/
bit   shift;                                              //标记界面的切换
/*函数声明*/
void  init();                                             //初始化
void  mainwindow();                                       //主窗口
void  menuwindow();                                       //菜单窗口
void  settimewindow();                                    //时间设置窗口
/*主函数*/
void  main()
{
      init();
      while(1)
      {
            mainwindow();
      }
      
}
/*函数定义*/
void  init()
{
      shift=0;
      LCD12864_init();   
      LCD12864_SET_CGRAM(0,str1);
      LCD12864_SET_CGRAM(1,str2);
}                        
void  mainwindow()
{
      if(check()||shift)
            {
                 shift=0;
                 LCD12864_write_cmd(0x01); 
                 time.year=DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead))+2000;
                 time.month=DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead));
                 time.date=DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead));
                 LCD12864_showstring("    年    月  日",0,0);
                 //20XX年
                 temp=DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead));
                 LCD12864_pos(0,0);
                 LCD12864_write_data('2');
                 LCD12864_write_data('0');
                 LCD12864_write_data(temp/10+'0');
                 LCD12864_write_data(temp%10+'0');
                 //XX月
                 temp=DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead));
                 LCD12864_pos(0,4);
                 if(temp/10)LCD12864_write_data(temp/10+'0');
                 else LCD12864_write_data(' ');
                 LCD12864_write_data(temp%10+'0');
                 //XX日
                 temp=DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead));
                 LCD12864_pos(0,6);
                 if(temp/10)LCD12864_write_data(temp/10+'0');
                 else LCD12864_write_data(' ');
                 LCD12864_write_data(temp%10+'0');
                
                 //星期X
                 temp=DS1302_Read_Data(DayRead);
                 LCD12864_showstring("星期",1,0);
                 if(temp!=3)
                 {
                      LCD12864_write_data(xingqi[(temp-1)*2]);
                      LCD12864_write_data(xingqi[(temp-1)*2+1]);
                 }
                 else 
                 {
                      LCD12864_display_CGRAM(0,1,2);
                 }
                 //显示农历
                 lunar_calendar(&time);
            }
                 //AM or PM
                 temp=DS1302_Read_Data(HourRead);
                 if(temp>>7)
                 {
                      if((temp>>5)%2)
                      {
                          LCD12864_showstring("PM",2,0);
                      }
                      else 
                      {
                          LCD12864_showstring("AM",2,0);
                      }
                 }
            
      
            //XX:XX:XX
            temp=DS1302_convert_Data(HourRead,temp);
            LCD12864_pos(2,2);
            if(temp/10)LCD12864_write_data(temp/10+'0');
            else LCD12864_write_data(' ');
            LCD12864_write_data(temp%10+'0');
            LCD12864_write_data(':');
      
            temp=DS1302_convert_Data(MinuteRead,DS1302_Read_Data(MinuteRead));
            LCD12864_write_data(temp/10+'0');
            LCD12864_write_data(temp%10+'0');
            LCD12864_write_data(':');
      
            temp=DS1302_convert_Data(SecondRead,DS1302_Read_Data(SecondRead));
            LCD12864_write_data(temp/10+'0');
            LCD12864_write_data(temp%10+'0');
            while(temp==DS1302_convert_Data(SecondRead,DS1302_Read_Data(SecondRead)))
            if(keycheck()==1)menuwindow();
}                                       
void  menuwindow()
{
      uchar p=0;
      LCD12864_init();
      while(1)
      {
           
           LCD12864_showstring("→",p,1);
           LCD12864_showstring("设置时间",0,2);
           LCD12864_showstring("设置闹钟",1,2);
           LCD12864_showstring("关于本机",2,2);
           LCD12864_showstring("返回主页面",3,2);
           switch (keycheck())
           {
           case 2:LCD12864_showstring("  ",p,1);p=(p+1)%4;break;
           case 3:LCD12864_showstring("  ",p,1);p=(p+3)%4;break;
           case 4:
                  switch (p)
                  {
                  case 0:settimewindow();break;
                  case 1:break;
                  case 2:break;
                  case 3:shift=1;return;break;
                  }
                  break;
           }
           delay1ms(300);
      }
}
void  settimewindow()
{
      uchar y,m,d,h,i,n,s;
      bit b;
      LCD12864_init();
      DS1302_Write_Data(ProtectWrite,0x00);
      LCD12864_showstring("设置时间",0,2);
      b=1;
      s=1;
      y=DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead));
      m=DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead));
      while(b)
      {

           delay1ms(300);
           LCD12864_pos(1,1);
           LCD12864_write_data(' ');
           LCD12864_write_data('2');
           LCD12864_write_data('0');
           LCD12864_write_data(y/10+'0');
           LCD12864_write_data(y%10+'0');
           LCD12864_write_data('-');
           LCD12864_write_data(m/10+'0');
           LCD12864_write_data(m%10+'0');
           LCD12864_write_data('-');
           LCD12864_write_data(d/10+'0');
           LCD12864_write_data(d%10+'0');
           LCD12864_pos(2,2);
           if(h>10)
           LCD12864_write_data(h/10+'0');
           else
           LCD12864_write_data(' ');
           LCD12864_write_data(h%10+'0');

           LCD12864_write_data(':');

           LCD12864_write_data(i/10+'0');
           LCD12864_write_data(i%10+'0');

           LCD12864_write_data(':');

           LCD12864_write_data(n/10+'0');
           LCD12864_write_data(n%10+'0');
           switch (keycheck())
           {
           case 2:
                  switch (s)
                  {
                      case 1:y=(y+1)%100;break;
                      case 2:m=m%12+1;break;
                      case 4:h=h%24+1;break;
                      case 5:i=(i+1)%60;break;
                      case 6:n=(n+1)%60;break;
                      case 3:switch (m)
                             {
                                 case 1:
                                 case 3:
                                 case 5:
                                 case 7:
                                 case 8:
                                 case 10:
                                 case 12:d=d%31+1;break;
                                 case 2: d=y%4==0?d%29+1:d%28+1;break;
                                 default:d=d%30+1;break;
                             }
                  }
                  break;
           case 3:
                 switch (s)
                  {
                      case 1:y=(y+99)%100;break;
                      case 2:m=(m+10)%12+1;break;
                      case 4:h=(h+22)%24+1;break;
                      case 5:i=(i+59)%60;break;
                      case 6:n=(n+59)%60;break;
                      case 3:switch (m)
                             {
                                 case 1:
                                 case 3:
                                 case 5:
                                 case 7:
                                 case 8:
                                 case 10:
                                 case 12:d=(d+29)%31+1;break;
                                 case 2: d=y%4==0?(d+27)%29+1:(d+26)%28+1;break;
                                 default:d=(d+28)%30+1;break;
                             }
                             
                  }
                  break;
           case 4:if(s==6){b=0;LCD12864_init();}else s++;break;
           }
      }

      DS1302_Write_Data(YearWrite,(y/10<<4)|(y%10));
      DS1302_Write_Data(MonthWrite,(m/10<<4)|(m%10));
      DS1302_Write_Data(DateWrite,(d/10<<4)|(d%10));
      if(h>=12)
      DS1302_Write_Data(HourWrite,((h-12)/10<<4|(h-12)%10)|0xA0);
      else
      DS1302_Write_Data(HourWrite,(h/10<<4|h%10)|0x80);
      DS1302_Write_Data(MinuteWrite,(i/10<<4)|(i%10));
      DS1302_Write_Data(SecondWrite,(n/10<<4)|(n%10));
      
      DS1302_Write_Data(ProtectWrite,0x80);

}