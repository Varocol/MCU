#include "bsp_conf.h"
int main()
{
    GPIO g = GPIO(GPIOB,GPIO_Pin_0);
    g.OUT_MODE();
    Buzzer b = Buzzer(g);
    b.Init();
}