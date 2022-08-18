#ifndef __OJ_PWM_H
#define __OJ_PWM_H
#include "stm32f10x.h"
#include "RCC.h"
#include "GPIO.h"
/*

                Channel1    Channel2    Channel3    Channel4
TIM1: Default
                  PA8         PA9         PA10        PA11
      PartialRemap
                  PA8         PA9         PA10        PA11
      FullRemap
                  PE9         PE11        PE13        PE14
TIM2:
      Default
                  PA0         PA1         PA2         PA3  
      PartialRemap1
                  PA15        PB3         PA2         PA3
      PartialRemap2
                  PA0         PA1         PB10        PB11
      FullRemap
                  PA15        PB3         PB10        PB11
TIM3:
      Default
                  PA6         PA7         PB0         PB1
      PartialRemap
                  PB4         PB5         PB0         PB1
      FullRemap
                  PC6         PC7         PC8         PC9
TIM4:
      Default
                  PB6         PB7         PB8         PB9
      Remap
                  PD12        PD13        PD14        PD15
TIM5:
      Default
                  PA0         PA1         PA2         PA3
TIM8:
      Default
                  PC6         PC7         PC8         PC9

                  
ʹ��ͬһ��ʱ����ͬͨ��ʱҪע��:
1������ͨ����Ƶ����ͬ,�������һ������ͨ����Ƶ�ʲ�������(Ƶ����ARR����,����ʱ����ARRֻ��һ��)
2������ͨ����ռ�ձȿ��Բ�ͬ,�����CCRx����(x = 1,2,3,4)���Ը�·ռ�ձ����Լ���CCRx����
3��������һ��ͨ���õ�ʱ��AFIO��ӳ������ź�,������ͨ��������Ҳ����ӳ��

*/

typedef enum
{
  // ������� PA8
  TIM1_Channel1_Default,
  // ������� PA9
  TIM1_Channel2_Default,
  // ������� PA10
  TIM1_Channel3_Default,
  // ������� PA11
  TIM1_Channel4_Default,

  // ������� PA8
  TIM1_Channel1_PartialRemap,
  // ������� PA9
  TIM1_Channel2_PartialRemap,
  // ������� PA10
  TIM1_Channel3_PartialRemap,
  // ������� PA11
  TIM1_Channel4_PartialRemap,

  // ������� PE9
  TIM1_Channel1_FullRemap,
  // ������� PE11
  TIM1_Channel2_FullRemap,
  // ������� PE13
  TIM1_Channel3_FullRemap,
  // ������� PE14
  TIM1_Channel4_FullRemap,

  // ������� PA0
  TIM2_Channel1_Default,
  // ������� PA1
  TIM2_Channel2_Default,
  // ������� PA2
  TIM2_Channel3_Default,
  // ������� PA3
  TIM2_Channel4_Default,

  // ������� PA15
  TIM2_Channel1_PartialRemap1,
  // ������� PB3
  TIM2_Channel2_PartialRemap1,
  // ������� PA2
  TIM2_Channel3_PartialRemap1,
  // ������� PA3
  TIM2_Channel4_PartialRemap1,

  // ������� PA0
  TIM2_Channel1_PartialRemap2,
  // ������� PA1
  TIM2_Channel2_PartialRemap2,
  // ������� PB10
  TIM2_Channel3_PartialRemap2,
  // ������� PB11
  TIM2_Channel4_PartialRemap2,

  // ������� PA15
  TIM2_Channel1_FullRemap,
  // ������� PB3
  TIM2_Channel2_FullRemap,
  // ������� PB10
  TIM2_Channel3_FullRemap,
  // ������� PB11
  TIM2_Channel4_FullRemap,

  // ������� PA6
  TIM3_Channel1_Default,
  // ������� PA7
  TIM3_Channel2_Default,
  // ������� PB0
  TIM3_Channel3_Default,
  // ������� PB1
  TIM3_Channel4_Default,

  // ������� PB4
  TIM3_Channel1_PartialRemap,
  // ������� PB5
  TIM3_Channel2_PartialRemap,
  // ������� PB0
  TIM3_Channel3_PartialRemap,
  // ������� PB1
  TIM3_Channel4_PartialRemap,

  // ������� PC6
  TIM3_Channel1_FullRemap,
  // ������� PC7
  TIM3_Channel2_FullRemap,
  // ������� PC8
  TIM3_Channel3_FullRemap,
  // ������� PC9
  TIM3_Channel4_FullRemap,

  // ������� PB6
  TIM4_Channel1_Default,
  // ������� PB7
  TIM4_Channel2_Default,
  // ������� PB8
  TIM4_Channel3_Default,
  // ������� PB9
  TIM4_Channel4_Default,

  // ������� PD12
  TIM4_Channel1_Remap,
  // ������� PD13
  TIM4_Channel2_Remap,
  // ������� PD14
  TIM4_Channel3_Remap,
  // ������� PD15
  TIM4_Channel4_Remap,

  // ������� PA0
  TIM5_Channel1_Default,
  // ������� PA1
  TIM5_Channel2_Default,
  // ������� PA2
  TIM5_Channel3_Default,
  // ������� PA3
  TIM5_Channel4_Default,

  // ������� PC6
  TIM8_Channel1_Default,
  // ������� PC7
  TIM8_Channel2_Default,
  // ������� PC8
  TIM8_Channel3_Default,
  // ������� PC9
  TIM8_Channel4_Default,

} TIMx_Channelx_enum;

class PWM
{
private:
  TIMx_Channelx_enum TIMx_Channelx;
  TIM_TypeDef *TIMx;
  double Frequency;
  double DutyRatio;
public:
  PWM();
  PWM(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio);
  void Pin_Init();
  void Init();
  void Start();
  void ShutUp();
  void Set_PWM_Param(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio);
  void Update(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio);
  void Set_TIMx_Channelx_enum(TIMx_Channelx_enum TIMx_Channelx);
  void Set_Frequency(double Frequency);
  void Set_DutyRatio(double DutyRatio);
  ~PWM();
};

#endif /*__OJ_PWM_H*/