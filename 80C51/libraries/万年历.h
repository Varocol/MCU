#include<REG52.H>
#include<INTRINS.H>
#include<math.h>
#include"DS1302name.h"
#define uint  unsigned int
#define uchar unsigned char

/*变量声明*/
uchar byte1,byte2,byte3,byte4,byte5,flag;//DHT11

struct Time
{
    uchar month,date;
    uint  year;
}time;                                   //时间结构体
struct nongli
{
    uchar run;
    uchar month[13];
    struct Time  chunjie;
}G;
uchar  temp;
uchar  code yue[49]="  月二月  月四月五月六月七月八月九月十月冬月腊月";
uchar  code ri [121]="初一初二初  初四初五初六初七初八初九初十十一十二十  十四十五十六十七十八十九二十廿一廿二廿  廿四廿五廿六廿七廿八廿九  十";//字符数手动规定死
uchar  code xingqi[15]="一二  四五六日";
uchar  code str1[]=
{
0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00/*"三"*/
};
uchar  code str2[]=
{     
0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0xF8,
0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00/*"正"*/
};
uchar  code T[][3]=
{
{0x09,0x2e,0x50}, //1999         
{0x0C,0x96,0x45}, //2000
{0x4d,0x4A,0xB8}, //2001
{0x0d,0x4A,0x4C}, //2002
{0x0d,0xA5,0x41}, //2003
{0x25,0xAA,0xB6}, //2004
{0x05,0x6A,0x49}, //2005
{0x7A,0xAd,0xBd}, //2006
{0x02,0x5d,0x52}, //2007
{0x09,0x2d,0x47}, //2008
{0x5C,0x95,0xBA}, //2009
{0x0A,0x95,0x4e}, //2010
{0x0B,0x4A,0x43}, //2011
{0x4B,0x55,0x37}, //2012
{0x0A,0xd5,0x4A}, //2013
{0x95,0x5A,0xBf}, //2014
{0x04,0xBA,0x53}, //2015
{0x0A,0x5B,0x48}, //2016
{0x65,0x2B,0xBC}, //2017
{0x05,0x2B,0x50}, //2018
{0x0A,0x93,0x45}, //2019
{0x47,0x4A,0xB9}, //2020
{0x06,0xAA,0x4C}, //2021
{0x0A,0xd5,0x41}, //2022
{0x24,0xdA,0xB6}, //2023
{0x04,0xB6,0x4A}, //2024
{0x69,0x57,0x3d}, //2025
{0x0A,0x4e,0x51}, //2026
{0x0d,0x26,0x46}, //2027
{0x5e,0x93,0x3A}, //2028
{0x0d,0x53,0x4d}, //2029
{0x05,0xAA,0x43}, //2030
{0x36,0xB5,0x37}, //2031
{0x09,0x6d,0x4B}, //2032
{0xB4,0xAe,0xBf}, //2033
{0x04,0xAd,0x53}, //2034
{0x0A,0x4d,0x48}, //2035
{0x6d,0x25,0xBC}, //2036
{0x0d,0x25,0x4f}, //2037
{0x0d,0x52,0x44}, //2038
{0x5d,0xAA,0x38}, //2039
{0x0B,0x5A,0x4C}, //2040
{0x05,0x6d,0x41}, //2041
{0x24,0xAd,0xB6}, //2042
{0x04,0x9B,0x4A}, //2043
{0x7A,0x4B,0xBe}, //2044
{0x0A,0x4B,0x51}, //2045
{0x0A,0xA5,0x46}, //2046
{0x5B,0x52,0xBA}, //2047
{0x06,0xd2,0x4e}, //2048
{0x0A,0xdA,0x42}, //2049
{0x35,0x5B,0x37}, //2050
{0x09,0x37,0x4B}, //2051
{0x84,0x97,0xC1}, //2052
{0x04,0x97,0x53}, //2053
{0x06,0x4B,0x48}, //2054
{0x66,0xA5,0x3C}, //2055
{0x0e,0xA5,0x4f}, //2056
{0x06,0xB2,0x44}, //2057
{0x4A,0xB6,0x38}, //2058
{0x0A,0xAe,0x4C}, //2059
{0x09,0x2e,0x42}, //2060
{0x3C,0x97,0x35}, //2061
{0x0C,0x96,0x49}, //2062
{0x7d,0x4A,0xBd}, //2063
{0x0d,0x4A,0x51}, //2064
{0x0d,0xA5,0x45}, //2065
{0x55,0xAA,0xBA}, //2066
{0x05,0x6A,0x4e}, //2067
{0x0A,0x6d,0x43}, //2068
{0x45,0x2e,0xB7}, //2069
{0x05,0x2d,0x4B}, //2070
{0x8A,0x95,0xBf}, //2071
{0x0A,0x95,0x53}, //2072
{0x0B,0x4A,0x47}, //2073
{0x6B,0x55,0x3B}, //2074
{0x0A,0xd5,0x4f}, //2075
{0x05,0x5A,0x45}, //2076
{0x4A,0x5d,0x38}, //2077
{0x0A,0x5B,0x4C}, //2078
{0x05,0x2B,0x42}, //2079
{0x3A,0x93,0xB6}, //2080
{0x06,0x93,0x49}, //2081
{0x77,0x29,0xBd}, //2082
{0x06,0xAA,0x51}, //2083
{0x0A,0xd5,0x46}, //2084
{0x54,0xdA,0xBA}, //2085
{0x04,0xB6,0x4e}, //2086
{0x0A,0x57,0x43}, //2087
{0x45,0x27,0x38}, //2088
{0x0d,0x26,0x4A}, //2089
{0x8e,0x93,0x3e}, //2090
{0x0d,0x52,0x52}, //2091
{0x0d,0xAA,0x47}, //2092
{0x66,0xB5,0x3B}, //2093
{0x05,0x6d,0x4f}, //2094
{0x04,0xAe,0x45}, //2095
{0x4A,0x4e,0xB9}, //2096
{0x0A,0x4d,0x4C}, //2097
{0x0d,0x15,0x41}, //2098
{0x2d,0x92,0xB5}, //2099
{0x0d,0x53,0x49} //2100
};
/*接口声明*/
//LCD12864
sbit LCD_CS =P2^7;               //RS
sbit LCD_SID=P2^6;               //RW
sbit LCD_SCK=P2^5;               //EN
//DHT11
sbit DHT=P2^0;
//DS1302
sbit DS1302_CE = P1^0;           //rst
sbit DS1302_SK = P1^1;           //时钟
sbit DS1302_IO = P1^2;           //数据口
//矩阵键盘
sbit C4=P2^1;
sbit C3=P2^2;
sbit C2=P2^3;
sbit C1=P2^4;
/*函数声明*/
//LCD12864
void  LCD12864_sendbyte(uchar);                    //发送字节,从高到低
void  LCD12864_write_cmd(uchar);                   //写指令,RS=L,RW=L
void  LCD12864_write_data(uchar);                  //写数据,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);                   //字符位置,以中文字符16*16点阵为单位
void  LCD12864_init();                             //初始化,设置并口(有些型号的12864分左右屏)
void  LCD12864_check_busy();                       //判断12864是否在忙,一定要有,否则可能导致数据丢失
void  LCD12864_SET_CGRAM(uchar,uchar*);            //写入CGRAM
void  LCD12864_display_CGRAM(uchar,uchar,uchar);   //显示CGRAM
void  LCD12864_showstring(uchar*,uint,uint);       //不能把vscode里面显示的汉字所占位数当作实际位数！！！中文就是占2个字节的
uchar LCD12864_read_status();                      //读状态,RS=L,RW=H
uchar LCD12864_receivebyte();                      //读取字节,从高到低

