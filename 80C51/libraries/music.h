#include"REG52.H"

const double jq=1.0850694444444e-6;
int basicspeed; 
sbit beep=P2^0;

int cal(int hz)
{
    return 1.0/(hz*jq*10);
}

void music(int hz,float yinfu)
{
    int diao=cal(hz);
    int ci=60.0*hz/basicspeed*yinfu;
    int x;
   while(ci--)//用函数来延时误差太大
   {
   beep=~beep;
    x=diao;
    while(x--);
    }
}
void pause(float yinfu)
{
   int time=(60.0/basicspeed*yinfu)/(jq*10);
   while(time--);
}