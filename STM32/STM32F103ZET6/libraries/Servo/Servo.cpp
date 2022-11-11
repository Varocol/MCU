#include "Servo.h"
/**
 * @brief  Servo-空构造方法
 * @param  None
 * @return None
 */
Servo::Servo()
{
}

/**
 * @brief  Servo-带参构造方法
 * @param  Param        Servo参数列表
 * @return None
 */
Servo::Servo(Servo_Param Param)
{
    Set_Servo_Param(Param);
}

/**
 * @brief  Servo-析构方法
 * @param  None
 * @return None
 */
Servo::~Servo()
{
}

/**
 * @brief  Servo-设置参数方法
 * @param  Param        Servo参数列表
 * @return None
 */
void Servo::Set_Servo_Param(Servo_Param Param)
{
    //防止受控脉宽超出舵机阈值
    if (Param.CURRENT_START < Param.CURRENT_MIN)
    {
        Param.CURRENT_START = Param.CURRENT_MIN;
    }
    if (Param.CURRENT_END > Param.CURRENT_MAX)
    {
        Param.CURRENT_END = Param.CURRENT_MAX;
    }
    this->Param = Param;
    //这一步只是用于设置通道引脚和驱动频率
    Set_PWM_Param(Param.pwmch, Param.freq, MAP_TO_Percent((Param.MAP_MAX + Param.MAP_MIN) / 2));
}

/**
 * @brief  Servo-转向方法
 * @param  MAP_Value    映射后的转向参数
 * @return None
 */
void Servo::Turn(double MAP_VAL)
{
    //防止舵机转向过度
    if (MAP_VAL < Param.MAP_MIN)
    {
        MAP_VAL = Param.MAP_MIN;
    }
    if (MAP_VAL > Param.MAP_MAX)
    {
        MAP_VAL = Param.MAP_MAX;
    }
    Update(Param.pwmch, Param.freq, MAP_TO_Percent(MAP_VAL));
}

/**
 * @brief  Servo-脉宽转换成占空比百分比
 * @param  CURRENT      脉宽
 * @return Percent      占空比百分比
 */
double Servo::CURRENT_To_Percent(double CURRENT)
{
    return CURRENT * Param.freq / 10;
}

/**
 * @brief  Servo-映射值转换成脉宽
 * @param  MAP_VAL      映射值
 * @return CURRENT      脉宽
 */
double Servo::MAP_TO_CURRENT(double MAP_VAL)
{
    return (MAP_VAL - Param.MAP_MIN) / (Param.MAP_MAX - Param.MAP_MIN) * (Param.CURRENT_END - Param.CURRENT_START) + Param.CURRENT_START;
}

/**
 * @brief  Servo-映射值转换成占空比
 * @param  MAP_VAL      映射值
 * @return Percent      占空比百分比
 */
double Servo::MAP_TO_Percent(double MAP_VAL)
{
    return CURRENT_To_Percent(MAP_TO_CURRENT(MAP_VAL));
}
