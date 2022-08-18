#include "NVIC.h"
/**
  * @brief  NVIC-�չ��췽��
  * @retval None
  */
NVIC_Operate::NVIC_Operate()
{
}
/**
  * @brief  NVIC-��������
  * @retval None
  */
NVIC_Operate::~NVIC_Operate()
{
}
/**
  * @brief  NVIC-���췽��
  * @param  NVIC_InitStructure    NVIC��ʼ���ṹ��
  * @retval None
  */
NVIC_Operate::NVIC_Operate(NVIC_InitTypeDef &NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
}
/**
  * @brief  NVIC-����NVIC��ʼ���ṹ��
  * @param  NVIC_InitStructure    NVIC��ʼ���ṹ��
  * @retval None
  */
void NVIC_Operate::Set_NVIC_InitStructure(NVIC_InitTypeDef &NVIC_InitStructure)
{
  this->NVIC_InitStructure = NVIC_InitStructure;
}
/**
  * @brief  NVIC-NVIC���ø��·���
  * @param  NVIC_InitStructure    NVIC��ʼ���ṹ��
  * @retval None
  */
void NVIC_Operate::Update(NVIC_InitTypeDef &NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
  Init();
}
/**
  * @brief  NVIC-��ʼ������
  * @param  None
  * @retval None
  */
void NVIC_Operate::Init()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  NVIC-����NVIC����
  * @param  None
  * @retval None
  */
void NVIC_Operate::Start()
{
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  Init();
}
/**
  * @brief  NVIC-�ر�NVIC����
  * @param  None
  * @retval None
  */
void NVIC_Operate::ShutUp()
{
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  Init();
}
