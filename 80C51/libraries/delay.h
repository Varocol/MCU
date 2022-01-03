#ifndef uchar
#define uchar unsigned char 
#endif
#ifndef uint
#define uint  unsigned int
#endif
void delay1ms(unsigned int x)
{
     unsigned int i,j;
     for(i=0;i<x;i++)
     for(j=0;j<110;j++);
     
}
void delay5us()
{
}