#include "SPI.h"
/**
 * @brief  SPI-空构造方法
 * @param  None
 * @retval None
 */
SPI::SPI()
{
}

/**
 * @brief  SPI-析构方法
 * @param  None
 * @retval None
 */
SPI::~SPI()
{
}

/**
 * @brief  SPI-构造方法
 * @param  SPIx_Param   SPI的参数列表
 * @retval None
 */
SPI::SPI(SPI_Param SPIx_Param)
{
    Set_SPI_Param(SPIx_Param);
}

/**
 * @brief  SPI-发送字节
 * @param  data         16位数据
 * @retval None
 */
void SPI::Send_Data(uint16_t data)
{
    SPI_I2S_SendData(SPIx_Param.SPIx, data);
    while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_TXE) == RESET)
        ;
}

/**
 * @brief  SPI-发送字节数组(自带发送CRC功能)
 * @param  buffer       16位字节数组
 * @param  cnt          16位字节数组大小
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
 * @brief  SPI-发送字节数组(自带发送CRC功能)
 * @param  buffer       16位字节数组
 * @param  cnt          16位字节数组大小
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
 * @brief  SPI-接收字节
 * @param  None
 * @retval 接收缓冲器的值
 */
uint16_t SPI::Receive_Data()
{
    return SPI_I2S_ReceiveData(SPIx_Param.SPIx);
}

/**
 * @brief  SPI-GPIO引脚初始化
 * @param  None
 * @retval None
 */
