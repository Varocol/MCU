#include "MOTOR.h"
/*
 * @brief       MOTOR空构造方法
 * @param       void
 * @return      null
 */
MOTOR::MOTOR ()
{

}

/*
 * @brief       MOTOR带参构造方法
 * @param       pwmch1          驱动通道1
 * @param       pwmch2          驱动通道2
 * @param       dir             电机转动方向
 * @param       freq            电机驱动频率
 * @return      null
 */
MOTOR::MOTOR (MOTOR_Param Param)
{
    Set_Param(Param);
}

/*
 * @brief       MOTOR析构方法
 * @param       void
 * @return      null
 */
MOTOR::~MOTOR ()
{
    delete Channel1;
    delete Channel2;
}

/*
 * @brief       MOTOR设置参数方法
 * @param       pwmch1          驱动通道1
 * @param       pwmch2          驱动通道2
 * @param       dir             电机转动方向
 * @param       freq            电机驱动频率
 * @return      null
 */
void MOTOR::Set_Param (MOTOR_Param Param)
{
    this->Param = Param;
}

/*
 * @brief       MOTOR初始化PWM通道
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
 * @brief       MOTOR初始化
 * @param       null
 * @return      void
 */
void MOTOR::Init ()
{
    PWM_Init();
}

/*
 * @brief       MOTOR驱动方法
 * @param       speed           电机转动速度(-Speed_Max ~ Speed_Max)
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

