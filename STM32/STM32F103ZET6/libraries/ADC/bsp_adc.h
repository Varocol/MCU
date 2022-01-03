#ifndef __BSP_ADC_H
#define __BSP_ADC_H
#include "bsp_conf.h"
#define  ADCx  ADC1 
#define  ADC_Channel_Pin    GPIOA
#define  ADC_Channel_Port   GPIO_Pin_0
void     ADC_Config();
#endif  /*__BSP_ADC_H*/