#include "TIM.h"
//TIM����������ʼ���ṹ��
TIM_TimeBaseInitTypeDef TIM2_TimeBaseStructure =
    {
        RCC_Operate::Get_SYSCLK_Frequency() / 1000000, //72
        TIM_CounterMode_Up,
        999,          //��1000��,����ÿ��1ms
        TIM_CKD_DIV1, //�����ź��˲�Ƶ��
        0,            //�ظ�����,ֻ��ͨ�ú͸߼���ʱ������
};
//TIMͨ����ʼ���ṹ��
TIM_OCInitTypeDef TIM2_OCStructure =
    {
        TIM_OCMode_PWM1,          //ͨ��ģʽ
        TIM_OutputState_Enable,   //����/����ʹ��(OCx)
        TIM_OutputNState_Disable, //����/�������ʹ��,ֻ�и߼���ʱ������(OCxN)
        500,                      //CCRx��ֵ,��������ռ�ձ�
        TIM_OCPolarity_High,      //����/������,�ߵ�ƽ��Ч(OCx)
        TIM_OCNPolarity_High,     //����/���񻥲��������,�ߵ�ƽ��Ч(OCNx)
        TIM_OCIdleState_Reset,    //�������״̬(OCx)
        TIM_OCNIdleState_Reset    //�������״̬(OCxN)
};
//NVIC�жϳ�ʼ���ṹ��
NVIC_InitTypeDef TIM2_NVIC_Structure =
    {
        TIM2_IRQn,
        0,
        5,
        ENABLE};
//NVIC�ж϶���
NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(&TIM2_NVIC_Structure);

//TIM2��ʼ������
TIM_Parma TIM2_Parma =
    {
        TIM2,
        TIM2_TimeBaseStructure,
        TIM2_OCStructure,
        TIM2_NVIC_Operate,
        ENABLE,
        TIM_IT_Update,
        OC1};

//TIM2����
TIM TIM_2 = TIM(TIM2_Parma);

/**
  * @brief  TIM���캯��
  * @param  None
  * @retval None
  */
TIM::TIM()
{
}

/**
  * @brief  TIM��������
  * @param  None
  * @retval None
  */
TIM::~TIM()
{
}

/**
  * @brief  TIM���캯��
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
TIM::TIM(TIM_Parma TIMx_Parma)
{
  Set_TIM_Parma(TIMx_Parma);
}

/**
  * @brief  TIM��̬���뼶��ʱ����
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
void TIM::Delay_ms(uint32_t ms)
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
  NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(&NVIC_InitStructure);
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
bool TIM::Delay_Complete()
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

/**
  * @brief  TIM���ò����б���
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
void TIM::Set_TIM_Parma(TIM_Parma TIMx_Parma)
{
  this->TIMx_Parma = TIMx_Parma;
}

/**
  * @brief  TIM���²����б���
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
void TIM::Update(TIM_Parma TIMx_Parma)
{
  TIM_DeInit(TIMx_Parma.TIMx);
  Set_TIM_Parma(TIMx_Parma);
  Init();
}

/**
  * @brief  TIMͨ����GPIO���ų�ʼ��
  * @param  TIMx_Parma:TIM��ʼ�������б�
  * @retval None
  */
void TIM::Pin_Init()
{
  //���ǵ���̫�����,�����и�����Ҫ��������(CHx,CHxN,BKIN,ETR)
  //CHN (eg: TIM2 CH1 PA0 PWM���)
  {
    GPIO_InitTypeDef GPIO_InitStructure =
        {
            GPIO_Pin_0,
            GPIO_Speed_50MHz,
            GPIO_Mode_AF_PP};
    GPIO TIM2_CH1_PA0 = GPIO(GPIOA, GPIO_InitStructure);
    TIM2_CH1_PA0.Init();
  }
  //CHxN
  {

  }
  //BKIN
  {

  }
  //ETR
  {
  }
}

/**
  * @brief  TIM����������ʼ������
  * @param  None
  * @retval None
  */
void TIM::Base_Init()
{
  // ��ʼ����ʱ����������
  TIM_TimeBaseInit(TIMx_Parma.TIMx, &TIMx_Parma.TIM_TimeBaseStructure);
}

/**
  * @brief  TIMOCͨ����ʼ������
  * @param  None
  * @retval None
  */
void TIM::OC_Init()
{
  //������������
  Pin_Init();
  //����OCͨ��
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
  * @brief  TIM��ʼ������
  * @param  None
  * @retval None
  */
void TIM::Init()
{
  // ϵͳʱ�Ӻ���������TIMxʱ��
  RCC_Operate::RCC_Config(TIMx_Parma.TIMx, ENABLE);
  // TIMx�Ĵ�����λ
  TIM_DeInit(TIMx_Parma.TIMx);
  //���û�������
  Base_Init();
  //����ͨ������
  OC_Init();
  // �����ʱ���жϱ�־λ/
  TIM_ClearFlag(TIMx_Parma.TIMx, TIM_FLAG_Update);
  // ���ü�ʱ���ж�
  TIM_ITConfig(TIMx_Parma.TIMx, TIMx_Parma.TIM_IT_Selection, TIMx_Parma.TIM_IT_State);
  //NVIC����
  TIMx_Parma.TIM_NVIC_Operate.Init();
  //������ʱ��
  Start();
}

/**
  * @brief  ����TIM����
  * @param  None
  * @retval None
  */
void TIM::Start()
{
  TIM_Cmd(TIMx_Parma.TIMx, ENABLE);
}

/** @brief  �ر�TIM����
  * @param  None
  * @retval None
  */
void TIM::Shutup()
{
  TIM_Cmd(TIMx_Parma.TIMx, DISABLE);
}
