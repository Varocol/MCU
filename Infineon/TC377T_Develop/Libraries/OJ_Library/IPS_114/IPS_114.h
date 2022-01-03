#ifndef __OJ_IPS_114_H
#define __OJ_IPS_114_H
#include "SPI.h"
#include "GPIO.h"
//������ɫö�٣���Ҫ�Ŀ������м���
typedef enum
{
    IPS_RED = 0xF800,       //��ɫ
    IPS_BLUE = 0x001F,      //��ɫ
    IPS_YELLOW = 0xFFE0,    //��ɫ
    IPS_GREEN = 0x07E0,     //��ɫ
    IPS_WHITE = 0xFFFF,     //��ɫ
    IPS_BLACK = 0x0000,     //��ɫ
    IPS_GRAY = 0x8430,      //��ɫ
    IPS_BROWN = 0xBC40,     //��ɫ
    IPS_PURPLE = 0xF81F,    //��ɫ
    IPS_PINK = 0xFE19       //��ɫ
} IPS_114_Color;

//IPS114��ʾ����
//0 ����ģʽ
//1 ����ģʽ  ��ת180
//2 ����ģʽ
//3 ����ģʽ  ��ת180
typedef enum
{
    Direction0,             //0 ����ģʽ
    Direction1,             //1 ����ģʽ  ��ת180
    Direction2,             //2 ����ģʽ
    Direction3              //3 ����ģʽ  ��ת180
} IPS_114_DISPLAY_DIR;

//IPS_114�����ṹ��
typedef struct
{
        PIN_enum IPS_114_BL_PIN;            //IPS_114 Һ����������
        PIN_enum IPS_114_REST_PIN;          //IPS_114 Һ����λ����
        PIN_enum IPS_114_DC_PIN;            //IPS_114 Һ������λ����
        IPS_114_Color IPS_114_PENCOLOR;     //IPS_114 д�ֱ���ɫ
        IPS_114_Color IPS_114_BGCOLOR;      //IPS_114 ������ɫ
        uint16 IPS_114_Width;               //IPS_114 ���
        uint16 IPS_114_Height;              //IPS_114 �߶�
        IPS_114_DISPLAY_DIR Dir;            //IPS_114 ��ʾ����
} IPS_114_Param;

class IPS_114 : public SPI
{
    private:
        IPS_114_Param Param;
        GPIO *IPS_114_BL_PIN;
        GPIO *IPS_114_REST_PIN;
        GPIO *IPS_114_DC_PIN;
        uint16 IPS_114_X_MAX;
        uint16 IPS_114_Y_MAX;
        void Write_Index (uint8 dat);
        void Write_Data (uint8 dat);
        void Write_Data_16bit (uint16 dat);
        void Set_Region (uint16 x1, uint16 y1, uint16 x2, uint16 y2);
    public:
        IPS_114 ();
        ~IPS_114 ();
        IPS_114 (IPS_114_Param Param1, SPI_Param Param2);
        void Set_Param (IPS_114_Param Param, SPI_Param Param2);
        void Pin_Init ();
        void Init ();
        void Clear (IPS_114_Color Color);
        void Draw_Point (uint16 x, uint16 y, IPS_114_Color Color);
        void Show_Char (uint16 x, uint16 y, const int8 dat);
        void Show_String (uint16 x, uint16 y, const int8 dat[]);
        void Show_Num (uint16 x, uint16 y, int32 num);
        void Show_Float (uint16 x, uint16 y, double dat, uint8 num, uint8 pointnum);
        void Displayimage_032 (uint8 *p, uint16 width, uint16 height);
        void Displayimage_032_zoom (uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
        void Displayimage_032_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
                uint16 dis_width, uint16 dis_height);
        void Displayimage_8660_zoom (uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
        void Displayimage_8660_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
                uint16 dis_width, uint16 dis_height);
        void Displayimage_7725 (uint8 *p, uint16 width, uint16 height);
        void Display_Chinese (uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, IPS_114_Color color);
};

#endif /*__OJ_IPS_114_H*/
