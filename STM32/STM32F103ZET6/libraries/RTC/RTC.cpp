#include "RTC.h"
#include "System.h"
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
 * @brief  RTC_Operate-设置RTC分频系数(不能设置类参数中的分频值)
 * @param  PrescalerValue           分频系数
 * @retval None
 */
void RTC_Operate::SetPrescaler(uint32_t PrescalerValue)
{
    RTC_WaitForLastTask();
    RTC_SetPrescaler(PrescalerValue);
}

/**
 * @brief  RTC_Operate-设置RTC计数器值(不能设置类参数中的计数器值)
 * @param  CounterValue             计数器值
 * @retval None
 */
void RTC_Operate::SetCounter(uint32_t CounterValue)
{
    RTC_WaitForLastTask();
    RTC_SetCounter(CounterValue);
}

/**
 * @brief  RTC_Operate-设置RTC闹钟值(不能设置类参数中的闹钟值)
 * @param  AlarmValue               闹钟值
 * @retval None
 */
void RTC_Operate::SetAlarm(uint32_t AlarmValue)
{
    RTC_WaitForLastTask();
    RTC_SetAlarm(AlarmValue);
}

/**
 * @brief  RTC_Operate-获取分频系数
 *         注意：
 *         由于分频寄存器无法读取,所以该方法只返回用于设置RTC的RTC参数值,
 *         若需要获取实际的分频值,需要使用秒脉冲ASOS、RTC时钟源频率以及定时器测量得出,
 *         如果闲麻烦可以直接设置分频系数,使其变为一个确定值。
 * @param  None
 * @retval 分频系数
 */
uint32_t RTC_Operate::GetPrescaler()
{
    return RTCx_Param.PrescalerValue;
}

/**
 * @brief  RTC_Operate-获取计数值
 * @param  None
 * @retval CounterValue
 */
uint32_t RTC_Operate::GetCounter()
{
    return RTC_GetCounter();
}

/**
 * @brief  RTC_Operate-获取余数值
 * @param  None
 * @retval DividerValue
 */
uint32_t RTC_Operate::GetDivider()
{
    return RTC_GetDivider();
}

/**
 * @brief  RTC_Operate-获取小数点时间(通过余数寄存器转换得到)
 * @param  None
 * @retval 小数点时间
 */
double RTC_Operate::Get_Divider_Time()
{
    uint32_t Freq = Get_Clock_Freq();
    return Freq != 0 ? GetDivider() * 1.0 / Freq : 0;
}

/**
 * @brief  RTC_Operate-获取RTC时钟频率
 * @param  None
 * @retval RTC时钟频率
 */
uint32_t RTC_Operate::Get_Clock_Freq()
{
    uint32_t tmp = RCC->BDCR & RCC_RTCCLKSource_HSE_Div128;
    switch (tmp)
    {
        // LSE 32768Hz
    case RCC_RTCCLKSource_LSE:
        return 32768;
        // LSI 40000Hz
    case RCC_RTCCLKSource_LSI:
        return 40000;
        // HSE 8000000Hz
    case RCC_RTCCLKSource_HSE_Div128:
        return 8000000;
    default:
        return 0;
    }
}

/**
 * @brief  RTC_Operate-获取UNIX时间
 * @param  None
 * @retval UNIX时间
 */
uint32_t RTC_Operate::Get_Unix_Time()
{
    return GetCounter();
}

/**
 * @brief  RTC_Operate-RTC设置UNIX时间
 * @param  Time         UNIX时间
 * @retval None
 */
void RTC_Operate::Set_Unix_Time(uint32_t Time)
{
    SetCounter((uint32_t)Time);
}

/**
 * @brief  RTC_Operate-通过RTC的时间戳获取当前时区的时间
 * @param  None
 * @retval RTC时间
 */
tm RTC_Operate::Get_Time()
{
    time_t T;
    tm temp;
    time(&T);
    //使用更安全的_localtime_r减少内存分配
    _localtime_r(&T, &temp);
    return temp;
}

/**
 * @brief  RTC_Operate-设置RTC时间
 * @param  Time         需要设置的时间(输入的时间只能大于或等于UNIX时间并小于或等于溢出时间)
 * @retval None
 */
void RTC_Operate::Set_Time(tm Time)
{
    SetCounter((uint32_t)mktime(&Time));
}

/**
 * @brief  RTC_Operate-设置RTC时区
 * @param  Time         需要设置的时区(0~23)
 * @retval None
 */
void RTC_Operate::Set_TimeZone(uint8_t Time)
{
    tzset(Time);
}

/**
 * @brief  RTC_Operate-RTC基本初始化(建议在整机掉电,即备份域完全复位时使用,也可以理解为重新设置RTC时使用)
 * @param  None
 * @retval None
 */
void RTC_Operate::Base_Init()
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
    SetAlarm(RTCx_Param.AlarmValue);
    //退出配置模式
    ExitConfigMode();
    //配置NVIC
    RTCx_Param.RTC_NVIC_Operate.Init();
    //配置中断
    ITConfig(RTCx_Param.RTC_IT_Selection, RTCx_Param.RTC_IT_State);
}

/**
 * @brief  RTC_Operate-RTC用于访问值的功能性初始化(不修改PRL、CNT、ALR)
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