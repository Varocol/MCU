#include "Platform.h"

/*
 * @brief       ƽ̨ms����ʱ����
 * @param       time        ��ʱʱ��(ms)
 * @return      void
 */
void platform_delay_ms (uint32 time)
{
    systick_delay_ms(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       ƽ̨ms����ʱ����
 * @param       time        ��ʱʱ��(us)
 * @return      void
 */
void platform_delay_us (uint32 time)
{
    systick_delay_us(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       ƽ̨ms����ʱ����
 * @param       time        ��ʱʱ��(ns)
 * @return      void
 */
void platform_delay_ns (uint32 time)
{
    systick_delay_ns(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       ƽ̨ms����ȡʱ�亯��
 * @param       time        ��ʱʱ��(ms)
 * @return      void
 */
uint32 platform_getval_ms ()
{
    return systick_getval_ms(PLATFORM_GET_TIME_STM);
}

/*
 * @brief       ƽ̨us����ȡʱ�亯��
 * @param       time        ��ʱʱ��(us)
 * @return      void
 */
uint32 platform_getval_us ()
{
    return systick_getval_us(PLATFORM_GET_TIME_STM);
}

/*
 * @brief       ƽ̨ns����ȡʱ�亯��
 * @param       time        ��ʱʱ��(ns)
 * @return      void
 */
uint32 platform_getval_ns ()
{
    return systick_getval_ns(PLATFORM_GET_TIME_STM);
}

