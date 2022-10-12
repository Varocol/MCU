#include "I2C.h"
/**
 * @brief  I2C-�չ��췽��
 * @param  None
 * @retval None
 */
I2C::I2C()
{
}

/**
 * @brief  I2C-���췽��
 * @param  I2Cx_Param     I2C�Ĳ����б�
 * @retval None
 */
I2C::I2C(I2C_Param I2Cx_Param)
{
  Set_I2C_Param(I2Cx_Param);
}

/**
 * @brief  I2C-��������
 * @param  None
 * @retval None
 */
I2C::~I2C()
{
}

/**
 * @brief  I2C-GPIO���ų�ʼ��
 * @param  None
 * @retval None
 */
void I2C::Pin_Init()
{
  //��Ӳ������û�и���ߵ�ƽ���Կ����ڲ�����(IN_MODE)
  GPIO I2C_SCL = GPIO();
  GPIO I2C_SDA = GPIO();
  //��SCL��SDA��������,��©
  if (I2Cx_Param.I2C_Pin_Remap == I2C1_Remap && I2Cx_Param.I2Cx == I2C1)
  {
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
    I2C_SCL.Set_GPIO_Param(PB8);
    I2C_SCL.IN_MODE();
    I2C_SCL.Update(PB8, GPIO_Mode_AF_OD);
    I2C_SDA.Set_GPIO_Param(PB9);
    I2C_SDA.IN_MODE();
    I2C_SDA.Update(PB8, GPIO_Mode_AF_OD);
  }
  else if (I2Cx_Param.I2C_Pin_Remap == I2C_Default)
  {
    if (I2Cx_Param.I2Cx == I2C1)
    {
      I2C_SCL.Set_GPIO_Param(PB6);
      I2C_SCL.IN_MODE();
      I2C_SCL.Update(PB6, GPIO_Mode_AF_OD);
      I2C_SDA.Set_GPIO_Param(PB7);
      I2C_SDA.IN_MODE();
      I2C_SDA.Update(PB7, GPIO_Mode_AF_OD);
    }
    else if (I2Cx_Param.I2Cx == I2C2)
    {
      I2C_SCL.Set_GPIO_Param(PB10);
      I2C_SCL.IN_MODE();
      I2C_SCL.Update(PB10, GPIO_Mode_AF_OD);
      I2C_SDA.Set_GPIO_Param(PB11);
      I2C_SDA.IN_MODE();
      I2C_SDA.Update(PB11, GPIO_Mode_AF_OD);
    }
  }
}

/**
 * @brief  I2C-��ʼ������
 * @param  None
 * @retval None
 */
void I2C::Init()
{
  //����I2Cʱ��
  RCC_Enable();
  // I2C�Ĵ�����λ
  I2C_DeInit(I2Cx_Param.I2Cx);
  //�����λ,����ͨѶʧ�ܺ�λBusy
  Software_Reset(ENABLE);
  Software_Reset(DISABLE);
  //���ų�ʼ��
  Pin_Init();
  //����I2C
  I2C_Init(I2Cx_Param.I2Cx, &I2Cx_Param.I2C_InitStructure);
  //����I2C�ж����ȼ�
  NVIC_Operate(I2Cx_Param.I2C_ER_NVIC_InitStructure).Init();
  NVIC_Operate(I2Cx_Param.I2C_EV_NVIC_InitStructure).Init();
  //����I2C�ж�
  ITConfig(I2Cx_Param.I2C_IT_Selection, I2Cx_Param.I2C_IT_State);
  //����DMA
  DMACmd(I2Cx_Param.I2C_DMA_State);
  //ʹ��I2C
  Enable();
}

/**
 * @brief  I2C-����I2C����(I2Cʹ��)
 * @param  None
 * @retval None
 */
void I2C::Enable()
{
  I2C_Cmd(I2Cx_Param.I2Cx, ENABLE);
}

/**
 * @brief  I2C-�ر�I2C����(I2Cʧ��)
 * @param  None
 * @retval None
 */
void I2C::Disable()
{
  I2C_Cmd(I2Cx_Param.I2Cx, DISABLE);
}

/**
 * @brief  I2C-ʹ��/ʧ��DMA����
 * @param  I2Cx_Param     I2C�Ĳ����б�
 * @retval None
 */
