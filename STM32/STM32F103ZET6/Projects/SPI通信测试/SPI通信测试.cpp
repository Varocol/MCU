#include "Libraries.h"
#define TEST_MODE 5
#define SPI2_RX_DR_ADDR (SPI2_BASE + 0x0C)
#define SPI2_RX_DMA_CHANNEL DMA1_Channel4
#define SPI2_RX_DMA_CHANNEL_IRQN DMA1_Channel4_IRQn
#define SPI1_TX_DR_ADDR (SPI1_BASE + 0x0C)
#define SPI1_TX_DMA_CHANNEL DMA1_Channel3
#define SPI1_TX_DMA_CHANNEL_IRQN DMA1_Channel3_IRQn
/*
    ����һ:
        ����SPI_NSS_Master_Softģʽ
         SPI1��������,ģʽΪ�����ģʽ,SPI2�����ӻ�,ģʽΪӲ����ģʽ,����SPI2���յ��Ľ���������;
    ���Զ�:
        ����SPI_NSS_Master_SSOE_Hardģʽ
        SPI1��������,ģʽΪӲ����ģʽ�����ģʽ(��SPI_NSS_Master_SSOE_Hardģʽ),SPI2�����ӻ�,ģʽΪӲ����ģʽ,����SPI2���յ��Ľ���������;
    ������:
        ����SPI_NSS_Master_Hardģʽ(����ô��,����)
        SPI1��������,ģʽΪӲ����ģʽ������ģʽ(��SPI_NSS_Master_Hardģʽ),SPI2�����ӻ�,ģʽΪӲ����ģʽ,����SPI2���յ��Ľ���������;
    ������:
        ����SPI_NSS_Slave_Softģʽ(���ģʽҲ����ô��)
        SPI1��������,ģʽΪӲ����ģʽ������ģʽ(��SPI_NSS_Master_Hardģʽ),SPI2�����ӻ�,ģʽΪ�����ģʽ,����SPI2���յ��Ľ���������;
        ��β�����,��������ʹ��SPI_NSS_Master_Hardģʽ,����ʹ���������ⲿ����,�ֱ�ΪPC7(����),PC6(�ӻ�),��ȻҲ����������ΪPI_NSS_Master_SSOE_Hard
        ʱ,��ֻʹ��PC6��ģʽ,Ҳ��ͨ����,���Իῴ���в��ִ��뱻ע��,���β������EXTI�ⲿ�жϡ�
    ������:
        CRCУ��,�ٷ��Ƽ��Ĺر�SPI�Ĳ������,�Լ��жϵĲ��ԡ�

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
    //��ʼ������
    USART_1.Init();
    //��ʼ���źŵ�
    LED_1.Init();
#if TEST_MODE != 5
    //��ʼ��DMA
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
        DMA_IT_TC | DMA_IT_HT | DMA_IT_TE // DMA_IT_TC | DMA_IT_HT | DMA_IT_TE(���ֻ�ǹ���ѡ��,ʵ�ʲ������������ʽ����)
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
    //��ģʽ�²�����SSOE,ͬʱҲ����ʼ��nssӲ������,����ʹ������GPIO����������,���������nss,�е㼦��
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
    //��ģʽ�²�����SSOE,ͬʱҲ����ʼ��nssӲ������,����ʹ������GPIO����������,���������nss,�е㼦��
    //�������Slaveģʽ�µ��ⲿnss���Ų������ڲ�nss,������Ҫʹ���ⲿ�жϴ����޸��ڲ�nss
    //���Կ�����Ҫ�����ⲿ����
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
    //��SPI_2_Test����SPI_2ʹ��SPI_2_Test�ܹ����жϺ���ʹ��
    SPI_2 = SPI_2_Test;
    //��ʼ��GPIO PC6,Ϊ�˷����ȡ�����ź�
    GPIO Read_Pin = GPIO(PC6);
    Read_Pin.OUT_MODE();
    //��ʼ���ⲿ�ж�
    EXTI_PC6.Init();
    printf("��ʼ����ɣ�\n");
    //Ƭѡ����ʹ�����½���
    // SPI_1_Test.NSS_High();
    //���������˹ٷ��Ƽ���SPI�رշ���,���Բ���ʹ������ķ�ʽ����
    //��ΪSSOEģʽ������������Ҫ�ر�SPI,������ر�Ӧ����spi����ʱʹ��
    Read_Pin.Pin_High();
    Read_Pin.IN_MODE();
    //�������ŵ�ƽ�仯
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
        DMA_IT_TE // DMA_IT_TC | DMA_IT_HT | DMA_IT_TE(���ֻ�ǹ���ѡ��,ʵ�ʲ������������ʽ����)
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
        //Ƭѡ����
        SPI_1_Test.NSS_Low();
        //���͵�������
        // SPI_1_Test.Send_Data('1');
        // printf("����һ:���յ����ֽ� %c\n", SPI_2_Test.Receive_Data());
        //���Ͷ������
        //����SPI1���ʹ�������,����ʹ��DMA��֤
        //��ս��ջ�����
        memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
        SPI_1_Test.Send_Buffer((uint8_t *)SendBuffer, strlen(SendBuffer) + 1);
        printf("����һ:�����ַ���\n%s\n", ReceiveBuffer);
        //��ʱ
        SysTick_Operate::Delay_ms(250);
        LED_1.Toggle();
        SPI_1_Test.NSS_High();
        //������ʱʹ�õ�ƽ�仯������
        SysTick_Operate::Delay_ms(250);
    }
#else
    while (1)
    {
        //Ƭѡ����
        SPI_1_Test.NSS_Low();
        //���Ͷ������
        //����SPI1���ʹ�������,����ʹ��DMA��֤
        //��ս��ջ�����
        memset(ReceiveBuffer, 0, sizeof(ReceiveBuffer));
        //����ʹ��DMA����CRC��ռ��һ���Ŀռ�,����ָ��ֱ�Ӵ�βָ��ͷ,�Ӷ�������һ�����ݴ�λ,���Ը�λDMA
        //��Ҫע����������ʼ����Ҫ���ʼ��һ��,��֪��Ϊʲô�������ξͺ�ʹ
        SPI2_RX_DMA.Init();
        SPI2_RX_DMA.Init();
        //����SPI1_TX DMAͨ��
        // SPI1_TX_DMA.Init();
        SPI_1_Test.Send_Buffer((uint8_t *)SendBuffer, strlen(SendBuffer) + 1);
        //�ȴ�SPI2_RX DMA�������
        while (DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET)
            ;
        printf("SPI1 CRC:%d\n\n", SPI_1_Test.GetCRC(SPI_CRC_Tx));
        //�ж��Ƿ�У��ɹ�
        if (SPI_I2S_GetFlagStatus(SPI2, SPI_FLAG_CRCERR) == RESET)
        {
            printf("����һ:�����ַ���\n%s\n", (uint8_t *)ReceiveBuffer);
            printf("SPI2 CRC:%d\n\n", SPI_2_Test.GetCRC(SPI_CRC_Rx));
        }
        else
        {
            printf("У��ʧ��!\n");
        }
        // CRC�Ĵ�������
        SPI_1_Test.ClearCRC();
        SPI_2_Test.ClearCRC();
        //��ʱ
        SysTick_Operate::Delay_ms(500);
        LED_1.Toggle();
        SPI_1_Test.NSS_High();
        //������ʱʹ�õ�ƽ�仯������
        SysTick_Operate::Delay_ms(500);
    }
#endif
}
void End()
{
}