//DS1302
uchar DS1302_Read_Data (uchar);                    //读数据
uchar DS1302_convert_Data(uchar,uchar);            //转换数据
void  DS1302_Write_Data(uchar,uchar);              //写入数据
//DHT11
void  DHT11_delay40us();
void  DHT11_delay50us();
void  DHT11_delay18ms();
void  DHT11_delay1s();
void  DHT11_init();
void  DHT11_check();
uchar DHT11_readbyte();

//延时
void  delay1ms(uint);

//按键检测
uchar keycheck();
//农历计算
void  lunar_calendar(struct Time*);                //计算农历 
void  nonglicalculate(uint);                       //提取农历信息
uint  calculateday(struct Time*,struct Time*);     //计算天数  
bit   check();                                     //判断是否需要更新年月日

/*函数定义*/
//LCD12864
void  LCD12864_sendbyte(uchar Data)
{
      uchar i;
      for(i=0;i<8;i++)
      {
          LCD_SCK=0;
          LCD_SID=Data>>7;          
          Data<<=1;
          LCD_SCK=1;
          LCD_SCK=0;
      }
}
void  LCD12864_write_cmd(uchar cmd)
{
      LCD_CS=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xf8);
      LCD12864_sendbyte(0xf0&cmd);
      LCD12864_sendbyte(0xf0&cmd<<4);
      LCD_CS=0;
}
void  LCD12864_write_data(uchar Data)
{
      LCD_CS=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xfa);
      LCD12864_sendbyte(0xf0&Data);
      LCD12864_sendbyte(0xf0&Data<<4);
      LCD_CS=0;
}
void  LCD12864_pos(uchar x,uchar y)
{
    switch (x)
    {
    case 0:x=0x80;
           break;
    case 1:x=0x90;
           break;
    case 2:x=0x88;
           break;
    case 3:x=0x98;
           break;
    }
    LCD12864_write_cmd(x+y);
}
void  LCD12864_init()
{
      LCD12864_write_cmd(0x30);
      LCD12864_write_cmd(0x0C);
      LCD12864_write_cmd(0x01);
      LCD12864_write_cmd(0x06);
}
void  LCD12864_check_busy()
{
      do ;
      while(LCD12864_read_status()&0x80);
}
void  LCD12864_SET_CGRAM(uchar num,uchar *p)
{
      uchar i,firstadd;
      LCD12864_write_cmd(0x34);             //扩充指令集
      LCD12864_write_cmd(0x02);             //第13条,允许设置CGRAM地址
      LCD12864_write_cmd(0x30);             //回到基本指令集
      firstadd=(0x40|num<<4);
      for(i=0;i<16;i++)
      {
          LCD12864_write_cmd(firstadd+i);   //设置纵坐标
          LCD12864_write_data(p[i*2]);
          LCD12864_write_data(p[i*2+1]);
      }
}
void  LCD12864_display_CGRAM(uchar num,uchar x,uchar y)
{
      LCD12864_pos(x,y);
      LCD12864_write_data(0x00);            //CGRAM当作数据调用
      LCD12864_write_data(num*2);
}
void  LCD12864_showstring(uchar*p,uint row,uint col)
{
      uchar i;
      LCD12864_pos(row,col);
      for(i=0;p[i]!='\0';i++)
      {
            LCD12864_write_data(p[i]);
      }
}
uchar LCD12864_read_status()
{
      LCD12864_sendbyte(0xfc);
      return LCD12864_receivebyte();
}
uchar LCD12864_receivebyte()
{
      uchar tmp1,tmp2,i;
      tmp1=0;
      tmp2=0;
      for(i=0;i<8;i++)
      {          
          tmp1<<=1;
          LCD_SCK=0;
          LCD_SCK=1;
          LCD_SCK=0;
          if(LCD_SID)tmp1++;
      }
      for(i=0;i<8;i++)
      {          
          tmp2<<=1;
          LCD_SCK=0;
          LCD_SCK=1;
          LCD_SCK=0;
          if(LCD_SID)tmp2++;
      }
      return (tmp1&0xf0)|(tmp2>>4);
}

