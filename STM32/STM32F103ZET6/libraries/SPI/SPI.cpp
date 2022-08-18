#include "SPI.h"
/**
 * @brief  SPI-�չ��췽��
 * @param  None
 * @retval None
 */
SPI::SPI()
{
}

/**
 * @brief  SPI-��������
 * @param  None
 * @retval None
 */
SPI::~SPI()
{
}

/**
 * @brief  SPI-���췽��
 * @param  SPIx_Param   SPI�Ĳ����б�
 * @retval None
 */
SPI::SPI(SPI_Param SPIx_Param)
{
    Set_SPI_Param(SPIx_Param);
}

/**
 * @brief  SPI-�����ֽ�
 * @param  data         16λ����
 * @retval None
 */
void SPI::Send_Data(uint16_t data)
{
    SPI_I2S_SendData(SPIx_Param.SPIx, data);
    while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_TXE) == RESET)
        ;
}

/**
 * @brief  SPI-�����ֽ�����(�Դ�����CRC����)
 * @param  buffer       16λ�ֽ�����
 * @param  cnt          16λ�ֽ������С
 * @retval None
 */
void SPI::Send_Buffer(uint8_t *buffer, uint32_t cnt)
{
    FunctionalState CRC_State;
    uint16_t CR1_CRCEN_Set = 0x2000;
    if (SPIx_Param.SPIx->CR1 & CR1_CRCEN_Set)
    {
        CRC_State = ENABLE;
    }
    else
    {
        CRC_State = DISABLE;
    }
    for (uint32_t i = 0; i < cnt; i++)
    {
        if (i == cnt - 1 && CRC_State == ENABLE)
        {
            TransmitCRC();
        }
        Send_Data(buffer[i]);
    }
}

/**
 * @brief  SPI-�����ֽ�����(�Դ�����CRC����)
 * @param  buffer       16λ�ֽ�����
 * @param  cnt          16λ�ֽ������С
 * @retval None
 */
void SPI::Send_Buffer(uint16_t *buffer, uint32_t cnt)
{
    FunctionalState CRC_State;
    uint16_t CR1_CRCEN_Set = 0x2000;
    if (SPIx_Param.SPIx->CR1 & CR1_CRCEN_Set)
    {
        CRC_State = ENABLE;
    }
    else
    {
        CRC_State = DISABLE;
    }
    for (uint32_t i = 0; i < cnt; i++)
    {
        if (i == cnt - 1 && CRC_State == ENABLE)
        {
            TransmitCRC();
        }
        Send_Data(buffer[i]);
    }
}

/**
 * @brief  SPI-�����ֽ�
 * @param  None
 * @retval ���ջ�������ֵ
 */
uint16_t SPI::Receive_Data()
{
    return SPI_I2S_ReceiveData(SPIx_Param.SPIx);
}

/**
 * @brief  SPI-GPIO���ų�ʼ��
 * @param  None
 * @retval None
 */
