#include "MOTOR.h"
/*
 * @brief       MOTOR�չ��췽��
 * @param       void
 * @return      null
 */
MOTOR::MOTOR ()
{

}

/*
 * @brief       MOTOR���ι��췽��
 * @param       pwmch1          ����ͨ��1
 * @param       pwmch2          ����ͨ��2
 * @param       dir             ���ת������
 * @param       freq            �������Ƶ��
 * @return      null
 */
MOTOR::MOTOR (MOTOR_Param Param)
{
    Set_Param(Param);
}

/*
 * @brief       MOTOR��������
 * @param       void
 * @return      null
 */
MOTOR::~MOTOR ()
{
    delete Channel1;
    delete Channel2;
}

/*
 * @brief       MOTOR���ò�������
 * @param       pwmch1          ����ͨ��1
 * @param       pwmch2          ����ͨ��2
 * @param       dir             ���ת������
 * @param       freq            �������Ƶ��
 * @return      null
 */
void MOTOR::Set_Param (MOTOR_Param Param)
{
    this->Param = Param;
}

/*
 * @brief       MOTOR��ʼ��PWMͨ��
 * @param       null
 * @return      void
 */
void MOTOR::PWM_Init ()
{
    Channel1 = new PWM(Param.pwmch1, Param.freq, 0);
    Channel2 = new PWM(Param.pwmch2, Param.freq, 0);

    Channel1->Init();
    Channel2->Init();
}

/*
 * @brief       MOTOR��ʼ��
 * @param       null
 * @return      void
 */
void MOTOR::Init ()
{
    PWM_Init();
}

/*
 * @brief       MOTOR��������
 * @param       speed           ���ת���ٶ�(-Speed_Max ~ Speed_Max)
 * @return      void
 */
void MOTOR::Run (double speed)
{
    if(speed > Param.Speed_Max)
    {
        speed = Param.Speed_Max;
    }
    else if(speed < -Param.Speed_Max)
    {
        speed = -Param.Speed_Max;
    }
    if (Param.dir == MOTOR_Direction_1)
    {
        if (speed > 0)
        {
            Channel1->Set_Percent(speed);
            Channel2->Set_Percent(0);
        }
        else
        {
            Channel1->Set_Percent(0);
            Channel2->Set_Percent(-speed);
        }

    }
    else if (Param.dir == MOTOR_Direction_2)
    {
        if (speed > 0)
        {
            Channel1->Set_Percent(0);
            Channel2->Set_Percent(speed);
        }
        else
        {
            Channel1->Set_Percent(-speed);
            Channel2->Set_Percent(0);
        }
    }
    Channel1->Init();
    Channel2->Init();
}

