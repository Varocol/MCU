#include "PWM.h"
/**
 * @brief  PWM-空构造方法
 * @param  None
 * @retval None
 */
PWM::PWM()
{
}

/**
 * @brief  PWM-构造方法
 * @param  TIMx_Channelx        选择TIMx的CHx通道
 * @param  Frequency            频率(不低于1,不高于cpu工作频率问题不大)
 * @param  DutyRatio            占空比
 * @retval None
 */
PWM::PWM(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio)
{
    Set_PWM_Param(TIMx_Channelx, Frequency, DutyRatio);
}

/**
 * @brief  PWM-析构方法
 * @param  None
 * @retval None
 */
PWM::~PWM()
{
}

/**
 * @brief  PWM-GPIO引脚初始化
 * @param  None
 * @retval None
 */
void PWM::Pin_Init()
{
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    PIN_enum Channel_Pin;
    //设置重映射
    switch (TIMx_Channelx)
    {
    case TIM1_Channel1_PartialRemap:
    case TIM1_Channel2_PartialRemap:
    case TIM1_Channel3_PartialRemap:
    case TIM1_Channel4_PartialRemap:
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);
        break;
    case TIM1_Channel1_FullRemap:
    case TIM1_Channel2_FullRemap:
    case TIM1_Channel3_FullRemap:
    case TIM1_Channel4_FullRemap:
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);
        break;
    case TIM2_Channel1_PartialRemap1:
    case TIM2_Channel2_PartialRemap1:
    case TIM2_Channel3_PartialRemap1:
    case TIM2_Channel4_PartialRemap1:
        GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);
        break;
    case TIM2_Channel1_PartialRemap2:
    case TIM2_Channel2_PartialRemap2:
    case TIM2_Channel3_PartialRemap2:
    case TIM2_Channel4_PartialRemap2:
        GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
        break;
    case TIM2_Channel1_FullRemap:
    case TIM2_Channel2_FullRemap:
    case TIM2_Channel3_FullRemap:
    case TIM2_Channel4_FullRemap:
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
        break;
    case TIM3_Channel1_PartialRemap:
    case TIM3_Channel2_PartialRemap:
    case TIM3_Channel3_PartialRemap:
    case TIM3_Channel4_PartialRemap:
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
        break;
    case TIM3_Channel1_FullRemap:
    case TIM3_Channel2_FullRemap:
    case TIM3_Channel3_FullRemap:
    case TIM3_Channel4_FullRemap:
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
        break;
    case TIM4_Channel1_Remap:
    case TIM4_Channel2_Remap:
    case TIM4_Channel3_Remap:
    case TIM4_Channel4_Remap:
        GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
        break;
    default:
        break;
    }
    //获取引脚
    switch (TIMx_Channelx)
    {
        // PA8
    case TIM1_Channel1_Default:
        Channel_Pin = PA8;
        break;
    // PA9
    case TIM1_Channel2_Default:
        Channel_Pin = PA9;
        break;
    // PA10
    case TIM1_Channel3_Default:
        Channel_Pin = PA10;
        break;
    // PA11
    case TIM1_Channel4_Default:
        Channel_Pin = PA11;
        break;
    // PA8
    case TIM1_Channel1_PartialRemap:
        Channel_Pin = PA8;
        break;
    // PA9
    case TIM1_Channel2_PartialRemap:
        Channel_Pin = PA9;
        break;
    // PA10
    case TIM1_Channel3_PartialRemap:
        Channel_Pin = PA10;
        break;
    // PA11
    case TIM1_Channel4_PartialRemap:
        Channel_Pin = PA11;
        break;
    // PE9
    case TIM1_Channel1_FullRemap:
        Channel_Pin = PE9;
        break;
    // PE11
    case TIM1_Channel2_FullRemap:
        Channel_Pin = PE11;
        break;
    // PE13
    case TIM1_Channel3_FullRemap:
        Channel_Pin = PE13;
        break;
    // PE14
    case TIM1_Channel4_FullRemap:
        Channel_Pin = PE14;
        break;
    // PA0
    case TIM2_Channel1_Default:
        Channel_Pin = PA0;
        break;
    // PA1
    case TIM2_Channel2_Default:
        Channel_Pin = PA1;
        break;
    // PA2
    case TIM2_Channel3_Default:
        Channel_Pin = PA2;
        break;
    // PA3
    case TIM2_Channel4_Default:
        Channel_Pin = PA3;
        break;
    // PA15
    case TIM2_Channel1_PartialRemap1:
        Channel_Pin = PA15;
        break;
    // PB3
    case TIM2_Channel2_PartialRemap1:
        Channel_Pin = PB3;
        break;
    // PA2
    case TIM2_Channel3_PartialRemap1:
        Channel_Pin = PA2;
        break;
    // PA3
    case TIM2_Channel4_PartialRemap1:
        Channel_Pin = PA3;
        break;
    // PA0
    case TIM2_Channel1_PartialRemap2:
        Channel_Pin = PA0;
        break;
    // PA1
    case TIM2_Channel2_PartialRemap2:
        Channel_Pin = PA1;
        break;
    // PB10
    case TIM2_Channel3_PartialRemap2:
        Channel_Pin = PB10;
        break;
    // PB11
    case TIM2_Channel4_PartialRemap2:
        Channel_Pin = PB11;
        break;
    // PA15
    case TIM2_Channel1_FullRemap:
        Channel_Pin = PA15;
        break;
    // PB3
    case TIM2_Channel2_FullRemap:
        Channel_Pin = PB3;
        break;
    // PB10
    case TIM2_Channel3_FullRemap:
        Channel_Pin = PB10;
        break;
    // PB11
    case TIM2_Channel4_FullRemap:
        Channel_Pin = PB11;
        break;
    // PA6
    case TIM3_Channel1_Default:
        Channel_Pin = PA6;
        break;
    // PA7
    case TIM3_Channel2_Default:
        Channel_Pin = PA7;
        break;
    // PB0
    case TIM3_Channel3_Default:
        Channel_Pin = PB0;
        break;
    // PB1
    case TIM3_Channel4_Default:
        Channel_Pin = PB1;
        break;
    // PB4
    case TIM3_Channel1_PartialRemap:
        Channel_Pin = PB4;
        break;
    // PB5
    case TIM3_Channel2_PartialRemap:
        Channel_Pin = PB5;
        break;
    // PB0
    case TIM3_Channel3_PartialRemap:
        Channel_Pin = PB0;
        break;
    // PB1
    case TIM3_Channel4_PartialRemap:
        Channel_Pin = PB1;
        break;
    // PC6
    case TIM3_Channel1_FullRemap:
        Channel_Pin = PC6;
        break;
    // PC7
    case TIM3_Channel2_FullRemap:
        Channel_Pin = PC7;
        break;
    // PC8
    case TIM3_Channel3_FullRemap:
        Channel_Pin = PC8;
        break;
    // PC9
    case TIM3_Channel4_FullRemap:
        Channel_Pin = PC9;
        break;
    // PB6
    case TIM4_Channel1_Default:
        Channel_Pin = PB6;
        break;
    // PB7
    case TIM4_Channel2_Default:
        Channel_Pin = PB7;
        break;
    // PB8
    case TIM4_Channel3_Default:
        Channel_Pin = PB8;
        break;
    // PB9
    case TIM4_Channel4_Default:
        Channel_Pin = PB9;
        break;
    // PD12
    case TIM4_Channel1_Remap:
        Channel_Pin = PD12;
        break;
    // PD13
    case TIM4_Channel2_Remap:
        Channel_Pin = PD13;
        break;
    // PD14
    case TIM4_Channel3_Remap:
        Channel_Pin = PD14;
        break;
    // PD15
    case TIM4_Channel4_Remap:
        Channel_Pin = PD15;
        break;
    // PA0
    case TIM5_Channel1_Default:
        Channel_Pin = PA0;
        break;
    // PA1
    case TIM5_Channel2_Default:
        Channel_Pin = PA1;
        break;
    // PA2
    case TIM5_Channel3_Default:
        Channel_Pin = PA2;
        break;
    // PA3
    case TIM5_Channel4_Default:
        Channel_Pin = PA3;
        break;
    // PC6
    case TIM8_Channel1_Default:
        Channel_Pin = PC6;
        break;
    // PC7
    case TIM8_Channel2_Default:
        Channel_Pin = PC7;
        break;
    // PC8
    case TIM8_Channel3_Default:
        Channel_Pin = PC8;
        break;
    // PC9
    case TIM8_Channel4_Default:
        Channel_Pin = PC9;
        break;
    }
    GPIO Channel = GPIO(Channel_Pin, GPIO_Mode_AF_PP);
    Channel.Init();
}

