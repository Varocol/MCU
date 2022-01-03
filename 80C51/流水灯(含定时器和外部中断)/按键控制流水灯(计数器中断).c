#include<REG52.H>
#include<math.h>
sbit key=P2^0; 
int c=1;
void setup(void)
{
    TMOD = 0x05;
    TH0 = 0xFF;
    TL0 = 0xFF;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void start(void);
void main()
{
    setup();
    key=1;
    start();
}
void start()
{    
    unsigned char b[4]={0xfe,0xfd,0xfb,0xf7};
    unsigned char i;
    unsigned int j;
    for(i=0;i<4;i=(i+c+4)%4)
    {  
        P1=b[i];
        j=46080;
        while(j--);
	    j=46080;
	    while(j--);
    }
}

void Timer0Interrupt(void) interrupt 1
{
    TH0 = 0xFF;
    TL0 = 0xFF;
    c=-c;
}
