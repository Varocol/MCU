#include "Libraries.h"
#define TEST_MODE 5
#define SPI2_RX_DR_ADDR (SPI2_BASE + 0x0C)
#define SPI2_RX_DMA_CHANNEL DMA1_Channel4
#define SPI2_RX_DMA_CHANNEL_IRQN DMA1_Channel4_IRQn
#define SPI1_TX_DR_ADDR (SPI1_BASE + 0x0C)
#define SPI1_TX_DMA_CHANNEL DMA1_Channel3
#define SPI1_TX_DMA_CHANNEL_IRQN DMA1_Channel3_IRQn
/*
    测试一:
        检验SPI_NSS_Master_Soft模式
         SPI1当作主机,模式为软件主模式,SPI2当作从机,模式为硬件从模式,并将SPI2接收到的结果串口输出;
    测试二:
        检验SPI_NSS_Master_SSOE_Hard模式
        SPI1当作主机,模式为硬件主模式的输出模式(即SPI_NSS_Master_SSOE_Hard模式),SPI2当作从机,模式为硬件从模式,并将SPI2接收到的结果串口输出;
    测试三:
        检验SPI_NSS_Master_Hard模式(不怎么用,鸡肋)
        SPI1当作主机,模式为硬件主模式的输入模式(即SPI_NSS_Master_Hard模式),SPI2当作从机,模式为硬件从模式,并将SPI2接收到的结果串口输出;
    测试四:
        检验SPI_NSS_Slave_Soft模式(这个模式也不怎么用)
        SPI1当作主机,模式为硬件主模式的输入模式(即SPI_NSS_Master_Hard模式),SPI2当作从机,模式为软件从模式,并将SPI2接收到的结果串口输出;
        这次测试中,由于主机使用SPI_NSS_Master_Hard模式,所以使用了两个外部引脚,分别为PC7(主机),PC6(从机),当然也测试了主机为PI_NSS_Master_SSOE_Hard
        时,即只使用PC6的模式,也是通过的,所以会看到有部分代码被注释,本次测验基于EXTI外部中断。
    测试五:
        CRC校验,官方推荐的关闭SPI的步骤测试,以及中断的测试。

*/
SPI SPI_1_Test;
SPI SPI_2_Test;
DMA_InitTypeDef SPI2_RX_DMA_InitStructure;
void Setup();
void Test();
void End();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    //初始化串口
    USART_1.Init();
    //初始化信号灯
    LED_1.Init();
#if TEST_MODE != 5
    //初始化DMA
    NVIC_InitTypeDef SPI2_RX_DMA_NVIC_InitStructure = {
        SPI2_RX_DMA_CHANNEL_IRQN,
        0,
        10,
        ENABLE};
    DMA_InitTypeDef SPI2_RX_DMA_InitStructure = {
        SPI2_RX_DR_ADDR,
        (uint32_t)ReceiveBuffer,
        DMA_DIR_PeripheralSRC,
        strlen(SendBuffer) + 1,
        DMA_PeripheralInc_Disable,
        DMA_MemoryInc_Enable,
        DMA_PeripheralDataSize_Byte,
        DMA_MemoryDataSize_Byte,
        DMA_Mode_Circular,
        DMA_Priority_High,
        DMA_M2M_Disable};
    DMA_Param SPI2_RX_DMA_Param = {
        SPI2_RX_DMA_CHANNEL,
        SPI2_RX_DMA_InitStructure,
        NVIC_Operate(SPI2_RX_DMA_NVIC_InitStructure),
        DISABLE,
        DMA_IT_TC | DMA_IT_HT | DMA_IT_TE // DMA_IT_TC | DMA_IT_HT | DMA_IT_TE(这个只是供你选择,实际并不能用与的形式传参)
    };
    SPI2_RX_DMA = DMA(SPI2_RX_DMA_Param);
