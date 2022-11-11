#ifndef __OJ_TIM_H
#define __OJ_TIM_H
#include "stm32f10x.h"
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"

//TODO 需要改TIM整体架构
// OC通道列表
typedef enum
{
    OC1,
    OC2,
    OC3,
    OC4
} OC_enum;
// TIM参数列表
typedef struct
{
    TIM_TypeDef *TIMx;                             // TIMx
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // TIM基础参数初始化结构体
    TIM_OCInitTypeDef TIM_OCStructure;             // TIMOC通道初始化结构体
    TIM_ICInitTypeDef TIM_ICStructure;             // TIMIC初始化结构体
    NVIC_InitTypeDef TIM_NVIC_InitStructure;       // TIM中断初始化结构体
    uint16_t TIM_IT_Selection;                     // TIM中断位选择
    OC_enum OCx;                                   // TIM选择oc通道
    FunctionalState TIM_IT_State;                  // TIM中断使(失)能
} TIM_Parma;

class TIM
{
private:
    TIM_Parma TIMx_Parma;

public:
    TIM();
    ~TIM();
    TIM(TIM_Parma TIMx_Parma);
    void Update(TIM_Parma TIMx_Parma);
    void Set_TIM_Parma(TIM_Parma TIMx_Parma);
    void Pin_Init(); //后续会更新自动配置引脚
    void Base_Init();
    void OC_Init();
    void IC_Init();
    void ITConfig(uint16_t TIM_IT, FunctionalState NewState);
    void Init();
    void Enable();
    void Disable();
};
extern void (*TIM1_BRK_Handler)(void);
extern void (*TIM1_UP_Handler)(void);
extern void (*TIM1_TRG_COM_Handler)(void);
extern void (*TIM1_CC_Handler)(void);
extern void (*TIM2_Handler)(void);
extern void (*TIM3_Handler)(void);
extern void (*TIM4_Handler)(void);
extern void (*TIM8_BRK_Handler)(void);
extern void (*TIM8_UP_Handler)(void);
extern void (*TIM8_TRG_COM_Handler)(void);
extern void (*TIM8_CC_Handler)(void);
extern void (*TIM5_Handler)(void);
extern void (*TIM6_Handler)(void);
extern void (*TIM7_Handler)(void);
#endif