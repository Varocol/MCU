#ifndef __OJ_MOTOR_H
#define __OJ_MOTOR_H
#include "PWM.h"
//������·PWM���Ƶ��ԭ��,һ�˽ӵ�,һ�˲���PWM��������Ƶ�ѹ
//����תֻ�轻��������ֵ����

//���ת������,��������߲巴�˿���ʹ�÷���λ��ת�������
typedef enum
{
    MOTOR_Direction_1, MOTOR_Direction_2,
} MOTOR_Direction;

typedef struct
{
        ATOM_PIN_enum pwmch1;   //MOTOR ͨ��1����
        ATOM_PIN_enum pwmch2;   //MOTOR ͨ��2����
        MOTOR_Direction dir;    //MOTOR ���ת������
        uint32 freq;            //MOTOR �������Ƶ��
        uint8 Speed_Max;        //MOTOR ����ٶ���ֵ
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
