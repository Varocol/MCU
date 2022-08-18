#include "Encoder.h"
void Encoder_Init ()
{
    gpt12_init(ECOUNTE_LEFT_Tx, ECOUNTE_LEFT_PIN1, ECOUNTE_LEFT_PIN2);     //左编码器初始化
    gpt12_init(ECOUNTE_RIGHT_Tx, ECOUNTE_RIGHT_PIN1, ECOUNTE_RIGHT_PIN2);   //右编码器初始化
}

void Encoder_Read ()
{
    speedl = gpt12_get(ECOUNTE_LEFT_Tx);
    speedr = gpt12_get(ECOUNTE_RIGHT_Tx);
    Left_ctr.currspeed = speedl;
    Right_ctr.currspeed = speedr;
    gpt12_clear(ECOUNTE_LEFT_Tx);
    gpt12_clear(ECOUNTE_RIGHT_Tx);
}
