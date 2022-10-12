#include "EXTI.h"
/**
 * @brief  EXTI-GPIOxת����GPIOPortSource
 * @param  GPIOx                GPIO�˿�
 * @retval GPIO_PortSource
 */
uint8_t EXTI_Operate::GPIO_2_GPIO_PortSource(GPIO_TypeDef *GPIOx)
{
    if (GPIOx == GPIOA)
    {
        return GPIO_PortSourceGPIOA;
    }
    else if (GPIOx == GPIOB)
    {
        return GPIO_PortSourceGPIOB;
    }
    else if (GPIOx == GPIOC)
    {
        return GPIO_PortSourceGPIOC;
    }
    else if (GPIOx == GPIOD)
    {
        return GPIO_PortSourceGPIOD;
    }
    else if (GPIOx == GPIOE)
    {
        return GPIO_PortSourceGPIOE;
    }
    else if (GPIOx == GPIOF)
    {
        return GPIO_PortSourceGPIOF;
    }
    else if (GPIOx == GPIOG)
    {
        return GPIO_PortSourceGPIOG;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  EXTI-EXTI_Linexת����GPIO_PinSource
 * @param  EXTI_Linex           EXTIͨ��
 * @retval GPIO_PinSource
 */
uint8_t EXTI_Operate::EXTI_2_GPIO_PinSource(uint32_t EXTI_Linex)
{
    switch (EXTI_InitStructure.EXTI_Line)
    {
    case EXTI_Line0:
        return GPIO_PinSource0;
    case EXTI_Line1:
        return GPIO_PinSource1;
    case EXTI_Line2:
        return GPIO_PinSource2;
    case EXTI_Line3:
        return GPIO_PinSource3;
    case EXTI_Line4:
        return GPIO_PinSource4;
    case EXTI_Line5:
        return GPIO_PinSource5;
    case EXTI_Line6:
        return GPIO_PinSource6;
    case EXTI_Line7:
        return GPIO_PinSource7;
    case EXTI_Line8:
        return GPIO_PinSource8;
    case EXTI_Line9:
        return GPIO_PinSource9;
    case EXTI_Line10:
        return GPIO_PinSource10;
    case EXTI_Line11:
        return GPIO_PinSource11;
    case EXTI_Line12:
        return GPIO_PinSource12;
    case EXTI_Line13:
        return GPIO_PinSource13;
    case EXTI_Line14:
        return GPIO_PinSource14;
    case EXTI_Line15:
        return GPIO_PinSource15;
    default:
        return 0;
    }
}

/**
 * @brief  EXTI-�չ��췽��
 * @param  None
 * @retval None
 */
EXTI_Operate::EXTI_Operate()
{
}

/**
 * @brief  EXTI-��������
 * @param  None
 * @retval None
 */
EXTI_Operate::~EXTI_Operate()
{
}

/**
 * @brief  EXTI-���췽��1
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure);
}

/**
 * @brief  EXTI-���췽��2
 * @param  EXTI_InitStructure         EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure    NVIC�жϳ�ʼ���ṹ��
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure);
}

/**
 * @brief  EXTI-���췽��3
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @param  GPIOx                GPIO�˿�
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, GPIOx);
}

/**
 * @brief  EXTI-���췽��4
 * @param  EXTI_InitStructure         EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure    NVIC�жϳ�ʼ���ṹ��
 * @param  GPIOx                      GPIO�˿�
 * @retval None
 */
EXTI_Operate::EXTI_Operate(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure, GPIOx);
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�1
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->Init_Type = EXTI_16_20_Event;
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�2
 * @param  EXTI_InitStructure           EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure      NVIC�жϳ�ʼ���ṹ��
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->EXTI_NVIC_InitStructure = EXTI_NVIC_InitStructure;
    this->Init_Type = EXTI_16_20_Intterupt;
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�3
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @param  GPIOx                GPIO�˿�
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->GPIOx = GPIOx;
    this->Init_Type = EXTI_0_15_Event;
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�4
 * @param  EXTI_InitStructure           EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure      NVIC�жϳ�ʼ���ṹ��
 * @param  GPIOx                        GPIO�˿�
 * @retval None
 */
void EXTI_Operate::Set_EXTI_Param(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    this->EXTI_InitStructure = EXTI_InitStructure;
    this->EXTI_NVIC_InitStructure = EXTI_NVIC_InitStructure;
    this->GPIOx = GPIOx;
    this->Init_Type = EXTI_0_15_Intterupt;
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�1
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure);
    Init();
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�2
 * @param  EXTI_InitStructure         EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure    NVIC�жϳ�ʼ���ṹ��
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure);
    Init();
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�3
 * @param  EXTI_InitStructure   EXTI��ʼ���ṹ��
 * @param  GPIOx                GPIO�˿�
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, GPIOx);
    Init();
}

/**
 * @brief  EXTI-����EXTI�Ĳ����б�4
 * @param  EXTI_InitStructure         EXTI��ʼ���ṹ��
 * @param  EXTI_NVIC_InitStructure    NVIC�жϳ�ʼ���ṹ��
 * @param  GPIOx                      GPIO�˿�
 * @retval None
 */
void EXTI_Operate::Update(EXTI_InitTypeDef EXTI_InitStructure, NVIC_InitTypeDef EXTI_NVIC_InitStructure, GPIO_TypeDef *GPIOx)
{
    Set_EXTI_Param(EXTI_InitStructure, EXTI_NVIC_InitStructure, GPIOx);
    Init();
}

/**
 * @brief  EXTI-��������ж�/�¼���־
 * @param  None
 * @retval None
 */
void EXTI_Operate::GenerateSWInterrupt()
{
    EXTI_GenerateSWInterrupt(EXTI_InitStructure.EXTI_Line);
}

/**
 * @brief  EXTI-���Ӳ��/������ж�/�¼���־
 * @param  None
 * @retval None
 */
void EXTI_Operate::ClearFlag()
{
    EXTI_ClearFlag(EXTI_InitStructure.EXTI_Line);
}

/**
 * @brief  EXTI-��ʼ��
 * @param  None
 * @retval None
 */
void EXTI_Operate::Init()
{
    //���û�г�ʼ�������򲻳�ʼ��
    if (Init_Type == EXTI_Init_None)
    {
        return;
    }
    // EXTI0~15 ѡ��GPIOx��ΪEXTI_Linex�������
    if (Init_Type == EXTI_0_15_Event || Init_Type == EXTI_0_15_Intterupt)
    {
        //����AFIOʱ��
        RCC_Operate::RCC_Config(AFIO, ENABLE);
        //����AFIO��AFIO_EXTICRx�Ĵ���
        GPIO_EXTILineConfig(GPIO_2_GPIO_PortSource(GPIOx), EXTI_2_GPIO_PinSource(EXTI_InitStructure.EXTI_Line));
    }
    //����EXTI�ж����ȼ�
    if (Init_Type == EXTI_16_20_Intterupt || Init_Type == EXTI_0_15_Intterupt)
    {
        NVIC_Operate(EXTI_NVIC_InitStructure).Init();
    }
    //����EXTI(����EXTI�Ƚ�����,��������ķ����Դ�EXTI��ʼ��)
    Enable();
}

/**
 * @brief  EXTI-����EXTI����(EXTIʹ��)
 * @param  None
 * @retval None
 */
void EXTI_Operate::Enable()
{
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief  EXTI-�ر�EXTI����(EXTIʧ��)
 * @param  None
 * @retval None
 */
void EXTI_Operate::Disable()
{
    EXTI_InitStructure.EXTI_LineCmd = DISABLE;
    EXTI_Init(&EXTI_InitStructure);
}