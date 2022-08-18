#include "core2_main.h"

void core2_setup ()
{

}

void core2_loop ()
{
    if (run_flag)
    {
        Encoder_Read();             //获取速度
        Get_Mid_Bias();             //获取中线偏差
        MidBias_FitTurnR();         //获取转向半径及转向角速度
        Servo_Control();            //舵机转向
        Motor_Control();            //速度控制
    }
}

