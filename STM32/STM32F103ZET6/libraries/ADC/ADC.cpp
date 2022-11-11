#include "ADC.h"
void (*ADC1_2_Handler)(void);
void (*ADC3_Handler)(void);
/**
 * @brief  ADC-空构造方法
 * @param  None
 * @retval None
 */
ADC::ADC()
{
}

/**
 * @brief  ADC-析构方法
 * @param  None
 * @retval None
 */
ADC::~ADC()
{
}

/**
 * @brief  ADC-构造方法
 * @param  ADCx_Param     ADC的参数列表
 * @retval None
 */
ADC::ADC(ADC_Param ADCx_Param)
{
    Set_ADC_Param(ADCx_Param);
}

/**
 * @brief  ADC-设置ADC的参数列表
 * @param  ADCx_Param     ADC的参数列表
 * @retval None
 */
void ADC::Set_ADC_Param(ADC_Param ADCx_Param)
{
    this->ADCx_Param = ADCx_Param;
}

/**
 * @brief  ADC-参数列表更新
 * @param  ADCx_Param     ADC的参数列表
 * @retval None
 */
void ADC::Update(ADC_Param ADCx_Param)
{
    ADC_DeInit(this->ADCx_Param.ADCx);
    Set_ADC_Param(ADCx_Param);
    Init();
}

/**
 * @brief  ADC-使用DMA传输功能
 * @param  NewState       是否使能DMA
 * @retval None
 */
