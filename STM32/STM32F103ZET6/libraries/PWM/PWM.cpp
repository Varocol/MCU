#include "PWM.h"

/*
   使用同一定时器不同通道时要注意:
   1、各个通道的频率相同,且由最后一次配置通道的频率操作决定(频率由ARR控制,而定时器的ARR只有一个)
   2、各个通道的占空比可以不同,这个由CCRx控制(x = 1,2,3,4)所以各路占空比由自己的CCRx决定
   3、当其中一个通道用的时经AFIO重映射的引脚后,其他的通道的引脚也会重映射
*/

//TIM1 CH1 Default = PA8
//TIM1 CH2 Default = PA9
//TIM1 CH3 Default = PA10
//TIM1 CH4 Default = PA11
//TIM1 CH1 PartialRemap = PA8
//TIM1 CH2 PartialRemap = PA9
//TIM1 CH3 PartialRemap = PA10
//TIM1 CH4 PartialRemap = PA11
//TIM1 CH1 FullRemap = PE9
//TIM1 CH2 FullRemap = PE11
//TIM1 CH3 FullRemap = PE13
//TIM1 CH4 FullRemap = PE14
//TIM2 CH1 Default = PA0
//TIM2 CH2 Default = PA1
//TIM2 CH3 Default = PA2
//TIM2 CH4 Default = PA3
//TIM2 CH1 PartialRemap1 = PA15
//TIM2 CH2 PartialRemap1 = PB3
//TIM2 CH3 PartialRemap1 = PA2
//TIM2 CH4 PartialRemap1 = PA3
//TIM2 CH1 PartialRemap2 = PA0
//TIM2 CH2 PartialRemap2 = PA1
//TIM2 CH3 PartialRemap2 = PB10
//TIM2 CH4 PartialRemap2 = PB11
//TIM2 CH1 FullRemap = PA15
//TIM2 CH2 FullRemap = PB3
//TIM2 CH3 FullRemap = PB10
//TIM2 CH4 FullRemap = PB11
//TIM3 CH1 Default = PA6
//TIM3 CH2 Default = PA7
//TIM3 CH3 Default = PB0
//TIM3 CH4 Default = PB1
//TIM3 CH1 PartialRemap = PB4
//TIM3 CH2 PartialRemap = PB5
//TIM3 CH3 PartialRemap = PB0
//TIM3 CH4 PartialRemap = PB1
//TIM3 CH1 FullRemap = PC6
//TIM3 CH2 FullRemap = PC7
//TIM3 CH3 FullRemap = PC8
//TIM3 CH4 FullRemap = PC9
//TIM4 CH1 Default = PB6
//TIM4 CH2 Default = PB7
//TIM4 CH3 Default = PB8
//TIM4 CH4 Default = PB9
//TIM4 CH1 Remap = PD12
//TIM4 CH2 Remap = PD13
//TIM4 CH3 Remap = PD14
//TIM4 CH4 Remap = PD15
//TIM5 CH1 = PA0
//TIM5 CH2 = PA1
//TIM5 CH3 = PA2
//TIM5 CH4 = PA3
//TIM8 CH1 = PC6
//TIM8 CH2 = PC7
//TIM8 CH3 = PC8
//TIM8 CH4 = PC9

// GPIO TIM1_CH1_Default = GPIO(GPIOA, T1_C1_1);
// GPIO TIM1_CH2_Default = GPIO(GPIOA, T1_C2_1);
// GPIO TIM1_CH3_Default = GPIO(GPIOA, T1_C3_1);
// GPIO TIM1_CH4_Default = GPIO(GPIOA, T1_C4_1);
// GPIO TIM1_CH1_PartialRemap = GPIO(GPIOA, T1_C1_2);
// GPIO TIM1_CH2_PartialRemap = GPIO(GPIOA, T1_C2_2);
// GPIO TIM1_CH3_PartialRemap = GPIO(GPIOA, T1_C3_2);
// GPIO TIM1_CH4_PartialRemap = GPIO(GPIOA, T1_C4_2);
// GPIO TIM1_CH1_FullRemap = GPIO(GPIOE, T1_C1_3);
// GPIO TIM1_CH2_FullRemap = GPIO(GPIOE, T1_C2_3);
// GPIO TIM1_CH3_FullRemap = GPIO(GPIOE, T1_C1_3);
// GPIO TIM1_CH4_FullRemap = GPIO(GPIOE, T1_C1_3);

