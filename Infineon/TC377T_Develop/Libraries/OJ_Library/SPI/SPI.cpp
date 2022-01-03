#include "SPI.h"
/*
 * @brief       SPI空构造方法
 * @param       void
 * @return      null
 */
SPI::SPI ()
{

}

/*
 * @brief       GPIO析构方法
 * @param       void
 * @return      null
 */
SPI::~SPI ()
{

}

/*
 * @brief       SPI带参构造方法
 * @param       Param       SPI参数列表
 * @return      null
 */
SPI::SPI (SPI_Param Param)
{
    Set_Param(Param);
}

/*
 * @brief       SPI设置参数方法
 * @param       Param       SPI参数列表
 * @return      void
 */
void SPI::Set_Param (SPI_Param Param)
{
    this->Param = Param;
}

/*
 * @brief       SPI初始化
 * @param       null
 * @return      void
 */
void SPI::Init ()
{
    spi_init(Param.SPI_Selection, Param.SCK_Pin, Param.MOSI_Pin, Param.MISO_Pin,
            Param.CS_Pin, Param.Mode, Param.Baud);
}

/*
 * @brief       SPI发送接收方法
 * @param       modata      发送的数据缓冲区地址
 * @param       midata      发送数据时接收到的数据的存储地址(不需要接收则传 NULL)
 * @param       len         发送的字节数
 * @param       continuous  本次通信是CS是否持续保持有效状态 1:持续保持  0:每传输完一个字节关闭CS(一般设置为1 即可)
 * @return      void
 */
void SPI::MOSI_Send (uint8 *modata, uint8 *midata, uint32 len, uint8 continuous)
{
    spi_mosi(Param.SPI_Selection, Param.CS_Pin, modata, midata, len, continuous);
}
