#ifndef __PLATFORM_H
#define __PLATFORM_H
#include "headfile.h"
//用于统一输出和延时的函数以及一些统一变量
//所有的平台函数均兼容三核,主要是考虑到rtthread的函数不能兼容三核
//由于这些函数直接使用底层，所以被包含在了headfile.h内，使用起来更方便
//上面的宏定义不要轻易去改，尤其是第二个，否则会有点问题

#define PLATFORM_DELAY_STM STM0
#define PLATFORM_GET_TIME_STM  STM0
#define PLATFORM_OUTPUT_UART UART0

//平台串口输出
//全部使用UART0输出,如果检测到是核0调用，则使用rt_kprintf()
#define platform_printf(...)\
    if(IfxCpu_getCoreId() == IfxCpu_Id_0)\
        rt_kprintf(__VA_ARGS__);\
    else\
        printf (__VA_ARGS__)

//平台延时函数(3核均可使用)
//原理为如果检测到核0使用，则自动使用rtdelay，否则使用stm1延时
void platform_delay_ms (uint32 time);
void platform_delay_us (uint32 time);
void platform_delay_ns (uint32 time);

//平台获取时间函数
//默认使用stm0模块
uint32 platform_getval_ms ();
uint32 platform_getval_us ();
uint32 platform_getval_ns ();

extern uint8 Shift;
extern int16 Offset;
extern uint8 Img_Middle;
extern uint8 Road_Middle;
extern uint8 Img_Row_Min;
extern uint8 Img_Row_Max;
extern uint8 Beep_Flag;
extern uint32 start;
extern uint32 end;

#endif /*__OJ_PLATFORM_H*/
