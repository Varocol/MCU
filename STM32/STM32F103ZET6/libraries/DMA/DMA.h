#ifndef __OJ_DMA_h
#define __OJ_DMA_h
#include "NVIC.h"
#include "RCC.h"
/*
        Channel1        Channel2        Channel3        Channel4        Channel5        Channel6        Channel7
DMA1:   ADC1            SPI1_RX         SPI1_TX         SPI/I2S2_RX     SPI/I2S2_TX     USART2_RX       USART2_TX
        TIM2_CH3        USART3_TX       USART3_RX       USART1_TX       USART1_RX       I2C1_TX         I2C1_RX
        TIM4_CH1        TIM1_CH1        TIM1_CH2        I2C2_TX         I2C2_RX         TIM1_CH3        TIM2_CH2
                        TIM2_UP         TIM3_CH4        TIM1_TX4        TIM1_UP         TIM3_CH1        TIM2_CH4
                        TIM3_CH3        TIM3_UP         TIM1_TRIG       TIM2_CH1        TIM3_TRIG       TIM4_UP
                                                        TIM1_COM        TIM4_CH3
                                                        TIM4_CH2

DMA2:   SPI/I2S3_RX     SPI/I2S3_TX     UART4_RX        SDIO            ADC3
        TIM5_CH4        TIM5_CH3        TIM6_UP         TIM5_CH2        UART4_TX
        TIM5_TRIG       TIM5_UP         DAC_Channel_1   TIM7_UP         TIM5_CH1
        TIM8_CH3        TIM8_CH4        TIM8_CH1        DAC_Channel_2   TIM8_CH2
        TIM8_UP         TIM8_TRIG
                        TIM8_COM

�жϱ�־λ�б�
DMA_IT_HT   //��������־
DMA_IT_TC   //������ɱ�־
DMA_IT_TE   //��������־
*/
typedef struct
{
    DMA_Channel_TypeDef *DMA_Channelx;       // DMA_Channelx
    DMA_InitTypeDef DMA_InitStructure;       // DMA��ʼ���ṹ��
    NVIC_InitTypeDef DMA_NVIC_InitStructure; // DMA�жϳ�ʼ���ṹ��
    uint32_t DMA_IT_Selection;               // DMA�ж�λѡ��
    FunctionalState DMA_IT_State;            // DMA�ж�ʹ(ʧ)��
} DMA_Param;
class DMA
{
private:
    DMA_Param DMAx_Param;
    DMA_TypeDef *Get_DMA(DMA_Channel_TypeDef *DMA_Channelx);

public:
    DMA();
    ~DMA();
    DMA(DMA_Param DMAx_Param);
    void Update(DMA_Param DMAx_Param);
    void Set_DMA_Param(DMA_Param DMAx_Param);
    void ITConfig(uint32_t DMA_IT, FunctionalState NewState);
    void SetCurrDataCounter(uint16_t DataNumber);
    void Init();
    void Enable();
    void Disable();

    void RCC_Enable();
    void RCC_Disable();
    static void RCC_Enable(DMA_TypeDef *DMAx);
    static void RCC_Disable(DMA_TypeDef *DMAx);
};
#endif /*_OJ_DMA_h*/