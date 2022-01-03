#ifndef __OJ_SERVER_H
#define __OJ_SERVER_H
#define CURRENT_START 0.0005
#define CURRENT_END 0.0025
#define ANGLE_WHITH 180
#include "PWM.h"
class Servo : public PWM
{
private:
public:
    ~Servo();
    Servo();
    Servo(TIMx_Channelx_Selection T_C_S, double hz, double angle);
    double Angle_to_DutyRatio(double angle, double hz);
    void Init();
    void Update(TIMx_Channelx_Selection T_C_S, double hz, double angle);
};
#endif