//DS1302
uchar DS1302_Read_Data (uchar address)
{
      uchar i,result=0;
      //初始电平
      DS1302_CE=0;
      DS1302_SK=0;
      _nop_();
      //开始传输 
      DS1302_CE=1;
      //传输地址
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //从高到低1us
          DS1302_IO=address&0x01;    //准备数据并发送
          _nop_();            //发送数据延时1us
          DS1302_SK=1;              //时钟信号上升沿
          _nop_();            //从低到高1us
          address>>=1;
      }
      DS1302_IO=1;                   //释放总线
      for(i=0;i<8;i++)
      {
          result>>=1;
          DS1302_SK=1;
          _nop_();
          DS1302_SK=0;
          _nop_();
          if(DS1302_IO)
          result|=0x80;
      }
      return result;
}  
uchar DS1302_convert_Data(uchar address,uchar Data)
{
      if(address==HourRead&&Data>>7)//bit7为1,12小时制 
      {
          return ((Data>>4)%2)*10+Data%16;
      }
      else
      {
          return Data/16*10+Data%16;
      }
}
void  DS1302_Write_Data(uchar address,uchar Data)
{
      uchar i;
      //初始电平
      DS1302_CE=0;
      DS1302_SK=0;
      _nop_();
      //开始传输 
      DS1302_CE=1;
      //传输地址
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //从高到低1us
          DS1302_IO=address&0x01;    //准备数据并发送
          _nop_();            //发送数据延时1us
          DS1302_SK=1;               //时钟信号上升沿
          _nop_();            //从低到高1us
          address>>=1;
      }
      //传输数据
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //从高到低1us
          DS1302_IO=Data&0x01;       //准备数据并发送
          _nop_();            //发送数据延时1us
          DS1302_SK=1;               //时钟信号上升沿
          _nop_();            //从低到高1us
          Data>>=1;
      }
      DS1302_CE=0;
      _nop_();
}
//DHT11
void  DHT11_delay40us()
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=14;a>0;a--);
}
void  DHT11_delay50us()
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=19;a>0;a--);
}
void  DHT11_delay18ms()
{
    unsigned char a,b;
    for(b=161;b>0;b--)
        for(a=50;a>0;a--);
}
void  DHT11_delay1s()
{
    uint i,j;
    for(i=0;i<1000;i++)
    for(j=0;j<110;j++);
}
void  DHT11_init()
{
    flag=1;
    DHT11_delay1s();
    DHT=1;
    DHT=0;
    DHT11_delay18ms();
    DHT=1;
    DHT11_delay50us();
    flag=DHT;
    if(DHT)
    {
         LCD12864_showstring("初始化失败！",0,1);
    }
    else
     {
         while(!DHT);
         while(DHT);
     }
}
void  DHT11_check()
{
    flag=(byte1+byte2+byte3+byte4)==byte5;
}
uchar DHT11_readbyte()
{
    uchar i,result;
    result=0;
    for(i=0;i<8;i++)
    {
        while(!DHT);
        DHT11_delay40us();
        result<<=1;
        if(DHT)
        {
           while(DHT);
           result|=1;
        }  
    }
    return result;
}

