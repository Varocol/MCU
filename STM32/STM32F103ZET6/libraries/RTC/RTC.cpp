#include "RTC.h"
/**
 * @brief  RTC_Operate-�չ��췽��
 * @param  None
 * @retval None
 */
RTC_Operate::RTC_Operate()
{
}

/**
 * @brief  RTC_Operate-��������
 * @param  None
 * @retval None
 */
RTC_Operate::~RTC_Operate()
{
}

/**
 * @brief  RTC_Operate-���췽��
 * @param  RTCx_Param   RTC�Ĳ����б�
 * @retval None
 */
RTC_Operate::RTC_Operate(RTC_Param RTCx_Param)
{
    Set_RTC_Param(RTCx_Param);
}

/**
 * @brief  RTC_Operate-����RTC�Ĳ����б�
 * @param  RTCx_Param   RTC�Ĳ����б�
 * @retval None
 */
void RTC_Operate::Update(RTC_Param RTCx_Param)
{
    Set_RTC_Param(RTCx_Param);
    Init();
}

/**
 * @brief  RTC_Operate-�����б�����
 * @param  RTCx_Param   RTC�Ĳ����б�
 * @retval None
 */
void RTC_Operate::Set_RTC_Param(RTC_Param RTCx_Param)
{
    this->RTCx_Param = RTCx_Param;
}

/**
 * @brief  RTC_Operate-�жϷ���
 * @param  RTC_IT       �жϱ�־��ѡ��
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void RTC_Operate::ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT, NewState);
}

/**
 * @brief  RTC_Operate-����RTC����ģʽ
 * @param  None
 * @retval None
 */
void RTC_Operate::EnterConfigMode()
{
    RTC_WaitForLastTask();
    RTC_EnterConfigMode();
}

/**
 * @brief  RTC_Operate-�˳�RTC����ģʽ
 * @param  None
 * @retval None
 */
void RTC_Operate::ExitConfigMode()
{
    RTC_WaitForLastTask();
    RTC_ExitConfigMode();
}

/**
 * @brief  RTC_Operate-����RTC��Ƶϵ��
 * @param  PrescalerValue           ��Ƶϵ��
 * @retval None
 */
void RTC_Operate::SetPrescaler(uint32_t PrescalerValue)
{
    RTCx_Param.PrescalerValue = PrescalerValue;
    RTC_WaitForLastTask();
    RTC_SetPrescaler(PrescalerValue);
}

/**
 * @brief  RTC_Operate-����RTC������ֵ
 * @param  CounterValue             ������ֵ
 * @retval None
 */
void RTC_Operate::SetCounter(uint32_t CounterValue)
{
    RTCx_Param.CounterValue = CounterValue;
    RTC_WaitForLastTask();
    RTC_SetCounter(CounterValue);
}

/**
 * @brief  RTC_Operate-����RTC����ֵ
 * @param  AlarmValue               ����ֵ
 * @retval None
 */
void RTC_Operate::SetAlarm(uint32_t AlarmValue)
{
    RTCx_Param.AlarmValue = AlarmValue;
    RTC_WaitForLastTask();
    RTC_SetAlarm(AlarmValue);
}

/**
 * @brief  RTC_Operate-RTC������ʼ��
 *         ��Ƶ�������Լ�����ֵ��Ҫ��������,��ʼ����������
 * @param  None
 * @retval None
 */
void RTC_Operate::Init()
{
    //��λ������(������������λ,����bkp�����Լ�RTC��������)
    // BKP_DeInit();��
    // RCC_Operate::Backup_Reset();
    //����PWR��BKPʱ��
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);
    //��������BKP����(��λ��������������,��Ҫ��������)
    PWR_BackupAccessCmd(ENABLE);
    //������ѡʱ������ʱ��Դ
    if (RTCx_Param.RTC_CLK == RTC_CLK_LSE)
    {
        //������Ҫ��RTC�ṩ�ź�Դ��ʱ��
        RCC_LSEConfig(RCC_LSE_ON);
        //�ȴ�ʱ��Դ����
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
            ;
        //����RTCʱ��Դѡ��(һ��ѡ��LSE,��ΪLSE���ڱ�������,��VBat����,���Կ��Գ����ṩ�ź�)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    }
    //��ʱ��Դ���ڱ�������,����ֻ��VDD��
    else if (RTCx_Param.RTC_CLK == RTC_CLK_LSI)
    {
        //������Ҫ��RTC�ṩ�ź�Դ��ʱ��
        RCC_LSICmd(ENABLE);
        //�ȴ�ʱ��Դ����
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
            ;
        //����RTCʱ��Դѡ��(һ��ѡ��LSE,��ΪLSE���ڱ�������,��VBat����,���Կ��Գ����ṩ�ź�)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    }
    //��ʱ��Դ���ڱ�������,����ֻ��VDD��
    else if (RTCx_Param.RTC_CLK == RTC_CLK_HSE_Div128)
    {
        //������Ҫ��RTC�ṩ�ź�Դ��ʱ��
        RCC_HSEConfig(RCC_HSE_ON);
        //�ȴ�ʱ��Դ����
        if (RCC_WaitForHSEStartUp() == ERROR)
        {
            while (1)
                ;
        }
        //����RTCʱ��Դѡ��(һ��ѡ��LSE,��ΪLSE���ڱ�������,��VBat����,���Կ��Գ����ṩ�ź�)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
    }
    //ʹ��RTCʱ��
    Start();
    //�ȴ�RTCʱ��ͬ��
    RTC_WaitForSynchro();
    //��������ģʽ
    EnterConfigMode();
    //����RTC��Ƶϵ��
    SetPrescaler(RTCx_Param.PrescalerValue);
    //����RTC����ֵ
    SetCounter(RTCx_Param.CounterValue);
    //����RTC����ֵ
    SetCounter(RTCx_Param.AlarmValue);
    //�˳�����ģʽ
    ExitConfigMode();
    //����NVIC
    RTCx_Param.RTC_NVIC_Operate.Init();
    //�����ж�
    ITConfig(RTCx_Param.RTC_IT_Selection, RTCx_Param.RTC_IT_State);
}

/**
 * @brief  RTC_Operate-����RTCʱ�ӷ���
 * @param  None
 * @retval None
 */
void RTC_Operate::Start()
{
    RCC_Operate::RCC_Config(RTC, ENABLE);
}

/**
 * @brief  RTC_Operate-�ر�RTCʱ�ӷ���
 * @param  None
 * @retval None
 */
void RTC_Operate::Shutup()
{
    RCC_Operate::RCC_Config(RTC, DISABLE);
}