#include<reg52.h>
#define uint unsigned int
unsigned char flag=0,a,i;
unsigned char table[]="I get a ";
void init()
{        
    SM0=1;
    SM1=0;
    EA=1;
    ES=1; 
}
void delay_1ms(uint x)
{
   uint i,j;
   for(i=0;i<x;i++)
   for(j=0;j<110;j++);
}
void main()
{
    init();
    while(1)
    {
       SBUF=0xaa;
       delay_1ms(1000);
    }
}
void ser() interrupt 4
{
    TI=0;
}
/*
3个点注意：
   1.虽然说在物理上两个sbuf地址不同,只是在赋值上不同,但是RI不会认那个是接受数据的sbuf,只要sbuf中有数据RI就会置1。
   2.ascii的范围是0~127,所以有效数据位是7位,调试串口软件的时候要设置成7位数据包，否则最高位会变成1，即D0=RI=1,这也会导致乱码。
   3.以上两点均是仿真结论,真实结论是单片机与电脑通信的波特率应该为19200bps
*/