// GPIO TIM2_CH1_Default = GPIO(GPIOA, T2_C1_1);
// GPIO TIM2_CH2_Default = GPIO(GPIOA, T2_C2_1);
// GPIO TIM2_CH3_Default = GPIO(GPIOA, T2_C3_1);
// GPIO TIM2_CH4_Default = GPIO(GPIOA, T2_C4_1);
// GPIO TIM2_CH1_PartialRemap1 = GPIO(GPIOA, T2_C1_2);
// GPIO TIM2_CH2_PartialRemap1 = GPIO(GPIOB, T2_C2_2);
// GPIO TIM2_CH3_PartialRemap1 = GPIO(GPIOA, T2_C3_2);
// GPIO TIM2_CH4_PartialRemap1 = GPIO(GPIOA, T2_C4_2);
// GPIO TIM2_CH1_PartialRemap2 = GPIO(GPIOA, T2_C1_3);
// GPIO TIM2_CH2_PartialRemap2 = GPIO(GPIOA, T2_C2_3);
// GPIO TIM2_CH3_PartialRemap2 = GPIO(GPIOB, T2_C3_3);
// GPIO TIM2_CH4_PartialRemap2 = GPIO(GPIOB, T2_C4_3);
// GPIO TIM2_CH1_FullRemap = GPIO(GPIOA, T2_C1_4);
// GPIO TIM2_CH2_FullRemap = GPIO(GPIOB, T2_C2_4);
// GPIO TIM2_CH3_FullRemap = GPIO(GPIOB, T2_C3_4);
// GPIO TIM2_CH4_FullRemap = GPIO(GPIOB, T2_C4_4);

// GPIO TIM3_CH1_Default = GPIO(GPIOA, T3_C1_1);
// GPIO TIM3_CH2_Default = GPIO(GPIOA, T3_C2_1);
// GPIO TIM3_CH3_Default = GPIO(GPIOB, T3_C3_1);
// GPIO TIM3_CH4_Default = GPIO(GPIOB, T3_C4_1);
// GPIO TIM3_CH1_PartialRemap = GPIO(GPIOB, T3_C1_2);
// GPIO TIM3_CH2_PartialRemap = GPIO(GPIOB, T3_C2_2);
// GPIO TIM3_CH3_PartialRemap = GPIO(GPIOB, T3_C3_2);
// GPIO TIM3_CH4_PartialRemap = GPIO(GPIOB, T3_C4_2);
// GPIO TIM3_CH1_FullRemap = GPIO(GPIOC, T3_C1_3);
// GPIO TIM3_CH2_FullRemap = GPIO(GPIOC, T3_C2_3);
// GPIO TIM3_CH3_FullRemap = GPIO(GPIOC, T3_C3_3);
// GPIO TIM3_CH4_FullRemap = GPIO(GPIOC, T3_C4_3);

// GPIO TIM4_CH1_Default = GPIO(GPIOB, T4_C1_1);
// GPIO TIM4_CH2_Default = GPIO(GPIOB, T4_C2_1);
// GPIO TIM4_CH3_Default = GPIO(GPIOB, T4_C3_1);
// GPIO TIM4_CH4_Default = GPIO(GPIOB, T4_C4_1);
// GPIO TIM4_CH1_Remap = GPIO(GPIOD, T4_C1_2);
// GPIO TIM4_CH2_Remap = GPIO(GPIOD, T4_C2_2);
// GPIO TIM4_CH3_Remap = GPIO(GPIOD, T4_C3_2);
// GPIO TIM4_CH4_Remap = GPIO(GPIOD, T4_C4_2);

// GPIO TIM5_CH1_Default = GPIO(GPIOA, T5_C1);
// GPIO TIM5_CH2_Default = GPIO(GPIOA, T5_C2);
// GPIO TIM5_CH3_Default = GPIO(GPIOA, T5_C3);
// GPIO TIM5_CH4_Default = GPIO(GPIOA, T5_C4);

// GPIO TIM8_CH1_Default = GPIO(GPIOC, T8_C1);
// GPIO TIM8_CH2_Default = GPIO(GPIOC, T8_C2);
// GPIO TIM8_CH3_Default = GPIO(GPIOC, T8_C3);
// GPIO TIM8_CH4_Default = GPIO(GPIOC, T8_C4);

