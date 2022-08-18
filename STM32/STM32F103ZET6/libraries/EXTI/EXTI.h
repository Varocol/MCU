#ifndef __OJ_EXIT_H
#define __OJ_EXIT_H
#include "stm32f10x.h"
#include "RCC.h"
#include "NVIC.h"
/*
    说明:EXTI有20个处理通道,EXTI0对应GPIOx(x=A...G)_Pin_0,EXTI1对应GPIOx(x=A...G)_Pin_1,
    以此类推,而EXTI16~20接了特殊通道。初始化时分为两块部分,第一部分是EXTI本身的参数，后面可以接
    GPIO的选择参数,如果不传参对应的是EXTI16~20的部分,也可以接NVIC中断部分。
    初始化参数：
    1.EXTI16~20的硬件事件   EXTI_InitStructure
    2.EXTI16~20的硬件中断   EXTI_InitStructure | EXTI_NVIC_Operate
    3.EXTI0~15的硬件事件    EXTI_InitStructure | GPIOx
    4.EXTI0~15的硬件中断    EXTI_InitStructure | EXTI_NVIC_Operate | GPIOx

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