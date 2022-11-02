#include "ADC.h"
/**
 * @brief  ADC-�չ��췽��
 * @param  None
 * @retval None
 */
ADC::ADC()
{
}

/**
 * @brief  ADC-��������
 * @param  None
 * @retval None
 */
ADC::~ADC()
{
}

/**
 * @brief  ADC-���췽��
 * @param  ADCx_Param     ADC�Ĳ����б�
 * @retval None
 */
ADC::ADC(ADC_Param ADCx_Param)
{
    Set_ADC_Param(ADCx_Param);
}

/**
 * @brief  ADC-����ADC�Ĳ����б�
 * @param  ADCx_Param     ADC�Ĳ����б�
 * @retval None
 */
void ADC::Set_ADC_Param(ADC_Param ADCx_Param)
{
    this->ADCx_Param = ADCx_Param;
}

/**
 * @brief  ADC-�����б����
 * @param  ADCx_Param     ADC�Ĳ����б�
 * @retval None
 */
void ADC::Update(ADC_Param ADCx_Param)
{
    ADC_DeInit(this->ADCx_Param.ADCx);
    Set_ADC_Param(ADCx_Param);
    Init();
}

/**
 * @brief  ADC-ʹ��DMA���书��
 * @param  NewState       �Ƿ�ʹ��DMA
 * @retval None
 */
void ADC::DMACmd(FunctionalState NewState)
{
    ADC_DMACmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-�жϷ���
 * @param  ADC_IT         �жϱ�־��ѡ��
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void ADC::ITConfig(uint16_t ADC_IT, FunctionalState NewState)
{
    ADCx_Param.ADC_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Operate(ADCx_Param.ADC_NVIC_InitStructure).Init();
    ADC_ITConfig(ADCx_Param.ADCx, ADC_IT, NewState);
}

/**
 * @brief  ADC-��ͨ��GPIO��ʼ��
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
 * @brief  ADC-GPIO���ų�ʼ��
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
 * @brief  ADC-��ʼ������
 * @param  None
 * @retval None
 */
void ADC::Init()
{
    // ����ADCʱ��
    RCC_Enable();
    // ����ADC����ʱ��
    RCC_Operate::ADC_CLKConfig(ADCx_Param.ADC_Base_InitStructure.RCC_PCLK2_Divx);
    // ADCx�Ĵ�����λ
    ADC_DeInit(ADCx_Param.ADCx);
    // ���ų�ʼ��
    Pin_Init();
    // ������ʼ��ADC
    uint8_t listsize = ADCx_Param.ADC_RegularChannel_InitStructure.ADC_Channellist.size();
    ADC_InitTypeDef ADC_InitStructure = {
        .ADC_Mode = ADCx_Param.ADC_Base_InitStructure.ADC_Mode,
        .ADC_ScanConvMode = ADCx_Param.ADC_Base_InitStructure.ADC_ScanConvMode,
        .ADC_ContinuousConvMode = ADCx_Param.ADC_Base_InitStructure.ADC_ContinuousConvMode,
        .ADC_ExternalTrigConv = ADCx_Param.ADC_RegularChannel_InitStructure.ADC_ExternalTrigConv,
        .ADC_DataAlign = ADCx_Param.ADC_Base_InitStructure.ADC_DataAlign,
        .ADC_NbrOfChannel = listsize};
    ADC_Init(ADCx_Param.ADCx, &ADC_InitStructure);
    // ���ù���ͨ����źͲ���ʱ��
    for (ADC_Channel_ConInfo it : ADCx_Param.ADC_RegularChannel_InitStructure.ADC_Channellist)
    {
        ADC_RegularChannelConfig(ADCx_Param.ADCx, it.ADC_Channel, it.Rank, it.ADC_SampleTime);
    }
    // ����ע��ͨ�����г���
    ADC_InjectedSequencerLengthConfig(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_Channellist.size());
    for (ADC_Channel_ConInfo it : ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_Channellist)
    {
        ADC_InjectedChannelConfig(ADCx_Param.ADCx, it.ADC_Channel, it.Rank, it.ADC_SampleTime);
    }
    // ����ע��ͨ�����Զ�ע��
    ADC_AutoInjectedConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_Base_InitStructure.ADC_JAuto);
    // ���ü��ģʽ
    ADC_DiscModeCmd(ADCx_Param.ADCx, ADCx_Param.ADC_RegularChannel_InitStructure.ADC_DiscMode);
    ADC_InjectedDiscModeCmd(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_DiscMode);
    ADC_DiscModeChannelCountConfig(ADCx_Param.ADCx, ADCx_Param.ADC_Base_InitStructure.ADC_DiscModeNumber);
    // ���ù���ͨ���ⲿ����
    // ������ADC_Init���Ѿ������˴���ʹ��,���Բ���Ҫ����
    ADC_ExternalTrigConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_RegularChannel_InitStructure.ADC_ExternalTrig);
    // ����ע��ͨ���ⲿ����
    ADC_ExternalTrigInjectedConvCmd(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_ExternalTrig);
    ADC_ExternalTrigInjectedConvConfig(ADCx_Param.ADCx, ADCx_Param.ADC_InjectedChannel_InitStructure.ADC_ExternalTrigConv);
    // ����DMA
    DMACmd(ADCx_Param.ADC_DMA_State);
    // �����ж�
    ITConfig(ADCx_Param.ADC_IT_Selection, ADCx_Param.ADC_IT_State);
    // ��ADC��˯��ģʽ����
    Enable();
    // ��ʼ��ADCУ׼�Ĵ���
    ADC_ResetCalibration(ADCx_Param.ADCx);
    // �ȴ�У׼�Ĵ�����ʼ�����
    while (ADC_GetResetCalibrationStatus(ADCx_Param.ADCx))
        ;
    // ADC��ʼУ׼
    ADC_StartCalibration(ADCx_Param.ADCx);
    // �ȴ�У׼���
    while (ADC_GetCalibrationStatus(ADCx_Param.ADCx))
        ;
}

