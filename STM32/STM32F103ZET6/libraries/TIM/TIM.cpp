#include "TIM.h"
//TIM基本参数初始化结构体
TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure =
    {
        RCC_Operate::Get_SYSCLK_Frequency() / 1000000, //72
        TIM_CounterMode_Up,
        999,          //计1000次,这样每次1ms
        TIM_CKD_DIV1, //输入信号滤波频率
        0,            //重复次数,只用通用和高级定时器才有
};
//TIM通道初始化结构体
TIM_OCInitTypeDef TIM2_OCStructure =
    {
        TIM_OCMode_PWM1,          //通道模式
        TIM_OutputState_Enable,   //输入/捕获使能(OCx)
        TIM_OutputNState_Disable, //输入/互补输出使能,只有高级定时器才有(OCxN)
        500,                      //CCRx的值,用来设置占空比
        TIM_OCPolarity_High,      //输入/捕获极性,高电平有效(OCx)
        TIM_OCNPolarity_High,     //输入/捕获互补输出极性,高电平有效(OCNx)
        TIM_OCIdleState_Reset,    //输出空闲状态(OCx)
        TIM_OCNIdleState_Reset    //输出空闲状态(OCxN)
};
//NVIC中断初始化结构体
NVIC_InitTypeDef TIM2_NVIC_Structure =
    {
        TIM2_IRQn,
        0,
        5,
        ENABLE};
//NVIC中断对象
NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(&TIM2_NVIC_Structure);

//TIM2初始化参数
TIM_Parma TIM2_Parma =
    {
        TIM2,
        TIM2_TimeBaseStructure,
        TIM2_OCStructure,
        TIM2_NVIC_Operate,
        ENABLE,
        TIM_IT_Update,
        OC1};

//TIM2对象
TIM TIM_2 = TIM(TIM2_Parma);

/**
  * @brief  TIM构造函数
  * @param  None
  * @retval None
  */
TIM::TIM()
{
}

/**
  * @brief  TIM析构函数
  * @param  None
  * @retval None
  */
TIM::~TIM()
{
}

/**
  * @brief  TIM构造函数
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
TIM::TIM(TIM_Parma TIMx_Parma)
{
  Set_TIM_Parma(TIMx_Parma);
}

/**
  * @brief  TIM静态毫秒级延时方法
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
void TIM::Delay_ms(uint32_t ms)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  //开启TIM2时钟
  RCC_Operate::RCC_Config(TIM2, ENABLE);
  //TIM2寄存器复位
  TIM_DeInit(TIM2);
  //TIM基础参数结构体
  // 配置定时器的分频因子(PSC)
  TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
  // 配置定时器的重装载寄存器(ARR)
  TIM_TimeBaseStructure.TIM_Period = (1000 - 1); // 这个值可以临时设置
  // 时钟分频因子，基本定时器没有
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // 重复计数器的值，基本定时器没有
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // 初始化定时器
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  // 清除计时器中断标志位/
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  // 开启计时器中断
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //NVIC配置
  NVIC_InitTypeDef NVIC_InitStructure =
      {
          TIM2_IRQn,
          0,
          3,
          ENABLE};
  NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(&NVIC_InitStructure);
  TIM2_NVIC_Operate.Init();
  //设置时间
  time_ms = ms;
  // 使能计数器
  TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  判断延时是否完成函数
  * @param  None
  * @retval 是否延时结束
  */
bool TIM::Delay_Complete()
{
  //检查TIM2状态
  if((!(TIM2->CR1 & TIM_CR1_CEN)) && current_time_ms == 0)
  {
    return true;
  }
  else 
  {
    return false;
  }
}

/**
  * @brief  TIM设置参数列表函数
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
void TIM::Set_TIM_Parma(TIM_Parma TIMx_Parma)
{
  this->TIMx_Parma = TIMx_Parma;
}

/**
  * @brief  TIM更新参数列表函数
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
void TIM::Update(TIM_Parma TIMx_Parma)
{
  TIM_DeInit(TIMx_Parma.TIMx);
  Set_TIM_Parma(TIMx_Parma);
  Init();
}

/**
  * @brief  TIM通道的GPIO引脚初始化
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
void TIM::Pin_Init()
{
  //考虑到有太多情况,请自行根据需要配置引脚(CHx,CHxN,BKIN,ETR)
  //CHN (eg: TIM2 CH1 PA0 PWM输出)
  {
    GPIO_InitTypeDef GPIO_InitStructure =
        {
            GPIO_Pin_0,
            GPIO_Speed_50MHz,
            GPIO_Mode_AF_PP};
    GPIO TIM2_CH1_PA0 = GPIO(GPIOA, GPIO_InitStructure);
    TIM2_CH1_PA0.Init();
  }
  //CHxN
  {

  }
  //BKIN
  {

  }
  //ETR
  {
  }
}

/**
  * @brief  TIM基本参数初始化函数
  * @param  None
  * @retval None
  */
void TIM::Base_Init()
{
  // 初始化定时器基础参数
  TIM_TimeBaseInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_TimeBaseStructure);
}

/**
  * @brief  TIMOC通道初始化函数
  * @param  None
  * @retval None
  */
void TIM::OC_Init()
{
  //配置所需引脚
  Pin_Init();
  //配置OC通道
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
  * @brief  TIM初始化函数
  * @param  None
  * @retval None
  */
void TIM::Init()
{
  // 系统时钟函数，开启TIMx时钟
  RCC_Operate::RCC_Config(TIMx_Parma.TIMx, ENABLE);
  // TIMx寄存器复位
  TIM_DeInit(TIMx_Parma.TIMx);
  //配置基本参数
  Base_Init();
  //配置通道参数
  OC_Init();
  // 清除计时器中断标志位/
  TIM_ClearFlag(TIMx_Parma.TIMx, TIM_FLAG_Update);
  // 配置计时器中断
  TIM_ITConfig(TIMx_Parma.TIMx, TIMx_Parma.TIM_IT_Selection, TIMx_Parma.TIM_IT_State);
  //NVIC配置
  TIMx_Parma.TIM_NVIC_Operate.Init();
  //开启定时器
  Start();
}

/**
  * @brief  开启TIM函数
  * @param  None
  * @retval None
  */
void TIM::Start()
{
  TIM_Cmd(TIMx_Parma.TIMx, ENABLE);
}

/** @brief  关闭TIM函数
  * @param  None
  * @retval None
  */
void TIM::Shutup()
{
  TIM_Cmd(TIMx_Parma.TIMx, DISABLE);
}
