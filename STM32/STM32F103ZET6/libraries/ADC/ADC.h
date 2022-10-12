#ifndef __OJ_ADC_H
#define __OJ_ADC_H
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include <vector>
using std::vector;
/*
ADC引脚:
            ADC1                ADC2                ADC3
CH0         PA0                 PA0                 PA0
CH1         PA1                 PA1                 PA1
CH2         PA2                 PA2                 PA2
CH3         PA3                 PA3                 PA3
CH4         PA4                 PA4                 /
CH5         PA5                 PA5                 /
CH6         PA6                 PA6                 /
CH7         PA7                 PA7                 /
CH8         PB0                 PB0                 /
CH9         PB1                 PB1                 VSS
CH10        PC0                 PC0                 PC0
CH11        PC1                 PC1                 PC1
CH12        PC2                 PC2                 PC2
CH13        PC3                 PC3                 PC3
CH14        PC4                 PC4                 VSS
CH15        PC5                 PC5                 VSS
CH16        内部温度传感器       VSS                 VSS
CH17        REFINT              VSS                 VSS

ADC1/ADC2 规则通道外部触发
TIM1_CC1事件
TIM1_CC2事件
TIM1_CC3事件
TIM2_CC2事件
TIM3_TRGO事件
TIM4_CC4事件
EXTI11/TIM8_TRGO事件
SWSTART

ADC1/ADC2 注入通道外部触发
TIM1_TRGO事件
TIM1_CC4事件
TIM2_TRGO事件
TIM2_CC1事件
TIM3_CC4事件
TIM4_TRGO事件
EXTI15/TIM8_CC4事件
JSWSTART

ADC3 规则通道外部触发
TIM3_CC1事件
TIM2_CC3事件
TIM1_CC3事件
TIM8_CC1事件
TIM8_TRGO事件
TIM5_CC1事件
TIM5_CC3事件
SWSTART

ADC3 注入通道外部触发
TIM1_TRGO
TIM1_CC4
TIM4_CC3
TIM8_CC2
TIM8_CC4
TIM5_TRGO
TIM5_CC4
JSWSTART

中断标志位列表
ADC_IT_AWD      //设置了模拟看门狗状态位
ADC_IT_EOC      //规则组转换结束
ADC_IT_JEOC     //注入组转换结束

由于此库将所有的功能全部考虑进去,所以参数配置略微复杂
*/

typedef struct
{
    uint8_t ADC_Channel;    // ADC通道
    uint8_t Rank;           // ADC通道转换序号(排在列表第几个转换)1-16
    uint8_t ADC_SampleTime; // ADC通道采样时间
} ADC_Channel_ConInfo;

typedef struct
{
    vector<ADC_Channel_ConInfo> ADC_Channellist; // ADC通道列表
    uint32_t ADC_ExternalTrigConv;               // ADC外部触发条件选择
    FunctionalState ADC_DiscMode;                // ADC间断模式使能(失能)
    FunctionalState ADC_ExternalTrig;            // ADC外部触发使能(失能)

} ADC_Channel_InitTypeDef;

typedef struct
{
    uint32_t RCC_PCLK2_Divx;                // ADC转换时钟分频配置(不超过14MHz)
    uint8_t ADC_DiscModeNumber;             // ADC间断模式转换通道个数(1-8)
    uint32_t ADC_DataAlign;                 // ADC数据对齐格式(左对齐或者右对齐)
    uint32_t ADC_Mode;                      // ADC模式选择(总共10种)
    FunctionalState ADC_JAuto;              // ADC自动注入使使(失)能
    FunctionalState ADC_ContinuousConvMode; // ADC连续转换模式使(失)能
    FunctionalState ADC_ScanConvMode;       // ADC扫描模式使(失)能
} ADC_Base_InitTypeDef;

typedef struct
{
    ADC_TypeDef *ADCx;                                         // ADCx
    ADC_Base_InitTypeDef ADC_Base_InitStructure;               // ADC基础初始化结构体
    ADC_Channel_InitTypeDef ADC_RegularChannel_InitStructure;  // ADC规则通道初始化结构体
    ADC_Channel_InitTypeDef ADC_InjectedChannel_InitStructure; // ADC注入通道初始化结构体
    NVIC_InitTypeDef ADC_NVIC_InitStructure;                   // ADC中断结构体
    uint32_t ADC_IT_Selection;                                 // ADC中断位选择
    FunctionalState ADC_IT_State;                              // ADC中断使(失)能
    FunctionalState ADC_DMA_State;                             // ADCDMA使(失)能
} ADC_Param;

class ADC
{
private:
    ADC_Param ADCx_Param;
    void Pin_Init(uint8_t ADC_Channel);
public:
    ADC();
    ~ADC();
    ADC(ADC_Param ADCx_Param);
    void Set_ADC_Param(ADC_Param ADCx_Param);
    void Update(ADC_Param ADCx_Param);
    void DMACmd(FunctionalState NewState);
    void ITConfig(uint16_t ADC_IT, FunctionalState NewState);
    void Pin_Init();
    void Init();
    void Enable();
    void Disable();
    static void TempSensorVrefintCmd(FunctionalState NewState);
    void SoftwareStartConvCmd(FunctionalState NewState);
    void SoftwareStartInjectedConvCmd(FunctionalState NewState);
    void AnalogWatchdogCmd(uint32_t ADC_AnalogWatchdog);
    void AnalogWatchdogThresholdsConfig(uint16_t HighThreshold, uint16_t LowThreshold);
    void AnalogWatchdogSingleChannelConfig(uint8_t ADC_Channel);
    void SetInjectedOffset(uint8_t ADC_InjectedChannel, uint16_t Offset);

    void RCC_Enable();
    void RCC_Disable();
    static void RCC_Enable(ADC_TypeDef *ADCx);
    static void RCC_Disable(ADC_TypeDef *ADCx);
};

#endif /*__OJ_ADC_H*/
