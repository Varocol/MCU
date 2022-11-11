#ifndef __OJ_RTC_H
#define __OJ_RTC_H
#include "RCC.h"
#include "NVIC.h"
#include "time.h"
/*
配置RTC过程：
    1.复位备份域(可选)
    2.开启PWR和BKP时钟
    3.开启备份域访问
    4.开启RTC所需时钟源
    5.等待时钟源就绪
    6.选择RTC时钟源(3种可选)
    7.开启RTC时钟(一定要先开启,否则无法配置)
    8.等待RTC时钟与APB1时钟同步(没有这一步就无法配置中断)
    9.配置中断以及分频、计数、闹钟寄存器
    10.配置的时候如果配置中断则直接配置,若配置除中断以外的则需先开启配置模式
    11.配置完后关闭退出配置模式
    12.若配置了中断还需配置NVIC

中断标志位列表
RTC_IT_OW    //溢出中断
RTC_IT_ALR   //闹钟中断
RTC_IT_SEC   //秒中断

RTC时间基准值：1970-1-1 00:00:00    (最小允许值)
RTC溢出时间:   2106-2-7 06:28:15    (最大允许值)

*/
typedef enum
{
    RTC_CLK_LSE,
    RTC_CLK_LSI,
    RTC_CLK_HSE_Div128
} RTC_CLK_enum;

//基础初始化会使用下面所有的参数
//而一般初始化会使用
typedef struct
{
    uint32_t PrescalerValue;                 // RTC分频系数
    uint32_t CounterValue;                   // RTC计数器值
    uint32_t AlarmValue;                     // RTC闹钟值
    RTC_CLK_enum RTC_CLK;                    // RTC时钟选择
    NVIC_InitTypeDef RTC_NVIC_InitStructure; // RTC中断初始化结构体
    uint32_t RTC_IT_Selection;               // RTC中断位选择
    FunctionalState RTC_IT_State;            // RTC中断使(失)能
} RTC_Param;

class RTC_Operate
{
private:
    RTC_Param RTCx_Param;

public:
    RTC_Operate();
    ~RTC_Operate();
    RTC_Operate(RTC_Param RTCx_Param);
    void Update(RTC_Param RTCx_Param);
    void Set_RTC_Param(RTC_Param RTCx_Param);
    void ITConfig(uint16_t RTC_IT, FunctionalState NewState);
    void EnterConfigMode();
    void ExitConfigMode();

    static void SetPrescaler(uint32_t PrescalerValue);
    static void SetCounter(uint32_t CounterValue);
    static void SetAlarm(uint32_t AlarmValue);

    uint32_t GetPrescaler();
    static uint32_t GetCounter();
    static uint32_t GetDivider();
    static uint32_t Get_Clock_Freq();
    static double Get_Divider_Time();

    static uint32_t Get_Unix_Time();
    static void Set_Unix_Time(uint32_t Time);
    static tm Get_Time();
    static void Set_Time(tm Time);
    static void Set_TimeZone(uint8_t TimeZone);

    void Base_Init();
    void Init();
    static void RCC_Enable();
    static void RCC_Disable();
};

extern void (*RTC_Handler)(void);
extern void (*RTCAlarm_Handler)(void);

#endif /*__OJ_RTC_H*/