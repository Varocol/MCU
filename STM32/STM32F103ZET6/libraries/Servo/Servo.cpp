#include "Servo.h"

/**
  * @brief  �����������
  * @param  None
  * @retval None
  */
Servo::~Servo()
{
}

/**
  * @brief  ����չ��캯��
  * @param  None
  * @retval None
  */
Servo::Servo()
{
}

/**
  * @brief  ������캯��
  * @param  T_C_S:ѡ��TIMx��CHxͨ��
  * @param  hz:�������Ƶ��
  * @param  angle:���ת���Ƕ�
  * @retval None
  */
Servo::Servo(TIMx_Channelx_Selection T_C_S, double hz, double angle)
{
  Set_Frequency(hz);
  Set_DutyRatio(Angle_to_DutyRatio(angle, hz));
  Set_TIMx_Channelx_Selection(T_C_S);
}

/**
  * @brief  �Ƕ�ת��ռ�ձȺ���
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
  * @brief  �����ʼ������
  * @param  None
  * @retval None
  */
void Servo::Init()
{
  PWM::Init();
}

/**
  * @brief  ������²�������
  * @param  hz:�������Ƶ��
  * @param  angle:���ת���Ƕ�
  * @retval None
  */
void Servo::Update(TIMx_Channelx_Selection T_C_S, double hz, double angle)
{
  Set_TIMx_Channelx_Selection(T_C_S);
  Set_Frequency(hz);
  Set_DutyRatio(Angle_to_DutyRatio(angle, hz));
  Init();
}