//延时
void  delay1ms(uint x)
{
      uint i,j;
      for(i=0;i<x;i++)
      for(j=0;j<110;j++);
}

//按键检测
uchar keycheck()
{
      C1=1;
      C2=1;
      C3=1;
      C4=1;
      temp=P2>>1&0x0f;
      switch (temp)
      {
      case 0x07:return 1;break;
      case 0x0B:return 2;break;
      case 0x0D:return 3;break;
      case 0x0E:return 4;break;
      default  :return 0;break;
      }
}
//农历计算与显示
void  lunar_calendar(struct Time*Data)
{
      int tmp;                     //记录天数之差
      struct Time s;               
      uchar count,i;                //count用来记录农历月份
      nonglicalculate(Data->year);  //计算当年春节公历   
      if(Data->month<G.chunjie.month||Data->month==G.chunjie.month&&Data->date<G.chunjie.date)nonglicalculate(Data->year-1);
      if(Data->year!=G.chunjie.year)
      {
          s.year=G.chunjie.year;
          s.month=12;
          s.date=31;
          tmp=calculateday(&s,&G.chunjie);
          s.year=Data->year;
          s.month=1;
          s.date=1;
          tmp+=calculateday(Data,&s);
      }
      else
      {
          tmp=calculateday(Data,&G.chunjie);
      }   
      for(i=0;i<13&&tmp>=0;i++)
      {
          tmp-=G.month[i];
      }
      i--;
      tmp+=G.month[i];
      count=i;
      //闰年判断
      if(G.run!=0)
      {
          if(i==G.run){LCD12864_showstring("闰",1,3);count=i-1;}
          else if(i<G.run)count=i;
          else if(i>G.run)count=i-1;
      }
      //输出农历字符串
      LCD12864_pos(1,4);
      /*
      LCD12864_write_data(count/10+48);
      LCD12864_write_data(count%10+48);
      LCD12864_write_data(' ');
      LCD12864_write_data(tmp/10+48);
      LCD12864_write_data(tmp%10+48);
      */
      for(i=0;i<4;i++)
      {
          if(count*4+i==0)
          {
              LCD12864_display_CGRAM(1,1,4);
              i+=2;
          }
          else if(count*4+i==8)
          {
              LCD12864_display_CGRAM(0,1,4);
              i+=2;
          }
          LCD12864_write_data(yue[count*4+i]);
      }
      for(i=0;i<4;i++)
      {
          if(tmp*4+i==10||tmp*4+i==50||tmp*4+i==90)
          {
             LCD12864_display_CGRAM(0,1,7);
             break;
          }
          else if(tmp*4+i==116)
          {
             LCD12864_display_CGRAM(0,1,6);
             i+=2;
          }
          LCD12864_write_data(ri[tmp*4+i]);
      }
}
void  nonglicalculate(uint x)
{
      //计算闰月
      uchar i;
      G.run=T[x-1999][0]>>4;
      for(i=0;i<13;i++)
      {
          if(i<4)G.month[i]=(T[x-1999][0]>>(3-i))%2?30:29;
          else if(i<11)G.month[i]=(T[x-1999][1]>>(12-i))%2?30:29;
          else G.month[i]=(T[x-1999][2]>>7)%2?30:29;
      }
      G.chunjie.year=x;
      G.chunjie.month=(T[x-1999][2]>>5)&0x03;
      G.chunjie.date=T[x-1999][2]&0x1f;
}
uint  calculateday(struct Time*a,struct Time*b)
{
      uchar i;
      uint result=0;
      for(i=b->month;i<a->month;i++)
      {
          switch (i)
          {
          case 1:
          case 3:
          case 5:
          case 7:
          case 8:
          case 10:
          case 12:result+=31;
                 break;
          case 2:result=b->year%4==0&&b->year%100!=0||b->year%400==0?result+29:result+28;
                 break;
          default:result+=30;
                 break;
          } 
      }
      result=result+a->date-b->date;
      return result;
}                         
bit   check()
{
       if(time.year!=2000+DS1302_convert_Data(YearRead,DS1302_Read_Data(YearRead)))
          return 1;
       else if(time.month!=DS1302_convert_Data(MonthRead,DS1302_Read_Data(MonthRead)))
          return 1;
       else if(time.date!=DS1302_convert_Data(DateRead,DS1302_Read_Data(DateRead)))
          return 1;
       else 
          return 0;
}
