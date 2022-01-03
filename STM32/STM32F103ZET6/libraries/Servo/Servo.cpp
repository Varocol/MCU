#include "Servo.h"

/**
  * @brief  舵机析构函数
  * @param  None
  * @retval None
  */
Servo::~Servo()
{
}

/**
  * @brief  舵机空构造函数
  * @param  None
  * @retval None
  */
Servo::Servo()
{
}

/**
  * @brief  舵机构造函数
  * @param  T_C_S:选择TIMx的CHx通道
  * @param  hz:舵机驱动频率
  * @param  angle:舵机转动角度
  * @retval None
  */
Servo::Servo(TIMx_Channelx_Selection T_C_S, double hz, double angle)
{
  Set_Frequency(hz);
  Set_DutyRatio(Angle_to_DutyRatio(angle, hz));
  Set_TIMx_Channelx_Selection(T_C_S);
}

/**
  * @brief  角度转换占空比函数
  * @param  None
  * @retval None
  */
double Servo::Angle_to_DutyRatio(double angle, double hz)
{
  if (angle < 0)
  {
    angle = angle - (int)((angle + 1) / ANGLE_WHITH) * ANGLE_WHITH + ANGLE_WHITH;
  }
  angle = (angle - 1) - (int)((angle - 1) / ANGLE_WHITH) * ANGLE_WHITH + 1;
  return ((angle / ANGLE_WHITH) * (CURRENT_END - CURRENT_START) + CURRENT_START) * hz;
}

/**
  * @brief  舵机初始化函数
  * @param  None
  * @retval None
  */
void Servo::Init()
{
  PWM::Init();
}

/**
  * @brief  舵机更新参数函数
  * @param  hz:舵机驱动频率
  * @param  angle:舵机转动角度
  * @retval None
  */
void Servo::Update(TIMx_Channelx_Selection T_C_S, double hz, double angle)
{
  Set_TIMx_Channelx_Selection(T_C_S);
  Set_Frequency(hz);
  Set_DutyRatio(Angle_to_DutyRatio(angle, hz));
  Init();
}