void SPI::Pin_Init()
{
    GPIO SCK = GPIO();
    GPIO MOSI = GPIO();
    GPIO MISO = GPIO();
    //初始化软件NSS
    if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Soft)
    {
        NSS.Init();
    }

    //初始化主模式下 硬件NSS SSOE=0,SSM=0 即输入模式(此时使用软件引脚)
    if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard && SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && SPIx_Param.SPI_NSS == SPI_NSS_Master_Hard)
    {
        NSS.Init();
    }

    //以下初始化SCK MOSI MISO和硬件NSS
    if (SPIx_Param.SPIx == SPI1)
    {
        if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master)
        {
            if (SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard)
            {
                // SSOE开启,输出模式下,需要用到硬件NSS
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
                // SSOE开启,输出模式下,需要用到硬件NSS
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
                // SSOE开启,输出模式下,需要用到硬件NSS
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
 * @brief  SPI-片选引脚拉高
 * @param  None
 * @retval None
 */
void SPI::NSS_High()
{
    Set_NSS_Val(1);
}

/**
 * @brief  SPI-片选引脚拉低
 * @param  None
 * @retval None
 */
void SPI::NSS_Low()
{
    Set_NSS_Val(0);
}

/**
 * @brief  SPI-设置NSS软件模式片选引脚高低
 * @note   在软件主模式下,从设备完全受NSS_Soft引脚的管理,
 *         在软件从模式下,SPINSS信号受到SSI位影响,所以不需要
 *         NSS_Soft的初始化也能够执行。
 * @param  BitVal       状态值
 * @retval None
 */
void SPI::Set_NSS_Val(uint8_t BitVal)
{
    uint16_t SPI_MODE = SPIx_Param.SPI_InitStructure.SPI_Mode;
    uint16_t SPI_NSS = SPIx_Param.SPI_InitStructure.SPI_NSS;
    uint8_t SPI_NSS_Mode = SPIx_Param.SPI_NSS;
    //软件 主模式(主要被使用)
    if (SPI_MODE == SPI_Mode_Master && SPI_NSS == SPI_NSS_Soft)
    {
        NSS.Set_Pin_Val(BitVal);
    }
    //软件 从模式(基本用不到)
    else if (SPI_MODE == SPI_Mode_Slave && SPI_NSS == SPI_NSS_Soft)
    {
        //取最后一位
        if (BitVal & 0x01)
        {
            SPI_NSSInternalSoftwareConfig(SPIx_Param.SPIx, SPI_NSSInternalSoft_Set);
        }
        else
        {
            SPI_NSSInternalSoftwareConfig(SPIx_Param.SPIx, SPI_NSSInternalSoft_Reset);
        }
    }
    //硬件 主模式输入模式(ssoe = 0,ssm = 0),NSS对象为外部设置的空闲GPIO对象
    //硬件 主模式输出模式(ssoe = 1,ssm = 0),NSS对象为对应硬件NSS引脚的GPIO对象
    else if (SPI_MODE == SPI_Mode_Master && SPI_NSS == SPI_NSS_Hard)
    {
        if (SPI_NSS_Mode == SPI_NSS_Master_SSOE_Hard)
        {
            //输出模式下,关闭SPI,并拉高NSS引脚(Stm32的bug,一定要关闭SPI后这个引脚才能释放
            //否则如果SSOE=1,此时引脚不受GPIO控制,若SSOE=0,则下一次硬件无法再次控制此引脚)
            if (BitVal & 0x01)
            {
                ShutUp();
                NSS.Set_Pin_Val(1);
            }
            //输入模式下,开启SSOE,引脚自动拉低
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
 * @brief  SPI-设置NSS软件模式片选引脚高低
 * @note   该方法也适合当ssoe=0,ssm=0时,nss工作于硬件模式的
 *         输入模式下,该模式下外部引脚被ssoe控制,所以可以尝试
 *         使用其他引脚代替。
 * @param  NSS_Soft     NSS GPIO对象
 * @retval None
 */
void SPI::Set_NSS_Pin(GPIO &NSS_Soft)
{
    NSS = NSS_Soft;
}

/**
 * @brief  SPI-参数列表更新
 * @param  SPIx_Param   SPI的参数列表
 * @retval None
 */
void SPI::Update(SPI_Param SPIx_Param)
{
    SPI_I2S_DeInit(this->SPIx_Param.SPIx);
    Set_SPI_Param(SPIx_Param);
    Init();
}

/**
 * @brief  SPI-设置SPI的参数列表
 * @param  SPIx_Param   SPI的参数列表
 * @retval None
 */
void SPI::Set_SPI_Param(SPI_Param SPIx_Param)
{
    this->SPIx_Param = SPIx_Param;
}

/**
 * @brief  SPI-使用DMA传输功能
 * @param  SPI_DMA_enum 使用DMA传输的引脚
 * @param  state        是否使能DMA
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
 * @brief  SPI-中断方法
 * @param  SPI_I2S_IT   中断标志的选择
 * @param  NewState     使能或失能
 * @retval None
 */
void SPI::ITConfig(uint8_t SPI_I2S_IT, FunctionalState NewState)
{
    SPI_I2S_ITConfig(SPIx_Param.SPIx, SPI_I2S_IT, NewState);
}

/**
 * @brief  SPI-启用CRC计算
 * @param  NewState     使能或失能
 * @retval None
 */
void SPI::CalculateCRC(FunctionalState NewState)
{
    FunctionalState SPI_State;
    uint16_t CR1_SPE_Set = ((uint16_t)0x0040);
    //获取SPI状态
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
 * @brief  SPI-清空CRC校验值
 * @param  NewState     使能或失能
 * @retval None
 */
void SPI::ClearCRC()
{
    FunctionalState SPI_State;
    uint16_t CR1_SPE_Set = ((uint16_t)0x0040);
    //获取SPI状态
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
 * @brief  SPI-启用CRC计算
 * @param  None
 * @retval None
 */
void SPI::TransmitCRC()
{
    SPI_TransmitCRC(SPIx_Param.SPIx);
}

/**
 * @brief  SPI-获取CRC校验值
 * @param  SPI_CRC      SPI_CRC_TX或者SPI_CRC_RX
 * @retval CRC寄存器中的值
 */
uint16_t SPI::GetCRC(uint8_t SPI_CRC)
{
    return SPI_GetCRC(SPIx_Param.SPIx, SPI_CRC);
}

/**
 * @brief  SPI-初始化方法
 * @param  None
 * @retval None
 */
void SPI::Init()
{
    //开启SPI时钟
    RCC_Operate::RCC_Config(SPIx_Param.SPIx, ENABLE);
    // SPIx寄存器复位
    SPI_I2S_DeInit(SPIx_Param.SPIx);
    //引脚初始化
    Pin_Init();
    //配置SPI
    SPI_Init(SPIx_Param.SPIx, &SPIx_Param.SPI_InitStructure);
    //配置SPI中断优先级
    SPIx_Param.SPI_NVIC_Operate.Init();
    //配置SPI中断
    ITConfig(SPIx_Param.SPI_IT_Selection, SPIx_Param.SPI_IT_State);
    //配置为NSS硬件模式的输出模式(ssoe=1,ssm=0)
    if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && SPIx_Param.SPI_InitStructure.SPI_NSS == SPI_NSS_Hard && SPIx_Param.SPI_NSS == SPI_NSS_Master_SSOE_Hard)
    {
        SPI_SSOutputCmd(SPIx_Param.SPIx, ENABLE);
    }
    //使能SPI
    Start();
}

/**
 * @brief  SPI-开启SPI方法(SPI使能)
 * @param  None
 * @retval None
 */
void SPI::Start()
{
    SPI_Cmd(SPIx_Param.SPIx, ENABLE);
}

/**
 * @brief  SPI-关闭SPI方法(SPI失能)
 * @param  None
 * @retval None
 */
void SPI::ShutUp()
{
    uint16_t SPI_Direction = SPIx_Param.SPI_InitStructure.SPI_Direction;
    //在主或从模式下的全双工模式(BIDIMODE=0，RXONLY=0)
    if (SPI_Direction == SPI_Direction_2Lines_FullDuplex)
    {
        //等待RXNE=1并接收最后一个数据
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //等待TXE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //等待BSY=0
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_BSY) == SET)
            ;
    }
    //在主或从模式下的单向只发送模式(BIDIMODE=0，RXONLY=0)或双向的发送模式(BIDIMODE=1，BIDIOE=1)
    //单向只发送重复上面,所以只写双向的发送模式
    else if (SPI_Direction == SPI_Direction_1Line_Tx)
    {
        //等待TXE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //等待BSY=0
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_BSY) == SET)
            ;
    }
    //在主模式下的单向只接收模式(MSTR=1，BIDIMODE=0，RXONLY=1)或双向的接收模式(MSTR=1，BIDIMODE=1，BIDIOE=0)
    else if (SPIx_Param.SPI_InitStructure.SPI_Mode == SPI_Mode_Master && (SPI_Direction == SPI_Direction_2Lines_RxOnly || SPI_Direction == SPI_Direction_1Line_Rx))
    {
        //等待最后一个RXNE=1
        while (SPI_I2S_GetFlagStatus(SPIx_Param.SPIx, SPI_I2S_FLAG_RXNE) == RESET)
            ;
        //最后一个数据由外部代码读出
    }
    SPI_Cmd(SPIx_Param.SPIx, DISABLE);
}