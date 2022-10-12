#ifndef __OJ_TIM_H
#define __OJ_TIM_H
#include "stm32f10x.h"
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"

//TODO ��Ҫ��TIM����ܹ�
// OCͨ���б�
typedef enum
{
    OC1,
    OC2,
    OC3,
    OC4
} OC_enum;
// TIM�����б�
typedef struct
{
    TIM_TypeDef *TIMx;                             // TIMx
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; // TIM����������ʼ���ṹ��
    TIM_OCInitTypeDef TIM_OCStructure;             // TIMOCͨ����ʼ���ṹ��
    TIM_ICInitTypeDef TIM_ICStructure;             // TIMIC��ʼ���ṹ��
    NVIC_InitTypeDef TIM_NVIC_InitStructure;       // TIM�жϳ�ʼ���ṹ��
    uint16_t TIM_IT_Selection;                     // TIM�ж�λѡ��
    OC_enum OCx;                                   // TIMѡ��ocͨ��
    FunctionalState TIM_IT_State;                  // TIM�ж�ʹ(ʧ)��
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
    void Pin_Init(); //����������Զ���������
    void Base_Init();
    void OC_Init();
    void IC_Init();
    void ITConfig(uint16_t TIM_IT, FunctionalState NewState);
    void Init();
    void Enable();
    void Disable();
};
#endif