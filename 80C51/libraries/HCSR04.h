#include<REG52.H>
#include<INTRINS.H>
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned uint
#endif
/*��������*/
double S;                              //��¼����
const double jq=1.0850694444444e-6;
/*�ӿڶ���*/
sbit   HCSR04_TRIG=P2^0;

/*��������*/
void   HCSR04_timerset();              //��ʼ����ʱ��
void   HCSR04_init();                  //��TRIG����10us������ģ��,�����ö�ʱ����¼ʱ��
void   HCSR04_delay();                 //21us��ʱ
void   HCSR04_distance();              //����ʱ�������


/*��������*/
void   HCSR04_timerset()
{
       TMOD=0x09;
       TR0=1;
}
void   HCSR04_init()                 
{
       TH0=0;
       TL0=0;
       HCSR04_TRIG=1;
       HCSR04_delay();
       HCSR04_TRIG=0;
}
void   HCSR04_delay()
{
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
       _nop_();
}
void   HCSR04_distance()
{
       while(!INT0);
       while(INT0);
       S=(TH0*256+TL0)*jq*17000;
       S=(long)S*10;
       S/=10;
} 
