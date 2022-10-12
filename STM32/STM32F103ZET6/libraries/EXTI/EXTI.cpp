#include "EXTI.h"
/**
 * @brief  EXTI-GPIOx转换成GPIOPortSource
 * @param  GPIOx                GPIO端口
 * @retval GPIO_PortSource
 */
uint8_t EXTI_Operate::GPIO_2_GPIO_PortSource(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA)
    {
        return GPIO_PortSourceGPIOA;
    }
    else if (GPIOx == GPIOB)
    {
        return GPIO_PortSourceGPIOB;
    }
    else if (GPIOx == GPIOC)
    {
        return GPIO_PortSourceGPIOC;
    }
    else if (GPIOx == GPIOD)
    {
        return GPIO_PortSourceGPIOD;
    }
    else if (GPIOx == GPIOE)
    {
        return GPIO_PortSourceGPIOE;
    }
    else if (GPIOx == GPIOF)
    {
        return GPIO_PortSourceGPIOF;
    }
    else if (GPIOx == GPIOG)
    {
        return GPIO_PortSourceGPIOG;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  EXTI-EXTI_Linex转换成GPIO_PinSource
 * @param  EXTI_Linex           EXTI通道
 * @retval GPIO_PinSource
 */
uint8_t EXTI_Operate::EXTI_2_GPIO_PinSource(uint32_t EXTI_Linex)
{
    switch (EXTI_InitStructure.EXTI_Line)
    {
    case EXTI_Line0:
        return GPIO_PinSource0;
    case EXTI_Line1:
        return GPIO_PinSource1;
    case EXTI_Line2:
        return GPIO_PinSource2;
    case EXTI_Line3:
        return GPIO_PinSource3;
    case EXTI_Line4:
        return GPIO_PinSource4;
    case EXTI_Line5:
        return GPIO_PinSource5;
    case EXTI_Line6:
        return GPIO_PinSource6;
    case EXTI_Line7:
        return GPIO_PinSource7;
    case EXTI_Line8:
        return GPIO_PinSource8;
    case EXTI_Line9:
        return GPIO_PinSource9;
    case EXTI_Line10:
        return GPIO_PinSource10;
    case EXTI_Line11:
        return GPIO_PinSource11;
    case EXTI_Line12:
        return GPIO_PinSource12;
    case EXTI_Line13:
        return GPIO_PinSource13;
    case EXTI_Line14:
        return GPIO_PinSource14;
    case EXTI_Line15:
        return GPIO_PinSource15;
    default:
        return 0;
    }
}

/**
 * @brief  EXTI-空构造方法
 * @param  None
 * @retval None
 */
EXTI_Operate::EXTI_Operate()
{
}

/**
 * @brief  EXTI-析构方法
 * @param  None
 * @retval None
 */
EXTI_Operate::~EXTI_Operate()
{
}

/**
 * @brief  EXTI-构造方法1
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure);
}

/**
 * @brief  EXTI-构造方法2
 * @param  EXTI_InitStructure         EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure    NVIC中断初始化结构体
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure);
}

/**
 * @brief  EXTI-构造方法3
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @param  GPIOx                GPIO端口
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, GPIOx);
}

/**
 * @brief  EXTI-构造方法4
 * @param  EXTI_InitStructure         EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure    NVIC中断初始化结构体
 * @param  GPIOx                      GPIO端口
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure, GPIOx);
}

/**
 * @brief  EXTI-设置EXTI的参数列表1
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->Init_Type = EXTI_16_20_Event;
}

/**
 * @brief  EXTI-设置EXTI的参数列表2
 * @param  EXTI_InitStructure           EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure      NVIC中断初始化结构体
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->EXTI_NVIC_InitStructure = EXTI_NVIC_InitStructure;
    this->Init_Type = EXTI_16_20_Intterupt;
}

/**
 * @brief  EXTI-设置EXTI的参数列表3
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @param  GPIOx                GPIO端口
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->GPIOx = GPIOx;
    this->Init_Type = EXTI_0_15_Event;
}

/**
 * @brief  EXTI-设置EXTI的参数列表4
 * @param  EXTI_InitStructure           EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure      NVIC中断初始化结构体
 * @param  GPIOx                        GPIO端口
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->EXTI_NVIC_InitStructure = EXTI_NVIC_InitStructure;
    this->GPIOx = GPIOx;
    this->Init_Type = EXTI_0_15_Intterupt;
}

/**
 * @brief  EXTI-更新EXTI的参数列表1
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure);
    Init();
}

/**
 * @brief  EXTI-更新EXTI的参数列表2
 * @param  EXTI_InitStructure         EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure    NVIC中断初始化结构体
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure);
    Init();
}

/**
 * @brief  EXTI-更新EXTI的参数列表3
 * @param  EXTI_InitStructure   EXTI初始化结构体
 * @param  GPIOx                GPIO端口
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, GPIOx);
    Init();
}

/**
 * @brief  EXTI-更新EXTI的参数列表4
 * @param  EXTI_InitStructure         EXTI初始化结构体
 * @param  EXTI_NVIC_InitStructure    NVIC中断初始化结构体
 * @param  GPIOx                      GPIO端口
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure, GPIOx);
    Init();
}

/**
 * @brief  EXTI-产生软件中断/事件标志
 * @param  None
 * @retval None
 */
void EXTI_Operate::GenerateSWInterrupt()
{
    EXTI_GenerateSWInterrupt(EXTI_InitStructure.EXTI_Line);
}

/**
 * @brief  EXTI-清除硬件/软件的中断/事件标志
 * @param  None
 * @retval None
 */
void EXTI_Operate::ClearFlag()
{
    EXTI_ClearFlag(EXTI_InitStructure.EXTI_Line);
}

/**
 * @brief  EXTI-初始化
 * @param  None
 * @retval None
 */
void EXTI_Operate::Init()
{
    //如果没有初始化参数则不初始化
    if (Init_Type == EXTI_Init_None)
    {
        return;
    }
    // EXTI0~15 选择GPIOx作为EXTI_Linex的输入端
    if (Init_Type == EXTI_0_15_Event || Init_Type == EXTI_0_15_Intterupt)
    {
        //开启AFIO时钟
        RCC_Operate::RCC_Config(AFIO, ENABLE);
        //配置AFIO的AFIO_EXTICRx寄存器
        GPIO_EXTILineConfig(GPIO_2_GPIO_PortSource(GPIOx), EXTI_2_GPIO_PinSource(EXTI_InitStructure.EXTI_Line));
    }
    //配置EXTI中断优先级
    if (Init_Type == EXTI_16_20_Intterupt || Init_Type == EXTI_0_15_Intterupt)
    {
        NVIC_Operate(EXTI_NVIC_InitStructure).Init();
    }
    //开启EXTI(由于EXTI比较特殊,所以下面的方法自带EXTI初始化)
    Enable();
}

/**
 * @brief  EXTI-开启EXTI方法(EXTI使能)
 * @param  None
 * @retval None
 */
void EXTI_Operate::Enable()
{
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief  EXTI-关闭EXTI方法(EXTI失能)
 * @param  None
 * @retval None
 */
void EXTI_Operate::Disable()
{
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
}