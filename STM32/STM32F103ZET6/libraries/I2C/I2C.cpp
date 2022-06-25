#include "I2C.h"
//I2C1_Default I2C_SCL = PB6
GPIO_InitTypeDef I2C1_SCL_Pin_1 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Default I2C_SDA = PB7
GPIO_InitTypeDef I2C1_SDA_Pin_1 =
    {
        GPIO_Pin_7,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Remap   I2C_SCL = PB8
GPIO_InitTypeDef I2C1_SCL_Pin_2 =
    {
        GPIO_Pin_8,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Remap   I2C_SDA = PB9
GPIO_InitTypeDef I2C1_SDA_Pin_2 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C2_Default I2C_SCL = PB10
GPIO_InitTypeDef I2C2_SCL_Pin =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C2_Default I2C_SDA = PB11
GPIO_InitTypeDef I2C2_SDA_Pin =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};
/**
  * @brief  I2C�չ��췽��
  * @param  None
  * @retval None
  */
I2C::I2C()
{
}

/**
  * @brief  I2C���췽��
  * @param  I2Cx_Param:I2C�Ĳ����б�
  * @retval None
  */
I2C::I2C(I2C_Param I2Cx_Param)
{
  Set_I2C_Param(I2Cx_Param);
}

/**
  * @brief  I2C��������
  * @param  None
  * @retval None
  */
I2C::~I2C()
{
}

/**
  * @brief  I2C GPIO���ų�ʼ��
  * @param  None
  * @retval None
  */
void I2C::Pin_Init()
{
  //��Ӳ������û�и���ߵ�ƽ���Կ����ڲ�����(IN_MODE)
  //I2C1_SCL = PB8    I2C1_SDA = PB9
  if (I2Cx_Param.I2C_Pin_Remap_Selection == I2C1_Remap)
  {
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
    //������,��©
    GPIO *I2C1_SCL = new GPIO(GPIOB, I2C1_SCL_Pin_2);
    I2C1_SCL->IN_MODE();
    I2C1_SCL->Update(GPIOB, I2C1_SCL_Pin_2);
    delete I2C1_SCL;
    //������,��©
    GPIO *I2C1_SDA = new GPIO(GPIOB, I2C1_SDA_Pin_2);
    I2C1_SDA->IN_MODE();
    I2C1_SDA->Update(GPIOB, I2C1_SDA_Pin_2);
    delete I2C1_SDA;
  }
  else if (I2Cx_Param.I2C_Pin_Remap_Selection == I2C_Default)
  {
    //I2C1_SCL = PB6    I2C1_SDA = PB7
    if (I2Cx_Param.I2Cx == I2C1)
    {
      //������,��©
      GPIO *I2C1_SCL = new GPIO(GPIOB, I2C1_SCL_Pin_1);
      I2C1_SCL->IN_MODE();
      I2C1_SCL->Update(GPIOB, I2C1_SCL_Pin_1);
      delete I2C1_SCL;
      //������,��©
      GPIO *I2C1_SDA = new GPIO(GPIOB, I2C1_SDA_Pin_1);
      I2C1_SDA->IN_MODE();
      I2C1_SDA->Update(GPIOB, I2C1_SDA_Pin_1);
      delete I2C1_SDA;
    }
    // I2C2_SCL = PB10    I2C2_SDA = PB11
    else if (I2Cx_Param.I2Cx == I2C2)
    {
      //������,��©
      GPIO *I2C2_SCL = new GPIO(GPIOB, I2C2_SCL_Pin);
      I2C2_SCL->IN_MODE();
      I2C2_SCL->Update(GPIOB, I2C2_SCL_Pin);
      delete I2C2_SCL;
      //������,��©
      GPIO *I2C2_SDA = new GPIO(GPIOB, I2C2_SDA_Pin);
      I2C2_SDA->IN_MODE();
      I2C2_SDA->Update(GPIOB, I2C2_SDA_Pin);
      delete I2C2_SDA;
    }
  }
}

/**
  * @brief  I2C ��ʼ������
  * @param  None
  * @retval None
  */
void I2C::Init()
{
  //����I2Cʱ��
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, ENABLE);
  //I2C�Ĵ�����λ
  I2C_DeInit(I2Cx_Param.I2Cx);
  //�����λ,����ͨѶʧ�ܺ�λBusy
  Software_Reset(ENABLE);
  Software_Reset(DISABLE);
  //���ų�ʼ��
  Pin_Init();
  //����I2C
  I2C_Init(I2Cx_Param.I2Cx, &I2Cx_Param.I2C_InitStructure);
  //����I2C�ж����ȼ�
  I2Cx_Param.I2C_ER_NVIC_Operate.Init();
  I2Cx_Param.I2C_EV_NVIC_Operate.Init();
  //����I2C�ж�
  I2C_ITConfig(I2Cx_Param.I2Cx, I2Cx_Param.I2C_IT_Selection, I2Cx_Param.I2C_IT_State);
  //ʹ��I2C
  Start();
}

