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

中断标志位列表
DMA_IT_HT   //传输过半标志
DMA_IT_TC   //传输完成标志
DMA_IT_TE   //传输错误标志
*/

// DMA外设枚举
typedef enum
{
    // DMA1_Channel1
    DMA_ADC1 = 1,
    DMA_TIM2_CH3,
    DMA_TIM4_CH1,
    // DMA1_Channel2
    DMA_SPI1_RX = 11,
    DMA_USART3_TX,
    DMA_TIM1_CH1,
    DMA_TIM2_UP,
    DMA_TIM3_CH3,
    // DMA1_Channel3
    DMA_SPI1_TX = 21,
    DMA_USART3_RX,
    DMA_TIM1_CH2,
    DMA_TIM3_CH4,
    DMA_TIM3_UP,
    // DMA1_Channel4
    DMA_SPI2_I2S2_RX = 31,
    DMA_USART1_TX,
    DMA_I2C2_TX,
    DMA_TIM1_TX4,
    DMA_TIM1_TRIG,
    DMA_TIM1_COM,
    DMA_TIM4_CH2,
    // DMA1_Channel5
    DMA_SPI2_I2S2_TX = 41,
    DMA_USART1_RX,
    DMA_I2C2_RX,
    DMA_TIM1_UP,
    DMA_TIM2_CH1,
    DMA_TIM4_CH3,
    // DMA1_Channel6
    DMA_USART2_RX = 51,
    DMA_I2C1_TX,
    DMA_TIM1_CH3,
    DMA_TIM3_CH1,
    DMA_TIM3_TRIG,
    // DMA1_Channel7
    DMA_USART2_TX = 61,
    DMA_I2C1_RX,
    DMA_TIM2_CH2,
    DMA_TIM2_CH4,
    DMA_TIM4_UP,
    // DMA2_Channel1
    DMA_SPI3_I2S3_RX = 71,
    DMA_TIM5_CH4,
    DMA_TIM5_TRIG,
    DMA_TIM8_CH3,
    DMA_TIM8_UP,
    // DMA2_Channel2
    DMA_SPI3_I2S3_TX = 81,
    DMA_TIM5_CH3,
    DMA_TIM5_UP,
    DMA_TIM8_CH4,
    DMA_TIM8_TRIG,
    DMA_TIM8_COM,
    // DMA2_Channel3
    DMA_UART4_RX = 91,
    DMA_TIM6_UP,
    DMA_DAC_Channel_1,
    DMA_TIM8_CH1,
    // DMA2_Channel4
    DMA_SDIO = 101,
    DMA_TIM5_CH2,
    DMA_TIM7_UP,
    DMA_DAC_Channel_2,
    // DMA2_Channel5
    DMA_ADC3 = 111,
    DMA_UART4_TX,
    DMA_TIM5_CH1,
    DMA_TIM8_CH2
} DMA_Perip_enum;

typedef struct
{
    DMA_Channel_TypeDef *DMA_Channelx;       // DMA_Channelx
    DMA_InitTypeDef DMA_InitStructure;       // DMA初始化结构体
    NVIC_InitTypeDef DMA_NVIC_InitStructure; // DMA中断初始化结构体
    uint32_t DMA_IT_Selection;               // DMA中断位选择
    FunctionalState DMA_IT_State;            // DMA中断使(失)能
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
    static DMA_Channel_TypeDef *Get_DMA_Channel(DMA_Perip_enum perip);
    static uint8_t Get_DMAx_Channelx_IRQn(DMA_Channel_TypeDef *DMAx_Channelx);
    static bool Check_DMAx_Channelx(DMA_Channel_TypeDef *DMAx_Channelx);
};
#endif /*_OJ_DMA_h*/