#ifndef __OJ_SERVO_H
#define __OJ_SERVO_H
#include "headfile.h"
#include "PWM.h"

//舵机参数结构体
typedef struct
{
        ATOM_PIN_enum pwmch;        //Servo PWM通道
        uint32 freq;                //Servo 驱动频率
        double CURRENT_MAX;         //Servo 脉宽最大值(只用于记录),单位ms
        double CURRENT_MIN;         //Servo 脉宽最小值(只用于记录),单位ms
        double CURRENT_END;         //Servo 受控范围脉宽最大值,单位ms
        double CURRENT_START;       //Servo 受控范围脉宽最小值,单位ms
        double MAP_MAX;             //Servo 映射最大值
        double MAP_MIN;             //Servo 映射最小值
} Servo_Param;

class Servo : public PWM
{
    private:
        Servo_Param Param;
        double CURRENT_To_Percent (double CURRENT);
        double MAP_TO_CURRENT (double MAP_VAL);
        double MAP_TO_Percent (double MAP_VAL);
    public:
        Servo ();
        Servo (Servo_Param Param);
        ~Servo ();
        void Set_Param (Servo_Param Param);
        void Turn (double MAP_VAL);
};

#endif  /*__OJ_SERVO_H*/

