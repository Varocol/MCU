#ifndef __OJ_PWM_H
#define __OJ_PWM_H
#include "stm32f10x.h"
#include "RCC.h"
#include "GPIO.h"
typedef enum
{
  // 输出引脚 PA8
  TIM1_Channel1_Selection_Default,
  // 输出引脚 PA9
  TIM1_Channel2_Selection_Default,
  // 输出引脚 PA10
  TIM1_Channel3_Selection_Default,
  // 输出引脚 PA11
  TIM1_Channel4_Selection_Default,

  // 输出引脚 PA8
  TIM1_Channel1_Selection_PartialRemap,
  // 输出引脚 PA9
  TIM1_Channel2_Selection_PartialRemap,
  // 输出引脚 PA10
  TIM1_Channel3_Selection_PartialRemap,
  // 输出引脚 PA11
  TIM1_Channel4_Selection_PartialRemap,

  // 输出引脚 PE9
  TIM1_Channel1_Selection_FullRemap,
  // 输出引脚 PE11
  TIM1_Channel2_Selection_FullRemap,
  // 输出引脚 PE13
  TIM1_Channel3_Selection_FullRemap,
  // 输出引脚 PE14
  TIM1_Channel4_Selection_FullRemap,

  // 输出引脚 PA0
  TIM2_Channel1_Selection_Default,
  // 输出引脚 PA1
  TIM2_Channel2_Selection_Default,
  // 输出引脚 PA2
  TIM2_Channel3_Selection_Default,
  // 输出引脚 PA3
  TIM2_Channel4_Selection_Default,

  // 输出引脚 PA15
  TIM2_Channel1_Selection_PartialRemap1,
  // 输出引脚 PB3
  TIM2_Channel2_Selection_PartialRemap1,
  // 输出引脚 PA2
  TIM2_Channel3_Selection_PartialRemap1,
  // 输出引脚 PA3
  TIM2_Channel4_Selection_PartialRemap1,

  // 输出引脚 PA0
  TIM2_Channel1_Selection_PartialRemap2,
  // 输出引脚 PA1
  TIM2_Channel2_Selection_PartialRemap2,
  // 输出引脚 PB10
  TIM2_Channel3_Selection_PartialRemap2,
  // 输出引脚 PB11
  TIM2_Channel4_Selection_PartialRemap2,

  // 输出引脚 PA15
  TIM2_Channel1_Selection_FullRemap,
  // 输出引脚 PB3
  TIM2_Channel2_Selection_FullRemap,
  // 输出引脚 PB10
  TIM2_Channel3_Selection_FullRemap,
  // 输出引脚 PB11
  TIM2_Channel4_Selection_FullRemap,

  // 输出引脚 PA6
  TIM3_Channel1_Selection_Default,
  // 输出引脚 PA7
  TIM3_Channel2_Selection_Default,
  // 输出引脚 PB0
  TIM3_Channel3_Selection_Default,
  // 输出引脚 PB1
  TIM3_Channel4_Selection_Default,

  // 输出引脚 PB4
  TIM3_Channel1_Selection_PartialRemap,
  // 输出引脚 PB5
  TIM3_Channel2_Selection_PartialRemap,
  // 输出引脚 PB0
  TIM3_Channel3_Selection_PartialRemap,
  // 输出引脚 PB1
  TIM3_Channel4_Selection_PartialRemap,

  // 输出引脚 PC6
  TIM3_Channel1_Selection_FullRemap,
  // 输出引脚 PC7
  TIM3_Channel2_Selection_FullRemap,
  // 输出引脚 PC8
  TIM3_Channel3_Selection_FullRemap,
  // 输出引脚 PC9
  TIM3_Channel4_Selection_FullRemap,

  // 输出引脚 PB6
  TIM4_Channel1_Selection_Default,
  // 输出引脚 PB7
  TIM4_Channel2_Selection_Default,
  // 输出引脚 PB8
  TIM4_Channel3_Selection_Default,
  // 输出引脚 PB9
  TIM4_Channel4_Selection_Default,

  // 输出引脚 PD12
  TIM4_Channel1_Selection_Remap,
  // 输出引脚 PD13
  TIM4_Channel2_Selection_Remap,
  // 输出引脚 PD14
  TIM4_Channel3_Selection_Remap,
  // 输出引脚 PD15
  TIM4_Channel4_Selection_Remap,

  // 输出引脚 PA0
  TIM5_Channel1_Selection_Default,
  // 输出引脚 PA1
  TIM5_Channel2_Selection_Default,
  // 输出引脚 PA2
  TIM5_Channel3_Selection_Default,
  // 输出引脚 PA3
  TIM5_Channel4_Selection_Default,

  // 输出引脚 PC6
  TIM8_Channel1_Selection_Default,
  // 输出引脚 PC7
  TIM8_Channel2_Selection_Default,
  // 输出引脚 PC8
  TIM8_Channel3_Selection_Default,
  // 输出引脚 PC9
  TIM8_Channel4_Selection_Default,

} TIMx_Channelx_Selection;

class PWM
{
private:
  TIMx_Channelx_Selection T_C_S;
  TIM_TypeDef *TIMx;
  double Frequency; //PWM频率
  double DutyRatio; //PWM占空比
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