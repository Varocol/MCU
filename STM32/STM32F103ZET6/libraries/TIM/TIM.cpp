#include "TIM.h"
/**
 * @brief  TIM-构造方法
 * @param  None
 * @retval None
 */
TIM::TIM()
{
}

/**
 * @brief  TIM-析构方法
 * @param  None
 * @retval None
 */
TIM::~TIM()
{
}

/**
 * @brief  TIM-构造方法
 * @param  TIMx_Parma   TIM初始化参数列表
 * @retval None
 */
TIM::TIM(TIM_Parma TIMx_Parma)
{
  Set_TIM_Parma(TIMx_Parma);
}

/**
 * @brief  TIM-设置参数列表方法
 * @param  TIMx_Parma   TIM初始化参数列表
 * @retval None
 */
void TIM::Set_TIM_Parma(TIM_Parma TIMx_Parma)
{
  this->TIMx_Parma = TIMx_Parma;
}

/**
 * @brief  TIM-更新参数列表方法
 * @param  TIMx_Parma   TIM初始化参数列表
 * @retval None
 */
void TIM::Update(TIM_Parma TIMx_Parma)
{
  TIM_DeInit(TIMx_Parma.TIMx);
  Set_TIM_Parma(TIMx_Parma);
  Init();
}

/**
 * @brief  TIM-通道的GPIO引脚初始化
 * @param  TIMx_Parma   TIM初始化参数列表
 * @retval None
 */
void TIM::Pin_Init()
{
  // 考虑到有太多情况,请自行根据需要配置引脚(CHx,CHxN,BKIN,ETR)
  //  CHN (eg: TIM2 CH1 PA0 PWM输出)
  {
      // GPIO_InitTypeDef GPIO_InitStructure =
      //     {
      //         GPIO_Pin_0,
      //         GPIO_Speed_50MHz,
      //         GPIO_Mode_AF_PP};
      // GPIO TIM2_CH1_PA0 = GPIO(GPIOA, GPIO_InitStructure);
      // TIM2_CH1_PA0.Init();
  }
  // CHxN
  {

  }
  // BKIN
  {

  }
  // ETR
  {
  }
}

/**
 * @brief  TIM-基本参数初始化方法
 * @param  None
 * @retval None
 */
void TIM::Base_Init()
{
  // 初始化定时器基础参数
  TIM_TimeBaseInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_TimeBaseStructure);
}

/**
 * @brief  TIM-OC通道初始化方法
 * @param  None
 * @retval None
 */
void TIM::OC_Init()
{
  // 配置OC通道
  switch (TIMx_Parma.OCx)
  {
  case OC1:
    TIM_OC1Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC2:
    TIM_OC2Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC3:
    TIM_OC3Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC4:
    TIM_OC4Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  }
}

/**
 * @brief  TIM-IC初始化方法
 * @param  None
 * @retval None
 */
void TIM::IC_Init()
{
  TIM_ICInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_ICStructure);
}

/**
 * @brief  TIM-初始化方法
 * @param  None
 * @retval None
 */
void TIM::Init()
{
  // 系统时钟方法，开启TIMx时钟
  RCC_Operate::RCC_Config(TIMx_Parma.TIMx, ENABLE);
  // TIMx寄存器复位
  TIM_DeInit(TIMx_Parma.TIMx);
  // 配置所需引脚
  Pin_Init();
  // 配置基本参数
  Base_Init();
  // 配置通道参数
  OC_Init();
  // 配置IC参数
  IC_Init();
  // 清除计时器中断标志位
  TIM_ClearFlag(TIMx_Parma.TIMx, TIM_FLAG_Update);
  // 配置计时器中断
  ITConfig(TIMx_Parma.TIM_IT_Selection, TIMx_Parma.TIM_IT_State);
  // 开启定时器
  Enable();
}

/**
 * @brief  TIM-中断方法
 * @param  TIM_IT       中断标志的选择
 * @param  NewState     使能或失能
 * @retval None
 */
void TIM::ITConfig(uint16_t TIM_IT, FunctionalState NewState)
{
  // NVIC配置
  TIMx_Parma.TIM_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Operate(TIMx_Parma.TIM_NVIC_InitStructure).Init();
  TIM_ITConfig(TIMx_Parma.TIMx, TIM_IT, NewState);
}

/**
 * @brief  TIM-开启TIM方法
 * @param  None
 * @retval None
 */
void TIM::Enable()
{
  TIM_Cmd(TIMx_Parma.TIMx, ENABLE);
}

/**
 * @brief  TIM-关闭TIM方法
 * @param  None
 * @retval None
 */
void TIM::Disable()
{
  TIM_Cmd(TIMx_Parma.TIMx, DISABLE);
}
