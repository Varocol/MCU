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
    //����RCCʱ��
    RCC_Operate::RCC_Config(Get_DMA(DMAx_Param.DMA_Channelx), ENABLE);
    // DMA�Ĵ�����λ
    DMA_DeInit(this->DMAx_Param.DMA_Channelx);
    //����DMA
    DMA_Init(DMAx_Param.DMA_Channelx, &DMAx_Param.DMA_InitStructure);
    //����DMA�ж����ȼ�
    DMAx_Param.DMA_NVIC_Operate.Init();
    //����DMA�ж�
    ITConfig(DMAx_Param.DMA_IT_Selection, DMAx_Param.DMA_IT_State);
    //ʹ��DMA
    Start();
}

/**
 * @brief  DMA-�жϷ���
 * @param  DMA_IT       �жϱ�־��ѡ��
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void DMA::ITConfig(uint32_t DMA_IT, FunctionalState NewState)
{
    DMA_ITConfig(DMAx_Param.DMA_Channelx, DMA_IT, NewState);
}

/**
 * @brief  DMA-����DMA����(DMAʹ��)
 * @param  None
 * @retval None
 */
void DMA::Start()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, ENABLE);
}

/**
 * @brief  DMA-�ر�DMA����(DMAʧ��)
 * @note   �ùرշ�������stm32�ٷ��Ƽ��Ĺر�˳��,����Ӧ���ڴ�����ɺ�ʹ��
 *         ���仹δ��ʼ����ʹ��
 * @param  None
 * @retval None
 */
void DMA::ShutUp()
{
    DMA_Cmd(DMAx_Param.DMA_Channelx, DISABLE);
}

/**
 * @brief  DMA-��ȡDMAͨ��������DMA
 * @param
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