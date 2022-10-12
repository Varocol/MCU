#include "System.h"
Servo_Param Param =
    {
        .pwmch = TIM3_Channel1_Default,
        .freq = 50,
        .CURRENT_MAX = 2.5,
        .CURRENT_MIN = 0.5,
        .CURRENT_END = 2.5,
        .CURRENT_START = 0.5,
        .MAP_MAX = 100,
        .MAP_MIN = 0};
int main()
{
    Servo servo = Servo(Param);
    servo.Init();
}
