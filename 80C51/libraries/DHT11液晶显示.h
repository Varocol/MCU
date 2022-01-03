#include<REG52.H>
#include"12864libs.h"
#define uchar unsigned char 
#define uint unsigned int 

sbit  DHT=P2^0;
uchar byte1,byte2,byte3,byte4,byte5,flag;
uchar string [10];

void   DHT11_delay40us();
void   DHT11_delay50us();
void   DHT11_delay18ms();
void   DHT11_delay1s();
void   DHT11_init();
void   DHT11_check();
uchar  DHT11_readbyte();
uchar* DHT11_string(uchar,uchar);

void   DHT11_delay40us()
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=14;a>0;a--);
}
void   DHT11_delay50us()
{
    uchar a,b;
    for(b=1;b>0;b--)
        for(a=19;a>0;a--);
}
void   DHT11_delay18ms()
{
    unsigned char a,b;
    for(b=161;b>0;b--)
        for(a=50;a>0;a--);
}
void   DHT11_delay1s()
{
    uint i,j;
    for(i=0;i<1000;i++)
    for(j=0;j<110;j++);
}
void   DHT11_init()
{
    flag=1;
    DHT11_delay1s();
    DHT=1;
    DHT=0;
    DHT11_delay18ms();
    DHT=1;
    DHT11_delay50us();
    flag=DHT;
    if(DHT)
    {
         LCD12864_showstring("³õÊ¼»¯Ê§°Ü£¡",0,1);
    }
    else
     {
         while(!DHT);
         while(DHT);
     }
}
void   DHT11_check()
{
    flag=(byte1+byte2+byte3+byte4)==byte5;
}
uchar  DHT11_readbyte()
{
    uchar i,result;
    result=0;
    for(i=0;i<8;i++)
    {
        while(!DHT);
        DHT11_delay40us();
        result<<=1;
        if(DHT)
        {
           while(DHT);
           result|=1;
        }  
    }
    return result;
}
uchar* DHT11_string(uchar ZS,uchar XS)
{      
    uchar i,count,tmp;
    string[0]=':';
    
    count=ZS==0?1:0;
    tmp=0;
    while(ZS)
    {
        tmp=tmp*10+ZS%10;
        ZS/=10;
        count++;
    }
    for(i=1;count--;i++)
    {
        string [i]=tmp%10+'0';
        tmp/=10;
    }
    string[i++]='.';

    count=XS==0?1:0;
    tmp=0;
    while(XS)
    {
        tmp=tmp*10+XS%10;
        XS/=10;
        count++;
    }
    for(;count--;i++)
    {
        string [i]=tmp%10+'0';
        tmp/=10;
    }
    string[i]='\0';
    return string;
}