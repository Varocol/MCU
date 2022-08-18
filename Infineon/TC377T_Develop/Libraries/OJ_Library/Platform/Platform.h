#ifndef __PLATFORM_H
#define __PLATFORM_H
#include "headfile.h"
//����ͳһ�������ʱ�ĺ����Լ�һЩͳһ����
//���е�ƽ̨��������������,��Ҫ�ǿ��ǵ�rtthread�ĺ������ܼ�������
//������Щ����ֱ��ʹ�õײ㣬ʹ������������
//����ĺ궨�岻Ҫ����ȥ�ģ������ǵڶ�����������е�����

#define PLATFORM_DELAY_STM STM0
#define PLATFORM_GET_TIME_STM  STM0
#define PLATFORM_OUTPUT_UART UART0

//ƽ̨�������
//ȫ��ʹ��UART0���,�����⵽�Ǻ�0���ã���ʹ��rt_kprintf()
#define platform_printf(...)\
        if(IfxCpu_getCoreId() == IfxCpu_Id_0)\
            rt_kprintf (__VA_ARGS__);\
        else\
            printf (__VA_ARGS__)


#ifdef __cplusplus
extern "C" {
#endif
//ƽ̨��ʱ����(3�˾���ʹ��)
//ԭ��Ϊ�����⵽��0ʹ�ã����Զ�ʹ��rtdelay������ʹ��stm1��ʱ
void platform_delay_ms (uint32 time);
void platform_delay_us (uint32 time);
void platform_delay_ns (uint32 time);

//ƽ̨��ȡʱ�亯��
//Ĭ��ʹ��stm0ģ��
uint32 platform_getval_ms ();
uint32 platform_getval_us ();
uint32 platform_getval_ns ();
#ifdef __cplusplus
}
#endif
#endif /*__OJ_PLATFORM_H*/
