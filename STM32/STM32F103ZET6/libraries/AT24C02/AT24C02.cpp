#include "AT24C02.h"
/**
  * @brief  AT24C02�չ��췽��
  * @param  None
  * @retval None
  */
AT24C02::AT24C02()
{
}

/**
  * @brief  AT24C02���췽��
  * @param  AT24C02x_Param:AT24C02�Ĳ����б�
  * @retval None
  */
AT24C02::AT24C02(AT24C02_Param AT24C02x_Param)
{
    Set_AT24C02x_Param(AT24C02x_Param);
}

/**
  * @brief  AT24C02��������
  * @param  None
  * @retval None
  */
AT24C02::~AT24C02()
{
}

/**
  * @brief  AT24C02 ��ʼ������
  * @param  None
  * @retval None
  */
void AT24C02::Init()
{
    PROCESS_CONDITION = true;
    if (AT24C02x_Param.I2Cx == I2C1)
    {
        I2Cx = &I2C_1;
    }
    else if (AT24C02x_Param.I2Cx == I2C2)
    {
        I2Cx = &I2C_2;
    }
    I2Cx->Init();
}

/**
  * @brief  I2C�����б����
  * @param  I2Cx_Param:I2C�Ĳ����б�
  * @retval None
  */
void AT24C02::Update(AT24C02_Param AT24C02x_Param)
{
    Set_AT24C02x_Param(AT24C02x_Param);
    Init();
}

/**
  * @brief  ����AT24C02�Ĳ����б�
  * @param  AT24C02x_Param:AT24C02�Ĳ����б�
  * @retval None
  */
void AT24C02::Set_AT24C02x_Param(AT24C02_Param AT24C02x_Param)
{
    this->AT24C02x_Param = AT24C02x_Param;
}

/**
  * @brief  STM32��EERPOM����һ���ֽڷ���
  * @param  Data:����
  * @param  Byte_Addr:�ֵ�ַ
  * @retval None
   */