void SPI::Pin_Init()
{
    GPIO SCK = GPIO();
    GPIO MOSI = GPIO();
    GPIO MISO = GPIO();
    //��ʼ�����NSS
    if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Soft)
    {
        NSS.Init();
    }

    //��ʼ����ģʽ�� Ӳ��NSS SSOE=0,SSM=0 ������ģʽ(��ʱʹ���������)
    if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard && SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && SPIx_Param.SPI_NSS == SPI_NSS_Master_Hard)
    {
        NSS.Init();
    }

    //���³�ʼ��SCK MOSI MISO��Ӳ��NSS
    if (SPIx_Param.SPIx == SPI1)
    {
        if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master)
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                // SSOE����,���ģʽ��,��Ҫ�õ�Ӳ��NSS
                if (SPIx_Param.SPI_NSS == SPI_NSS_Master_SSOE_Hard)
                {
                    NSS = GPIO();
                    NSS.Update(PA4, GPIO_Mode_AF_PP);
                }
            }
            SCK.Update(PA5, GPIO_Mode_AF_PP);
            MOSI.Update(PA7, GPIO_Mode_AF_PP);
            MISO.Update(PA6, GPIO_Mode_IPU);
        }
        else
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                NSS.Update(PA4, GPIO_Mode_IPU);
            }
            SCK.Update(PA5, GPIO_Mode_IN_FLOATING);
            MOSI.Update(PA7, GPIO_Mode_IPU);
            MISO.Update(PA6, GPIO_Mode_AF_PP);
        }
    }
    else if (SPIx_Param.SPIx == SPI2)
    {
        if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master)
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                // SSOE����,���ģʽ��,��Ҫ�õ�Ӳ��NSS
                if (SPIx_Param.SPI_NSS == SPI_NSS_Master_SSOE_Hard)
                {
                    NSS = GPIO();
                    NSS.Update(PB12, GPIO_Mode_AF_PP);
                }
            }
            SCK.Update(PB13, GPIO_Mode_AF_PP);
            MOSI.Update(PB15, GPIO_Mode_AF_PP);
            MISO.Update(PB14, GPIO_Mode_IPU);
        }
        else
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                NSS.Update(PB12, GPIO_Mode_IPU);
            }
            SCK.Update(PB13, GPIO_Mode_IN_FLOATING);
            MOSI.Update(PB15, GPIO_Mode_IPU);
            MISO.Update(PB14, GPIO_Mode_AF_PP);
        }
    }
    else if (SPIx_Param.SPIx == SPI3)
    {
        if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master)
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                // SSOE����,���ģʽ��,��Ҫ�õ�Ӳ��NSS
                if (SPIx_Param.SPI_NSS == SPI_NSS_Master_SSOE_Hard)
                {
                    NSS = GPIO();
                    NSS.Update(PA15, GPIO_Mode_AF_PP);
                }
            }
            SCK.Update(PB3, GPIO_Mode_AF_PP);
            MOSI.Update(PB5, GPIO_Mode_AF_PP);
            MISO.Update(PB4, GPIO_Mode_IPU);
        }
        else
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                NSS.Update(PA15, GPIO_Mode_IPU);
            }
            SCK.Update(PB3, GPIO_Mode_IN_FLOATING);
            MOSI.Update(PB5, GPIO_Mode_IPU);
            MISO.Update(PB4, GPIO_Mode_AF_PP);
        }
    }
}

/**
 * @brief  SPI-Ƭѡ��������
 * @param  None
 * @retval None
 */
void SPI::NSS_High()
{
    Set_NSS_Val(1);
}

/**
 * @brief  SPI-Ƭѡ��������
 * @param  None
 * @retval None
 */
void SPI::NSS_Low()
{
    Set_NSS_Val(0);
}

/**
 * @brief  SPI-����NSS���ģʽƬѡ���Ÿߵ�
 * @note   �������ģʽ��,���豸��ȫ��NSS_Soft���ŵĹ���,
 *         �������ģʽ��,SPINSS�ź��ܵ�SSIλӰ��,���Բ���Ҫ
 *         NSS_Soft�ĳ�ʼ��Ҳ�ܹ�ִ�С�
 * @param  BitVal       ״ֵ̬
 * @retval None
 */
void SPI::Set_NSS_Val(uint8_t BitVal)
{
    uint16_t SPI_MODE = SPIx_Param.SPI_InitStructure.SPI_Mode;
    uint16_t SPI_NSS = SPIx_Param.SPI_InitStructure.SPI_NSS;
    uint8_t SPI_NSS_Mode = SPIx_Param.SPI_NSS;
    //��� ��ģʽ(��Ҫ��ʹ��)
    if (SPI_MODE == SPI_Mode_Master && SPI_NSS == SPI_NSS_Soft)
    {
        NSS.Set_Pin_Val(BitVal);
    }
    //��� ��ģʽ(�����ò���)
    else if (SPI_MODE == SPI_Mode_Slave && SPI_NSS == SPI_NSS_Soft)
    {
        //ȡ���һλ
        if (BitVal & 0x01)
        {
            SPI_NSSInternalSoftwareConfig(SPIx_Param.SPIx, SPI_NSSInternalSoft_Set);
        }
        else
        {
            SPI_NSSInternalSoftwareConfig(SPIx_Param.SPIx, SPI_NSSInternalSoft_Reset);
        }
    }
    //Ӳ�� ��ģʽ����ģʽ(ssoe = 0,ssm = 0),NSS����Ϊ�ⲿ���õĿ���GPIO����
    //Ӳ�� ��ģʽ���ģʽ(ssoe = 1,ssm = 0),NSS����Ϊ��ӦӲ��NSS���ŵ�GPIO����
    else if (SPI_MODE == SPI_Mode_Master && SPI_NSS == SPI_NSS_Hard)
    {
        if (SPI_NSS_Mode == SPI_NSS_Master_SSOE_Hard)
        {
            //���ģʽ��,�ر�SPI,������NSS����(Stm32��bug,һ��Ҫ�ر�SPI��������Ų����ͷ�
            //�������SSOE=1,��ʱ���Ų���GPIO����,��SSOE=0,����һ��Ӳ���޷��ٴο��ƴ�����)
            if (BitVal & 0x01)
            {
                ShutUp();
                NSS.Set_Pin_Val(1);
            }
            //����ģʽ��,����SSOE,�����Զ�����
            else
            {
                Start();
            }
        }
        else if (SPI_NSS_Mode == SPI_NSS_Master_Hard)
        {
            NSS.Set_Pin_Val(BitVal);
        }
    }
}

