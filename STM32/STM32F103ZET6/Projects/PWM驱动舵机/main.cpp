#include "bsp_conf.h"

int main()
{
    Servo servo = Servo(TIM3_Channel1_Selection_Default, 100, -181);
    servo.Init();
}