void AT24C02::Write_Byte(uint8_t Byte_Addr, uint8_t Data)
{
    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //�ж������Ƿ�æµ
    {
        //����FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //���Busyλ
        while (I2Cx->GetFlagStatus(I2C_FLAG_BUSY) == SET)
        {
            if ((FLAG_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(BUSY_ERROR, "Write_Byte");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�ж�AT24C02�ڲ��Ƿ�æµ
    Check_AT24C02_Busy();

    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //������ʼ����
    I2Cx->Generate_START(ENABLE);

    //���EV5�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV5�¼�
        while (I2Cx->Check_Event(EV5) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV5", "Write_Byte");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //���͵�ַ
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //���EV6�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV6�¼�
        while (I2Cx->Check_Event(EV6_1) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV6_1", "Write_Byte");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�����ֵ�ַ
    I2Cx->SendData(Byte_Addr);

    //���EV8�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV8�¼�
        while (I2Cx->Check_Event(EV8) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8", "Write_Byte");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //��������
    I2Cx->SendData(Data);

    //���EV8_2�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV8_2�¼�
        while (I2Cx->Check_Event(EV8_2) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8_2", "Write_Byte");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //����ֹͣ����
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  STM32����дAT24C02
  * @param  Byte_Addr:�ֵ�ַ
  * @param  p:���ڴ����ݵ�����
  * @param  num:��������ֽ���
  * @retval None
  */
void AT24C02::Write_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;
    int num_temp;
    int count = 0;
    while (num)
    {
        num_temp = 8 - (Byte_Addr & 0x07);
        num_temp = num_temp < num ? num_temp : num;
        Write_Page(Byte_Addr, p, num_temp);
        Byte_Addr = ((Byte_Addr >> 3) + 1) << 3;
        p += num_temp;
        num -= num_temp;
        count++;
    }
}

/**
  * @brief  STM32ҳдAT24C02
  * @param  Byte_Addr:�ֵ�ַ
  * @param  p:���ڴ����ݵ�����
  * @param  num:��������ֽ���
  * @retval None
  */
void AT24C02::Write_Page(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //�ж������Ƿ�æµ
    {
        //����FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //���Busyλ
        while (I2Cx->GetFlagStatus(I2C_FLAG_BUSY) == SET)
        {
            if ((FLAG_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(BUSY_ERROR, "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�ж�AT24C02�ڲ��Ƿ�æµ
    Check_AT24C02_Busy();

    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //������ʼ����
    I2Cx->Generate_START(ENABLE);

    //���EV5�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV5�¼�
        while (I2Cx->Check_Event(EV5) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV5", "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //���͵�ַ
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //���EV6�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV6�¼�
        while (I2Cx->Check_Event(EV6_1) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV6_1", "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�����ֵ�ַ
    I2Cx->SendData(Byte_Addr);

    //��������
    for (int i = 0; i < num; i++)
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV8�¼�
        while (I2Cx->Check_Event(EV8) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8", "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
        //��������
        I2Cx->SendData(p[i]);
    }

    //���EV8_2�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV8_2�¼�
        while (I2Cx->Check_Event(EV8_2) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8_2", "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //����ֹͣ����
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  STM32��EERPOM��ȡһ�����������
  * @param  Byte_Addr:�ֵ�ַ
  * @param  p:���ڴ����ݵ�����
  * @param  num:��������ֽ���
  * @retval None
  */
void AT24C02::Read_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //�ж������Ƿ�æµ
    {
        //����FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //���Busyλ
        while (I2Cx->GetFlagStatus(I2C_FLAG_BUSY) == SET)
        {
            if ((FLAG_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(BUSY_ERROR, "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�ж�AT24C02�ڲ��Ƿ�æµ
    Check_AT24C02_Busy();

    //��������һ���޷���ȷ������ȫ����ֹ
    Check_PROCESS_CONDITION;

    //��һ����
    //������ʼ����
    I2Cx->Generate_START(ENABLE);

    //���EV5�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV5�¼�
        while (I2Cx->Check_Event(EV5) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV5", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //����AT24C02��ַ
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //���EV6�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV6�¼�
        while (I2Cx->Check_Event(EV6_1) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV6_1", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�����ֵ�ַ
    I2Cx->SendData(Byte_Addr);

    //���EV8�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV8�¼�
        while (I2Cx->Check_Event(EV8) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //�ڶ�����
    //������ʼ����
    I2Cx->Generate_START(ENABLE);

    //���EV5�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV5�¼�
        while (I2Cx->Check_Event(EV5) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV5", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //����AT24C02��ַ
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Receiver);

    //���EV6�¼�
    {
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV6�¼�
        while (I2Cx->Check_Event(EV6_2) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV6_2", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
    }

    //��������
    for (int i = 0; i < num; i++)
    {
        if (i == num - 1)
        {
            I2Cx->AcknowledgeConfig(DISABLE);
        }
        else
        {
            I2Cx->AcknowledgeConfig(ENABLE);
        }
        //����EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //���EV7�¼�
        while (I2Cx->Check_Event(EV7) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV7", "Read_Buffer");
                PROCESS_CONDITION = false;
                return;
            }
        }
        p[i] = I2Cx->ReceiveData();
    }

    //������������
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  AT24C02Ӧ���ѯ(��æ����)
  * @param  None
  * @retval None
  */
void AT24C02::Check_AT24C02_Busy()
{
    // //��һ��,Ұ����,ֱ�Ӽ��flagλ
    // //����EVENT_TIMEOUT
    // EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
    // do
    // {
    //     //������ʼ����
    //     I2Cx->Generate_START(ENABLE);
    //     //����FLAG_TIMEOUT
    //     FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
    //     //���SBλ
    //     while (I2Cx->GetFlagStatus(I2C_FLAG_SB) == RESET)
    //     {
    //         if ((FLAG_TIMEOUT--) == 0)
    //         {
    //             DEBUG_ERROR_INFO(FLAG_ERROR, "SB", "Check_AT24C02_Busy");
    //             PROCESS_CONDITION = false;
    //             return;
    //         }
    //     }
    //     //���͵�ַ
    //     I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);
    //     if ((EVENT_TIMEOUT--) == 0)
    //     {
    //         DEBUG_ERROR_INFO(FLAG_ERROR, "ADDR", "Check_AT24C02_Busy");
    //         PROCESS_CONDITION = false;
    //         return;
    //     }
    // }
    // //���ADDRλ
    // while (I2Cx->GetFlagStatus(I2C_FLAG_ADDR) == RESET);
    // //���AFӦ��ʧ��λ
    // I2Cx->ClearFlag(I2C_FLAG_AF);
    // //����ֹͣλ
    // I2Cx->Generate_STOP(ENABLE);

    //�ڶ���,����ʱ��
    //����EVENT_TIMEOUT
    EVENT_TIMEOUT = 1000;
    do
    {
        //���AFӦ��ʧ��λ
        I2Cx->ClearFlag(I2C_FLAG_AF);
        //������ʼ����
        I2Cx->Generate_START(ENABLE);
        //����FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //���SBλ
        while (I2Cx->GetFlagStatus(I2C_FLAG_SB) == RESET)
        {
            if ((FLAG_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(FLAG_ERROR, "SB", "Check_AT24C02_Busy");
                PROCESS_CONDITION = false;
                return;
            }
        }
        //���͵�ַ
        I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);
        //�ȴ��������
        while (I2Cx->GetFlagStatus(I2C_FLAG_TXE) == RESET && I2Cx->GetFlagStatus(I2C_FLAG_AF) == RESET)
            ;
        if ((EVENT_TIMEOUT--) == 0)
        {
            DEBUG_ERROR_INFO(EVENT_ERROR, "EV6", "Check_AT24C02_Busy");
            PROCESS_CONDITION = false;
            return;
        }
    }
    //���EV6�¼�
    while (I2Cx->Check_Event(EV6_1) == ERROR);
    //���AFӦ��ʧ��λ
    I2Cx->ClearFlag(I2C_FLAG_AF);
    //����ֹͣλ
    I2Cx->Generate_STOP(ENABLE);
}
