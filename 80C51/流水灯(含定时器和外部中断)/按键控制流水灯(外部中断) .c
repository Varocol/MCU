#include<REG52.H>
#include<math.h>
sbit key=P2^0; 
int c=1;
void setup(void)
{
    EA = 1;
    EX0 = 1;
    IT0 = 0;
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

void Timer0Interrupt(void) interrupt 0
{
    c=-c;
}
