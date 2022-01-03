#include<REG52.H>
#include<INTRINS.H>
#include"DS1302name.h"
#define uchar unsigned char
#define uint unsigned int

/*���Ŷ���*/
sbit DS1302_CE = P1^0;                           //rst
sbit DS1302_SK = P1^1;                           //ʱ��
sbit DS1302_IO = P1^2;                           //���ݿ�

/*��������*/
void  DS1302_init();
void  DS1302_Write_Data(uchar,uchar);            //д����
uchar DS1302_Read_Data (uchar);                  //������
uchar DS1302_convert_Data(uchar,uchar);
/*��������*/
void  DS1302_init()
{      
      //DS1302_Write_Data(SecondWrite,0x80);     //����ʱ����ͣλ
      DS1302_Write_Data(ProtectWrite,0x00);    //����
}
void  DS1302_Write_Data(uchar address,uchar Data)
{
      uchar i;
      //��ʼ��ƽ
      DS1302_CE=0;
      DS1302_SK=0;
      _nop_();
      //��ʼ���� 
      DS1302_CE=1;
      //�����ַ
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //�Ӹߵ���1us
          DS1302_IO=address&0x01;    //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          DS1302_SK=1;               //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          address>>=1;
      }
      //��������
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //�Ӹߵ���1us
          DS1302_IO=Data&0x01;       //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          DS1302_SK=1;               //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          Data>>=1;
      }
      DS1302_CE=0;
      _nop_();
}
uchar DS1302_Read_Data (uchar address)
{
      uchar i,result=0;
      //��ʼ��ƽ
      DS1302_CE=0;
      DS1302_SK=0;
      _nop_();
      //��ʼ���� 
      DS1302_CE=1;
      //�����ַ
      for(i=0;i<8;i++)
      {
          DS1302_SK=0;
          _nop_();            //�Ӹߵ���1us
          DS1302_IO=address&0x01;    //׼�����ݲ�����
          _nop_();            //����������ʱ1us
          DS1302_SK=1;              //ʱ���ź�������
          _nop_();            //�ӵ͵���1us
          address>>=1;
      }
      DS1302_IO=1;                   //�ͷ�����
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
      if(address==HourRead&&Data>>7)//bit7Ϊ1,12Сʱ�� 
      {
          return ((Data>>4)%2)*10+Data%16;
      }
      else
      {
          return Data/16*10+Data%16;
      }
}

