#include "DMA.h"
/**
 * @brief  DMA空构造方法
 * @param  None
 * @retval None
 */
DMA::DMA()
{
}

/**
 * @brief  DMA析构函数
 * @param  None
 * @retval None
 */
DMA::~DMA()
{
}

/**
 * @brief  DMA构造方法
 * @param  DMAx_Param:DMA的参数列表
 * @retval None
 */
DMA::DMA(DMA_Param DMAx_Param)
{
    Set_DMA_Param(DMAx_Param);
}

/**
 * @brief  设置DMA的参数列表
 * @param  DMAx_Param:DMA的参数列表
 * @retval None
 */
void DMA::Set_DMA_Param(DMA_Param DMAx_Param)
{
    this->DMAx_Param = DMAx_Param;
}

/**
 * @brief  DMA参数列表更新
 * @param  DMAx_Param:DMA的参数列表
 * @retval None
 */
void DMA::Update(DMA_Param DMAx_Param)
{
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    Set_DMA_Param(DMAx_Param);
    Init();
}

/**
 * @brief  DMA 初始化函数
 * @param  None
 * @retval None
 */
void DMA::Init()
{
    //开启RCC时钟
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), ENABLE);
    // DMA寄存器复位
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    //配置DMA
    DMA_Init(DMAx_Param.DMA_Channelx, &DMAx_Param.DMA_InitStructure);
    //配置DMA中断优先级
    DMAx_Param.DMA_NVIC_Operate.Init();
    //配置DMA中断
    DMA_ITConfig(DMAx_Param.DMA_Channelx, DMAx_Param.DMA_IT_Selection, DMAx_Param.DMA_IT_State);
    //使能DMA
    Start();
}

/**
 * @brief  开启DMA函数(DMA使能)
 * @param  None
 * @retval None
 */
void DMA::Start()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, ENABLE);
}

/**
 * @brief  关闭DMA函数(DMA失能)
 * @param  None
 * @retval None
 */
void DMA::ShutUp()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, DISABLE);
}

/**
 * @brief  获取DMA通道所属的DMA
 * @param
 * @retval None
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