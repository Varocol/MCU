#include "TIM.h"
/**
 * @brief  TIM-���췽��
 * @param  None
 * @retval None
 */
TIM::TIM()
{
}

/**
 * @brief  TIM-��������
 * @param  None
 * @retval None
 */
TIM::~TIM()
{
}

/**
 * @brief  TIM-���췽��
 * @param  TIMx_Parma   TIM��ʼ�������б�
 * @retval None
 */
TIM::TIM(TIM_Parma TIMx_Parma)
{
  Set_TIM_Parma(TIMx_Parma);
}

/**
 * @brief  TIM-���ò����б���
 * @param  TIMx_Parma   TIM��ʼ�������б�
 * @retval None
 */
void TIM::Set_TIM_Parma(TIM_Parma TIMx_Parma)
{
  this->TIMx_Parma = TIMx_Parma;
}

/**
 * @brief  TIM-���²����б���
 * @param  TIMx_Parma   TIM��ʼ�������б�
 * @retval None
 */
void TIM::Update(TIM_Parma TIMx_Parma)
{
  TIM_DeInit(TIMx_Parma.TIMx);
  Set_TIM_Parma(TIMx_Parma);
  Init();
}

/**
 * @brief  TIM-ͨ����GPIO���ų�ʼ��
 * @param  TIMx_Parma   TIM��ʼ�������б�
 * @retval None
 */
void TIM::Pin_Init()
{
  // ���ǵ���̫�����,�����и�����Ҫ��������(CHx,CHxN,BKIN,ETR)
  //  CHN (eg: TIM2 CH1 PA0 PWM���)
  {
      // GPIO_InitTypeDef GPIO_InitStructure =
      //     {
      //         GPIO_Pin_0,
      //         GPIO_Speed_50MHz,
      //         GPIO_Mode_AF_PP};
      // GPIO TIM2_CH1_PA0 = GPIO(GPIOA, GPIO_InitStructure);
      // TIM2_CH1_PA0.Init();
  }
  // CHxN
  {

  }
  // BKIN
  {

  }
  // ETR
  {
  }
}

/**
 * @brief  TIM-����������ʼ������
 * @param  None
 * @retval None
 */
void TIM::Base_Init()
{
  // ��ʼ����ʱ����������
  TIM_TimeBaseInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_TimeBaseStructure);
}

/**
 * @brief  TIM-OCͨ����ʼ������
 * @param  None
 * @retval None
 */
void TIM::OC_Init()
{
  // ����OCͨ��
  switch (TIMx_Parma.OCx)
  {
  case OC1:
    TIM_OC1Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC2:
    TIM_OC2Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC3:
    TIM_OC3Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  case OC4:
    TIM_OC4Init(TIMx_Parma.TIMx, &TIMx_Parma.TIM_OCStructure);
    break;
  }
}

/**
 * @brief  TIM-IC��ʼ������
 * @param  None
 * @retval None
 */
void TIM::IC_Init()
{
  TIM_ICInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_ICStructure);
}

/**
 * @brief  TIM-��ʼ������
 * @param  None
 * @retval None
 */
void TIM::Init()
{
  // ϵͳʱ�ӷ���������TIMxʱ��
  RCC_Operate::RCC_Config(TIMx_Parma.TIMx, ENABLE);
  // TIMx�Ĵ�����λ
  TIM_DeInit(TIMx_Parma.TIMx);
  // ������������
  Pin_Init();
  // ���û�������
  Base_Init();
  // ����ͨ������
  OC_Init();
  // ����IC����
  IC_Init();
  // �����ʱ���жϱ�־λ
  TIM_ClearFlag(TIMx_Parma.TIMx, TIM_FLAG_Update);
  // ���ü�ʱ���ж�
  ITConfig(TIMx_Parma.TIM_IT_Selection, TIMx_Parma.TIM_IT_State);
  // ������ʱ��
  Enable();
}

/**
 * @brief  TIM-�жϷ���
 * @param  TIM_IT       �жϱ�־��ѡ��
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void TIM::ITConfig(uint16_t TIM_IT, FunctionalState NewState)
{
  // NVIC����
  TIMx_Parma.TIM_NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Operate(TIMx_Parma.TIM_NVIC_InitStructure).Init();
  TIM_ITConfig(TIMx_Parma.TIMx, TIM_IT, NewState);
}

/**
 * @brief  TIM-����TIM����
 * @param  None
 * @retval None
 */
void TIM::Enable()
{
  TIM_Cmd(TIMx_Parma.TIMx, ENABLE);
}

/**
 * @brief  TIM-�ر�TIM����
 * @param  None
 * @retval None
 */
void TIM::Disable()
{
  TIM_Cmd(TIMx_Parma.TIMx, DISABLE);
}
