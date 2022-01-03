#ifndef __OJ_PWM_H
#define __OJ_PWM_H
#include "stm32f10x.h"
#include "RCC.h"
#include "GPIO.h"
typedef enum
{
  // ������� PA8
  TIM1_Channel1_Selection_Default,
  // ������� PA9
  TIM1_Channel2_Selection_Default,
  // ������� PA10
  TIM1_Channel3_Selection_Default,
  // ������� PA11
  TIM1_Channel4_Selection_Default,

  // ������� PA8
  TIM1_Channel1_Selection_PartialRemap,
  // ������� PA9
  TIM1_Channel2_Selection_PartialRemap,
  // ������� PA10
  TIM1_Channel3_Selection_PartialRemap,
  // ������� PA11
  TIM1_Channel4_Selection_PartialRemap,

  // ������� PE9
  TIM1_Channel1_Selection_FullRemap,
  // ������� PE11
  TIM1_Channel2_Selection_FullRemap,
  // ������� PE13
  TIM1_Channel3_Selection_FullRemap,
  // ������� PE14
  TIM1_Channel4_Selection_FullRemap,

  // ������� PA0
  TIM2_Channel1_Selection_Default,
  // ������� PA1
  TIM2_Channel2_Selection_Default,
  // ������� PA2
  TIM2_Channel3_Selection_Default,
  // ������� PA3
  TIM2_Channel4_Selection_Default,

  // ������� PA15
  TIM2_Channel1_Selection_PartialRemap1,
  // ������� PB3
  TIM2_Channel2_Selection_PartialRemap1,
  // ������� PA2
  TIM2_Channel3_Selection_PartialRemap1,
  // ������� PA3
  TIM2_Channel4_Selection_PartialRemap1,

  // ������� PA0
  TIM2_Channel1_Selection_PartialRemap2,
  // ������� PA1
  TIM2_Channel2_Selection_PartialRemap2,
  // ������� PB10
  TIM2_Channel3_Selection_PartialRemap2,
  // ������� PB11
  TIM2_Channel4_Selection_PartialRemap2,

  // ������� PA15
  TIM2_Channel1_Selection_FullRemap,
  // ������� PB3
  TIM2_Channel2_Selection_FullRemap,
  // ������� PB10
  TIM2_Channel3_Selection_FullRemap,
  // ������� PB11
  TIM2_Channel4_Selection_FullRemap,

  // ������� PA6
  TIM3_Channel1_Selection_Default,
  // ������� PA7
  TIM3_Channel2_Selection_Default,
  // ������� PB0
  TIM3_Channel3_Selection_Default,
  // ������� PB1
  TIM3_Channel4_Selection_Default,

  // ������� PB4
  TIM3_Channel1_Selection_PartialRemap,
  // ������� PB5
  TIM3_Channel2_Selection_PartialRemap,
  // ������� PB0
  TIM3_Channel3_Selection_PartialRemap,
  // ������� PB1
  TIM3_Channel4_Selection_PartialRemap,

  // ������� PC6
  TIM3_Channel1_Selection_FullRemap,
  // ������� PC7
  TIM3_Channel2_Selection_FullRemap,
  // ������� PC8
  TIM3_Channel3_Selection_FullRemap,
  // ������� PC9
  TIM3_Channel4_Selection_FullRemap,

  // ������� PB6
  TIM4_Channel1_Selection_Default,
  // ������� PB7
  TIM4_Channel2_Selection_Default,
  // ������� PB8
  TIM4_Channel3_Selection_Default,
  // ������� PB9
  TIM4_Channel4_Selection_Default,

  // ������� PD12
  TIM4_Channel1_Selection_Remap,
  // ������� PD13
  TIM4_Channel2_Selection_Remap,
  // ������� PD14
  TIM4_Channel3_Selection_Remap,
  // ������� PD15
  TIM4_Channel4_Selection_Remap,

  // ������� PA0
  TIM5_Channel1_Selection_Default,
  // ������� PA1
  TIM5_Channel2_Selection_Default,
  // ������� PA2
  TIM5_Channel3_Selection_Default,
  // ������� PA3
  TIM5_Channel4_Selection_Default,

  // ������� PC6
  TIM8_Channel1_Selection_Default,
  // ������� PC7
  TIM8_Channel2_Selection_Default,
  // ������� PC8
  TIM8_Channel3_Selection_Default,
  // ������� PC9
  TIM8_Channel4_Selection_Default,

} TIMx_Channelx_Selection;

class PWM
{
private:
  TIMx_Channelx_Selection T_C_S;
  TIM_TypeDef *TIMx;
  double Frequency; //PWMƵ��
  double DutyRatio; //PWMռ�ձ�
public:
  PWM();
  PWM(TIMx_Channelx_Selection T_C_S, double Frequency, double DutyRatio);
  void Pin_Init();
  void Init();
  void Start();
  void ShutUp();
  void Update(TIMx_Channelx_Selection T_C_S, double Frequency, double DutyRatio);
  void Set_TIMx_Channelx_Selection(TIMx_Channelx_Selection T_C_S);
  void Set_Frequency(double Frequency);
  void Set_DutyRatio(double DutyRatio);
  ~PWM();
};

#endif /*__OJ_PWM_H*/