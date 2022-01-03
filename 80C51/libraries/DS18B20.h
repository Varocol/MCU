#include<REG52.H>
#include<INTRINS.H>
#define bit9  0x1f
#define bit10 0x3f
#define bit11 0x5f
#define bit12 0x7f
#define uchar unsigned char
#define uint unsigned int 


uchar LS,MS;                      //LS用来存储低8位,MS用来存储高8位
float temp;                       //记录温度值
sbit  DQ=P2^0;                    //DQ
bit   flag;                       //标识初始化是否成功
uchar string [10];                //存字符串

void  DS18B20_init();              //初始化DS18b20
void  DS18B20_write(uchar);        //写指令
void  DS18B20_delay750ms();        //延时750ms
void  DS18B20_delay68us();         //延时68us
void  DS18B20_delay500us();        //延时500us
void  COM_init();                  //串口初始化
void  COM_send(uchar*);            //串口发送数据
void  TEMP_convert();              //将LS,MS转换成数据
void  pause();                     //暂停1s
uchar*DS18B20_string(float);       //float转换为字符串
uchar DS18B20_read();              //读取数据


void  DS18B20_init()
{
   DQ=0;
   DS18B20_delay500us();
   DQ=1;
   DS18B20_delay68us();
   flag=DQ;
   DS18B20_delay500us();
   if(flag)
   {
       COM_send("初始化失败!\n");
   }
}
void  DS18B20_write(uchar cmd)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        DQ=0;                     //从低电平开始写
        DQ=cmd&0x01;              //取出最低位并延时
        DS18B20_delay68us();      //延时68us检查脉冲
        DQ=1;                     //释放总线
        cmd=cmd>>1;               //为下一位做准备
    }
}
void  DS18B20_delay750ms()
{
   uchar a,b,c;
    for(c=147;c>0;c--)
        for(b=127;b>0;b--)
            for(a=17;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}
void  DS18B20_delay68us()
{
   uchar a,b;
   for(b=3;b>0;b--)
        for(a=8;a>0;a--);
}
void  DS18B20_delay500us()
{
    uchar a,b;
    for(b=91;b>0;b--)
        for(a=1;a>0;a--);
}
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
        if(p[i]!='+')
        {
        SBUF=p[i];
        while(!TI);
        TI=0;
        }
    }
}
void  TEMP_convert()
{
   uchar zs,xs;
   zs=(LS>>4)|(MS<<4);
   if(zs>>7)
   {
       zs=~zs+1;
   }
   xs=LS&0x0f;
   temp=zs+xs/16.0;
}
void  pause()
{
    uint i,j;
    for(i=0;i<1000;i++)
    for(j=0;j<110;j++);
}
uchar*DS18B20_string(float T)
{
    uchar xs;                     //存小数位
    float XS;                     //存小数
    uchar i,j;
    
    if(T<0)
    {
        string [0]='-';
        T=-T;
    }
    else
    {
        string [0]='+';
    }

    XS=(int)T;
    j=T==0?1:0;
    while(XS>=1)
    {
       XS/=10;
       j++;
    }
    for(i=1;i<=j;i++)
    {
       XS*=10;
       xs=XS;
       string [i]=xs+'0';
       XS-=xs;
    }

    if(T-(int)T>0)
    {
        string [i++]='.';
        XS=T-(int)T;
        for(;XS>0;i++)
        {
            XS*=10;
            xs=XS;
            string [i]=xs+'0';
            XS-=xs;
        }
    }
    string[i]='\0';
    return string;
}
uchar DS18B20_read()
{
   uchar value,i;
   value=0;
   for(i=0;i<8;i++)
   {
       DQ=0;
       value>>=1;
       DQ=1;
       if(DQ)
       {
           value|=0x80;
       }
       DS18B20_delay68us();
   }
   return value;
}