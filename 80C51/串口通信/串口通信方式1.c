#include<reg52.h>
unsigned char flag=0,a,i;
unsigned char table[]="I get a ";
void init()
{        
    TMOD=0x20;
    TH1=0xfd;//9600bps
    TL1=0xfd;
    PCON=0x00;//SMOD=0
    TR1=1;
    SM0=0;
    SM1=1;
    REN=1;
    EA=1;
    ES=1; 
}
void main()
{
    init();
    while(1)
    {
        if(flag==1)
        {
            ES=0;
            i=0;
            while(table[i]!='\0')
            {
               SBUF=table[i];
               while(!TI);
               TI=0;
               i++;
            }
            SBUF=a;
            while(!TI);
            TI=0;
            ES=1;
            flag=0;
        }
    }
}
void ser() interrupt 4
{
    RI=0;
    a=SBUF;
    flag=1;
}
/*
2个点注意：
   1.虽然说在物理上两个sbuf地址不同,只是在赋值上不同,但是RI不会认那个是接受数据的sbuf,只要sbuf中有数据RI就会置1。
   2.ascii的范围是0~127,所以有效数据位是7位,调试串口软件的时候要设置成7位数据包，否则最高位会变成1，即D0=RI=1,这也会导致乱码。
*/
