#ifndef __OJ_EXIT_H
#define __OJ_EXIT_H
#include "stm32f10x.h"
#include "RCC.h"
#include "NVIC.h"
/*
    ˵��:EXTI��20������ͨ��,EXTI0��ӦGPIOx(x=A...G)_Pin_0,EXTI1��ӦGPIOx(x=A...G)_Pin_1,
    �Դ�����,��EXTI16~20��������ͨ������ʼ��ʱ��Ϊ���鲿��,��һ������EXTI����Ĳ�����������Խ�
    GPIO��ѡ�����,��������ζ�Ӧ����EXTI16~20�Ĳ���,Ҳ���Խ�NVIC�жϲ��֡�
    ��ʼ��������
    1.EXTI16~20��Ӳ���¼�   EXTI_InitStructure
    2.EXTI16~20��Ӳ���ж�   EXTI_InitStructure | EXTI_NVIC_Operate
    3.EXTI0~15��Ӳ���¼�    EXTI_InitStructure | GPIOx
    4.EXTI0~15��Ӳ���ж�    EXTI_InitStructure | EXTI_NVIC_Operate | GPIOx

*/

typedef enum
{
    EXTI_Init_None,
    EXTI_16_20_Event,
    EXTI_16_20_Intterupt,
    EXTI_0_15_Event,
    EXTI_0_15_Intterupt
} EXTI_Init_Type;

class EXTI_Operate
{
private:
    EXTI_Init_Type Init_Type = EXTI_Init_None;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_Operate EXTI_NVIC_Operate;
    GPIO_TypeDef *GPIOx;
    uint8_t GPIO_2_GPIO_PortSource(GPIO_TypeDef *GPIOx);
    uint8_t EXTI_2_GPIO_PinSource(uint32_t EXTI_Linex);

public:
    EXTI_Operate();
    ~EXTI_Operate();
    EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure);
    EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate);
    EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx);
    EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate, GPIO_TypeDef *GPIOx);
    void Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure);
    void Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate);
    void Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx);
    void Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate, GPIO_TypeDef *GPIOx);
    void Update(EXTI_InitTypeDef EXTI_InitStructure);
    void Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate);
    void Update(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx);
    void Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_Operate EXTI_NVIC_Operate, GPIO_TypeDef *GPIOx);
    void GenerateSWInterrupt();
    void ClearFlag();
    void Init();
    void Start();
    void ShutUp();
};

#endif /*__OJ_EXIT_H*/