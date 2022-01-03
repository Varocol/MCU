#ifndef __OJ_MOTOR_H
#define __OJ_MOTOR_H
#include "PWM.h"
//采用两路PWM控制电机原理,一端接地,一端采用PWM输出来控制电压
//正反转只需交换两个数值即可

//电机转动方向,如果两条线插反了可以使用方向位调转电机方向
typedef enum
{
    MOTOR_Direction_1, MOTOR_Direction_2,
} MOTOR_Direction;

typedef struct
{
        ATOM_PIN_enum pwmch1;   //MOTOR 通道1引脚
        ATOM_PIN_enum pwmch2;   //MOTOR 通道2引脚
        MOTOR_Direction dir;    //MOTOR 电机转动方向
        uint32 freq;            //MOTOR 电机驱动频率
        uint8 Speed_Max;        //MOTOR 电机速度阈值
} MOTOR_Param;

class MOTOR
{
    private:
        PWM *Channel1;
        PWM *Channel2;
        MOTOR_Param Param;
    public:
        MOTOR ();
        MOTOR (MOTOR_Param Param);
        ~MOTOR ();
        void Set_Param (MOTOR_Param Param);
        void PWM_Init ();
        void Init ();
        void Run (double speed);

};

#endif  /*__OJ_MOTOR_H*/
