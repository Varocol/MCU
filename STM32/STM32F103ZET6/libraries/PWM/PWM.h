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

                  
使用同一定时器不同通道时要注意:
1、各个通道的频率相同,且由最后一次配置通道的频率操作决定(频率由ARR控制,而定时器的ARR只有一个)
2、各个通道的占空比可以不同,这个由CCRx控制(x = 1,2,3,4)所以各路占空比由自己的CCRx决定
3、当其中一个通道用的时经AFIO重映射的引脚后,其他的通道的引脚也会重映射

*/

typedef enum
{
  // 输出引脚 PA8
  TIM1_Channel1_Default,
  // 输出引脚 PA9
  TIM1_Channel2_Default,
  // 输出引脚 PA10
  TIM1_Channel3_Default,
  // 输出引脚 PA11
  TIM1_Channel4_Default,

  // 输出引脚 PA8
  TIM1_Channel1_PartialRemap,
  // 输出引脚 PA9
  TIM1_Channel2_PartialRemap,
  // 输出引脚 PA10
  TIM1_Channel3_PartialRemap,
  // 输出引脚 PA11
  TIM1_Channel4_PartialRemap,

  // 输出引脚 PE9
  TIM1_Channel1_FullRemap,
  // 输出引脚 PE11
  TIM1_Channel2_FullRemap,
  // 输出引脚 PE13
  TIM1_Channel3_FullRemap,
  // 输出引脚 PE14
  TIM1_Channel4_FullRemap,

  // 输出引脚 PA0
  TIM2_Channel1_Default,
  // 输出引脚 PA1
  TIM2_Channel2_Default,
  // 输出引脚 PA2
  TIM2_Channel3_Default,
  // 输出引脚 PA3
  TIM2_Channel4_Default,

  // 输出引脚 PA15
  TIM2_Channel1_PartialRemap1,
  // 输出引脚 PB3
  TIM2_Channel2_PartialRemap1,
  // 输出引脚 PA2
  TIM2_Channel3_PartialRemap1,
  // 输出引脚 PA3
  TIM2_Channel4_PartialRemap1,

  // 输出引脚 PA0
  TIM2_Channel1_PartialRemap2,
  // 输出引脚 PA1
  TIM2_Channel2_PartialRemap2,
  // 输出引脚 PB10
  TIM2_Channel3_PartialRemap2,
  // 输出引脚 PB11
  TIM2_Channel4_PartialRemap2,

  // 输出引脚 PA15
  TIM2_Channel1_FullRemap,
  // 输出引脚 PB3
  TIM2_Channel2_FullRemap,
  // 输出引脚 PB10
  TIM2_Channel3_FullRemap,
  // 输出引脚 PB11
  TIM2_Channel4_FullRemap,

  // 输出引脚 PA6
  TIM3_Channel1_Default,
  // 输出引脚 PA7
  TIM3_Channel2_Default,
  // 输出引脚 PB0
  TIM3_Channel3_Default,
  // 输出引脚 PB1
  TIM3_Channel4_Default,

  // 输出引脚 PB4
  TIM3_Channel1_PartialRemap,
  // 输出引脚 PB5
  TIM3_Channel2_PartialRemap,
  // 输出引脚 PB0
  TIM3_Channel3_PartialRemap,
  // 输出引脚 PB1
  TIM3_Channel4_PartialRemap,

  // 输出引脚 PC6
  TIM3_Channel1_FullRemap,
  // 输出引脚 PC7
  TIM3_Channel2_FullRemap,
  // 输出引脚 PC8
  TIM3_Channel3_FullRemap,
  // 输出引脚 PC9
  TIM3_Channel4_FullRemap,

  // 输出引脚 PB6
  TIM4_Channel1_Default,
  // 输出引脚 PB7
  TIM4_Channel2_Default,
  // 输出引脚 PB8
  TIM4_Channel3_Default,
  // 输出引脚 PB9
  TIM4_Channel4_Default,

  // 输出引脚 PD12
  TIM4_Channel1_Remap,
  // 输出引脚 PD13
  TIM4_Channel2_Remap,
  // 输出引脚 PD14
  TIM4_Channel3_Remap,
  // 输出引脚 PD15
  TIM4_Channel4_Remap,

  // 输出引脚 PA0
  TIM5_Channel1_Default,
  // 输出引脚 PA1
  TIM5_Channel2_Default,
  // 输出引脚 PA2
  TIM5_Channel3_Default,
  // 输出引脚 PA3
  TIM5_Channel4_Default,

  // 输出引脚 PC6
  TIM8_Channel1_Default,
  // 输出引脚 PC7
  TIM8_Channel2_Default,
  // 输出引脚 PC8
  TIM8_Channel3_Default,
  // 输出引脚 PC9
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