GPIO_InitTypeDef PWM_Pin_0 =
    {
        GPIO_Pin_0,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_1 =
    {
        GPIO_Pin_1,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_2 =
    {
        GPIO_Pin_2,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_3 =
    {
        GPIO_Pin_3,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_4 =
    {
        GPIO_Pin_4,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_5 =
    {
        GPIO_Pin_5,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_6 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_7 =
    {
        GPIO_Pin_7,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_8 =
    {
        GPIO_Pin_8,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_9 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_10 =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_11 =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_12 =
    {
        GPIO_Pin_12,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_13 =
    {
        GPIO_Pin_13,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_14 =
    {
        GPIO_Pin_14,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

GPIO_InitTypeDef PWM_Pin_15 =
    {
        GPIO_Pin_15,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_PP};

/**
  * @brief  PWM空构造函数
  * @param  None
  * @retval None
  */
PWM::PWM()
{
}

/**
  * @brief  PWM构造函数
  * @param  T_C_S:选择TIMx的CHx通道
  * @param  Frequency:频率(不低于1,不高于cpu工作频率问题不大)
  * @param  DutyRatio:占空比
  * @retval None
  */
PWM::PWM(TIMx_Channelx_Selection T_C_S, double Frequency, double DutyRatio)
{
    Set_TIMx_Channelx_Selection(T_C_S);
    Set_DutyRatio(DutyRatio);
    Set_Frequency(Frequency);
}

/**
  * @brief  PWM析构函数
  * @param  None
  * @retval None
  */
PWM::~PWM()
{
}

/**
  * @brief  PWM GPIO引脚初始化
  * @param  None
  * @retval None
  */
void PWM::Pin_Init()
{
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    GPIO *temp;
    switch (T_C_S)
    {
    // PA8
    case TIM1_Channel1_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_8);
        temp->Init();
        delete temp;
        break;
    // PA9
    case TIM1_Channel2_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    // PA10
    case TIM1_Channel3_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_10);
        temp->Init();
        delete temp;
        break;
    // PA11
    case TIM1_Channel4_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_11);
        temp->Init();
        delete temp;
        break;
    // PA8
    case TIM1_Channel1_Selection_PartialRemap:
        temp = new GPIO(GPIOA, PWM_Pin_8);
        temp->Init();
        delete temp;
        break;
    // PA9
    case TIM1_Channel2_Selection_PartialRemap:
        temp = new GPIO(GPIOA, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    // PA10
    case TIM1_Channel3_Selection_PartialRemap:
        temp = new GPIO(GPIOA, PWM_Pin_10);
        temp->Init();
        delete temp;
        break;
    // PA11
    case TIM1_Channel4_Selection_PartialRemap:
        temp = new GPIO(GPIOA, PWM_Pin_11);
        temp->Init();
        delete temp;
        break;
    // PE9
    case TIM1_Channel1_Selection_FullRemap:
        temp = new GPIO(GPIOE, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    // PE11
    case TIM1_Channel2_Selection_FullRemap:
        temp = new GPIO(GPIOE, PWM_Pin_11);
        temp->Init();
        delete temp;
        break;
    // PE13
    case TIM1_Channel3_Selection_FullRemap:
        temp = new GPIO(GPIOE, PWM_Pin_13);
        temp->Init();
        delete temp;
        break;
    // PE14
    case TIM1_Channel4_Selection_FullRemap:
        temp = new GPIO(GPIOE, PWM_Pin_14);
        temp->Init();
        delete temp;
        break;
    // PA0
    case TIM2_Channel1_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_0);
        temp->Init();
        delete temp;
        break;
    // PA1
    case TIM2_Channel2_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_1);
        temp->Init();
        delete temp;
        break;
    // PA2
    case TIM2_Channel3_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_2);
        temp->Init();
        delete temp;
        break;
    // PA3
    case TIM2_Channel4_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_3);
        temp->Init();
        delete temp;
        break;
    // PA15
    case TIM2_Channel1_Selection_PartialRemap1:
        temp = new GPIO(GPIOA, PWM_Pin_15);
        temp->Init();
        delete temp;
        break;
    // PB3
    case TIM2_Channel2_Selection_PartialRemap1:
        temp = new GPIO(GPIOB, PWM_Pin_3);
        temp->Init();
        delete temp;
        break;
    // PA2
    case TIM2_Channel3_Selection_PartialRemap1:
        temp = new GPIO(GPIOA, PWM_Pin_2);
        temp->Init();
        delete temp;
        break;
    // PA3
    case TIM2_Channel4_Selection_PartialRemap1:
        temp = new GPIO(GPIOA, PWM_Pin_3);
        temp->Init();
        delete temp;
        break;
    // PA0
    case TIM2_Channel1_Selection_PartialRemap2:
        temp = new GPIO(GPIOA, PWM_Pin_0);
        temp->Init();
        delete temp;
        break;
    // PA1
    case TIM2_Channel2_Selection_PartialRemap2:
        temp = new GPIO(GPIOA, PWM_Pin_1);
        temp->Init();
        delete temp;
        break;
    // PB10
    case TIM2_Channel3_Selection_PartialRemap2:
        temp = new GPIO(GPIOB, PWM_Pin_10);
        temp->Init();
        delete temp;
        break;
    // PB11
    case TIM2_Channel4_Selection_PartialRemap2:
        temp = new GPIO(GPIOB, PWM_Pin_11);
        temp->Init();
        delete temp;
        break;
    // PA15
    case TIM2_Channel1_Selection_FullRemap:
        temp = new GPIO(GPIOA, PWM_Pin_15);
        temp->Init();
        delete temp;
        break;
    // PB3
    case TIM2_Channel2_Selection_FullRemap:
        temp = new GPIO(GPIOB, PWM_Pin_3);
        temp->Init();
        delete temp;
        break;
    // PB10
    case TIM2_Channel3_Selection_FullRemap:
        temp = new GPIO(GPIOB, PWM_Pin_10);
        temp->Init();
        delete temp;
        break;
    // PB11
    case TIM2_Channel4_Selection_FullRemap:
        temp = new GPIO(GPIOB, PWM_Pin_11);
        temp->Init();
        delete temp;
        break;
    // PA6
    case TIM3_Channel1_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_6);
        temp->Init();
        delete temp;
        break;
    // PA7
    case TIM3_Channel2_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_7);
        temp->Init();
        delete temp;
        break;
    // PB0
    case TIM3_Channel3_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_0);
        temp->Init();
        delete temp;
        break;
    // PB1
    case TIM3_Channel4_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_1);
        temp->Init();
        delete temp;
        break;
    // PB4
    case TIM3_Channel1_Selection_PartialRemap:
        temp = new GPIO(GPIOB, PWM_Pin_4);
        temp->Init();
        delete temp;
        break;
    // PB5
    case TIM3_Channel2_Selection_PartialRemap:
        temp = new GPIO(GPIOB, PWM_Pin_5);
        temp->Init();
        delete temp;
        break;
    // PB0
    case TIM3_Channel3_Selection_PartialRemap:
        temp = new GPIO(GPIOB, PWM_Pin_0);
        temp->Init();
        delete temp;
        break;
    // PB1
    case TIM3_Channel4_Selection_PartialRemap:
        temp = new GPIO(GPIOB, PWM_Pin_1);
        temp->Init();
        delete temp;
        break;
    // PC6
    case TIM3_Channel1_Selection_FullRemap:
        temp = new GPIO(GPIOC, PWM_Pin_6);
        temp->Init();
        delete temp;
        break;
    // PC7
    case TIM3_Channel2_Selection_FullRemap:
        temp = new GPIO(GPIOC, PWM_Pin_7);
        temp->Init();
        delete temp;
        break;
    // PC8
    case TIM3_Channel3_Selection_FullRemap:
        temp = new GPIO(GPIOC, PWM_Pin_8);
        temp->Init();
        delete temp;
        break;
    // PC9
    case TIM3_Channel4_Selection_FullRemap:
        temp = new GPIO(GPIOC, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    // PB6
    case TIM4_Channel1_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_6);
        temp->Init();
        delete temp;
        break;
    // PB7
    case TIM4_Channel2_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_7);
        temp->Init();
        delete temp;
        break;
    // PB8
    case TIM4_Channel3_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_8);
        temp->Init();
        delete temp;
        break;
    // PB9
    case TIM4_Channel4_Selection_Default:
        temp = new GPIO(GPIOB, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    // PD12
    case TIM4_Channel1_Selection_Remap:
        temp = new GPIO(GPIOD, PWM_Pin_12);
        temp->Init();
        delete temp;
        break;
    // PD13
    case TIM4_Channel2_Selection_Remap:
        temp = new GPIO(GPIOD, PWM_Pin_13);
        temp->Init();
        delete temp;
        break;
    // PD14
    case TIM4_Channel3_Selection_Remap:
        temp = new GPIO(GPIOD, PWM_Pin_14);
        temp->Init();
        delete temp;
        break;
    // PD15
    case TIM4_Channel4_Selection_Remap:
        temp = new GPIO(GPIOD, PWM_Pin_15);
        temp->Init();
        delete temp;
        break;
    // PA0
    case TIM5_Channel1_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_0);
        temp->Init();
        delete temp;
        break;
    // PA1
    case TIM5_Channel2_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_1);
        temp->Init();
        delete temp;
        break;
    // PA2
    case TIM5_Channel3_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_2);
        temp->Init();
        delete temp;
        break;
    // PA3
    case TIM5_Channel4_Selection_Default:
        temp = new GPIO(GPIOA, PWM_Pin_3);
        temp->Init();
        delete temp;
        break;
    // PC6
    case TIM8_Channel1_Selection_Default:
        temp = new GPIO(GPIOC, PWM_Pin_6);
        temp->Init();
        delete temp;
        break;
    // PC7
    case TIM8_Channel2_Selection_Default:
        temp = new GPIO(GPIOC, PWM_Pin_7);
        temp->Init();
        delete temp;
        break;
    // PC8
    case TIM8_Channel3_Selection_Default:
        temp = new GPIO(GPIOC, PWM_Pin_8);
        temp->Init();
        delete temp;
        break; 
    // PC9
    case TIM8_Channel4_Selection_Default:
        temp = new GPIO(GPIOC, PWM_Pin_9);
        temp->Init();
        delete temp;
        break;
    }
}

