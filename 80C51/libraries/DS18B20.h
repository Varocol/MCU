#include<REG52.H>
#include<INTRINS.H>
#define bit9  0x1f
#define bit10 0x3f
#define bit11 0x5f
#define bit12 0x7f
#define uchar unsigned char
#define uint unsigned int 


uchar LS,MS;                      //LS�����洢��8λ,MS�����洢��8λ
float temp;                       //��¼�¶�ֵ
sbit  DQ=P2^0;                    //DQ
bit   flag;                       //��ʶ��ʼ���Ƿ�ɹ�
uchar string [10];                //���ַ���

void  DS18B20_init();              //��ʼ��DS18b20
void  DS18B20_write(uchar);        //дָ��
void  DS18B20_delay750ms();        //��ʱ750ms
void  DS18B20_delay68us();         //��ʱ68us
void  DS18B20_delay500us();        //��ʱ500us
void  COM_init();                  //���ڳ�ʼ��
void  COM_send(uchar*);            //���ڷ�������
void  TEMP_convert();              //��LS,MSת��������
void  pause();                     //��ͣ1s
uchar*DS18B20_string(float);       //floatת��Ϊ�ַ���
uchar DS18B20_read();              //��ȡ����


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
       COM_send("��ʼ��ʧ��!\n");
   }
}
void  DS18B20_write(uchar cmd)
{
    uchar i;
    for(i=0;i<8;i++)
    {
        DQ=0;                     //�ӵ͵�ƽ��ʼд
        DQ=cmd&0x01;              //ȡ�����λ����ʱ
        DS18B20_delay68us();      //��ʱ68us�������
        DQ=1;                     //�ͷ�����
        cmd=cmd>>1;               //Ϊ��һλ��׼��
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
    uchar xs;                     //��С��λ
    float XS;                     //��С��
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