#endif
#if TEST_MODE == 1
    NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
        SPI1_IRQn,
        0,
        13,
        ENABLE};
    NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
        SPI2_IRQn,
        0,
        14,
        ENABLE};
    SPI_InitTypeDef SPI1_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Master,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Soft,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_InitTypeDef SPI2_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Slave,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_Param SPI1_Param = {
        SPI1,
        SPI1_InitStructure,
        SPI_NSS_Master_Soft,
        NVIC_Operate(SPI1_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_Param SPI2_Param = {
        SPI2,
        SPI2_InitStructure,
        SPI_NSS_Slave_Hard,
        NVIC_Operate(SPI2_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    GPIO NSS_Soft = GPIO(PA4);
    SPI_1_Test = SPI(SPI1_Param);
    SPI_2_Test = SPI(SPI2_Param);
    SPI_1_Test.Set_NSS_Pin(NSS_Soft);
    SPI_2_Test.Init();
    SPI_1_Test.Init();
    SPI_1_Test.NSS_High();
#endif
#if TEST_MODE == 2
    NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
        SPI1_IRQn,
        0,
        13,
        ENABLE};
    NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
        SPI2_IRQn,
        0,
        14,
        ENABLE};
    SPI_InitTypeDef SPI1_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Master,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_InitTypeDef SPI2_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Slave,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_Param SPI1_Param = {
        SPI1,
        SPI1_InitStructure,
        SPI_NSS_Master_SSOE_Hard,
        NVIC_Operate(SPI1_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_Param SPI2_Param = {
        SPI2,
        SPI2_InitStructure,
        SPI_NSS_Slave_Hard,
        NVIC_Operate(SPI2_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_1_Test = SPI(SPI1_Param);
    SPI_2_Test = SPI(SPI2_Param);
    SPI_2_Test.Init();
    SPI_1_Test.Init();
#endif
#if TEST_MODE == 3
    //该模式下不开启SSOE,同时也不初始化nss硬件引脚,而是使用其他GPIO引脚来代替,类似于软件nss,有点鸡肋
    NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
        SPI1_IRQn,
        0,
        13,
        ENABLE};
    NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
        SPI2_IRQn,
        0,
        14,
        ENABLE};
    SPI_InitTypeDef SPI1_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Master,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_InitTypeDef SPI2_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Slave,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_Param SPI1_Param = {
        SPI1,
        SPI1_InitStructure,
        SPI_NSS_Master_Hard,
        NVIC_Operate(SPI1_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_Param SPI2_Param = {
        SPI2,
        SPI2_InitStructure,
        SPI_NSS_Slave_Hard,
        NVIC_Operate(SPI2_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    GPIO NSS_Soft = GPIO(PC6);
    SPI_1_Test = SPI(SPI1_Param);
    SPI_2_Test = SPI(SPI2_Param);
    SPI_1_Test.Set_NSS_Pin(NSS_Soft);
    SPI_2_Test.Init();
    SPI_1_Test.Init();
#endif
#if TEST_MODE == 4
    //该模式下不开启SSOE,同时也不初始化nss硬件引脚,而是使用其他GPIO引脚来代替,类似于软件nss,有点鸡肋
    //由于软件Slave模式下的外部nss引脚不接入内部nss,所以需要使用外部中断触发修改内部nss
    //所以可能需要两个外部引脚
    NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
        SPI1_IRQn,
        0,
        13,
        ENABLE};
    NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
        SPI2_IRQn,
        0,
        14,
        ENABLE};
    SPI_InitTypeDef SPI1_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Master,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_InitTypeDef SPI2_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Slave,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Soft,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        3};
    SPI_Param SPI1_Param = {
        SPI1,
        SPI1_InitStructure,
        SPI_NSS_Master_SSOE_Hard,
        NVIC_Operate(SPI1_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_Param SPI2_Param = {
        SPI2,
        SPI2_InitStructure,
        SPI_NSS_Slave_Soft,
        NVIC_Operate(SPI2_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    // GPIO NSS_Soft = GPIO(PC7);
    SPI_1_Test = SPI(SPI1_Param);
    SPI_2_Test = SPI(SPI2_Param);
    // SPI_1_Test.Set_NSS_Pin(NSS_Soft);
    SPI_2_Test.Init();
    SPI_1_Test.Init();
    //将SPI_2_Test赋给SPI_2使得SPI_2_Test能够被中断函数使用
    SPI_2 = SPI_2_Test;
    //初始化GPIO PC6,为了方便读取引脚信号
    GPIO Read_Pin = GPIO(PC6);
    Read_Pin.OUT_MODE();
    //初始化外部中断
    EXTI_PC6.Init();
    printf("初始化完成！\n");
    //片选拉高使得有下降沿
    // SPI_1_Test.NSS_High();
    //由于新增了官方推荐的SPI关闭方法,所以不再使用上面的方式拉高
    //因为SSOE模式下引脚拉高需要关闭SPI,而这个关闭应该在spi传输时使用
    Read_Pin.Pin_High();
    Read_Pin.IN_MODE();
    //测试引脚电平变化
    // while (1)
    // {
    //     SPI_1_Test.NSS_Low();
    //     SysTick_Operate::Delay_ms(1000);
    //     LED_1.Toggle();
    //     SPI_1_Test.NSS_High();
    //     SysTick_Operate::Delay_ms(1000);
    // }
#endif
#if TEST_MODE == 5
    NVIC_InitTypeDef SPI1_NVIC_InitStructure = {
        SPI1_IRQn,
        0,
        13,
        ENABLE};
    NVIC_InitTypeDef SPI2_NVIC_InitStructure = {
        SPI2_IRQn,
        0,
        14,
        ENABLE};
    SPI_InitTypeDef SPI1_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Master,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        7};
    SPI_InitTypeDef SPI2_InitStructure = {
        SPI_Direction_2Lines_FullDuplex,
        SPI_Mode_Slave,
        SPI_DataSize_8b,
        SPI_CPOL_Low,
        SPI_CPHA_1Edge,
        SPI_NSS_Hard,
        SPI_BaudRatePrescaler_2,
        SPI_FirstBit_MSB,
        7};
    SPI_Param SPI1_Param = {
        SPI1,
        SPI1_InitStructure,
        SPI_NSS_Master_SSOE_Hard,
        NVIC_Operate(SPI1_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    SPI_Param SPI2_Param = {
        SPI2,
        SPI2_InitStructure,
        SPI_NSS_Slave_Hard,
        NVIC_Operate(SPI2_NVIC_InitStructure),
        DISABLE,
        SPI_I2S_IT_ERR,
    };
    GPIO NSS_Soft = GPIO(PA4);
    SPI_1_Test = SPI(SPI1_Param);
    SPI_2_Test = SPI(SPI2_Param);
    // SPI_1_Test.Set_NSS_Pin(NSS_Soft);
    SPI_2_Test.Init();
    SPI_1_Test.Init();
    SPI_1_Test.CalculateCRC(ENABLE);
    SPI_2_Test.CalculateCRC(ENABLE);

    NVIC_InitTypeDef SPI2_RX_DMA_NVIC_InitStructure = {
        SPI2_RX_DMA_CHANNEL_IRQN,
        0,
        10,
        ENABLE};
    SPI2_RX_DMA_InitStructure = {
        SPI2_RX_DR_ADDR,
        (uint32_t)ReceiveBuffer,
        DMA_DIR_PeripheralSRC,
        strlen(SendBuffer) + 1,
        DMA_PeripheralInc_Disable,
        DMA_MemoryInc_Enable,
        DMA_PeripheralDataSize_Byte,
        DMA_MemoryDataSize_Byte,
        DMA_Mode_Normal,
        DMA_Priority_VeryHigh,
        DMA_M2M_Disable};
    DMA_Param SPI2_RX_DMA_Param = {
        SPI2_RX_DMA_CHANNEL,
        SPI2_RX_DMA_InitStructure,
        NVIC_Operate(SPI2_RX_DMA_NVIC_InitStructure),
        DISABLE,
        DMA_IT_TE // DMA_IT_TC | DMA_IT_HT | DMA_IT_TE(这个只是供你选择,实际并不能用与的形式传参)
    };
    SPI2_RX_DMA = DMA(SPI2_RX_DMA_Param);
    NVIC_InitTypeDef SPI1_TX_DMA_NVIC_InitStructure = {
        SPI1_TX_DMA_CHANNEL_IRQN,
        0,
        11,
        ENABLE};
    DMA_InitTypeDef SPI1_TX_DMA_InitStructure = {
        SPI1_TX_DR_ADDR,
        (uint32_t)SendBuffer,
        DMA_DIR_PeripheralDST,
        strlen(SendBuffer) + 1,
        DMA_PeripheralInc_Disable,
        DMA_MemoryInc_Enable,
        DMA_PeripheralDataSize_Byte,
        DMA_MemoryDataSize_Byte,
        DMA_Mode_Normal,
        DMA_Priority_High,
        DMA_M2M_Disable};
    DMA_Param SPI1_TX_DMA_Param = {
        SPI1_TX_DMA_CHANNEL,
        SPI1_TX_DMA_InitStructure,
        NVIC_Operate(SPI1_TX_DMA_NVIC_InitStructure),
        DISABLE,
        DMA_IT_TC | DMA_IT_HT | DMA_IT_TE};
    // SPI1_TX_DMA = DMA(SPI1_TX_DMA_Param);
    // SPI_1_Test.Use_DMA(SPI_DMA_TX, ENABLE);
#endif
    SPI2_RX_DMA.Init();
    SPI_2_Test.Use_DMA(SPI_DMA_RX, ENABLE);
}
void Test()
{
#if TEST_MODE != 5
    while (1)
    {
        //片选拉低
        SPI_1_Test.NSS_Low();
        //发送单个数据
        // SPI_1_Test.Send_Data('1');
        // printf("测试一:接收单个字节 %c\n", SPI_2_Test.Receive_Data());
        //发送多个数据
        //由于SPI1发送大量数据,所以使用DMA验证
        //清空接收缓冲区
        memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
        SPI_1_Test.Send_Buffer((uint8_t *)SendBuffer, strlen(SendBuffer) + 1);
        printf("测试一:接收字符串\n%s\n", ReceiveBuffer);
        //延时
        SysTick_Operate::Delay_ms(250);
        LED_1.Toggle();
        SPI_1_Test.NSS_High();
        //二次延时使得电平变化更明显
        SysTick_Operate::Delay_ms(250);
    }
#else
    while (1)
    {
        //片选拉低
        SPI_1_Test.NSS_Low();
        //发送多个数据
        //由于SPI1发送大量数据,所以使用DMA验证
        //清空接收缓冲区
        memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
        //由于使用DMA传输CRC会占用一定的空间,导致指针直接从尾指向头,从而导致下一次数据错位,所以复位DMA
        //需要注意的是这个初始化需要多初始化一次,不知道为什么反正两次就好使
        SPI2_RX_DMA.Init();
        SPI2_RX_DMA.Init();
        //开启SPI1_TX DMA通道
        // SPI1_TX_DMA.Init();
        SPI_1_Test.Send_Buffer((uint8_t *)SendBuffer, strlen(SendBuffer) + 1);
        //等待SPI2_RX DMA传输完成
        while (DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET)
            ;
        printf("SPI1 CRC:%d\n\n", SPI_1_Test.GetCRC(SPI_CRC_Tx));
        //判断是否校验成功
        if (SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_CRCERR) == RESET)
        {
            printf("测试一:接收字符串\n%s\n", (uint8_t *)ReceiveBuffer);
            printf("SPI2 CRC:%d\n\n", SPI_2_Test.GetCRC(SPI_CRC_Rx));
        }
        else
        {
            printf("校验失败!\n");
        }
        // CRC寄存器清零
        SPI_1_Test.ClearCRC();
        SPI_2_Test.ClearCRC();
        //延时
        SysTick_Operate::Delay_ms(500);
        LED_1.Toggle();
        SPI_1_Test.NSS_High();
        //二次延时使得电平变化更明显
        SysTick_Operate::Delay_ms(500);
    }
#endif
}
void End()
{
}