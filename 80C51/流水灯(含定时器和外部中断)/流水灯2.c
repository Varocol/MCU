#include<Reg51.h>
sbit D1=P1^0;
sbit D2=P1^1;
sbit D3=P1^2;
sbit D4=P1^3;
void main()
{ 
    int i;
    while(1)
    {
       D1=0;
       for(i=0;i<10000;i++);
       D1=1;
       D2=0;
       for(i=0;i<10000;i++);
       D2=1;
       D3=0;
       for(i=0;i<10000;i++);
       D3=1;
       D4=0;
       for(i=0;i<10000;i++);
       D4=1;
    }
}