/**
 * @brief  SPI-����NSS���ģʽƬѡ���Ÿߵ�
 * @note   �÷���Ҳ�ʺϵ�ssoe=0,ssm=0ʱ,nss������Ӳ��ģʽ��
 *         ����ģʽ��,��ģʽ���ⲿ���ű�ssoe����,���Կ��Գ���
 *         ʹ���������Ŵ��档
 * @param  NSS_Soft     NSS GPIO����
 * @retval None
 */
void SPI::Set_NSS_Pin(GPIO &NSS_Soft)
{
    NSS = NSS_Soft;
}

/**
 * @brief  SPI-�����б����
 * @param  SPIx_Param   SPI�Ĳ����б�
 * @retval None
 */
void SPI::Update(SPI_Param SPIx_Param)
{
    SPI_I2S_DeInit(this->SPIx_Param.SPIx);
    Set_SPI_Param(SPIx_Param);
    Init();
}

/**
 * @brief  SPI-����SPI�Ĳ����б�
 * @param  SPIx_Param   SPI�Ĳ����б�
 * @retval None
 */
void SPI::Set_SPI_Param(SPI_Param SPIx_Param)
{
    this->SPIx_Param = SPIx_Param;
}

/**
 * @brief  SPI-ʹ��DMA���书��
 * @param  SPI_DMA_enum ʹ��DMA���������
 * @param  state        �Ƿ�ʹ��DMA
 * @retval None
 */
void SPI::Use_DMA(SPI_DMA_enum SPI_DMA_enum, FunctionalState state)
{
    switch (SPI_DMA_enum)
    {
    case SPI_DMA_TX:
        SPI_I2S_DMACmd(SPIx_Param.SPIx, SPI_I2S_DMAReq_Tx, state);
        break;
    case SPI_DMA_RX:
        SPI_I2S_DMACmd(SPIx_Param.SPIx, SPI_I2S_DMAReq_Rx, state);
        break;
    case SPI_DMA_BOTH:
        SPI_I2S_DMACmd(SPIx_Param.SPIx, SPI_I2S_DMAReq_Tx | SPI_I2S_DMAReq_Rx, state);
        break;
    }
}

/**
 * @brief  SPI-�жϷ���
 * @param  SPI_I2S_IT   �жϱ�־��ѡ��
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void SPI::ITConfig(uint8_t SPI_I2S_IT, FunctionalState NewState)
{
    SPI_I2S_ITConfig(SPIx_Param.SPIx, SPI_I2S_IT, NewState);
}

/**
 * @brief  SPI-����CRC����
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void SPI::CalculateCRC(FunctionalState NewState)
{
    FunctionalState SPI_State;
    uint16_t CR1_SPE_Set = ((uint16_t)0x0040);
    //��ȡSPI״̬
    if (SPIx_Param.SPIx->CR1 & CR1_SPE_Set)
    {
        SPI_State = ENABLE;
    }
    else
    {
        SPI_State = DISABLE;
    }
    SPI_Cmd(SPIx_Param.SPIx, DISABLE);
    SPI_CalculateCRC(SPIx_Param.SPIx, NewState);
    SPI_Cmd(SPIx_Param.SPIx, SPI_State);
}

/**
 * @brief  SPI-���CRCУ��ֵ
 * @param  NewState     ʹ�ܻ�ʧ��
 * @retval None
 */
