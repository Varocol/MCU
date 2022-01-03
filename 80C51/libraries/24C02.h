#include<REG52.H>
#include<INTRINS.H>
#include"12864libs.h"
#define uchar unsigned char
#define uint  unsigned int

/*引脚定义*/
sbit  IIC_SCL=P1^3;
sbit  IIC_SDA=P1^4;
bit   IIC_flag;
/*函数声明*/
void  AT24C02_delay5ms();
void  AT24C02_Reset();                           //IIC总线复位
void  AT24C02_Start_condition();                 //开始信号
void  AT24C02_Stop_condition();                  //结束信号
void  AT24C02_Write_byte(uchar);                 //写入单字节
void  AT24C02_Write_data(uchar,uchar,uchar);     //写入数据,参数为器件地址,内部地址,数据
void  AT24C02_Write_page(uchar,uchar,uchar*);    //页写
void  AT24C02_send_ACK();                        //发送应答
void  AT24C02_send_NACK();                       //终止接收
void  AT24C02_check_ACK();                       //应答查询
void  AT24C02_Read_page(uchar,uchar,uchar*);     //接收一页的数据           
uchar AT24C02_Read_byte();                       //接收字节
uchar AT24C02_Read_data(uchar,uchar);            //接受数据


void  AT24C02_delay5ms()
{
    uchar a,b,c;
    for(c=1;c>0;c--)
        for(b=200;b>0;b--)
            for(a=10;a>0;a--);
}
void  AT24C02_Reset()
{
      uchar i;
      IIC_flag=1;
      AT24C02_Start_condition();
      IIC_SCL=0;
      IIC_SDA=1;
      for(i=0;i<9;i++)
      {
          IIC_SCL=0;
          _nop_();
          IIC_SCL=1;
          _nop_();
          IIC_SCL=0;
          _nop_();
      }
      AT24C02_Start_condition();
      AT24C02_Stop_condition();
}
void  AT24C02_Start_condition()
{
      IIC_SCL=0;
      IIC_SDA=1;
      IIC_SCL=1;
      _nop_();
      IIC_SDA=0;
      _nop_();
}
void  AT24C02_Stop_condition()
{
      IIC_SCL=0;
      IIC_SDA=0;
      IIC_SCL=1;
      _nop_();
      IIC_SDA=1;
      _nop_();
}
void  AT24C02_Write_byte(uchar Data)
{
      uchar i;
      for(i=0;i<8;i++)
      {
          IIC_SCL=0;
          IIC_SDA=0x80&Data;                     //准备数据
          _nop_();
          IIC_SCL=1;
          _nop_();
          IIC_SCL=0;
          Data<<=1;                              //最高位发送
      }
}
void  AT24C02_Write_data(uchar add1,uchar add2,uchar Data)
{
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1);
      AT24C02_check_ACK();
      AT24C02_Write_byte(add2);
      AT24C02_check_ACK();
      AT24C02_Write_byte(Data);
      AT24C02_check_ACK();
      AT24C02_Stop_condition();
}
void  AT24C02_Write_page(uchar add1,uchar add2,uchar*p)
{
      uchar i;
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1);
      AT24C02_check_ACK();
      AT24C02_Write_byte(add2);
      AT24C02_check_ACK();
      for(i=0;i<8;i++)
      {
          AT24C02_Write_byte(p[i]);
          AT24C02_check_ACK();
      }
      AT24C02_Stop_condition();
}
void  AT24C02_send_ACK()
{
      IIC_SCL=0;
      IIC_SDA=0;
      _nop_();
      IIC_SCL=1;
      _nop_();
      IIC_SCL=0;
}
void  AT24C02_send_NACK()
{
      IIC_SCL=0;
      IIC_SDA=1;
      _nop_();
      IIC_SCL=1;
      _nop_();
      IIC_SCL=0;
}
void  AT24C02_check_ACK()
{
      IIC_SCL=0;
      _nop_();
      IIC_SCL=1;
      _nop_();
      if(IIC_SDA)
      {
         LCD12864_showstring("写入失败！",1,2);
         IIC_flag=0;
      }
}
void  AT24C02_Read_page(uchar add1,uchar add2,uchar*p)
{
      uchar i;
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1);
      AT24C02_check_ACK();
      AT24C02_Write_byte(add2);
      AT24C02_check_ACK();
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1+1);
      AT24C02_check_ACK();
      for(i=0;i<8;i++)
      {
            p[i]=AT24C02_Read_byte();
            if(i<7)AT24C02_send_ACK();
            else   AT24C02_send_NACK();
      }
      AT24C02_Stop_condition();
}
uchar AT24C02_Read_byte()
{
      uchar i,result=0;
      for(i=0;i<8;i++)
      {
            IIC_SCL=0;
            IIC_SDA=1;//释放总线
            _nop_();
            result<<=1;
            IIC_SCL=1;
            _nop_();
            result|=IIC_SDA;
            IIC_SCL=0;
      }
      return result;
}
uchar AT24C02_Read_data(uchar add1,uchar add2)
{
      uchar result;
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1);
      AT24C02_check_ACK();
      AT24C02_Write_byte(add2);
      AT24C02_check_ACK();
      AT24C02_Start_condition();
      AT24C02_Write_byte(add1+1);
      AT24C02_check_ACK();
      result=AT24C02_Read_byte();
      AT24C02_send_NACK();
      AT24C02_Stop_condition();
      return result;
}

