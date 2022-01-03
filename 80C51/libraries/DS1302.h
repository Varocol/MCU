#include<REG52.H>
#include<INTRINS.H>
#include"DS1302name.h"
#define uchar unsigned char
#define uint unsigned int

/*引脚定义*/
sbit DS1302_CE = P1^0;                           //rst
sbit DS1302_SK = P1^1;                           //时钟
sbit DS1302_IO = P1^2;                           //数据口

/*函数声明*/
void  DS1302_init();
void  DS1302_Write_Data(uchar,uchar);            //写数据
uchar DS1302_Read_Data (uchar);                  //读数据
uchar DS1302_convert_Data(uchar,uchar);
/*函数定义*/
void  DS1302_init()
{      
      //DS1302_Write_Data(SecondWrite,0x80);     //设置时钟暂停位
      DS1302_Write_Data(ProtectWrite,0x00);    //解锁
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

