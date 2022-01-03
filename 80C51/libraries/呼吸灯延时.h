#include"REG52.H"

const double jq=1.0850694444444e-6;
float speed;
long fps,time,ans,total;
unsigned char b[4]={0xfe,0xfd,0xfb,0xf7};
int c=1,led=0,T=1,count1=0,count2=0,flag=1;
//单位时间为1/fps,占比用ans/fps计算。


void setup()
{
   total=fps*speed/2;
   ans=0;
   P1=b[led];
   time=(1.0*ans)/(fps*total*jq);
   EA=1;
   ET0=1;
   TR0=1;
   EX0=1;
   IT0=1;
   TMOD=0x01;
   TH0=(65535-time)/256;
   TL0=(65535-time)%256;
}
void reset()
{
   //修改ans
   if(flag)
   {
      ans=total-ans;
      flag=1-flag; 
      count1++;
   }
   else 
   {
      if(count1==total+1)
      {
         ans=total-ans;
         T=-T;
         count1=0;
         count2++;
      }
      else
        ans=total-ans+T;
      flag=1-flag;
   }
}
//1 99,2 98,...,99 1,  99 1,98 2,...,1 99,   1 99,...
void Outsideinterrupt () interrupt 0
{
   c=-c;
}
void timer1interrupt () interrupt 1
{
   reset();
   time=(1.0*ans)/(fps*total*jq);
   TH0=(65535-time)/256;
   TL0=(65535-time)%256;
   if(count2==2)
   {
    count2=0;
    led=(led+c+4)%4;
   }
   if(!flag)P1=0xFF;
   else P1=b[led];
}  