/**
  * @brief  ����I2C����(I2Cʹ��)
  * @param  None
  * @retval None
  */
void I2C::Start()
{
  I2C_Cmd(I2Cx_Param.I2Cx, ENABLE);
}

/**
  * @brief  �ر�I2C����(I2Cʧ��)
  * @param  None
  * @retval None
  */
void I2C::ShutUp()
{
  I2C_Cmd(I2Cx_Param.I2Cx, DISABLE);
}

/**
  * @brief  I2C�����б����
  * @param  I2Cx_Param:I2C�Ĳ����б�
  * @retval None
  */
void I2C::Update(I2C_Param I2Cx_Param)
{
  I2C_DeInit(I2Cx_Param.I2Cx);
  Set_I2C_Param(I2Cx_Param);
  Init();
}

/**
  * @brief  ����I2C�Ĳ����б�
  * @param  I2Cx_Param:I2C�Ĳ����б�
  * @retval None
  */
void I2C::Set_I2C_Param(I2C_Param I2Cx_Param)
{
  this->I2Cx_Param = I2Cx_Param;
}

/**
  * @brief  I2C������ʼ����
  * @param  NewState:��ʼ������״̬
  * @retval None
  */
void I2C::Generate_START(FunctionalState NewState)
{
  I2C_GenerateSTART(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C������������
  * @param  NewState:����������״̬
  * @retval None
  */
void I2C::Generate_STOP(FunctionalState NewState)
{
  I2C_GenerateSTOP(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C����¼�
  * @param  Event:�¼�ö������
  * @retval �¼�״̬
  */
ErrorStatus I2C::Check_Event(I2C_Event Event)
{
  return I2C_CheckEvent(I2Cx_Param.I2Cx, Event);
}

/**
  * @brief  I2C����7λ��ַ����
  * @param  Addr:��ַ
  * @param  I2C_Direction:���䷽��
  * @retval None
  */
void I2C::Send7bitAddress(uint8_t Addr, uint8_t I2C_Direction)
{
  I2C_Send7bitAddress(I2Cx_Param.I2Cx, Addr, I2C_Direction);
}

/**
  * @brief  I2C����8λ����
  * @param  Data:����
  * @retval None
  */
void I2C::SendData(uint8_t Data)
{
  I2C_SendData(I2Cx_Param.I2Cx, Data);
}

/**
  * @brief  I2C����8λ����
  * @param  None
  * @retval Data:����
  */
uint8_t I2C::ReceiveData()
{
  return I2C_ReceiveData(I2Cx_Param.I2Cx);
}

/**
  * @brief  I2C����Ӧ���ź�
  * @param  NewState:Ӧ����״̬
  * @retval None
  */
void I2C::AcknowledgeConfig(FunctionalState NewState)
{
  I2C_AcknowledgeConfig(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C��ȡ��־λ����
  * @param  I2C_FLAG:I2C��־λ
  * @retval ��־λ״̬
  */
FlagStatus I2C::GetFlagStatus(uint32_t I2C_FLAG)
{
  return I2C_GetFlagStatus(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
  * @brief  I2C�����־λ
  * @param  I2C_FLAG:I2C��־λ
  * @retval None
  */
void I2C::ClearFlag(uint32_t I2C_FLAG)
{
  I2C_ClearFlag(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
  * @brief  I2C�����λ(���Ա�����Ϊǰһ��ͨѶʧ�ܺ�Busyλһֱ��1)
  * @param  None
  * @retval None
  */
void I2C::Software_Reset(FunctionalState NewState)
{
  I2C_SoftwareResetCmd(I2Cx_Param.I2Cx, NewState);
}