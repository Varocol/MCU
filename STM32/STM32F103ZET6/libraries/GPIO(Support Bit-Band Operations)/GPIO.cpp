#include "GPIO.h"

/**
 * @brief  GPIO-�չ��췽��
 * @retval None
 */
GPIO::GPIO()
{
}

/**
 * @brief  GPIO-��������
 * @retval None
 */
GPIO::~GPIO()
{
}

/**
 * @brief  GPIO-���췽��
 * @param  Pin          ����
 * @param  Val          GPIO��ʼ�����ֵ
 * @param  Mode         GPIOģʽ
 * @param  Speed        GPIO�ٶ�
 * @retval None
 */
GPIO::GPIO(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_GPIO_Param(Pin, Mode, Val, Speed);
}

/**
 * @brief  GPIO-����GPIO����
 * @param  Pin            ����
 * @retval None
 */
void GPIO::Set_Pin(PIN_enum Pin)
{
  this->Pin = Pin;
  GPIOx = Get_GPIOx(Pin);
  GPIOInitStructure.GPIO_Pin = Get_GPIO_Pin(Pin);
}

/**
 * @brief  GPIO-����GPIO��ʼ�����ֵ
 *         (����������������ֵ,����Ҫ��ʹ��Set_Pin_Val)
 * @param  Val          GPIO��ʼ�����ֵ
 * @retval None
 */
void GPIO::Set_Val(BitAction Val)
{
  this->Val = Val;
}

/**
 * @brief  GPIO-����GPIO�ٶ�
 * @param  Speed         GPIO�ٶ�
 * @retval None
 */
void GPIO::Set_Speed(GPIOSpeed_TypeDef Speed)
{
  GPIOInitStructure.GPIO_Speed = Speed;
}

/**
 * @brief  GPIO-����GPIOģʽ
 * @param  Speed         GPIOģʽ
 * @retval None
 */
void GPIO::Set_Mode(GPIOMode_TypeDef Mode)
{
  GPIOInitStructure.GPIO_Mode = Mode;
}

/**
 * @brief  GPIO-��ȡ����
 * @param  None
 * @retval Pin
 */
PIN_enum GPIO::Get_Pin()
{
  return Pin;
}

/**
 * @brief  GPIO-��ȡ���ų�ʼ��ֵ
 * @param  None
 * @retval Val
 */
BitAction GPIO::Get_Val()
{
  return Val;
}

/**
 * @brief  GPIO-����GPIO�˿�
 * @param  None
 * @retval GPIOx
 */
GPIO_TypeDef *GPIO::Get_GPIOx()
{
  return GPIOx;
}

/**
 * @brief  GPIO-����GPIO��ʼ���ṹ��
 * @param  None
 * @retval GPIOInitStructure
 */
GPIO_InitTypeDef GPIO::Get_GPIOInitStructure()
{
  return GPIOInitStructure;
}

/**
 * @brief  GPIO-��ȡPin����Ӧ�Ķ˿�
 * @param  Pin          ����
 * @retval Pin����Ӧ�Ķ˿�
 */
GPIO_TypeDef *GPIO::Get_GPIOx(PIN_enum Pin)
{
  GPIO_TypeDef *GPIOx;
  switch (Pin / 17)
  {
  case 0:
    GPIOx = GPIOA;
    break;
  case 1:
    GPIOx = GPIOB;
    break;
  case 2:
    GPIOx = GPIOC;
    break;
  case 3:
    GPIOx = GPIOD;
    break;
  case 4:
    GPIOx = GPIOE;
    break;
  case 5:
    GPIOx = GPIOF;
    break;
  case 6:
    GPIOx = GPIOG;
    break;
  }
  return GPIOx;
}

/**
 * @brief  GPIO-��ȡPin����Ӧ��GPIO_Pin
 * @param  Pin          ����
 * @retval Pin����Ӧ��GPIO_Pin
 */
uint16_t GPIO::Get_GPIO_Pin(PIN_enum Pin)
{
  uint16_t GPIO_Pin_x;
  switch (Pin % 17)
  {
  case 0:
    GPIO_Pin_x = GPIO_Pin_0;
    break;
  case 1:
    GPIO_Pin_x = GPIO_Pin_1;
    break;
  case 2:
    GPIO_Pin_x = GPIO_Pin_2;
    break;
  case 3:
    GPIO_Pin_x = GPIO_Pin_3;
    break;
  case 4:
    GPIO_Pin_x = GPIO_Pin_4;
    break;
  case 5:
    GPIO_Pin_x = GPIO_Pin_5;
    break;
  case 6:
    GPIO_Pin_x = GPIO_Pin_6;
    break;
  case 7:
    GPIO_Pin_x = GPIO_Pin_7;
    break;
  case 8:
    GPIO_Pin_x = GPIO_Pin_8;
    break;
  case 9:
    GPIO_Pin_x = GPIO_Pin_9;
    break;
  case 10:
    GPIO_Pin_x = GPIO_Pin_10;
    break;
  case 11:
    GPIO_Pin_x = GPIO_Pin_11;
    break;
  case 12:
    GPIO_Pin_x = GPIO_Pin_12;
    break;
  case 13:
    GPIO_Pin_x = GPIO_Pin_13;
    break;
  case 14:
    GPIO_Pin_x = GPIO_Pin_14;
    break;
  case 15:
    GPIO_Pin_x = GPIO_Pin_15;
    break;
  case 17:
    GPIO_Pin_x = GPIO_Pin_All;
    break;
  }
  return GPIO_Pin_x;
}

