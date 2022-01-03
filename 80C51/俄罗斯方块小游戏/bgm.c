#include"∂Ì¬ﬁÀπ∑ΩøÈ“Ù¿÷.h"
#include"music.h"
#include"INTRINS.H"
#define  mainmusiclines 172
#define  overmusiclines 7
#define  uchar unsigned char
#define  uint  unsigned int 
uchar musicflag;
void  musicinit()
{
      basicspeed=100;
      musicflag=1;
      EX0=1;
      EX1=1;
      IT0=1;
      IT1=1;
      PX1=1;
      EA=1;
}

void main()
{
     musicinit();
     while(1);
}

void mainmusicinterrupt() interrupt 0
{
     uchar i;
     for(i=0;musicflag;i=(i+1)%mainmusiclines)
     if(mainmusic[i].hz)
     music(mainmusic[i].hz,mainmusic[i].time);
     else
     pause(mainmusic[i].time);
     musicinit();
} 
void overmusicinterrupt() interrupt 2
{
     uchar i;
     for(i=0;i<overmusiclines;i++)
     if(overmusic[i].hz)
     music(overmusic[i].hz,overmusic[i].time);
     else
     pause(overmusic[i].time);
     musicflag=0;
}
