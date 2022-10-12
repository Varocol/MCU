#include "PWM.h"
/**
 * @brief  PWM-�չ��췽��
 * @param  None
 * @retval None
 */
PWM::PWM()
{
}

/**
 * @brief  PWM-���췽��
 * @param  TIMx_Channelx        ѡ��TIMx��CHxͨ��
 * @param  Frequency            Ƶ��(������1,������cpu����Ƶ�����ⲻ��)
 * @param  DutyRatio            ռ�ձ�
 * @retval None
 */
PWM::PWM(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio)
{
    Set_PWM_Param(TIMx_Channelx, Frequency, DutyRatio);
}

/**
 * @brief  PWM-��������
 * @param  None
 * @retval None
 */
PWM::~PWM()
{
}

/**
 * @brief  PWM-GPIO���ų�ʼ��
 * @param  None
 * @retval None
 */
void PWM::Pin_Init()
{
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    PIN_enum Channel_Pin;
    //������ӳ��
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
    //��ȡ����
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
 * @brief  PWM-��ʼ������
 * @param  None
 * @retval None
 */
void PWM::Init()
{
    //��ʼ��GPIO����
    Pin_Init();
    //��ȡTIM��ʼ����
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
    //����TIMʱ��
    RCC_Operate::RCC_Config(TIMx, ENABLE);
    // TIM�Ĵ�����λ
    TIM_DeInit(TIMx);
    //��������
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
    TIM_TimeBaseStructure.TIM_Period =
        RCC_Operate::Get_SYSCLK_Frequency() / ((TIM_TimeBaseStructure.TIM_Prescaler + 1) * Frequency) - 1; // ARR�Ĵ�����ֵ
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);
    TIM_OCInitTypeDef TIM_OCInitStructure;
    // TIMOCͨ������
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;             //����ͨ��PWMģʽ(�����ߵ�ƽ��Ч,����CCRxΪ�͵�ƽ)
    TIM_OCInitStructure.TIM_Pulse = DutyRatio * (TIMx->ARR + 1);  //����TIM��CCRx
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //ʹ��TIMͨ��
    //����ѡ��ͨ��
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
 * @brief  PWM-����PWM����
 * @param  TIMx_Channelx        ѡ��TIMx��CHxͨ��
 * @param  Frequency            Ƶ��(������1,������cpu����Ƶ�����ⲻ��)
 * @param  DutyRatio            ռ�ձ�
 * @retval None
 */
void PWM::Set_PWM_Param(TIMx_Channelx_enum TIMx_Channelx, double Frequency, double DutyRatio)
{
    Set_TIMx_Channelx_enum(TIMx_Channelx);
    Set_DutyRatio(DutyRatio);
    Set_Frequency(Frequency);
}

/**
 * @brief  PWM-�������·���
 * @param  TIMx_Channelx        ѡ��TIMx��CHxͨ��
 * @param  Frequency            Ƶ��(������1,������cpu����Ƶ�����ⲻ��)
 * @param  DutyRatio            ռ�ձ�
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
 * @brief  PWM-����PWMѡ��·
 * @param  TIMx_Channelx        ѡ��TIMx��CHxͨ��
 * @retval None
 */
void PWM::Set_TIMx_Channelx_enum(TIMx_Channelx_enum TIMx_Channelx)
{
    this->TIMx_Channelx = TIMx_Channelx;
}

/**
 * @brief  PWM-����PWMƵ�ʷ���
 * @param  Frequency            Ƶ��(������1,������cpu����Ƶ�����ⲻ��)
 * @retval None
 */
void PWM::Set_Frequency(double Frequency)
{
    this->Frequency = Frequency;
}

/**
 * @brief  PWM-����PWMռ�ձȷ���
 * @param  DutyRatio            ռ�ձ�
 * @retval None
 */
void PWM::Set_DutyRatio(double DutyRatio)
{
    this->DutyRatio = DutyRatio;
}

/**
 * @brief  PWM-����PWM����
 * @param  None
 * @retval None
 */
void PWM::Enable()
{
    RCC_Operate::RCC_Config(TIMx, ENABLE);
}

/**
 * @brief  PWM-�ر�PWM����
 * @param  None
 * @retval None
 */
void PWM::Disable()
{
    RCC_Operate::RCC_Config(TIMx, DISABLE);
}