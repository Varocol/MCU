#include "Screen.h"
//SPI�����б�
SPI_Param SPI_param = {SPI_2, //����ʹ�õ�SPI��
        SPI2_CS0_P15_2,  //����SPI_CS����
        SPI2_SCLK_P15_3, //����SPI_SCK����
        SPI2_MOSI_P15_5, //����SPI_MOSI����
        SPI2_MISO_P15_4, //����SPI_MISO����
        SPI_Mode_0,      //SPIģʽ(��4��)
        48 * 1000 * 1000 //SPI������
};
//IPS_114�����б�
IPS_114_Param IPS_114_param = {P15_4, //Һ���������Ŷ��� ����ʵ��ͨѶδʹ��P15_4��� ���︴��ΪGPIO
        P15_1, //Һ����λ���Ŷ���
        P15_0, //Һ������λ���Ŷ���
        IPS_RED, //����д�ֱʵ���ɫ
        IPS_WHITE, //���屳����ɫ
        IPS114_W, //����IPS114�����
        IPS114_H, //����IPS114���߶�
        Direction3, //����IPS114��ʾ����
        };
IPS_114 Screen;

/*
 * @brief       ��Ļ��ʼ��
 * @param       null
 * @return      null
 */
void Screen_Init ()
{
    Screen.Set_Param(IPS_114_param, SPI_param);
    Screen.Init();
}

/*
 * @brief       ��Ļ��ʾͼ��
 * @param       null
 * @return      null
 */
void Screen_Show_Img (uint8 *image, uint16 width, uint16 height)
{
    Screen.Displayimage_032(image, width, height);
}