/**
 * @brief  GPIO-��ʼ��GPIOΪ���ģʽ
 * @param  None
 * @retval None
 */
void GPIO::OUT_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO-��ʼ��GPIOΪ����ģʽ
 * @param  None
 * @retval None
 */
void GPIO::IN_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO-��������
 * @param  None
 * @retval None
 */
void GPIO::Pin_High()
{
  GPIO_SetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO-��������
 * @param  None
 * @retval None
 */
void GPIO::Pin_Low()
{
  GPIO_ResetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO-���ŷ�ת
 * @param  None
 * @retval None
 */
void GPIO::Pin_Toggle()
{
  Set_Pin_Val(Get_Input_Pin() == Bit_RESET ? Bit_SET : Bit_RESET);
}

/**
 * @brief  GPIO-��������ֵ
 * @param  BitVal       ����ֵ
 * @retval None
 */
void GPIO::Set_Pin_Val(uint8_t BitVal)
{
  GPIO_WriteBit(GPIOx, GPIOInitStructure.GPIO_Pin, (BitAction)BitVal);
}

/**
 * @brief  GPIO-���ö˿�ֵ
 * @param  PortVal      �˿�ֵ
 * @retval None
 */
void GPIO::Set_Port_Val(uint16_t PortVal)
{
  GPIO_Write(GPIOx, PortVal);
}

/**
 * @brief  GPIO-��ȡ�����������ֵ
 * @param  None
 * @retval �������ŵ���ֵ
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
 * @brief  GPIO-��ȡ�����������ֵ
 * @param  None
 * @retval ������ŵ���ֵ
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
 * @brief  GPIO-��ȡ����Ķ˿���ֵ
 * @param  None
 * @retval ����˿ڵ���ֵ
 */
uint16_t GPIO::Get_Input_Port()
{
  return GPIO_ReadInputData(GPIOx);
}

/**
 * @brief  GPIO-��ȡ����Ķ˿���ֵ
 * @param  None
 * @retval ����˿ڵ���ֵ
 */
uint16_t GPIO::Get_Output_Port()
{
  return GPIO_ReadOutputData(GPIOx);
}

/**
 * @brief  GPIO-���ò����б�
 * @param  Pin          ����
 * @param  Val          GPIO��ʼ�����ֵ
 * @param  Mode         GPIOģʽ
 * @param  Speed        GPIO�ٶ�
 * @retval None
 */
void GPIO::Set_GPIO_Param(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_Pin(Pin);
  Set_Val(Val);
  Set_Speed(Speed);
  Set_Mode(Mode);
}

/**
 * @brief  GPIO-��������
 * @param  Pin          ����
 * @param  Val          GPIO��ʼ�����ֵ
 * @param  Mode         GPIOģʽ
 * @param  Speed        GPIO�ٶ�
 * @retval None
 */
void GPIO::Update(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_GPIO_Param(Pin, Mode, Val, Speed);
  Init();
}

/**
 * @brief  GPIO-��ʼ������
 * @param  None
 * @retval None
 */
void GPIO::Init()
{
  Start(GPIOx);
  GPIO_Init(GPIOx, &GPIOInitStructure);
  switch (GPIOInitStructure.GPIO_Mode)
  {
  case GPIO_Mode_Out_OD:
  case GPIO_Mode_Out_PP:
    Set_Pin_Val(Val);
    break;
  default:
    break;
  }
}

/**
 * @brief  GPIO-����GPIO����(��ʱ��)
 * @param  None
 * @retval None
 */
void GPIO::Start(GPIO_TypeDef *GPIOx)
{
  RCC_Operate::RCC_Config(GPIOx, ENABLE);
}

/**
 * @brief  GPIO-�ر�GPIO����(�ر�ʱ��)
 * @param  None
 * @retval None
 */
void GPIO::ShutUp(GPIO_TypeDef *GPIOx)
{
  RCC_Operate::RCC_Config(GPIOx, DISABLE);
}