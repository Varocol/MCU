#include "GPIO.h"

/**
 * @brief  GPIO�չ��췽��
 * @retval None
 */
GPIO::GPIO()
{
}

/**
 * @brief  GPIO��������
 * @retval None
 */
GPIO::~GPIO()
{
}

/**
 * @brief  GPIO���캯��
 * @param  GPIOx:GPIO�˿�
 * @param  GPIO_Pin_x:GPIO����
 * @retval None
 */
GPIO::GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin_x)
{
  Set_GPIO(GPIOx);
  Set_GPIO_Pin(GPIO_Pin_x);
}

/**
 * @brief  GPIO���췽��
 * @param  GPIOx:GPIO�˿�
 * @param  GPIOInitStructure:GPIO��ʼ���ṹ��
 * @retval None
 */
GPIO::GPIO(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef GPIOInitStructure)
{
  Set_GPIO(GPIOx);
  Set_GPIOInitStructure(GPIOInitStructure);
}

/**
 * @brief  ����GPIO�˿�
 * @retval GPIOx
 */
GPIO_TypeDef *GPIO::Get_GPIOx()
{
  return GPIOx;
}

/**
 * @brief  ����GPIO��ʼ���ṹ��
 * @retval GPIOInitStructure
 */
GPIO_InitTypeDef GPIO::Get_GPIOInitStructure()
{
  return GPIOInitStructure;
}

/**
 * @brief  GPIO���ó�ʼ���ṹ��
 * @param  GPIOInitStructure:GPIO��ʼ���ṹ��
 * @retval None
 */
void GPIO::Set_GPIOInitStructure(GPIO_InitTypeDef GPIOInitStructure)
{
  this->GPIOInitStructure = GPIOInitStructure;
}

/**
 * @brief  GPIO����GPIO�˿�
 * @param  GPIOx:GPIO�˿�
 * @retval None
 */
void GPIO::Set_GPIO(GPIO_TypeDef *GPIOx)
{
  this->GPIOx = GPIOx;
}

/**
 * @brief  ����GPIO����
 * @param  GPIO_Pin_x:GPIO����
 * @retval None
 */
void GPIO::Set_GPIO_Pin(uint16_t GPIO_Pin_x)
{
  GPIOInitStructure.GPIO_Pin = GPIO_Pin_x;
}

/**
 * @brief  ���ö˿�����ֵ
 * @param  GPIO_Pin_x:GPIO����
 * @retval None
 */
void GPIO::Set_Port(uint16_t PortVal)
{
  GPIO_Write(GPIOx, PortVal);
}
/**
 * @brief  ��ʼ��GPIOΪ���ģʽ
 * @param  GPIOx:GPIO�˿�
 * @param  GPIO_Pin_x:GPIO����
 * @retval None
 */
void GPIO::OUT_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  ��ʼ��GPIOΪ����ģʽ
 * @param  GPIOx:GPIO�˿�
 * @param  GPIO_Pin_x:GPIO����
 * @retval None
 */
void GPIO::IN_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO pin������
 * @param  pin:pin��
 * @retval None
 */
void GPIO::Pin_On()
{
  GPIO_SetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO pin������
 * @param  pin:pin��
 * @retval None
 */
void GPIO::Pin_Off()
{
  GPIO_ResetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  ����Pin�ߵ�
 * @param  BitVal:״ֵ̬
 * @retval None
 */
void GPIO::Set_Pin(uint8_t BitVal)
{
  GPIO_WriteBit(GPIOx, GPIOInitStructure.GPIO_Pin, (BitAction)BitVal);
}

/**
 * @brief  ��ȡ�����Pin�ߵ�
 * @param  None
 * @retval pin�ڵĸߵ�
 */
BitAction GPIO::Get_Input_Pin()
{
  if (GPIO_ReadInputDataBit(GPIOx, GPIOInitStructure.GPIO_Pin) == 0x00)
  {
    return Bit_RESET;
  }
  else
  {
    return Bit_SET;
  }
}

/**
 * @brief  ��ȡ�����Pin�ߵ�
 * @param  None
 * @retval pin�ڵĸߵ�
 */
BitAction GPIO::Get_Output_Pin()
{
  if (GPIO_ReadOutputDataBit(GPIOx, GPIOInitStructure.GPIO_Pin) == 0x00)
  {
    return Bit_RESET;
  }
  else
  {
    return Bit_SET;
  }
}

/**
 * @brief  ��ȡ����Ķ˿�����
 * @param  None
 * @retval �˿�����
 */
uint16_t GPIO::Get_Input_Port()
{
  return GPIO_ReadInputData(GPIOx);
}

/**
 * @brief  ��ȡ����Ķ˿�����
 * @param  None
 * @retval �˿�����
 */
uint16_t GPIO::Get_Output_Port()
{
  return GPIO_ReadOutputData(GPIOx);
}

/**
 * @brief  GPIO���ø���
 * @param  GPIOx:GPIO�˿�
 * @param  GPIOInitStructure:GPIO��ʼ���ṹ��
 * @retval None
 */
void GPIO::Update(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef GPIOInitStructure)
{
  Set_GPIO(GPIOx);
  Set_GPIOInitStructure(GPIOInitStructure);
  Init();
}

/**
 * @brief  GPIO��ʼ������
 * @param  None
 * @retval None
 */
void GPIO::Init()
{
  Start();
  GPIO_Init(GPIOx, &GPIOInitStructure);
}
/**
 * @brief  ����GPIO����(��ʱ��)
 * @param  None
 * @retval None
 */
void GPIO::Start()
{
  RCC_Operate::RCC_Config(GPIOx, ENABLE);
}
/**
 * @brief  �ر�GPIO����(�ر�ʱ��)
 * @param  None
 * @retval None
 */
void GPIO::ShutUp()
{
  RCC_Operate::RCC_Config(GPIOx, DISABLE);
}