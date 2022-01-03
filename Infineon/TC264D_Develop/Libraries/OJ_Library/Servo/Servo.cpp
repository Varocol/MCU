#include "Servo.h"
/*
 * @brief       Servo�չ��췽��
 * @param       void
 * @return      null
 */
Servo::Servo ()
{
}

/*
 * @brief       Servo���ι��췽��
 * @param       Param       Servo����
 * @return      null
 */
Servo::Servo (Servo_Param Param)
{
    Set_Param(Param);
}

/*
 * @brief       Servo��������
 * @param       void
 * @return      null
 */
Servo::~Servo ()
{
}

/*
 * @brief       Servo���ò�������
 * @param       Param       Servo����
 * @return      null
 */
void Servo::Set_Param (Servo_Param Param)
{
    //��ֹ�ܿ������������ֵ
    if (Param.CURRENT_START < Param.CURRENT_MIN)
    {
        Param.CURRENT_START = Param.CURRENT_MIN;
    }
    if (Param.CURRENT_END > Param.CURRENT_MAX)
    {
        Param.CURRENT_END = Param.CURRENT_MAX;
    }
    this->Param = Param;
    //��һ��ֻ����������ͨ�����ź�����Ƶ��
    PWM::Set_Param(Param.pwmch, Param.freq, MAP_TO_Percent((Param.MAP_MAX + Param.MAP_MIN) / 2));
}

/*
 * @brief       Servoת�򷽷�
 * @param       MAP_Value       ӳ����ת�����
 * @return      void
 */
void Servo::Turn (double MAP_VAL)
{
    Set_Percent(MAP_TO_Percent(MAP_VAL));
    PWM::Init();
}

/*
 * @brief       Servo����ת����ռ�ձȰٷֱ�
 * @param       CURRENT         ����
 * @return      Percent         ռ�ձȰٷֱ�
 */
double Servo::CURRENT_To_Percent (double CURRENT)
{
    return CURRENT * Param.freq / 10;
}

/*
 * @brief       Servoӳ��ֵת��������
 * @param       MAP_VAL         ӳ��ֵ
 * @return      CURRENT         ����
 */
double Servo::MAP_TO_CURRENT (double MAP_VAL)
{
    return (MAP_VAL - Param.MAP_MIN) / (Param.MAP_MAX - Param.MAP_MIN) * (Param.CURRENT_END - Param.CURRENT_START)
            + Param.CURRENT_START;
}

/*
 * @brief       Servoӳ��ֵת����ռ�ձ�
 * @param       MAP_VAL         ӳ��ֵ
 * @return      Percent         ռ�ձȰٷֱ�
 */
double Servo::MAP_TO_Percent (double MAP_VAL)
{
    return CURRENT_To_Percent(MAP_TO_CURRENT(MAP_VAL));
}