/**
 * @brief  ADC-����ADC����(ADCʹ��)
 * @param  None
 * @retval None
 */
void ADC::Enable()
{
    ADC_Cmd(ADCx_Param.ADCx, ENABLE);
}

/**
 * @brief  ADC-�ر�ADC����(ADCʧ��)
 * @param  None
 * @retval None
 */
void ADC::Disable()
{
    ADC_Cmd(ADCx_Param.ADCx, DISABLE);
}

/**
 * @brief  ADC-�¶ȴ�������VREFINTʹ��(ʧ��)
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void ADC::TempSensorVrefintCmd(FunctionalState NewState)
{
    ADC_TempSensorVrefintCmd(NewState);
}

/**
 * @brief  ADC-�������ת������ͨ��ʹ��(ʧ��)
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void ADC::SoftwareStartConvCmd(FunctionalState NewState)
{
    ADC_SoftwareStartConvCmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-�������ת��ע��ͨ��ʹ��(ʧ��)
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void ADC::SoftwareStartInjectedConvCmd(FunctionalState NewState)
{
    ADC_SoftwareStartInjectedConvCmd(ADCx_Param.ADCx, NewState);
}

/**
 * @brief  ADC-ģ�⿴�Ź�ģʽѡ��
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void ADC::AnalogWatchdogCmd(uint32_t ADC_AnalogWatchdog)
{
    ADC_AnalogWatchdogCmd(ADCx_Param.ADCx, ADC_AnalogWatchdog);
}

/**
 * @brief  ADC-����ģ�⿴�Ź�������ֵ
 * @param  HighThreshold  ����
 * @param  LowThreshold   ����
 * @retval None
 */
void ADC::AnalogWatchdogThresholdsConfig(uint16_t HighThreshold, uint16_t LowThreshold)
{
    AnalogWatchdogThresholdsConfig(HighThreshold, LowThreshold);
}

/**
 * @brief  ADC-����ģ�⿴�Ź�ͨ��
 * @param  ADC_Channel    ADCͨ��
 * @retval None
 */
void ADC::AnalogWatchdogSingleChannelConfig(uint8_t ADC_Channel)
{
    ADC_AnalogWatchdogSingleChannelConfig(ADCx_Param.ADCx, ADC_Channel);
}

/**
 * @brief  ADC-����ע��ͨ��ƫ����
 * @param  ADC_InjectedChannel      ADCע��ͨ��
 *
 * @retval None
 */
void ADC::SetInjectedOffset(uint8_t ADC_InjectedChannel, uint16_t Offset)
{
    ADC_SetInjectedOffset(ADCx_Param.ADCx, ADC_InjectedChannel, Offset);
}

/**
 * @brief  ADC-����ADCʱ�ӷ���
 * @param  None
 * @retval None
 */
void ADC::RCC_Enable()
{
    RCC_Operate::RCC_Config(ADCx_Param.ADCx, ENABLE);
}

/**
 * @brief  ADC-�ر�ADCʱ�ӷ���
 * @param  None
 * @retval None
 */
void ADC::RCC_Disable()
{
    RCC_Operate::RCC_Config(ADCx_Param.ADCx, DISABLE);
}

/**
 * @brief  ADC-����ADCʱ�ӷ���
 * @param  None
 * @retval None
 */
void ADC::RCC_Enable(ADC_TypeDef *ADCx)
{
    RCC_Operate::RCC_Config(ADCx, ENABLE);
}

/**
 * @brief  ADC-�ر�ADCʱ�ӷ���
 * @param  None
 * @retval None
 */
void ADC::RCC_Disable(ADC_TypeDef *ADCx)
{
    RCC_Operate::RCC_Config(ADCx, DISABLE);
}