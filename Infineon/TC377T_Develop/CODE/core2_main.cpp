#include "core2_main.h"

void core2_setup ()
{

}

void core2_loop ()
{
    if (run_flag)
    {
        Encoder_Read();             //��ȡ�ٶ�
        Get_Mid_Bias();             //��ȡ����ƫ��
        MidBias_FitTurnR();         //��ȡת��뾶��ת����ٶ�
        Servo_Control();            //���ת��
        Motor_Control();            //�ٶȿ���
    }
}