/**
  * @brief  PWM初始化函数
  * @param  None
  * @retval None
  */
void PWM::Init()
{
    //初始化GPIO复用
    Pin_Init();
    //获取TIM初始参数
    if (T_C_S <= TIM1_Channel4_Selection_FullRemap)
    {
        TIMx = TIM1;
    }
    else if (T_C_S <= TIM2_Channel4_Selection_FullRemap)
    {
        TIMx = TIM2;
    }
    else if (T_C_S <= TIM3_Channel4_Selection_FullRemap)
    {
        TIMx = TIM3;
    }
    else if (T_C_S <= TIM4_Channel4_Selection_Remap)
    {
        TIMx = TIM4;
    }
    else if (T_C_S <= TIM5_Channel4_Selection_Default)
    {
        TIMx = TIM5;
    }
    else if (T_C_S <= TIM8_Channel4_Selection_Default)
    {
        TIMx = TIM8;
    }
    //开启TIM时钟
    RCC_Operate::RCC_Config(TIMx, ENABLE);
    //TIM寄存器复位
    TIM_DeInit(TIMx);
    //基本设置
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
    TIM_TimeBaseStructure.TIM_Period =
        RCC_Operate::Get_SYSCLK_Frequency() / ((TIM_TimeBaseStructure.TIM_Prescaler + 1) * Frequency) - 1; //ARR寄存器的值
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    TIM_OCInitTypeDef TIM_OCInitStructure;
    //TIMOC通道设置
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //设置通道PWM模式(上升高电平有效,超过CCRx为低电平)
    TIM_OCInitStructure.TIM_Pulse = DutyRatio * (TIMx->ARR + 1);  //设置TIM的CCRx
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //使能TIM通道
    //设置选择通道
    if (T_C_S % 4 == 0)
    {
        TIM_OC1Init(TIMx, &TIM_OCInitStructure);
    }
    else if (T_C_S % 4 == 1)
    {
        TIM_OC2Init(TIMx, &TIM_OCInitStructure);
    }
    else if (T_C_S % 4 == 2)
    {
        TIM_OC3Init(TIMx, &TIM_OCInitStructure);
    }
    else if (T_C_S % 4 == 3)
    {
        TIM_OC4Init(TIMx, &TIM_OCInitStructure);
    }
    Start();
}

