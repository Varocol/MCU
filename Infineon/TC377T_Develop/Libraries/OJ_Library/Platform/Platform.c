#include "Platform.h"

/*
 * @brief       平台ms级延时函数
 * @param       time        延时时间(ms)
 * @return      void
 */
void platform_delay_ms (uint32 time)
{
    systick_delay_ms(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       平台ms级延时函数
 * @param       time        延时时间(us)
 * @return      void
 */
void platform_delay_us (uint32 time)
{
    systick_delay_us(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       平台ms级延时函数
 * @param       time        延时时间(ns)
 * @return      void
 */
void platform_delay_ns (uint32 time)
{
    systick_delay_ns(PLATFORM_DELAY_STM, time);
}

/*
 * @brief       平台ms级获取时间函数
 * @param       time        延时时间(ms)
 * @return      void
 */
uint32 platform_getval_ms ()
{
    return systick_getval_ms(PLATFORM_GET_TIME_STM);
}

/*
 * @brief       平台us级获取时间函数
 * @param       time        延时时间(us)
 * @return      void
 */
uint32 platform_getval_us ()
{
    return systick_getval_us(PLATFORM_GET_TIME_STM);
}

/*
 * @brief       平台ns级获取时间函数
 * @param       time        延时时间(ns)
 * @return      void
 */
uint32 platform_getval_ns ()
{
    return systick_getval_ns(PLATFORM_GET_TIME_STM);
}

