#include "System.h"

/*
    USART:
        �ض���printf()�Լ�scanf()
    RTC:
        �ض���time()��clock()�Լ�difftime()
*/

//��Χ  0~23
//�й�����ʱ��
static uint8_t TimeZone = 0x08;

#ifdef __cplusplus
extern "C"
{
#endif
    //�ض���c�⺯��printf������,�ض�����ʹ��printf����,ǰ���ǵÿ���DEBUG_USARTx
    int fputc(int ch, FILE *f)
    {
        /* ����һ���ֽ����ݵ����� */
        PLATFORM_USART.Send_Data((uint8_t)ch);
        return ch;
    }
    //�ض���c�⺯��scanf������,�ض�����ʹ��scanf��getchar�Ⱥ���,ǰ���ǵÿ���DEBUG_USARTx,Ҫ�ر�RXNE�жϲſ�������ʹ��
    int fgetc(FILE *f)
    {
        /* �ȴ������������� */
        return (int)PLATFORM_USART.Receive_Data();
    }
    //�ض���time()
    time_t time(time_t *timer)
    {
        if (timer != NULL)
        {
            //ǰ����RTC��Ҫ����ʼ��
            *timer = RTC_Operate::GetCounter();
            return *timer;
        }
        return RTC_Operate::GetCounter();
    }
    //�ض���clock(),clk�Ǹ���RTCʱ�ӵ�ԭʼʱ��Ƶ������,�����LSE��Ϊ32768Hz,ȡ����ֵ����32768���ɵ���
    //��Щ����²�һ����õķ�Ƶ��������,���һֱʹ�����״�����ôû����,�����������֮ǰʹ�������Ĵ������ù�
    // RTC��Ƶ,��ôһ�ж����δ֪�������Ĵ����ڵ�ֵ�����¼���������Ҫ��
    clock_t clock(void)
    {
        clock_t t = RTC_Operate::GetCounter();
        return (t + 1) * RTC_x.GetPrescaler() - RTC_Operate::GetDivider();
    }
    //�ض���difftime(),��������ʱ���,��λs
    double difftime(time_t time1, time_t time0)
    {
        if (time1 < time0)
        {
            time_t tmp = time1;
            time1 = time0;
            time0 = tmp;
        }
        return ((time_t)(time1 - time0)) * 1.0 / RTC_Operate::Get_Clock_Freq();
    }
    //�ض���mktime,��չ��64λ
    time_t mktime(tm *timeptr)
    {
        time_t t;
        tm temp = *timeptr;
        temp.tm_year += 1900;
        temp.tm_mon += 1;
        if ((int)(temp.tm_mon -= 2) <= 0)
        {                      /* 1..12 -> 11,12,1..10 */
            temp.tm_mon += 12; /* Puts Feb last since it has leap day */
            temp.tm_year -= 1;
        }
        t = (((
                  (time_t)(temp.tm_year / 4 - temp.tm_year / 100 + temp.tm_year / 400 +
                           367 * temp.tm_mon / 12 + temp.tm_mday) +
                  temp.tm_year * 365 - 719499) *
                  24 +
              temp.tm_hour /* now have hours */
              ) * 60 +
             temp.tm_min /* now have minutes */
             ) * 60 +
            temp.tm_sec; /* finally seconds */
        if (t >= TimeZone * 60 * 60)
        {
            t -= TimeZone * 60 * 60;
        }
        else
        {
            t = 0;
        }
        return t;
    }
    //�ض���localtime,��չ��64λ
    tm *localtime(const time_t *timer)
    {
        static tm temp;
        _localtime_r(timer, &temp);
        return &temp;
    }
    //�ض���_localtime_r,��չ��64λ
    tm *_localtime_r(const time_t *timer, tm *result)
    {
        time_t t = *timer + TimeZone * 60 * 60;
        //ȷ��ʱ����
        //ʱ
        result->tm_hour = t % (24 * 60 * 60) / (60 * 60);
        //��
        result->tm_min = t % (60 * 60) / 60;
        //��
        result->tm_sec = t % 60;
        //��������
        t /= (24 * 60 * 60);
        //���� (1970-1-1 ������)
        result->tm_wday = (t + 4) % 7;
        //��1970�꿪ʼ����
        result->tm_year = t / 366 + 1970;
        for (; result->tm_year <= t / 365 + 1970; result->tm_year++)
        {
            if (days_between_years(result->tm_year, 1970) > t)
            {
                break;
            }
            if (result->tm_year == INT32_MAX)
            {
                break;
            }
        }
        //���
        result->tm_year -= 1;
        t -= days_between_years(result->tm_year, 1970);
        result->tm_year -= 1900;
        //һ���еڼ���
        result->tm_yday = t;
        result->tm_mday = t;
        //�·�
        for (result->tm_mon = 0; result->tm_mon < 12; result->tm_mon++)
        {
            int mon_day = days_in_months(result->tm_year + 1900, result->tm_mon + 1);
            if (result->tm_mday >= mon_day)
            {
                result->tm_mday -= mon_day;
            }
            else
            {
                break;
            }
        }
        //����������Ϊ1~31�ı�׼
        result->tm_mday++;
        return result;
    }
    //�ض���tzset,���Ǵ˰汾����û��
#ifdef __cplusplus
}
#endif
void tzset(uint8_t time)
{
    TimeZone = time % 24;
}
void usart_init()
{
    PLATFORM_USART.Init();
}
void led_init()
{
    PLATFORM_LED.Init();
}
void rtc_init()
{
    PLATFORM_RTC.Init();
}
void record_start_time()
{
    system_start_time = time(0);
}
void system_init()
{
    //��ʼ��RTC
    rtc_init();
    //��¼ϵͳ����ʱ��
    record_start_time();
    //��ʼ������
    usart_init();
    //��ʼ���źŵ�
    led_init();
}
//��ȡϵͳ����ʱ��
uint32_t system_time()
{
    return (uint32_t)time(0) - system_start_time;
}
//��ȡ���뼶ϵͳ����ʱ��
uint32_t system_time_ms()
{
    clock_t start_clock = (system_start_time + 1) * RTC_x.GetPrescaler();
    return difftime(start_clock, clock()) * 1000;
}
//ϵͳ����ʱ,��λs
void system_delay(uint32_t s)
{
    SysTick_Operate::Delay(s, (uint32_t)RCC_Operate::Get_SYSCLK_Frequency());
}
//ϵͳ����ʱ,��λms
void system_delay_ms(uint32_t ms)
{
    SysTick_Operate::Delay_ms(ms);
}