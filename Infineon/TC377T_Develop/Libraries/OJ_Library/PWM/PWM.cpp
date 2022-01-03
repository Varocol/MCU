#include "PWM.h"

/*
 * @brief       PWM空构造方法
 * @param       void
 * @return      null
 */
PWM::PWM ()
{

}

/*
 * @brief       PWM析构方法
 * @param       void
 * @return      null
 */
PWM::~PWM ()
{

}

/*
 * @brief       PWM带参构造方法
 * @param       pwmch       pwm通道
 * @param       freq        通道频率
 * @param       duty        通道占空比(float型百分比,例如23.5%)
 * @return      null
 */
PWM::PWM (ATOM_PIN_enum pwmch, uint32 freq, float32 percent)
{
    Set_Param(pwmch, freq, percent);
}

/*
 * @brief       PWM设置参数方法
 * @param       pwmch       pwm通道
 * @param       freq        通道频率
 * @param       duty        通道占空比(float型百分比,例如23.5%)
 * @return      void
 */
void PWM::Set_Param (ATOM_PIN_enum pwmch, uint32 freq, float32 percent)
{
    Set_Pin(pwmch);
    Set_Freq(freq);
    Set_Percent(percent);
}

/*
 * @brief       PWM设置输出通道
 * @param       pwmch         输出通道(引脚)
 * @return      void
 */
void PWM::Set_Pin (ATOM_PIN_enum pwmch)
{
    this->pwmch = pwmch;
}

/*
 * @brief       PWM设置频率
 * @param       freq          PWM频率
 * @return      void
 */
void PWM::Set_Freq (uint32 freq)
{
    this->freq = freq;
}

/*
 * @brief       PWM设置占空比
 * @param       duty          通道占空比(float型百分比,例如23.5%)
 * @return      void
 */
void PWM::Set_Percent (float32 percent)
{
    //限制percent的范围
    percent = percent < 0 ? 0 : percent > 100 ? 100 : percent;
    this->percent = percent;
}

/*
 * @brief       PWM初始化
 * @param       null
 * @return      void
 */
void PWM::Init ()
{
    g_atomDriver = gtm_pwm_get_g_atomDriver(pwmch, freq, persent2duty(percent));
    gtm_pwm_start(&g_atomDriver,TRUE);
}

/*
 * @brief       PWM开始
 * @param       null
 * @return      void
 */
void PWM::Start()
{
    gtm_pwm_start(&g_atomDriver,TRUE);
}

/*
 * @brief       PWM停止
 * @param       null
 * @return      void
 */
void PWM::Stop()
{
    gtm_pwm_stop(&g_atomDriver,TRUE);
}

/*
 * @brief       PWM更新占空比(立刻生效)
 * @param       duty          通道占空比(float型百分比,例如23.5%)
 * @return      void
 */
void PWM::Update_Percent (float32 percent)
{
    Set_Percent(percent);
    pwm_duty(pwmch, persent2duty(percent));
}

/*
 * @brief       占空比的百分值转数值
 * @param       null
 * @return      void
 */
uint32 PWM::persent2duty (float32 percent)
{
    switch (gtm_atom_mux(pwmch)->atom)
    {
        case 0 :
            return percent / 100 * GTM_ATOM0_PWM_DUTY_MAX;
        case 1 :
            return percent / 100 * GTM_ATOM1_PWM_DUTY_MAX;
        case 2 :
            return percent / 100 * GTM_ATOM2_PWM_DUTY_MAX;
        case 3 :
            return percent / 100 * GTM_ATOM3_PWM_DUTY_MAX;
        default :
            return 0;
    }
}
