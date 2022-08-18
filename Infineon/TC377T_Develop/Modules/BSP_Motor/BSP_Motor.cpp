#include "BSP_Motor.h"

MOTOR_Param LM_Param{ATOM0_CH4_P02_4, ATOM0_CH5_P02_5, MOTOR_Direction_1, 17000, 50, 10000};

MOTOR_Param RM_Param{ATOM0_CH6_P02_6, ATOM0_CH7_P02_7, MOTOR_Direction_1, 17000, 50, 10000};

MOTOR Left_Motor;
MOTOR Right_Motor;
//电机初始化
void Motor_Init ()
{
    Left_Motor.Set_Param(LM_Param);
    Right_Motor.Set_Param(RM_Param);
    Left_Motor.Init();
    Right_Motor.Init();
}

//电机速度控制
void Motor_Control ()
{
    //左右轮PID结构体现速度赋值
    Left_ctr.currspeed = speedl;
    Right_ctr.currspeed = speedr;
    //获取目标速度
    Left_ctr.goalspeed = 40;
    Right_ctr.goalspeed = 40;
    //pid实现
    PID_Realize_L_Speed();
    PID_Realize_R_Speed();
    //p w m赋值
    //Right_ctr.out = -2000;    //调试引脚用
    //Left_ctr.out = 2000;
    Left_Motor.Run(Left_ctr.out);
    Right_Motor.Run(Right_ctr.out);
}
