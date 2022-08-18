#ifndef __ENCODER_H
#define __ENCODER_H
#include "headfile.h"
#include "Variables.h"
#define ECOUNTE_LEFT_Tx   GPT12_T5              //���ֱ�������ʱ��
#define ECOUNTE_LEFT_PIN1 GPT12_T5INB_P10_3     //���ֱ���������1
#define ECOUNTE_LEFT_PIN2 GPT12_T5EUDB_P10_1    //���ֱ���������2
#define ECOUNTE_RIGHT_Tx  GPT12_T6              //���ֱ�������ʱ��
#define ECOUNTE_RIGHT_PIN1 GPT12_T6INA_P20_3    //���ֱ���������1
#define ECOUNTE_RIGHT_PIN2 GPT12_T6EUDA_P20_0   //���ֱ���������2

void Encoder_Init ();
void Encoder_Read ();

#endif /*__ENCODER_H*/
