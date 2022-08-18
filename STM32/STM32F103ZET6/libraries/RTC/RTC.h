#ifndef __OJ_RTC_H
#define __OJ_RTC_H
#include "RCC.h"
#include "NVIC.h"
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
*/
typedef enum
{
    RTC_CLK_LSE,
    RTC_CLK_LSI,
    RTC_CLK_HSE_Div128
} RTC_CLK_enum;

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
    void SetPrescaler(uint32_t PrescalerValue);
    void SetCounter(uint32_t CounterValue);
    void SetAlarm(uint32_t AlarmValue);
    void Init();
    void Start();
    void Shutup();
};

#endif /*__OJ_RTC_H*/