void I2C::DMACmd(FunctionalState NewState)
{
  I2C_DMACmd(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-�����б����
 * @param  I2Cx_Param     I2C�Ĳ����б�
 * @retval None
 */
void I2C::Update(I2C_Param I2Cx_Param)
{
  I2C_DeInit(I2Cx_Param.I2Cx);
  Set_I2C_Param(I2Cx_Param);
  Init();
}

/**
 * @brief  I2C-�жϷ���
 * @param  I2C_IT         �жϱ�־��ѡ��
 * @param  NewState       ʹ�ܻ�ʧ��
 * @retval None
 */
void I2C::ITConfig(uint16_t I2C_IT, FunctionalState NewState)
{
  I2C_ITConfig(I2Cx_Param.I2Cx, I2C_IT, NewState);
}

/**
 * @brief  I2C-����I2C�Ĳ����б�
 * @param  I2Cx_Param     I2C�Ĳ����б�
 * @retval None
 */
void I2C::Set_I2C_Param(I2C_Param I2Cx_Param)
{
  this->I2Cx_Param = I2Cx_Param;
}

/**
 * @brief  I2C-������ʼ����
 * @param  NewState       ��ʼ������״̬
 * @retval None
 */
void I2C::Generate_START(FunctionalState NewState)
{
  I2C_GenerateSTART(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-������������
 * @param  NewState       ����������״̬
 * @retval None
 */
void I2C::Generate_STOP(FunctionalState NewState)
{
  I2C_GenerateSTOP(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-����¼�
 * @param  Event          �¼�ö������
 * @retval �¼�״̬
 */
ErrorStatus I2C::Check_Event(I2C_Event Event)
{
  return I2C_CheckEvent(I2Cx_Param.I2Cx, Event);
}

/**
 * @brief  I2C-����7λ��ַ����
 * @param  Addr           ��ַ
 * @param  I2C_Direction  ���䷽��
 * @retval None
 */
void I2C::Send7bitAddress(uint8_t Addr, uint8_t I2C_Direction)
{
  I2C_Send7bitAddress(I2Cx_Param.I2Cx, Addr, I2C_Direction);
}

/**
 * @brief  I2C-����8λ����
 * @param  Data           ����
 * @retval None
 */
void I2C::SendData(uint8_t Data)
{
  I2C_SendData(I2Cx_Param.I2Cx, Data);
}

/**
 * @brief  I2C-����8λ����
 * @param  None
 * @retval 8λ����
 */
uint8_t I2C::ReceiveData()
{
  return I2C_ReceiveData(I2Cx_Param.I2Cx);
}

/**
 * @brief  I2C-����Ӧ���ź�
 * @param  NewState       Ӧ����״̬
 * @retval None
 */
void I2C::AcknowledgeConfig(FunctionalState NewState)
{
  I2C_AcknowledgeConfig(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-��ȡ��־λ����
 * @param  I2C_FLAG       I2C��־λ
 * @retval ��־λ״̬
 */
FlagStatus I2C::GetFlagStatus(uint32_t I2C_FLAG)
{
  return I2C_GetFlagStatus(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
 * @brief  I2C-�����־λ
 * @param  I2C_FLAG       I2C��־λ
 * @retval None
 */
void I2C::ClearFlag(uint32_t I2C_FLAG)
{
  I2C_ClearFlag(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
 * @brief  I2C-�����λ(���Ա�����Ϊǰһ��ͨѶʧ�ܺ�Busyλһֱ��1)
 * @param  None
 * @retval None
 */
void I2C::Software_Reset(FunctionalState NewState)
{
  I2C_SoftwareResetCmd(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-����I2Cʱ�ӷ���
 * @param  None
 * @retval None
 */
void I2C::RCC_Enable()
{
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, ENABLE);
}
/**
 * @brief  I2C-�ر�I2Cʱ�ӷ���
 * @param  None
 * @retval None
 */

void I2C::RCC_Disable()
{
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, DISABLE);
}

/**
 * @brief  I2C-����I2Cʱ�ӷ���
 * @param  None
 * @retval None
 */
void I2C::RCC_Enable(I2C_TypeDef *I2Cx)
{
  RCC_Operate::RCC_Config(I2Cx, ENABLE);
}

/**
 * @brief  I2C-�ر�I2Cʱ�ӷ���
 * @param  None
 * @retval None
 */
void I2C::RCC_Disable(I2C_TypeDef *I2Cx)
{
  RCC_Operate::RCC_Config(I2Cx, DISABLE);
}