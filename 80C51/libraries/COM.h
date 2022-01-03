#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
#include<REG52.H>
void  COM_init();                  //串口初始化
void  COM_send(uchar*);            //串口发送数据

void  COM_init()
{
    TMOD=0x20;
    TH1=0xfd;
    TL1=0xfd;//9600bps
    TR1=1;
    SM0=0;
    SM1=1;
}
void  COM_send(uchar* p)
{
    uint i;
    for(i=0;p[i]!='\0';i++)
    {
        SBUF=p[i];
        while(!TI);
        TI=0;
    }
}