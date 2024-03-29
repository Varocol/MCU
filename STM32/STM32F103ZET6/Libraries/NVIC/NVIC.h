#ifndef __OJ_NVIC_H
#define __OJ_NVIC_H
#include "stm32f10x.h"
#define NVIC_PriorityGroup NVIC_PriorityGroup_0
class NVIC_Operate
{
private:
    NVIC_InitTypeDef NVIC_InitStructure;
public:
    NVIC_Operate();
    ~NVIC_Operate();
    NVIC_Operate(NVIC_InitTypeDef &NVIC_InitStructure);
    void Update(NVIC_InitTypeDef &NVIC_InitStructure);
    void Set_NVIC_InitStructure(NVIC_InitTypeDef &NVIC_InitStructure);
    void Init();
    void Enable();
    void Disable();
};
#endif /*__OJ_NVIC_H*/