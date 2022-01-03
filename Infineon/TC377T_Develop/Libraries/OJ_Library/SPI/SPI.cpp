#include "SPI.h"
/*
 * @brief       SPI�չ��췽��
 * @param       void
 * @return      null
 */
SPI::SPI ()
{

}

/*
 * @brief       GPIO��������
 * @param       void
 * @return      null
 */
SPI::~SPI ()
{

}

/*
 * @brief       SPI���ι��췽��
 * @param       Param       SPI�����б�
 * @return      null
 */
SPI::SPI (SPI_Param Param)
{
    Set_Param(Param);
}

/*
 * @brief       SPI���ò�������
 * @param       Param       SPI�����б�
 * @return      void
 */
void SPI::Set_Param (SPI_Param Param)
{
    this->Param = Param;
}

/*
 * @brief       SPI��ʼ��
 * @param       null
 * @return      void
 */
void SPI::Init ()
{
    spi_init(Param.SPI_Selection, Param.SCK_Pin, Param.MOSI_Pin, Param.MISO_Pin,
            Param.CS_Pin, Param.Mode, Param.Baud);
}

/*
 * @brief       SPI���ͽ��շ���
 * @param       modata      ���͵����ݻ�������ַ
 * @param       midata      ��������ʱ���յ������ݵĴ洢��ַ(����Ҫ������ NULL)
 * @param       len         ���͵��ֽ���
 * @param       continuous  ����ͨ����CS�Ƿ����������Ч״̬ 1:��������  0:ÿ������һ���ֽڹر�CS(һ������Ϊ1 ����)
 * @return      void
 */
void SPI::MOSI_Send (uint8 *modata, uint8 *midata, uint32 len, uint8 continuous)
{
    spi_mosi(Param.SPI_Selection, Param.CS_Pin, modata, midata, len, continuous);
}
