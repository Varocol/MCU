#include <System.h>
/*
    STM32模拟中转I2C数据:
        使用I2C1当从机接受指令,I2C2当主机发送指令
        I2C1不断接收,并通过DMA放入缓冲区中。
        I2C2不断发送,并把得到的数据放入USART的缓冲区中。
        USART使用DMA发送数据。
*/

I2C I2C_T_1;
I2C I2C_T_2;

void Setup();
void Test();
void End();

void i2c1_ev_handler();
void i2c1_er_handler();
void i2c2_ev_handler();
void i2c2_er_handler();

int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    // 初始化系统
    system_init();
    // 挂载handler
    I2C1_EV_Handler = i2c1_ev_handler;
    I2C1_ER_Handler = i2c1_er_handler;
    I2C2_EV_Handler = i2c2_ev_handler;
    I2C2_ER_Handler = i2c2_er_handler;
    // 初始化两个I2C
    I2C_InitTypeDef I2C1_InitStructure = {
        .I2C_ClockSpeed = 100000,
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_DutyCycle = I2C_DutyCycle_16_9,
        .I2C_OwnAddress1 = 0x2C << 1,
        .I2C_Ack = I2C_Ack_Enable, // 默认会在第一个字节也就是地址匹配上后ack
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
    I2C_InitTypeDef I2C2_InitStructure = {
        .I2C_ClockSpeed = 100000,
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_DutyCycle = I2C_DutyCycle_16_9,
        .I2C_OwnAddress1 = 0xB0,
        .I2C_Ack = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
    // I2C1 错误中断
    NVIC_InitTypeDef I2C1_ER_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C1_ER_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 6,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C1 事件中断
    NVIC_InitTypeDef I2C1_EV_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C1_EV_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 7,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C2 错误中断
    NVIC_InitTypeDef I2C2_ER_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C2_ER_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 8,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C2 事件中断
    NVIC_InitTypeDef I2C2_EV_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C2_EV_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 9,
        .NVIC_IRQChannelCmd = ENABLE};
    I2C_Param I2C1_Param = {
        .I2Cx = I2C1,
        .I2C_InitStructure = I2C1_InitStructure,
        .I2C_ER_NVIC_InitStructure = I2C1_ER_NVIC_InitStructure,
        .I2C_EV_NVIC_InitStructure = I2C1_EV_NVIC_InitStructure,
        .I2C_Pin_Remap = I2C_Default,
        .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
        .I2C_IT_State = ENABLE,
        .I2C_DMA_State = DISABLE};
    I2C_Param I2C2_Param = {
        .I2Cx = I2C2,
        .I2C_InitStructure = I2C2_InitStructure,
        .I2C_ER_NVIC_InitStructure = I2C2_ER_NVIC_InitStructure,
        .I2C_EV_NVIC_InitStructure = I2C2_EV_NVIC_InitStructure,
        .I2C_Pin_Remap = I2C_Default,
        .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
        .I2C_IT_State = DISABLE,
        .I2C_DMA_State = DISABLE};
    I2C_T_1 = I2C(I2C1_Param);
    I2C_T_2 = I2C(I2C2_Param);
    I2C_T_1.Init();
    I2C_T_2.Init();
}
void Test()
{
    PLATFORM_USART.Send_String_DMA("123\n");
    uint32_t EVENT_TIMEOUT;
    // 产生起始条件
    I2C_T_2.Generate_START(ENABLE);

    // 检测EV5事件
    {
        // 重置EVENT_TIMEOUT
        EVENT_TIMEOUT = I2CT_EVENT_TIMEOUT;
        // 检测EV5事件
        while (I2C_T_2.Check_Event(EV5) == ERROR)
        {
            if ((EVENT_TIMEOUT--) == 0)
            {
                DEBUG_ERROR_INFO(EVENT_ERROR, "EV5", "Write_Byte");
                break;
            }
        }
    }
    PLATFORM_USART.Send_String_DMA("456\n");
    I2C_T_2.Send7bitAddress(0x2C, I2C_Direction_Transmitter);
    while (1)
        ;
}
void End()
{
}
void i2c1_ev_handler()
{
    switch (I2C_GetLastEvent(I2C1))
    {
    case EV1_2: // I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED
        // I2C_T_1.AcknowledgeConfig(ENABLE);
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:已匹配上地址\n");
        break;
    case EV2_1: // I2C_EVENT_SLAVE_BYTE_RECEIVED
    {
        // 发送一个应答信号
        I2C_T_1.AcknowledgeConfig(ENABLE);
        uint8_t tmp = I2C_T_1.ReceiveData();
        char *hex = "0123456789ABCDEF";
        PLATFORM_USART.Send_String_DMA("0x");
        PLATFORM_USART.Send_Data_DMA(hex[tmp / 16]);
        PLATFORM_USART.Send_Data_DMA(hex[tmp % 16]);
        PLATFORM_USART.Send_String_DMA(" ");
    }
    break;
    case EV4: // I2C_EVENT_SLAVE_STOP_DETECTED
        // 检测到停止信号
        // 按照官方给出的方案是读完SR1后直接一个I2C_Cmd()
        I2C_T_1.Enable();
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:指令获取结束\n");
        break;
    default:
        break;
    }
    // 检测中断位是否被清除
    if (I2C_GetITStatus(I2C1, I2C_IT_SB) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:SB未被清除\n");
        // 写DR寄存器清除标志位
        I2C_T_1.SendData(0x00);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_ADDR) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:ADDR未被清除\n");
        // 读SR1和SR2清除标志位
        I2C_GetLastEvent(I2C1);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_ADD10) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:ADD10未被清除\n");
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_STOPF) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:STOPF未被清除\n");
        I2C_T_1.Enable();
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_BTF) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:BTF未被清除\n");
        // 写DR寄存器清除标志位
        I2C_T_1.ReceiveData();
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_RXNE) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:RXNE未被清除\n");
        // 读DR寄存器清除标志位
        I2C_T_1.ReceiveData();
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_TXE) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:TXE未被清除\n");
    }
}
void i2c1_er_handler()
{
    // 检测中断位是否被清除
    if (I2C_GetITStatus(I2C1, I2C_IT_BERR) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:总线错误\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_BERR);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_ARLO) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:仲裁丢失\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_ARLO);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_AF) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:应答失败\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_AF);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_OVR) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:过载/欠载\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_OVR);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_PECERR) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:PEC错误\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_PECERR);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_TIMEOUT) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:超时/Tlow错误\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_TIMEOUT);
    }
    else if (I2C_GetITStatus(I2C1, I2C_IT_SMBALERT) != RESET)
    {
        PLATFORM_USART.Send_String_DMA("\n[I2C1]:SMBus警告\n");
        I2C_ClearITPendingBit(I2C1, I2C_IT_SMBALERT);
    }
}
void i2c2_ev_handler()
{
}

void i2c2_er_handler()
{
}