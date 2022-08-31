#include "System.h"

/*
    USART:
        重定向printf()以及scanf()
    RTC:
        重定向time()、clock()以及difftime()
*/

//范围  0~23
//中国北京时区
static uint8_t TimeZone = 0x08;

#ifdef __cplusplus
extern "C"
{
#endif
    //重定向c库函数printf到串口,重定向后可使用printf函数,前提是得开启DEBUG_USARTx
    int fputc(int ch, FILE *f)
    {
        /* 发送一个字节数据到串口 */
        PLATFORM_USART.Send_Data((uint8_t)ch);
        return ch;
    }
    //重定向c库函数scanf到串口,重定向后可使用scanf、getchar等函数,前提是得开启DEBUG_USARTx,要关闭RXNE中断才可以正常使用
    int fgetc(FILE *f)
    {
        /* 等待串口输入数据 */
        return (int)PLATFORM_USART.Receive_Data();
    }
    //重定向time()
    time_t time(time_t *timer)
    {
        if (timer != NULL)
        {
            //前提是RTC需要被初始化
            *timer = RTC_Operate::GetCounter();
            return *timer;
        }
        return RTC_Operate::GetCounter();
    }
    //重定向clock(),clk是根据RTC时钟的原始时钟频率来的,如果是LSE则为32768Hz,取出的值除以32768即可得秒
    //有些情况下不一定获得的分频比余数大,如果一直使用这套代码那么没问题,但是如果在那之前使用其他的代码设置过
    // RTC分频,那么一切都变的未知。余数寄存器内的值是向下计数的所以要减
    clock_t clock(void)
    {
        clock_t t = RTC_Operate::GetCounter();
        return (t + 1) * RTC_x.GetPrescaler() - RTC_Operate::GetDivider();
    }
    //重定向difftime(),返回两者时间差,单位s
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
    //重定向mktime,拓展到64位
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
    //重定向localtime,拓展到64位
    tm *localtime(const time_t *timer)
    {
        static tm temp;
        _localtime_r(timer, &temp);
        return &temp;
    }
    //重定向_localtime_r,拓展到64位
    tm *_localtime_r(const time_t *timer, tm *result)
    {
        time_t t = *timer + TimeZone * 60 * 60;
        //确定时分秒
        //时
        result->tm_hour = t % (24 * 60 * 60) / (60 * 60);
        //分
        result->tm_min = t % (60 * 60) / 60;
        //秒
        result->tm_sec = t % 60;
        //计算天数
        t /= (24 * 60 * 60);
        //星期 (1970-1-1 星期四)
        result->tm_wday = (t + 4) % 7;
        //从1970年开始计算
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
        //年份
        result->tm_year -= 1;
        t -= days_between_years(result->tm_year, 1970);
        result->tm_year -= 1900;
        //一年中第几天
        result->tm_yday = t;
        result->tm_mday = t;
        //月份
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
        //将天数归置为1~31的标准
        result->tm_mday++;
        return result;
    }
    //重定向tzset,但是此版本库中没有
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
    //初始化RTC
    rtc_init();
    //记录系统启动时间
    record_start_time();
    //初始化串口
    usart_init();
    //初始化信号灯
    led_init();
}
//获取系统运行时间
uint32_t system_time()
{
    return (uint32_t)time(0) - system_start_time;
}
//获取毫秒级系统运行时间
uint32_t system_time_ms()
{
    clock_t start_clock = (system_start_time + 1) * RTC_x.GetPrescaler();
    return difftime(start_clock, clock()) * 1000;
}
//系统级延时,单位s
void system_delay(uint32_t s)
{
    SysTick_Operate::Delay(s, (uint32_t)RCC_Operate::Get_SYSCLK_Frequency());
}
//系统级延时,单位ms
void system_delay_ms(uint32_t ms)
{
    SysTick_Operate::Delay_ms(ms);
}