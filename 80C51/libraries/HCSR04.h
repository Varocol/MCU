#include<REG52.H>
#include<INTRINS.H>
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned uint
#endif
/*变量定义*/
double S;                              //记录距离
const double jq=1.0850694444444e-6;
/*接口定义*/
sbit   HCSR04_TRIG=P2^0;

/*函数声明*/
void   HCSR04_timerset();              //初始化定时器
void   HCSR04_init();                  //给TRIG至少10us启动该模块,并启用定时器记录时间
void   HCSR04_delay();                 //21us延时
void   HCSR04_distance();              //根据时间算距离


/*函数定义*/
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
