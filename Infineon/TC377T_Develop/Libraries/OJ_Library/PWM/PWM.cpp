#include "PWM.h"

/*
 * @brief       PWM�չ��췽��
 * @param       void
 * @return      null
 */
PWM::PWM ()
{

}

/*
 * @brief       PWM��������
 * @param       void
 * @return      null
 */
PWM::~PWM ()
{

}

/*
 * @brief       PWM���ι��췽��
 * @param       pwmch       pwmͨ��
 * @param       freq        ͨ��Ƶ��
 * @param       duty        ͨ��ռ�ձ�(float�Ͱٷֱ�,����23.5%)
 * @return      null
 */
PWM::PWM (ATOM_PIN_enum pwmch, uint32 freq, float32 percent)
{
    Set_Param(pwmch, freq, percent);
}

/*
 * @brief       PWM���ò�������
 * @param       pwmch       pwmͨ��
 * @param       freq        ͨ��Ƶ��
 * @param       duty        ͨ��ռ�ձ�(float�Ͱٷֱ�,����23.5%)
 * @return      void
 */
void PWM::Set_Param (ATOM_PIN_enum pwmch, uint32 freq, float32 percent)
{
    Set_Pin(pwmch);
    Set_Freq(freq);
    Set_Percent(percent);
}

/*
 * @brief       PWM�������ͨ��
 * @param       pwmch         ���ͨ��(����)
 * @return      void
 */
void PWM::Set_Pin (ATOM_PIN_enum pwmch)
{
    this->pwmch = pwmch;
}

/*
 * @brief       PWM����Ƶ��
 * @param       freq          PWMƵ��
 * @return      void
 */
void PWM::Set_Freq (uint32 freq)
{
    this->freq = freq;
}

/*
 * @brief       PWM����ռ�ձ�
 * @param       duty          ͨ��ռ�ձ�(float�Ͱٷֱ�,����23.5%)
 * @return      void
 */
void PWM::Set_Percent (float32 percent)
{
    //����percent�ķ�Χ
    percent = percent < 0 ? 0 : percent > 100 ? 100 : percent;
    this->percent = percent;
}

/*
 * @brief       PWM��ʼ��
 * @param       null
 * @return      void
 */
void PWM::Init ()
{
    g_atomDriver = gtm_pwm_get_g_atomDriver(pwmch, freq, persent2duty(percent));
    gtm_pwm_start(&g_atomDriver,TRUE);
}

/*
 * @brief       PWM��ʼ
 * @param       null
 * @return      void
 */
void PWM::Start()
{
    gtm_pwm_start(&g_atomDriver,TRUE);
}

/*
 * @brief       PWMֹͣ
 * @param       null
 * @return      void
 */
void PWM::Stop()
{
    gtm_pwm_stop(&g_atomDriver,TRUE);
}

/*
 * @brief       PWM����ռ�ձ�(������Ч)
 * @param       duty          ͨ��ռ�ձ�(float�Ͱٷֱ�,����23.5%)
 * @return      void
 */
void PWM::Update_Percent (float32 percent)
{
    Set_Percent(percent);
    pwm_duty(pwmch, persent2duty(percent));
}

/*
 * @brief       ռ�ձȵİٷ�ֵת��ֵ
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
