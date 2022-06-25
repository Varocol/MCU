#ifndef __OJ_DMA_h
#define __OJ_DMA_h
#include "NVIC.h"
#include "RCC.h"
/*
DMA1:
Channel1:
ADC1            TIM2_CH3        TIM4_CH1
Channel2:
SPI1_RX         USART3_TX       TIM1_CH1        TIM2_UP         TIM3_CH3
Channel3:
SPI1_TX         USART3_RX       TIM1_CH2        TIM3_CH4        TIM3_UP
Channel4:
SPI/I2S2_RX     USART1_TX       I2C2_TX         TIM1_TX4        TIM1_TRIG       TIM1_COM        TIM4_CH2
Channel5:
SPI/I2S2_TX     USART1_RX       I2C2_RX         TIM1_UP         TIM2_CH1        TIM4_CH3
Channel6:
USART2_RX       I2C1_TX         TIM1_CH3        TIM3_CH1        TIM3_TRIG
Channel7:
USART2_TX       I2C1_RX         TIM2_CH2        TIM2_CH4        TIM4_UP

DMA2:
Channel1:
SPI/I2S3_RX     TIM5_CH4        TIM5_TRIG       TIM8_CH3        TIM8_UP
Channel2:
SPI/I2S3_TX     TIM5_CH3        TIM5_UP         TIM8_CH4        TIM8_TRIG       TIM8_COM
Channel3:
UART4_RX        TIM6_UP         DAC_Channel_1   TIM8_CH1
Channel4:
SDIO            TIM5_CH2        TIM7_UP         DAC_Channel_2
Channel5:
ADC3            UART4_TX        TIM5_CH1        TIM8_CH2

DMA_IT_HT   //传输过半标志
DMA_IT_TC   //传输完成标志
DMA_IT_TE   //传输错误标志
*/
typedef struct
{
    DMA_Channel_TypeDef *DMA_Channelx; // DMA_Channelx
    DMA_InitTypeDef DMA_InitStructure; // DMA初始化结构体
    NVIC_Operate DMA_NVIC_Operate;     // DMA中断对象
    FunctionalState DMA_IT_State;      // DMA中断使(失)能
    uint32_t DMA_IT_Selection;         // DMA中断位选择
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
    void Init();
    void Start();
    void ShutUp();
};
#endif /*_OJ_DMA_h*/