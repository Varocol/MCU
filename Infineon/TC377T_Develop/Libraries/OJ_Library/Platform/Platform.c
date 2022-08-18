#include "Platform.h"

//测试算法用的
//uint8 Shift = 0;
//int16 Offset = 0;

//智能车图像处理和控制需要的参量
//图像中线坐标
uint8 Img_Middle = MT9V03X_W / 2;
//赛道中线坐标
uint8 Road_Middle = MT9V03X_W / 2;
//寻中线行范围
uint8 Img_Row_Min = 0;
uint8 Img_Row_Max = MT9V03X_H;
//蜂鸣器标志位(0表示不响，1表示响)
uint8 Beep_Flag = 0;
//显示帧率所需的变量
uint32 start, end;
//智能车舵机角度
uint32 angle;
//智能车行驶速度
uint32 speed;


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

