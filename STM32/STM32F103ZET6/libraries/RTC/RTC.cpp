#include "RTC.h"
/**
 * @brief  RTC_Operate-空构造方法
 * @param  None
 * @retval None
 */
RTC_Operate::RTC_Operate()
{
}

/**
 * @brief  RTC_Operate-析构方法
 * @param  None
 * @retval None
 */
RTC_Operate::~RTC_Operate()
{
}

/**
 * @brief  RTC_Operate-构造方法
 * @param  RTCx_Param   RTC的参数列表
 * @retval None
 */
RTC_Operate::RTC_Operate(RTC_Param RTCx_Param)
{
    Set_RTC_Param(RTCx_Param);
}

/**
 * @brief  RTC_Operate-设置RTC的参数列表
 * @param  RTCx_Param   RTC的参数列表
 * @retval None
 */
void RTC_Operate::Update(RTC_Param RTCx_Param)
{
    Set_RTC_Param(RTCx_Param);
    Init();
}

/**
 * @brief  RTC_Operate-参数列表更新
 * @param  RTCx_Param   RTC的参数列表
 * @retval None
 */
void RTC_Operate::Set_RTC_Param(RTC_Param RTCx_Param)
{
    this->RTCx_Param = RTCx_Param;
}

/**
 * @brief  RTC_Operate-中断方法
 * @param  RTC_IT       中断标志的选择
 * @param  NewState     使能或失能
 * @retval None
 */
void RTC_Operate::ITConfig(uint16_t RTC_IT, FunctionalState NewState)
{
    RTC_WaitForLastTask();
    RTC_ITConfig(RTC_IT, NewState);
}

/**
 * @brief  RTC_Operate-进入RTC配置模式
 * @param  None
 * @retval None
 */
void RTC_Operate::EnterConfigMode()
{
    RTC_WaitForLastTask();
    RTC_EnterConfigMode();
}

/**
 * @brief  RTC_Operate-退出RTC配置模式
 * @param  None
 * @retval None
 */
void RTC_Operate::ExitConfigMode()
{
    RTC_WaitForLastTask();
    RTC_ExitConfigMode();
}

/**
 * @brief  RTC_Operate-设置RTC分频系数
 * @param  PrescalerValue           分频系数
 * @retval None
 */
void RTC_Operate::SetPrescaler(uint32_t PrescalerValue)
{
    RTCx_Param.PrescalerValue = PrescalerValue;
    RTC_WaitForLastTask();
    RTC_SetPrescaler(PrescalerValue);
}

/**
 * @brief  RTC_Operate-设置RTC计数器值
 * @param  CounterValue             计数器值
 * @retval None
 */
void RTC_Operate::SetCounter(uint32_t CounterValue)
{
    RTCx_Param.CounterValue = CounterValue;
    RTC_WaitForLastTask();
    RTC_SetCounter(CounterValue);
}

/**
 * @brief  RTC_Operate-设置RTC闹钟值
 * @param  AlarmValue               闹钟值
 * @retval None
 */
void RTC_Operate::SetAlarm(uint32_t AlarmValue)
{
    RTCx_Param.AlarmValue = AlarmValue;
    RTC_WaitForLastTask();
    RTC_SetAlarm(AlarmValue);
}

/**
 * @brief  RTC_Operate-RTC基本初始化
 *         分频、计数以及闹钟值需要额外设置,初始化不作设置
 * @param  None
 * @retval None
 */
void RTC_Operate::Init()
{
    //复位备份域(将整个备份域复位,包括bkp数据以及RTC计数器等)
    // BKP_DeInit();或
    // RCC_Operate::Backup_Reset();
    //开启PWR和BKP时钟
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);
    //允许访问BKP区域(复位后整个备份域被锁,需要开启访问)
    PWR_BackupAccessCmd(ENABLE);
    //根据所选时钟配置时钟源
    if (RTCx_Param.RTC_CLK == RTC_CLK_LSE)
    {
        //开启需要给RTC提供信号源的时钟
        RCC_LSEConfig(RCC_LSE_ON);
        //等待时钟源就绪
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
            ;
        //配置RTC时钟源选择(一般选择LSE,因为LSE处在备份域中,由VBat供电,所以可以持续提供信号)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    }
    //该时钟源不在备份域内,供电只能VDD供
    else if (RTCx_Param.RTC_CLK == RTC_CLK_LSI)
    {
        //开启需要给RTC提供信号源的时钟
        RCC_LSICmd(ENABLE);
        //等待时钟源就绪
        while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
            ;
        //配置RTC时钟源选择(一般选择LSE,因为LSE处在备份域中,由VBat供电,所以可以持续提供信号)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    }
    //该时钟源不在备份域内,供电只能VDD供
    else if (RTCx_Param.RTC_CLK == RTC_CLK_HSE_Div128)
    {
        //开启需要给RTC提供信号源的时钟
        RCC_HSEConfig(RCC_HSE_ON);
        //等待时钟源就绪
        if (RCC_WaitForHSEStartUp() == ERROR)
        {
            while (1)
                ;
        }
        //配置RTC时钟源选择(一般选择LSE,因为LSE处在备份域中,由VBat供电,所以可以持续提供信号)
        RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div128);
    }
    //使能RTC时钟
    Start();
    //等待RTC时钟同步
    RTC_WaitForSynchro();
    //进入配置模式
    EnterConfigMode();
    //设置RTC分频系数
    SetPrescaler(RTCx_Param.PrescalerValue);
    //设置RTC计数值
    SetCounter(RTCx_Param.CounterValue);
    //设置RTC闹钟值
    SetCounter(RTCx_Param.AlarmValue);
    //退出配置模式
    ExitConfigMode();
    //配置NVIC
    RTCx_Param.RTC_NVIC_Operate.Init();
    //配置中断
    ITConfig(RTCx_Param.RTC_IT_Selection, RTCx_Param.RTC_IT_State);
}

/**
 * @brief  RTC_Operate-开启RTC时钟方法
 * @param  None
 * @retval None
 */
void RTC_Operate::Start()
{
    RCC_Operate::RCC_Config(RTC, ENABLE);
}

/**
 * @brief  RTC_Operate-关闭RTC时钟方法
 * @param  None
 * @retval None
 */
void RTC_Operate::Shutup()
{
    RCC_Operate::RCC_Config(RTC, DISABLE);
}