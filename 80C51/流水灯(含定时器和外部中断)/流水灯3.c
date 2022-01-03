#include<REG52.H>
void delay();
void main()
{
    while(1)
    {
        P1=0xfe;
        delay();
        P1=0xfd;
        delay();
        P1=0xfb;
        delay();
        P1=0xf7;
        delay();
    }
} 
void delay()
{
    int x,y;
    for(x=0;x<100;x++)
    for(y=0;y<100;y++)
    ;
}