void ADC::DMACmd(FunctionalState NewState)
{
    ADC_DMACmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-中断方法
 * @param  ADC_IT         中断标志的选择
 * @param  NewState       使能或失能
 * @retval None
 */
void ADC::ITConfig(uint16_t ADC_IT, FunctionalState NewState)
{
    ADCx_Param.ADC_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Operate(ADCx_Param.ADC_NVIC_InitStructure).Init();
    ADC_ITConfig(ADCx_Param.ADCx, ADC_IT, NewState);
}

/**
 * @brief  ADC-单通道GPIO初始化
 * @param  None
 * @retval None
 */
void ADC::Pin_Init(uint8_t ADC_Channel)
{
    PIN_enum pin;
    switch (ADC_Channel)
    {
    case ADC_Channel_0:
        pin = PA0;
        break;
    case ADC_Channel_1:
        pin = PA1;
        break;
    case ADC_Channel_2:
        pin = PA2;
        break;
    case ADC_Channel_3:
        pin = PA3;
        break;
    case ADC_Channel_4:
        pin = PA4;
        break;
    case ADC_Channel_5:
        pin = PA5;
        break;
    case ADC_Channel_6:
        pin = PA6;
        break;
    case ADC_Channel_7:
        pin = PA7;
        break;
    case ADC_Channel_8:
        pin = PB0;
        break;
    case ADC_Channel_9:
        pin = PB1;
        break;
    case ADC_Channel_10:
        pin = PC0;
        break;
    case ADC_Channel_11:
        pin = PC1;
        break;
    case ADC_Channel_12:
        pin = PC2;
        break;
    case ADC_Channel_13:
        pin = PC3;
        break;
    case ADC_Channel_14:
        pin = PC4;
        break;
    case ADC_Channel_15:
        pin = PC5;
        break;
    }
    if (ADCx_Param.ADCx == ADC3)
    {
        switch (ADC_Channel)
        {
        case ADC_Channel_4:
        case ADC_Channel_5:
        case ADC_Channel_6:
        case ADC_Channel_7:
        case ADC_Channel_8:
        case ADC_Channel_9:
        case ADC_Channel_14:
        case ADC_Channel_15:
            pin = Pin_None;
        }
    }
    if (pin != Pin_None)
    {
        GPIO(pin, GPIO_Mode_AIN).Init();
    }
}

/**
 * @brief  ADC-GPIO引脚初始化
 * @param  None
 * @retval None
 */
void ADC::Pin_Init()
{
    for (ADC_Channel_ConInfo el : ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_Channellist)
    {
        Pin_Init(el.ADC_Channel);
    }
    for (ADC_Channel_ConInfo el : ADCx_Param.ADC_RegularChannel_InitStructure.ADC_Channellist)
    {
        Pin_Init(el.ADC_Channel);
    }
}

/**
 * @brief  ADC-初始化方法
 * @param  None
 * @retval None
 */
void ADC::Init()
{
    // 开启ADC时钟
    RCC_Enable();
    // 配置ADC工作时钟
    RCC_Operate::ADC_CLKConfig(ADCx_Param.ADC_Base_InitStructure.RCC_PCLK2_Divx);
    // ADCx寄存器复位
    ADC_DeInit(ADCx_Param.ADCx);
    // 引脚初始化
    Pin_Init();
    // 基础初始化ADC
    uint8_t listsize = ADCx_Param.ADC_RegularChannel_InitStructure.ADC_Channellist.size();
    ADC_InitTypeDef ADC_InitStructure = {
        .ADC_Mode = ADCx_Param.ADC_Base_InitStructure.ADC_Mode,
        .ADC_ScanConvMode = ADCx_Param.ADC_Base_InitStructure.ADC_ScanConvMode,
        .ADC_ContinuousConvMode = ADCx_Param.ADC_Base_InitStructure.ADC_ContinuousConvMode,
        .ADC_ExternalTrigConv = ADCx_Param.ADC_RegularChannel_InitStructure.ADC_ExternalTrigConv,
        .ADC_DataAlign = ADCx_Param.ADC_Base_InitStructure.ADC_DataAlign,
        .ADC_NbrOfChannel = listsize};
    ADC_Init(ADCx_Param.ADCx, &ADC_InitStructure);
    // 配置规则通道序号和采样时间
    for (ADC_Channel_ConInfo it : ADCx_Param.ADC_RegularChannel_InitStructure.ADC_Channellist)
    {
        ADC_RegularChannelConfig(ADCx_Param.ADCx, it.ADC_Channel, it.Rank, it.ADC_SampleTime);
    }
    // 配置注入通道序列长度
    ADC_InjectedSequencerLengthConfig(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_Channellist.size());
    for (ADC_Channel_ConInfo it : ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_Channellist)
    {
        ADC_InjectedChannelConfig(ADCx_Param.ADCx, it.ADC_Channel, it.Rank, it.ADC_SampleTime);
    }
    // 配置注入通道的自动注入
    ADC_AutoInjectedConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_Base_InitStructure.ADC_JAuto);
    // 配置间断模式
    ADC_DiscModeCmd(ADCx_Param.ADCx, ADCx_Param.ADC_RegularChannel_InitStructure.ADC_DiscMode);
    ADC_InjectedDiscModeCmd(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_DiscMode);
    ADC_DiscModeChannelCountConfig(ADCx_Param.ADCx, ADCx_Param.ADC_Base_InitStructure.ADC_DiscModeNumber);
    // 配置规则通道外部触发
    // 由于在ADC_Init里已经配置了触发使能,所以不需要配置
    ADC_ExternalTrigConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_RegularChannel_InitStructure.ADC_ExternalTrig);
    // 配置注入通道外部触发
    ADC_ExternalTrigInjectedConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_ExternalTrig);
    ADC_ExternalTrigInjectedConvConfig(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_ExternalTrigConv);
    // 配置DMA
    DMACmd(ADCx_Param.ADC_DMA_State);
    // 配置中断
    ITConfig(ADCx_Param.ADC_IT_Selection, ADCx_Param.ADC_IT_State);
    // 将ADC从睡眠模式唤醒
    Enable();
    // 初始化ADC校准寄存器
    ADC_ResetCalibration(ADCx_Param.ADCx);
    // 等待校准寄存器初始化完成
    while (ADC_GetResetCalibrationStatus(ADCx_Param.ADCx))
        ;
    // ADC开始校准
    ADC_StartCalibration(ADCx_Param.ADCx);
    // 等待校准完成
    while (ADC_GetCalibrationStatus(ADCx_Param.ADCx))
        ;
}