void SPI::ClearCRC()
{
    FunctionalState SPI_State;
    uint16_t CR1_SPE_Set = ((uint16_t)0x0040);
    //��ȡSPI״̬
    if (SPIx_Param.SPIx->CR1 & CR1_SPE_Set)
    {
        SPI_State = ENABLE;
    }
    else
    {
        SPI_State = DISABLE;
    }
    SPI_Cmd(SPIx_Param.SPIx, DISABLE);
    SPI_CalculateCRC(SPIx_Param.SPIx, DISABLE);
    SPI_CalculateCRC(SPIx_Param.SPIx, ENABLE);
    SPI_Cmd(SPIx_Param.SPIx, ENABLE);
    SPI_Cmd(SPIx_Param.SPIx, SPI_State);
}

/**
 * @brief  SPI-����CRC����
 * @param  None
 * @retval None
 */
void SPI::TransmitCRC()
{
    SPI_TransmitCRC(SPIx_Param.SPIx);
}

/**
 * @brief  SPI-��ȡCRCУ��ֵ
 * @param  SPI_CRC      SPI_CRC_TX����SPI_CRC_RX
 * @retval CRC�Ĵ����е�ֵ
 */
uint16_t SPI::GetCRC(uint8_t SPI_CRC)
{
    return SPI_GetCRC(SPIx_Param.SPIx, SPI_CRC);
}

/**
 * @brief  SPI-��ʼ������
 * @param  None
 * @retval None
 */
void SPI::Init()
{
    //����SPIʱ��
    RCC_Operate::RCC_Config(SPIx_Param.SPIx, ENABLE);
    // SPIx�Ĵ�����λ
    SPI_I2S_DeInit(SPIx_Param.SPIx);
    //���ų�ʼ��
    Pin_Init();
    //����SPI
    SPI_Init(SPIx_Param.SPIx, &SPIx_Param.SPI_InitStructure);
    //����SPI�ж����ȼ�
    SPIx_Param.SPI_NVIC_Operate.Init();
    //����SPI�ж�
    ITConfig(SPIx_Param.SPI_IT_Selection, SPIx_Param.SPI_IT_State);
    //����ΪNSSӲ��ģʽ�����ģʽ(ssoe=1,ssm=0)
    if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard && SPIx_Param.SPI_NSS == SPI_NSS_Master_SSOE_Hard)
    {
        SPI_SSOutputCmd(SPIx_Param.SPIx, ENABLE);
    }
    //ʹ��SPI
    Start();
}

/**
 * @brief  SPI-����SPI����(SPIʹ��)
 * @param  None
 * @retval None
 */
void SPI::Start()
{
    SPI_Cmd(SPIx_Param.SPIx, ENABLE);
}

/**
 * @brief  SPI-�ر�SPI����(SPIʧ��)
 * @param  None
 * @retval None
 */
void SPI::ShutUp()
{
    uint16_t SPI_Direction = SPIx_Param.SPI_InitStructure.SPI_Direction;
    //�������ģʽ�µ�ȫ˫��ģʽ(BIDIMODE=0��RXONLY=0)
    if (SPI_Direction == SPI_Direction_2Lines_FullDuplex)
    {
        //�ȴ�RXNE=1���������һ������
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //�ȴ�TXE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //�ȴ�BSY=0
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_BSY) == SET)
            ;
    }
    //�������ģʽ�µĵ���ֻ����ģʽ(BIDIMODE=0��RXONLY=0)��˫��ķ���ģʽ(BIDIMODE=1��BIDIOE=1)
    //����ֻ�����ظ�����,����ֻд˫��ķ���ģʽ
    else if (SPI_Direction == SPI_Direction_1Line_Tx)
    {
        //�ȴ�TXE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //�ȴ�BSY=0
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_BSY) == SET)
            ;
    }
    //����ģʽ�µĵ���ֻ����ģʽ(MSTR=1��BIDIMODE=0��RXONLY=1)��˫��Ľ���ģʽ(MSTR=1��BIDIMODE=1��BIDIOE=0)
    else if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && (SPI_Direction == SPI_Direction_2Lines_RxOnly || SPI_Direction == SPI_Direction_1Line_Rx))
    {
        //�ȴ����һ��RXNE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //���һ���������ⲿ�������
    }
    SPI_Cmd(SPIx_Param.SPIx, DISABLE);
}