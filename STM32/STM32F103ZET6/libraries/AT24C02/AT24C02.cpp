#include "AT24C02.h"
/**
  * @brief  AT24C02空构造方法
  * @param  None
  * @retval None
  */
AT24C02::AT24C02()
{
}

/**
  * @brief  AT24C02构造方法
  * @param  AT24C02x_Param:AT24C02的参数列表
  * @retval None
  */
AT24C02::AT24C02(AT24C02_Param AT24C02x_Param)
{
    Set_AT24C02x_Param(AT24C02x_Param);
}

/**
  * @brief  AT24C02析构函数
  * @param  None
  * @retval None
  */
AT24C02::~AT24C02()
{
}

/**
  * @brief  AT24C02 初始化函数
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
  * @brief  I2C参数列表更新
  * @param  I2Cx_Param:I2C的参数列表
  * @retval None
  */
void AT24C02::Update(AT24C02_Param AT24C02x_Param)
{
    Set_AT24C02x_Param(AT24C02x_Param);
    Init();
}

/**
  * @brief  设置AT24C02的参数列表
  * @param  AT24C02x_Param:AT24C02的参数列表
  * @retval None
  */
void AT24C02::Set_AT24C02x_Param(AT24C02_Param AT24C02x_Param)
{
    this->AT24C02x_Param = AT24C02x_Param;
}

/**
  * @brief  STM32向EERPOM发送一个字节方法
  * @param  Data:数据
  * @param  Byte_Addr:字地址
  * @retval None
   */
void AT24C02::Write_Byte(uint8_t Byte_Addr, uint8_t Data)
{
    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //判断总线是否忙碌
    {
        //重置FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //检测Busy位
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

    //判断AT24C02内部是否忙碌
    Check_AT24C02_Busy();

    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //产生起始条件
    I2Cx->Generate_START(ENABLE);

    //检测EV5事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV5事件
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

    //发送地址
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //检测EV6事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV6事件
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

    //发送字地址
    I2Cx->SendData(Byte_Addr);

    //检测EV8事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV8事件
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

    //发送数据
    I2Cx->SendData(Data);

    //检测EV8_2事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV8_2事件
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

    //产生停止条件
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  STM32区块写AT24C02
  * @param  Byte_Addr:字地址
  * @param  p:用于存数据的数组
  * @param  num:所需读的字节数
  * @retval None
  */
void AT24C02::Write_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //若程序有一处无法正确运行则全部终止
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
  * @brief  STM32页写AT24C02
  * @param  Byte_Addr:字地址
  * @param  p:用于存数据的数组
  * @param  num:所需读的字节数
  * @retval None
  */
void AT24C02::Write_Page(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //判断总线是否忙碌
    {
        //重置FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //检测Busy位
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

    //判断AT24C02内部是否忙碌
    Check_AT24C02_Busy();

    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //产生起始条件
    I2Cx->Generate_START(ENABLE);

    //检测EV5事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV5事件
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

    //发送地址
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //检测EV6事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV6事件
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

    //发送字地址
    I2Cx->SendData(Byte_Addr);

    //发送数据
    for (int i = 0; i < num; i++)
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV8事件
        while (I2Cx->Check_Event(EV8) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV8", "Write_Page");
                PROCESS_CONDITION = false;
                return;
            }
        }
        //发送数据
        I2Cx->SendData(p[i]);
    }

    //检测EV8_2事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV8_2事件
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

    //产生停止条件
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  STM32向EERPOM读取一个区块的数据
  * @param  Byte_Addr:字地址
  * @param  p:用于存数据的数组
  * @param  num:所需读的字节数
  * @retval None
  */
void AT24C02::Read_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num)
{
    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //判断总线是否忙碌
    {
        //重置FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //检测Busy位
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

    //判断AT24C02内部是否忙碌
    Check_AT24C02_Busy();

    //若程序有一处无法正确运行则全部终止
    Check_PROCESS_CONDITION;

    //第一部分
    //产生起始条件
    I2Cx->Generate_START(ENABLE);

    //检测EV5事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV5事件
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

    //发送AT24C02地址
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);

    //检测EV6事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV6事件
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

    //发送字地址
    I2Cx->SendData(Byte_Addr);

    //检测EV8事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV8事件
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

    //第二部分
    //产生起始条件
    I2Cx->Generate_START(ENABLE);

    //检测EV5事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV5事件
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

    //发送AT24C02地址
    I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Receiver);

    //检测EV6事件
    {
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV6事件
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

    //存入数据
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
        //重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        //检测EV7事件
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

    //产生结束条件
    I2Cx->Generate_STOP(ENABLE);
}

/**
  * @brief  AT24C02应答查询(判忙函数)
  * @param  None
  * @retval None
  */
void AT24C02::Check_AT24C02_Busy()
{
    // //第一种,野蛮法,直接检测flag位
    // //重置EVENT_TIMEOUT
    // EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
    // do
    // {
    //     //产生起始条件
    //     I2Cx->Generate_START(ENABLE);
    //     //重置FLAG_TIMEOUT
    //     FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
    //     //检测SB位
    //     while (I2Cx->GetFlagStatus(I2C_FLAG_SB) == RESET)
    //     {
    //         if ((FLAG_TIMEOUT--) == 0)
    //         {
    //             DEBUG_ERROR_INFO(FLAG_ERROR, "SB", "Check_AT24C02_Busy");
    //             PROCESS_CONDITION = false;
    //             return;
    //         }
    //     }
    //     //发送地址
    //     I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);
    //     if ((EVENT_TIMEOUT--) == 0)
    //     {
    //         DEBUG_ERROR_INFO(FLAG_ERROR, "ADDR", "Check_AT24C02_Busy");
    //         PROCESS_CONDITION = false;
    //         return;
    //     }
    // }
    // //检测ADDR位
    // while (I2Cx->GetFlagStatus(I2C_FLAG_ADDR) == RESET);
    // //清除AF应答失败位
    // I2Cx->ClearFlag(I2C_FLAG_AF);
    // //发送停止位
    // I2Cx->Generate_STOP(ENABLE);

    //第二种,完整时序法
    //重置EVENT_TIMEOUT
    EVENT_TIMEOUT = 1000;
    do
    {
        //清除AF应答失败位
        I2Cx->ClearFlag(I2C_FLAG_AF);
        //产生起始条件
        I2Cx->Generate_START(ENABLE);
        //重置FLAG_TIMEOUT
        FLAG_TIMEOUT = I2CT_FLAG_TIMEOUT;
        //检测SB位
        while (I2Cx->GetFlagStatus(I2C_FLAG_SB) == RESET)
        {
            if ((FLAG_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(FLAG_ERROR, "SB", "Check_AT24C02_Busy");
                PROCESS_CONDITION = false;
                return;
            }
        }
        //发送地址
        I2Cx->Send7bitAddress(AT24C02x_Param.AT24C02_ADDR, I2C_Direction_Transmitter);
        //等待发送完成
        while (I2Cx->GetFlagStatus(I2C_FLAG_TXE) == RESET && I2Cx->GetFlagStatus(I2C_FLAG_AF) == RESET)
            ;
        if ((EVENT_TIMEOUT--) == 0)
        {
            DEBUG_ERROR_INFO(EVENT_ERROR, "EV6", "Check_AT24C02_Busy");
            PROCESS_CONDITION = false;
            return;
        }
    }
    //检测EV6事件
    while (I2Cx->Check_Event(EV6_1) == ERROR);
    //清除AF应答失败位
    I2Cx->ClearFlag(I2C_FLAG_AF);
    //发送停止位
    I2Cx->Generate_STOP(ENABLE);
}