/**
 * @brief  PWM-初始化方法
 * @param  None
 * @retval None
 */
void PWM::Init()
{
    //初始化GPIO复用
    Pin_Init();
    //获取TIM初始参数
    if (TIMx_Channelx <= TIM1_Channel4_FullRemap)
    {
        TIMx = TIM1;
    }
    else if (TIMx_Channelx <= TIM2_Channel4_FullRemap)
    {
        TIMx = TIM2;
    }
    else if (TIMx_Channelx <= TIM3_Channel4_FullRemap)
    {
        TIMx = TIM3;
    }
    else if (TIMx_Channelx <= TIM4_Channel4_Remap)
    {
        TIMx = TIM4;
    }
    else if (TIMx_Channelx <= TIM5_Channel4_Default)
    {
        TIMx = TIM5;
    }
    else if (TIMx_Channelx <= TIM8_Channel4_Default)
    {
        TIMx = TIM8;
    }
    //开启TIM时钟
    RCC_Operate::RCC_Config(TIMx, ENABLE);
    // TIM寄存器复位
    TIM_DeInit(TIMx);
    //基本设置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
    TIM_TimeBaseStructure.TIM_Period =
        RCC_Operate::Get_SYSCLK_Frequency() / ((TIM_TimeBaseStructure.TIM_Prescaler + 1) * Frequency) - 1; // ARR寄存器的值
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // TIMOC通道设置
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //设置通道PWM模式(上升高电平有效,超过CCRx为低电平)
    TIM_OCInitStructure.TIM_Pulse = DutyRatio * (TIMx->ARR + 1);  //设置TIM的CCRx
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能TIM通道
    //设置选择通道
    switch (TIMx_Channelx % 4)
    {
    case 0:
        TIM_OC1Init(TIMx, &TIM_OCInitStructure);
        break;
    case 1:
        TIM_OC2Init(TIMx, &TIM_OCInitStructure);
        break;
    case 2:
        TIM_OC3Init(TIMx, &TIM_OCInitStructure);
        break;
    case 3:
        TIM_OC4Init(TIMx, &TIM_OCInitStructure);
        break;
    }
    Enable();
}

