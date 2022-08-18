#include "Libraries.h"
#include "bsp_led.h"
void Delay_ms(uint32_t ms); //����TIM2������ʱ,��Ҫ����delay_Complete���ж���ʱ�Ƿ����
bool Delay_Complete();      //��ʱ�Ƿ����
int main()
{
     // HSE_SetSysClock(RCC_PLLMul_9);
     LED_GPIOInit();
     LED.Pin_Off();
     while (1)
     {
          if (Delay_Complete())
          {
               Delay_ms(2000);
               LED.Set_Pin(flag);
          }
     }
}

/**
  * @brief  TIM��̬���뼶��ʱ����
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
void Delay_ms(uint32_t ms)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  //����TIM2ʱ��
  RCC_Operate::RCC_Config(TIM2, ENABLE);
  //TIM2�Ĵ�����λ
  TIM_DeInit(TIM2);
  //TIM���������ṹ��
  // ���ö�ʱ���ķ�Ƶ����(PSC)
  TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
  // ���ö�ʱ������װ�ؼĴ���(ARR)
  TIM_TimeBaseStructure.TIM_Period = (1000 - 1); // ���ֵ������ʱ����
  // ʱ�ӷ�Ƶ���ӣ�������ʱ��û��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // ����������ģʽ��������ʱ��ֻ�����ϼ�����û�м���ģʽ������
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // �ظ���������ֵ��������ʱ��û��
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // ��ʼ����ʱ��
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  // �����ʱ���жϱ�־λ/
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  // ������ʱ���ж�
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //NVIC����
  NVIC_InitTypeDef NVIC_InitStructure =
      {
          TIM2_IRQn,
          0,
          3,
          ENABLE};
  NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(NVIC_InitStructure);
  TIM2_NVIC_Operate.Init();
  //����ʱ��
  time_ms = ms;
  // ʹ�ܼ�����
  TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  �ж���ʱ�Ƿ���ɺ���
  * @param  None
  * @retval �Ƿ���ʱ����
  */
bool Delay_Complete()
{
  //���TIM2״̬
  if((!(TIM2->CR1 & TIM_CR1_CEN)) && current_time_ms == 0)
  {
    return true;
  }
  else 
  {
    return false;
  }
}