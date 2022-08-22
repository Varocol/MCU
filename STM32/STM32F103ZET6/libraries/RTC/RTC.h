#ifndef __OJ_RTC_H
#define __OJ_RTC_H
#include "RCC.h"
#include "NVIC.h"
#include "time.h"
/*
����RTC���̣�
    1.��λ������(��ѡ)
    2.����PWR��BKPʱ��
    3.�������������
    4.����RTC����ʱ��Դ
    5.�ȴ�ʱ��Դ����
    6.ѡ��RTCʱ��Դ(3�ֿ�ѡ)
    7.����RTCʱ��(һ��Ҫ�ȿ���,�����޷�����)
    8.�ȴ�RTCʱ����APB1ʱ��ͬ��(û����һ�����޷������ж�)
    9.�����ж��Լ���Ƶ�����������ӼĴ���
    10.���õ�ʱ����������ж���ֱ������,�����ó��ж�����������ȿ�������ģʽ
    11.�������ر��˳�����ģʽ
    12.���������жϻ�������NVIC

�жϱ�־λ�б�
RTC_IT_OW    //����ж�
RTC_IT_ALR   //�����ж�
RTC_IT_SEC   //���ж�

RTCʱ���׼ֵ��1970-1-1 00:00:00    (��С����ֵ)
RTC���ʱ��:   2106-2-7 06:28:15    (�������ֵ)

*/
typedef enum
{
    RTC_CLK_LSE,
    RTC_CLK_LSI,
    RTC_CLK_HSE_Div128
} RTC_CLK_enum;

//������ʼ����ʹ���������еĲ���
//��һ���ʼ����ʹ��
typedef struct
{
    uint32_t PrescalerValue;       // RTC��Ƶϵ��
    uint32_t CounterValue;         // RTC������ֵ
    uint32_t AlarmValue;           // RTC����ֵ
    RTC_CLK_enum RTC_CLK;          // RTCʱ��ѡ��
    NVIC_Operate RTC_NVIC_Operate; // RTC�ж϶���
    FunctionalState RTC_IT_State;  // RTC�ж�ʹ(ʧ)��
    uint32_t RTC_IT_Selection;     // RTC�ж�λѡ��
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
    void Start();
    void Shutup();
};

#endif /*__OJ_RTC_H*/