#include "DMA.h"
/**
 * @brief  DMA-�չ��췽��
 * @param  None
 * @retval None
 */
DMA::DMA()
{
}

/**
 * @brief  DMA-��������
 * @param  None
 * @retval None
 */
DMA::~DMA()
{
}

/**
 * @brief  DMA-���췽��
 * @param  DMAx_Param   DMA�Ĳ����б�
 * @retval None
 */
DMA::DMA(DMA_Param DMAx_Param)
{
    Set_DMA_Param(DMAx_Param);
}

/**
 * @brief  DMA-����DMA�Ĳ����б�
 * @param  DMAx_Param   DMA�Ĳ����б�
 * @retval None
 */
void DMA::Set_DMA_Param(DMA_Param DMAx_Param)
{
    this->DMAx_Param = DMAx_Param;
}

/**
 * @brief  DMA-�����б����
 * @param  DMAx_Param   DMA�Ĳ����б�
 * @retval None
 */
void DMA::Update(DMA_Param DMAx_Param)
{
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    Set_DMA_Param(DMAx_Param);
    Init();
}

/**
 * @brief  DMA-�����ڲ���ѭ��ģʽ�µ�����������
 * @param  DMAx_Param   DMA�Ĳ����б�
 * @retval None
 */
void DMA::SetCurrDataCounter(uint16_t DataNumber)
{
    DMA_SetCurrDataCounter(DMAx_Param.DMA_Channelx, DataNumber);
}

/**
 * @brief  DMA-��ʼ������
 * @param  None
 * @retval None
 */
void DMA::Init()
{
    // ����RCCʱ��
    RCC_Enable();
    // DMA�Ĵ�����λ
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    // ����DMA
    DMA_Init(DMAx_Param.DMA_Channelx, &DMAx_Param.DMA_InitStructure);
    // ����DMA�ж�
    ITConfig(DMAx_Param.DMA_IT_Selection, DMAx_Param.DMA_IT_State);
    // ʹ��DMA
    Enable();
}

/**
 * @brief  DMA-�жϷ���
 * @param  DMA_IT       �жϱ�־��ѡ��
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void DMA::ITConfig(uint32_t DMA_IT, FunctionalState NewState)
{
    DMAx_Param.DMA_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
    NVIC_Operate(DMAx_Param.DMA_NVIC_InitStructure).Init();
    DMA_ITConfig(DMAx_Param.DMA_Channelx, DMA_IT, NewState);
}

/**
 * @brief  DMA-����DMA����(DMAʹ��)
 * @param  None
 * @retval None
 */
void DMA::Enable()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, ENABLE);
}

/**
 * @brief  DMA-�ر�DMA����(DMAʧ��)
 * @param  None
 * @retval None
 */
void DMA::Disable()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, DISABLE);
}

/**
 * @brief  DMA-����DMAʱ�ӷ���
 * @param  None
 * @retval None
 */
void DMA::RCC_Enable()
{
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), ENABLE);
}

/**
 * @brief  �ر�DMA-DMAʱ�ӷ���
 * @param  None
 * @retval None
 */
void DMA::RCC_Disable()
{
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), DISABLE);
}

/**
 * @brief  DMA-����DMAʱ�ӷ���
 * @param  None
 * @retval None
 */
void DMA::RCC_Enable(DMA_TypeDef *DMAx)
{
    RCC_Operate::RCC_Config(DMAx, ENABLE);
}

/**
 * @brief  �ر�DMA-DMAʱ�ӷ���
 * @param  None
 * @retval None
 */
void DMA::RCC_Disable(DMA_TypeDef *DMAx)
{
    RCC_Operate::RCC_Config(DMAx, DISABLE);
}

/**
 * @brief  DMA-��ȡDMAͨ��������DMA
 * @param  DMA_Channelx     DMAͨ���ṹ��
 * @retval DMAͨ��������DMAx
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

/**
 * @brief  DMA-��ȡDMAͨ��
 * @param  perip                ����ö��
 * @retval DMAͨ��������DMAx
 */
DMA_Channel_TypeDef *DMA::Get_DMA_Channel(DMA_Perip_enum perip)
{
    switch (perip / 10)
    {
    case 0:
        return DMA1_Channel1;
    case 1:
        return DMA1_Channel2;
    case 2:
        return DMA1_Channel3;
    case 3:
        return DMA1_Channel4;
    case 4:
        return DMA1_Channel5;
    case 5:
        return DMA1_Channel6;
    case 6:
        return DMA1_Channel7;
    case 7:
        return DMA2_Channel1;
    case 8:
        return DMA2_Channel2;
    case 9:
        return DMA2_Channel3;
    case 10:
        return DMA2_Channel4;
    case 11:
        return DMA2_Channel5;
    default:
        return 0;
    }
}

/**
 * @brief  DMA-��ȡDMA�ж�IRQn
 * @param  DMAx_Channelx        DMAͨ��
 * @retval DMAͨ����Ӧ��IRQn
 */
uint8_t DMA::Get_DMAx_Channelx_IRQn(DMA_Channel_TypeDef *DMAx_Channelx)
{
    if (DMAx_Channelx == DMA1_Channel1)
    {
        return DMA1_Channel1_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel2)
    {
        return DMA1_Channel2_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel3)
    {
        return DMA1_Channel3_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel4)
    {
        return DMA1_Channel4_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel5)
    {
        return DMA1_Channel5_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel6)
    {
        return DMA1_Channel6_IRQn;
    }
    else if (DMAx_Channelx == DMA1_Channel7)
    {
        return DMA1_Channel7_IRQn;
    }
    else if (DMAx_Channelx == DMA2_Channel1)
    {
        return DMA2_Channel1_IRQn;
    }
    else if (DMAx_Channelx == DMA2_Channel2)
    {
        return DMA2_Channel2_IRQn;
    }
    else if (DMAx_Channelx == DMA2_Channel3)
    {
        return DMA2_Channel3_IRQn;
    }
    else if (DMAx_Channelx == DMA2_Channel4 || DMAx_Channelx == DMA2_Channel5)
    {
        return DMA2_Channel4_5_IRQn;
    }
    return 0;
}

/**
 * @brief  DMA-���DMAͨ���Ƿ��ڹ���
 * @param  DMAx_Channelx        DMAͨ��
 * @retval DMAͨ���Ƿ��ڹ���
 */
bool DMA::Check_DMAx_Channelx(DMA_Channel_TypeDef *DMAx_Channelx)
{
    assert_param(IS_DMA_ALL_PERIPH(DMAx_Channelx));
    return DMAx_Channelx->CCR & DMA_CCR1_EN;
}