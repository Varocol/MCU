#ifndef __OJ_SPI_H
#define __OJ_SPI_H
#include "headfile.h"

//SPIģʽ 0��CPOL=0 CPHA=0    1��CPOL=0 CPHA=1   2��CPOL=1 CPHA=0   3��CPOL=1 CPHA=1
typedef enum
{
    SPI_Mode_0, SPI_Mode_1, SPI_Mode_2, SPI_Mode_3
} SPI_Mode;

//SPI�����ṹ��
typedef struct
{
        SPIN_enum SPI_Selection;        //SPI ģ���
        SPI_PIN_enum CS_Pin;            //SPI Ƭѡ����
        SPI_PIN_enum SCK_Pin;           //SPI ʱ������
        SPI_PIN_enum MOSI_Pin;          //SPI MOSI����
        SPI_PIN_enum MISO_Pin;          //SPI MISO����
        SPI_Mode Mode;                  //SPI ����ģʽ
        uint32 Baud;                    //SPI ������
} SPI_Param;

class SPI
{
    private:
        SPI_Param Param;
    public:
        SPI ();
        ~SPI ();
        SPI (SPI_Param Param);
        void Set_Param (SPI_Param Param);
        void Init ();
        void MOSI_Send (uint8 *modata, uint8 *midata, uint32 len, uint8 continuous);
};

#endif  /*__OJ_SPI_H*/
