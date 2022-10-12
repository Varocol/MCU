#ifndef __OJ_ADC_H
#define __OJ_ADC_H
#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include <vector>
using std::vector;
/*
ADC����:
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
CH16        �ڲ��¶ȴ�����       VSS                 VSS
CH17        REFINT              VSS                 VSS

ADC1/ADC2 ����ͨ���ⲿ����
TIM1_CC1�¼�
TIM1_CC2�¼�
TIM1_CC3�¼�
TIM2_CC2�¼�
TIM3_TRGO�¼�
TIM4_CC4�¼�
EXTI11/TIM8_TRGO�¼�
SWSTART

ADC1/ADC2 ע��ͨ���ⲿ����
TIM1_TRGO�¼�
TIM1_CC4�¼�
TIM2_TRGO�¼�
TIM2_CC1�¼�
TIM3_CC4�¼�
TIM4_TRGO�¼�
EXTI15/TIM8_CC4�¼�
JSWSTART

ADC3 ����ͨ���ⲿ����
TIM3_CC1�¼�
TIM2_CC3�¼�
TIM1_CC3�¼�
TIM8_CC1�¼�
TIM8_TRGO�¼�
TIM5_CC1�¼�
TIM5_CC3�¼�
SWSTART

ADC3 ע��ͨ���ⲿ����
TIM1_TRGO
TIM1_CC4
TIM4_CC3
TIM8_CC2
TIM8_CC4
TIM5_TRGO
TIM5_CC4
JSWSTART

�жϱ�־λ�б�
ADC_IT_AWD      //������ģ�⿴�Ź�״̬λ
ADC_IT_EOC      //������ת������
ADC_IT_JEOC     //ע����ת������

���ڴ˿⽫���еĹ���ȫ�����ǽ�ȥ,���Բ���������΢����
*/

typedef struct
{
    uint8_t ADC_Channel;    // ADCͨ��
    uint8_t Rank;           // ADCͨ��ת�����(�����б�ڼ���ת��)1-16
    uint8_t ADC_SampleTime; // ADCͨ������ʱ��
} ADC_Channel_ConInfo;

typedef struct
{
    vector<ADC_Channel_ConInfo> ADC_Channellist; // ADCͨ���б�
    uint32_t ADC_ExternalTrigConv;               // ADC�ⲿ��������ѡ��
    FunctionalState ADC_DiscMode;                // ADC���ģʽʹ��(ʧ��)
    FunctionalState ADC_ExternalTrig;            // ADC�ⲿ����ʹ��(ʧ��)

} ADC_Channel_InitTypeDef;

typedef struct
{
    uint32_t RCC_PCLK2_Divx;                // ADCת��ʱ�ӷ�Ƶ����(������14MHz)
    uint8_t ADC_DiscModeNumber;             // ADC���ģʽת��ͨ������(1-8)
    uint32_t ADC_DataAlign;                 // ADC���ݶ����ʽ(���������Ҷ���)
    uint32_t ADC_Mode;                      // ADCģʽѡ��(�ܹ�10��)
    FunctionalState ADC_JAuto;              // ADC�Զ�ע��ʹʹ(ʧ)��
    FunctionalState ADC_ContinuousConvMode; // ADC����ת��ģʽʹ(ʧ)��
    FunctionalState ADC_ScanConvMode;       // ADCɨ��ģʽʹ(ʧ)��
} ADC_Base_InitTypeDef;

typedef struct
{
    ADC_TypeDef *ADCx;                                         // ADCx
    ADC_Base_InitTypeDef ADC_Base_InitStructure;               // ADC������ʼ���ṹ��
    ADC_Channel_InitTypeDef ADC_RegularChannel_InitStructure;  // ADC����ͨ����ʼ���ṹ��
    ADC_Channel_InitTypeDef ADC_InjectedChannel_InitStructure; // ADCע��ͨ����ʼ���ṹ��
    NVIC_InitTypeDef ADC_NVIC_InitStructure;                   // ADC�жϽṹ��
    uint32_t ADC_IT_Selection;                                 // ADC�ж�λѡ��
    FunctionalState ADC_IT_State;                              // ADC�ж�ʹ(ʧ)��
    FunctionalState ADC_DMA_State;                             // ADCDMAʹ(ʧ)��
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
