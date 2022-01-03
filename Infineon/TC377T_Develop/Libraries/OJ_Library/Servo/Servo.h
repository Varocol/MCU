#ifndef __OJ_SERVO_H
#define __OJ_SERVO_H
#include "headfile.h"
#include "PWM.h"

//��������ṹ��
typedef struct
{
        ATOM_PIN_enum pwmch;        //Servo PWMͨ��
        uint32 freq;                //Servo ����Ƶ��
        double CURRENT_MAX;         //Servo �������ֵ(ֻ���ڼ�¼),��λms
        double CURRENT_MIN;         //Servo ������Сֵ(ֻ���ڼ�¼),��λms
        double CURRENT_END;         //Servo �ܿط�Χ�������ֵ,��λms
        double CURRENT_START;       //Servo �ܿط�Χ������Сֵ,��λms
        double MAP_MAX;             //Servo ӳ�����ֵ
        double MAP_MIN;             //Servo ӳ����Сֵ
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