/**
  * @brief  开启PWM函数
  * @param  None
  * @retval None
  */
void PWM::Start()
{
    TIM_Cmd(TIMx, ENABLE);
}

/**
  * @brief  关闭PWM函数
  * @param  None
  * @retval None
  */
void PWM::ShutUp()
{
    TIM_Cmd(TIMx, DISABLE);
}

/**
  * @brief  PWM参数更新函数
  * @param  T_C_S:选择TIMx的CHx通道
  * @param  Frequency:频率(不低于1,不高于cpu工作频率问题不大)
  * @param  DutyRatio:占空比
  * @retval None
  */
void PWM::Update(TIMx_Channelx_Selection T_C_S, double Frequency, double DutyRatio)
{
    TIM_DeInit(TIMx);
    Set_TIMx_Channelx_Selection(T_C_S);
    Set_DutyRatio(DutyRatio);
    Set_Frequency(Frequency);
    Init();
}

/**
  * @brief  设置PWM选择路
  * @param  None
  * @retval None
  */
void PWM::Set_TIMx_Channelx_Selection(TIMx_Channelx_Selection T_C_S)
{
    this->T_C_S = T_C_S;
}

/**
  * @brief  设置PWM频率函数
  * @param  None
  * @retval None
  */
void PWM::Set_Frequency(double Frequency)
{
    this->Frequency = Frequency;
}

/**
  * @brief  设置PWM占空比函数
  * @param  None
  * @retval None
  */
void PWM::Set_DutyRatio(double DutyRatio)
{
    this->DutyRatio = DutyRatio;
}