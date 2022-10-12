#include "DMA.h"
/**
 * @brief  DMA-空构造方法
 * @param  None
 * @retval None
 */
DMA::DMA()
{
}

/**
 * @brief  DMA-析构方法
 * @param  None
 * @retval None
 */
DMA::~DMA()
{
}

/**
 * @brief  DMA-构造方法
 * @param  DMAx_Param   DMA的参数列表
 * @retval None
 */
DMA::DMA(DMA_Param DMAx_Param)
{
    Set_DMA_Param(DMAx_Param);
}

/**
 * @brief  DMA-设置DMA的参数列表
 * @param  DMAx_Param   DMA的参数列表
 * @retval None
 */
void DMA::Set_DMA_Param(DMA_Param DMAx_Param)
{
    this->DMAx_Param = DMAx_Param;
}

/**
 * @brief  DMA-参数列表更新
 * @param  DMAx_Param   DMA的参数列表
 * @retval None
 */
void DMA::Update(DMA_Param DMAx_Param)
{
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    Set_DMA_Param(DMAx_Param);
    Init();
}

/**
 * @brief  DMA-用于在不是循环模式下的数据量设置
 * @param  DMAx_Param   DMA的参数列表
 * @retval None
 */
void DMA::SetCurrDataCounter(uint16_t DataNumber)
{
    DMA_SetCurrDataCounter(DMAx_Param.DMA_Channelx, DataNumber);
}

/**
 * @brief  DMA-初始化方法
 * @param  None
 * @retval None
 */
void DMA::Init()
{
    //开启RCC时钟
    RCC_Enable();
    // DMA寄存器复位
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    //配置DMA
    DMA_Init(DMAx_Param.DMA_Channelx, &DMAx_Param.DMA_InitStructure);
    //配置DMA中断优先级
    NVIC_Operate(DMAx_Param.DMA_NVIC_InitStructure).Init();
    //配置DMA中断
    ITConfig(DMAx_Param.DMA_IT_Selection, DMAx_Param.DMA_IT_State);
    //使能DMA
    Enable();
}

/**
 * @brief  DMA-中断方法
 * @param  DMA_IT       中断标志的选择
 * @param  NewState     使能或失能
 * @retval None
 */
void DMA::ITConfig(uint32_t DMA_IT, FunctionalState NewState)
{
    DMA_ITConfig(DMAx_Param.DMA_Channelx, DMA_IT, NewState);
}

/**
 * @brief  DMA-开启DMA方法(DMA使能)
 * @param  None
 * @retval None
 */
void DMA::Enable()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, ENABLE);
}

/**
 * @brief  DMA-关闭DMA方法(DMA失能)
 * @param  None
 * @retval None
 */
void DMA::Disable()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, DISABLE);
}

/**
 * @brief  DMA-开启DMA时钟方法
 * @param  None
 * @retval None
 */
void DMA::RCC_Enable()
{
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), ENABLE);
}

/**
 * @brief  关闭DMA-DMA时钟方法
 * @param  None
 * @retval None
 */
void DMA::RCC_Disable()
{
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), DISABLE);
}

/**
 * @brief  DMA-开启DMA时钟方法
 * @param  None
 * @retval None
 */
void DMA::RCC_Enable(DMA_TypeDef *DMAx)
{
    RCC_Operate::RCC_Config(DMAx, ENABLE);
}

/**
 * @brief  关闭DMA-DMA时钟方法
 * @param  None
 * @retval None
 */
void DMA::RCC_Disable(DMA_TypeDef *DMAx)
{
    RCC_Operate::RCC_Config(DMAx, DISABLE);
}

/**
 * @brief  DMA-获取DMA通道所属的DMA
 * @param
 * @retval DMA通道所属的DMAx
 */
DMA_TypeDef *DMA::Get_DMA(DMA_Channel_TypeDef *DMA_Channelx)
{
    if (DMA_Channelx == DMA1_Channel1 || DMA_Channelx == DMA1_Channel2 ||
        DMA_Channelx == DMA1_Channel3 || DMA_Channelx == DMA1_Channel4 ||
        DMA_Channelx == DMA1_Channel5 || DMA_Channelx == DMA1_Channel6 ||
        DMA_Channelx == DMA1_Channel7)
    {
        return DMA1;
    }
    else
    {
        return DMA2;
    }
}