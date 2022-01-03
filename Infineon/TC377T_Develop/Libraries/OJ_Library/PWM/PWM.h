#ifndef __OJ_PWM_H
#define __OJ_PWM_H
#include "headfile.h"
class PWM
{
    private:
        ATOM_PIN_enum pwmch;                    //PWM 通道
        uint32 freq;                            //PWM 频率
        float32 percent;                        //PWM 占空比(百分制)
        uint32 persent2duty (float32 duty);
        IfxGtm_Atom_Pwm_Driver g_atomDriver;
    public:
        PWM ();
        ~PWM ();
        PWM (ATOM_PIN_enum pwmch, uint32 freq, float32 percent);
        void Set_Param (ATOM_PIN_enum pwmch, uint32 freq, float32 percent);
        void Set_Pin (ATOM_PIN_enum pwmch);
        void Set_Freq (uint32 freq);
        void Set_Percent (float32 percent);
        void Init ();
        void Start();
        void Stop();
        void Update_Percent (float32 percent);
};

#endif  /*__OJ_PWM_H*/