/**
 * @brief  ADC-开启ADC方法(ADC使能)
 * @param  None
 * @retval None
 */
void ADC::Enable()
{
    ADC_Cmd(ADCx_Param.ADCx, ENABLE);
}

/**
 * @brief  ADC-关闭ADC方法(ADC失能)
 * @param  None
 * @retval None
 */
void ADC::Disable()
{
    ADC_Cmd(ADCx_Param.ADCx, DISABLE);
}

/**
 * @brief  ADC-温度传感器和VREFINT使能(失能)
 * @param  NewState       使能或失能
 * @retval None
 */
void ADC::TempSensorVrefintCmd(FunctionalState NewState)
{
    ADC_TempSensorVrefintCmd(NewState);
}

/**
 * @brief  ADC-软件开启转换规则通道使能(失能)
 * @param  NewState       使能或失能
 * @retval None
 */
void ADC::SoftwareStartConvCmd(FunctionalState NewState)
{
    ADC_SoftwareStartConvCmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-软件开启转换注入通道使能(失能)
 * @param  NewState       使能或失能
 * @retval None
 */
void ADC::SoftwareStartInjectedConvCmd(FunctionalState NewState)
{
    ADC_SoftwareStartInjectedConvCmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-模拟看门狗模式选择
 * @param  NewState       使能或失能
 * @retval None
 */
void ADC::AnalogWatchdogCmd(uint32_t ADC_AnalogWatchdog)
{
    ADC_AnalogWatchdogCmd(ADCx_Param.ADCx, ADC_AnalogWatchdog);
}

/**
 * @brief  ADC-设置模拟看门狗上下阈值
 * @param  HighThreshold  上限
 * @param  LowThreshold   下限
 * @retval None
 */
void ADC::AnalogWatchdogThresholdsConfig(uint16_t HighThreshold, uint16_t LowThreshold)
{
    AnalogWatchdogThresholdsConfig(HighThreshold, LowThreshold);
}

/**
 * @brief  ADC-设置模拟看门狗通道
 * @param  ADC_Channel    ADC通道
 * @retval None
 */
void ADC::AnalogWatchdogSingleChannelConfig(uint8_t ADC_Channel)
{
    ADC_AnalogWatchdogSingleChannelConfig(ADCx_Param.ADCx, ADC_Channel);
}

/**
 * @brief  ADC-设置注入通道偏移量
 * @param  ADC_InjectedChannel      ADC注入通道
 *
 * @retval None
 */
void ADC::SetInjectedOffset(uint8_t ADC_InjectedChannel, uint16_t Offset)
{
    ADC_SetInjectedOffset(ADCx_Param.ADCx, ADC_InjectedChannel, Offset);
}

/**
 * @brief  ADC-开启ADC时钟方法
 * @param  None
 * @retval None
 */
void ADC::RCC_Enable()
{
    RCC_Operate::RCC_Config(ADCx_Param.ADCx, ENABLE);
}

/**
 * @brief  ADC-关闭ADC时钟方法
 * @param  None
 * @retval None
 */
void ADC::RCC_Disable()
{
    RCC_Operate::RCC_Config(ADCx_Param.ADCx, DISABLE);
}

/**
 * @brief  ADC-开启ADC时钟方法
 * @param  None
 * @retval None
 */
void ADC::RCC_Enable(ADC_TypeDef *ADCx)
{
    RCC_Operate::RCC_Config(ADCx, ENABLE);
}

/**
 * @brief  ADC-关闭ADC时钟方法
 * @param  None
 * @retval None
 */
void ADC::RCC_Disable(ADC_TypeDef *ADCx)
{
    RCC_Operate::RCC_Config(ADCx, DISABLE);
}