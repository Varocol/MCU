#ifndef __OJ_TIM_H
#define __OJ_TIM_H
#include "stm32f10x.h"
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
//OC通道列表
typedef enum
{
    OC1,
    OC2,
    OC3,
    OC4
} OC_Selection;
//TIM参数列表
typedef struct
{
    TIM_TypeDef *TIMx;                             //TIMx
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //TIM基础参数初始化结构体
    TIM_OCInitTypeDef TIM_OCStructure;             //TIMOC通道初始化结构体
    NVIC_Operate TIM_NVIC_Operate;                 //TIM配置对象
    FunctionalState TIM_IT_State;                  //TIM中断使(失)能
    uint16_t TIM_IT_Selection;                     //TIM中断位选择
    OC_Selection OCx;                              //TIM选择oc通道
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
    void Init();
    void Start();
    void Shutup();
};
#endif