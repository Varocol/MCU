#include "NVIC.h"
/**
  * @brief  NVIC�չ��췽��
  * @retval None
  */
NVIC_Operate::NVIC_Operate()
{
}
/**
  * @brief  NVIC��������
  * @retval None
  */
NVIC_Operate::~NVIC_Operate()
{
}
/**
  * @brief  NVIC���췽��
  * @param  NVIC_InitStructure:NVIC��ʼ���ṹ��
  * @retval None
  */
NVIC_Operate::NVIC_Operate(NVIC_InitTypeDef *NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
}
/**
  * @brief  д��NVIC_PriorityGroup
  * @retval None
  */
void NVIC_Operate::PriorityGroupConfig()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
}
/**
  * @brief  ����NVIC��ʼ���ṹ��
  * @param  NVIC_InitStructure:NVIC��ʼ���ṹ��
  * @retval None
  */
void NVIC_Operate::Set_NVIC_InitStructure(NVIC_InitTypeDef *NVIC_InitStructure)
{
  this->NVIC_InitStructure = NVIC_InitStructure;
}
/**
  * @brief  NVIC���ø��º���
  * @param  NVIC_InitStructure:NVIC��ʼ���ṹ��
  * @retval None
  */
void NVIC_Operate::Update(NVIC_InitTypeDef *NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
  Init();
}
/**
  * @brief  NVIC��ʼ������
  * @retval None
  */
void NVIC_Operate::Init()
{
  PriorityGroupConfig();
  NVIC_Init(NVIC_InitStructure);
}
/**
  * @brief  ����NVIC����
  * @retval None
  */
void NVIC_Operate::Start()
{
  NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
  Init();
}
/**
  * @brief  �ر�NVIC����
  * @retval None
  */
void NVIC_Operate::ShutUp()
{
  NVIC_InitStructure->NVIC_IRQChannelCmd = DISABLE;
  Init();
}