/**
 * @brief  PWM-设置PWM参数
 * @param  TIMx_Channelx        选择TIMx的CHx通道
 * @param  Frequency            频率(不低于1,不高于cpu工作频率问题不大)
 * @param  DutyRatio            占空比
 * @retval None
 */
void PWM::Set_PWM_Param(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio)
{
    Set_TIMx_Channelx_enum(TIMx_Channelx);
    Set_DutyRatio(DutyRatio);
    Set_Frequency(Frequency);
}

/**
 * @brief  PWM-参数更新方法
 * @param  TIMx_Channelx        选择TIMx的CHx通道
 * @param  Frequency            频率(不低于1,不高于cpu工作频率问题不大)
 * @param  DutyRatio            占空比
 * @retval None
 */
void PWM::Update(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio)
{
    TIM_DeInit(TIMx);
    Set_TIMx_Channelx_enum(TIMx_Channelx);
    Set_DutyRatio(DutyRatio);
    Set_Frequency(Frequency);
    Init();
}

/**
 * @brief  PWM-设置PWM选择路
 * @param  TIMx_Channelx        选择TIMx的CHx通道
 * @retval None
 */
void PWM::Set_TIMx_Channelx_enum(TIMx_Channelx_enum TIMx_Channelx)
{
    this->TIMx_Channelx = TIMx_Channelx;
}

/**
 * @brief  PWM-设置PWM频率方法
 * @param  Frequency            频率(不低于1,不高于cpu工作频率问题不大)
 * @retval None
 */
void PWM::Set_Frequency(double Frequency)
{
    this->Frequency = Frequency;
}

/**
 * @brief  PWM-设置PWM占空比方法
 * @param  DutyRatio            占空比
 * @retval None
 */
void PWM::Set_DutyRatio(double DutyRatio)
{
    this->DutyRatio = DutyRatio;
}

/**
 * @brief  PWM-开启PWM方法
 * @param  None
 * @retval None
 */
void PWM::Enable()
{
    RCC_Operate::RCC_Config(TIMx, ENABLE);
}

/**
 * @brief  PWM-关闭PWM方法
 * @param  None
 * @retval None
 */
void PWM::Disable()
{
    RCC_Operate::RCC_Config(TIMx, DISABLE);
}