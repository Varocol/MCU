#include "Libraries.h"
Servo_Param Param =
    {
        TIM3_Channel1_Default,
        50,
        2.5,
        0.5,
        2.5,
        0.5,
        100,
        0};
int main()
{
    Servo servo = Servo(Param);
    servo.Init();
}
