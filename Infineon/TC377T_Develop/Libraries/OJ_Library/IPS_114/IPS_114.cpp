#include "IPS_114.h"
/*
 * @brief       IPS_114�չ��췽��
 * @param       void
 * @return      null
 */
IPS_114::IPS_114 ()
{
}

/*
 * @brief       IPS_114�չ��췽��
 * @param       void
 * @return      null
 */
IPS_114::~IPS_114 ()
{
    delete IPS_114_BL_PIN;
    delete IPS_114_DC_PIN;
    delete IPS_114_REST_PIN;
}

/*
 * @brief       IPS_114���ι��췽��
 * @param       void
 * @return      null
 */
IPS_114::IPS_114 (IPS_114_Param Param1, SPI_Param Param2)
{
    Set_Param(Param1, Param2);
}

/*
 * @brief       IPS_114���ι��췽��
 * @param       Param       IPS_114�����б�
 * @return      null
 */
void IPS_114::Set_Param (IPS_114_Param Param, SPI_Param Param2)
{
    this->Param = Param;
    SPI::Set_Param(Param2);
}

/*
 * @brief       IPS_114���ų�ʼ��
 * @param       void
 * @return      null
 */
void IPS_114::Pin_Init ()
{
    IPS_114_BL_PIN = new GPIO(Param.IPS_114_BL_PIN, GPO, 1, PUSHPULL);
    IPS_114_DC_PIN = new GPIO(Param.IPS_114_DC_PIN, GPO, 0, PUSHPULL);
    IPS_114_REST_PIN = new GPIO(Param.IPS_114_REST_PIN, GPO, 0, PUSHPULL);

    IPS_114_BL_PIN->Init();
    IPS_114_DC_PIN->Init();
    IPS_114_REST_PIN->Init();
}

/*
 * @brief       IPS_114��ʼ������
 * @param       void
 * @return      null
 */
void IPS_114::Init ()
{
    //SPIģ���ʼ��
    SPI::Init();
    //���ų�ʼ��
    Pin_Init();
    //X,Y������ֵȷ��
    switch (Param.Dir)
    {
        case Direction0 :
        case Direction1 :
            IPS_114_X_MAX = Param.IPS_114_Width;
            IPS_114_Y_MAX = Param.IPS_114_Height;
            break;
        case Direction2 :
        case Direction3 :
            IPS_114_X_MAX = Param.IPS_114_Height;
            IPS_114_Y_MAX = Param.IPS_114_Width;
            break;
    }
    IPS_114_REST_PIN->Set_PinVal(0);
    systick_delay_ms(STM0, 200);

    IPS_114_REST_PIN->Set_PinVal(1);
    systick_delay_ms(STM0, 100);

    Write_Index(0x36);

    if (Param.Dir == Direction0)
        Write_Data(0x00);
    else if (Param.Dir == Direction1)
        Write_Data(0xC0);
    else if (Param.Dir == Direction2)
        Write_Data(0x70);
    else if (Param.Dir == Direction3)
        Write_Data(0xA0);

    Write_Index(0x3A);
    Write_Data(0x05);

    Write_Index(0xB2);
    Write_Data(0x0C);
    Write_Data(0x0C);
    Write_Data(0x00);
    Write_Data(0x33);
    Write_Data(0x33);

    Write_Index(0xB7);
    Write_Data(0x35);

    Write_Index(0xBB);
    Write_Data(0x37);

    Write_Index(0xC0);
    Write_Data(0x2C);

    Write_Index(0xC2);
    Write_Data(0x01);

    Write_Index(0xC3);
    Write_Data(0x12);

    Write_Index(0xC4);
    Write_Data(0x20);

    Write_Index(0xC6);
    Write_Data(0x0F);

    Write_Index(0xD0);
    Write_Data(0xA4);
    Write_Data(0xA1);

    Write_Index(0xE0);
    Write_Data(0xD0);
    Write_Data(0x04);
    Write_Data(0x0D);
    Write_Data(0x11);
    Write_Data(0x13);
    Write_Data(0x2B);
    Write_Data(0x3F);
    Write_Data(0x54);
    Write_Data(0x4C);
    Write_Data(0x18);
    Write_Data(0x0D);
    Write_Data(0x0B);
    Write_Data(0x1F);
    Write_Data(0x23);

    Write_Index(0xE1);
    Write_Data(0xD0);
    Write_Data(0x04);
    Write_Data(0x0C);
    Write_Data(0x11);
    Write_Data(0x13);
    Write_Data(0x2C);
    Write_Data(0x3F);
    Write_Data(0x44);
    Write_Data(0x51);
    Write_Data(0x2F);
    Write_Data(0x1F);
    Write_Data(0x1F);
    Write_Data(0x20);
    Write_Data(0x23);

    Write_Index(0x21);

    Write_Index(0x11);
    systick_delay_ms(STM0, 120);

    Write_Index(0x29);
    Clear(Param.IPS_114_BGCOLOR);
}

/*
 * @brief      Һ����������
 * @param      color           ��ɫ����
 * @return     void
 * @since      v1.0
 * Sample usage:               Clear(YELLOW);// ȫ������Ϊ��ɫ
 */
void IPS_114::Clear (IPS_114_Color Color)
{
    uint16 i, j;
    Set_Region(0, 0, IPS_114_X_MAX - 1, IPS_114_Y_MAX - 1);
    for (i = 0; i < IPS_114_X_MAX; i++)
    {
        for (j = 0; j < IPS_114_Y_MAX; j++)
        {
            Write_Data_16bit(Color);
        }
    }
}

/*
 * @brief      Һ������
 * @param      x               ����x��������
 * @param      y               ����y��������
 * @param      dat             ��Ҫ��ʾ����ɫ
 * @return     void
 * @since      v1.0
 * Sample usage:               Draw_Point(0,0,RED);  //����0,0��һ����ɫ�ĵ�
 */
void IPS_114::Draw_Point (uint16 x, uint16 y, IPS_114_Color Color)
{
    Set_Region(x, y, x, y);
    Write_Data_16bit(Color);
}

/*
 * @brief      Һ����ʾ�ַ�
 * @param      x               ����x�������� ������Χ 0 -��IPS_114_X_MAX-1��
 * @param      y               ����y�������� ������Χ 0 -��IPS_114_Y_MAX/16-1��
 * @param      dat             ��Ҫ��ʾ���ַ�
 * @return     void
 * @since      v1.0
 * Sample usage:               Show_Char(0,0,'x');//����0,0дһ���ַ�x
 */
void IPS_114::Show_Char (uint16 x, uint16 y, const int8 dat)
{
    uint8 i, j;
    uint8 temp;

    for (i = 0; i < 16; i++)
    {
        Set_Region(x, y + i, x + 7, y + i);
        temp = tft_ascii[dat - 32][i]; //��32��Ϊ��ȡģ�Ǵӿո�ʼȡ�� �ո���ascii�������32
        for (j = 0; j < 8; j++)
        {
            if (temp & 0x01)
            {
                Write_Data_16bit(Param.IPS_114_PENCOLOR);
            }
            else
                Write_Data_16bit(Param.IPS_114_BGCOLOR);
            temp >>= 1;
        }
    }
}

/*
 * @brief      Һ����ʾ�ַ���
 * @param      x               ����x��������  ������Χ 0 -��IPS_114_X_MAX-1��
 * @param      y               ����y��������  ������Χ 0 -��IPS_114_Y_MAX/16-1��
 * @param      dat             ��Ҫ��ʾ���ַ���
 * @return     void
 * @since      v1.0
 * Sample usage:               Show_String(0,0,"BHU YYDS");
 */
void IPS_114::Show_String (uint16 x, uint16 y, const int8 dat[])
{
    uint16 j;
    j = 0;
    while (dat[j] != '\0')
    {
        Show_Char(x + 8 * j, y * 16, dat[j]);
        j++;
    }
}

/*
 * @brief      Һ����ʾ����
 * @param      x               ����x��������  ������Χ 0 -��IPS_114_X_MAX-1��
 * @param      y               ����y��������  ������Χ 0 -��IPS_114_Y_MAX/16-1��
 * @param      dat             ��Ҫ��ʾ�ı�������������uint32
 * @return     void
 * @since      v1.0
 * Sample usage:               Show_Num(0,0,x);//xΪuint32����
 */
void IPS_114::Show_Num (uint16 x, uint16 y, int32 num)
{
    int32 temp = num < 0 ? -num : num;
    //���numΪ0��countֱ�Ӹ�1
    int32 count = num ? 0 : 1;
    while (temp)
    {
        count++;
        temp /= 10;
    }
    char *str = new char[count + 2];
    str[count + 1] = '\0';
    temp = num < 0 ? -num : num;
    while (temp)
    {
        str[count--] = temp % 10 + '0';
        temp /= 10;
    }
    if (num == 0)
        str[1] = '0';
    str[0] = num < 0 ? '-' : ' ';
    Show_String(x, y, str);
    delete[] str;
}

/*
 * @brief      Һ����ʾ������(ȥ������������Ч��0)
 * @param      x               ����x�������� ������Χ 0 -��IPS_114_X_MAX-1��
 * @param      y               ����y�������� ������Χ 0 -��IPS_114_Y_MAX/16-1��
 * @param      dat             ��Ҫ��ʾ�ı�������������float��double
 * @param      num             ����λ��ʾ����   ���10λ
 * @param      pointnum        С��λ��ʾ����   ���6λ
 * @return     void
 * @since      v1.0
 * Sample usage:               Show_Float(0,0,x,2,3);//��ʾ������   ������ʾ2λ   С����ʾ��λ
 * @note                       �ر�ע�⵱����С��������ʾ��ֵ����д���ֵ��һ����ʱ��
 *                                                          ���������ڸ��������ȶ�ʧ���⵼�µģ��Ⲣ������ʾ���������⣬
 *                                                          �й���������飬�����аٶ�ѧϰ   ���������ȶ�ʧ���⡣
 *                                                          ��������ʾһ�� ��-����   ������ʾһ���ո�
 */
void IPS_114::Show_Float (uint16 x, uint16 y, double dat, uint8 num, uint8 pointnum)
{
    uint32 length;
    int8 buff[34];
    int8 start, end, point;

    if (6 < pointnum)
        pointnum = 6;
    if (10 < num)
        num = 10;

    if (0 > dat)
        length = zf_sprintf(&buff[0], "%f", dat); //����
    else
    {
        length = zf_sprintf(&buff[1], "%f", dat);
        length++;
    }
    point = (int8) (length - 7);         //����С����λ��
    start = point - num - 1;    //������ʼλ
    end = point + pointnum + 1; //�������λ
    while (0 > start) //����λ����  ĩβӦ�����ո�
    {
        buff[end] = ' ';
        end++;
        start++;
    }

    if (0 > dat)
        buff[start] = '-';
    else
        buff[start] = ' ';

    buff[end] = '\0';

    Show_String(x, y, buff); //��ʾ����
}

/*
 * @brief      �����(�Ҷ�����ͷ)Һ����ʾ����
 * @param      *p              ͼ�������ַ
 * @param      width           ͼ����
 * @param      height          ͼ��߶�
 * @return     void
 * @since      v1.0
 * Sample usage:               ips114_displayimage032(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H)//��ʾ�Ҷ�����ͷ ͼ��
 * @note       ͼ��Ŀ���������Һ���Ŀ�ȣ����Զ�����������ʾ������������ʾȫ��Ұ
 */
void IPS_114::Displayimage_032 (uint8 *p, uint16 width, uint16 height)
{
    uint32 i, j;

    uint16 color = 0;
    uint16 temp = 0;

    uint16 coord_x = 0;
    uint16 coord_y = 0;

    coord_x = width > IPS_114_X_MAX ? IPS_114_X_MAX : width;
    coord_y = height > IPS_114_Y_MAX ? IPS_114_Y_MAX : height;
    Set_Region(0, 0, coord_x - 1, coord_y - 1);

    for (j = 0; j < coord_y; j++)
    {
        for (i = 0; i < coord_x; i++)
        {
            temp = *(p + j * width + i * width / coord_x); //��ȡ���ص�
            color = (0x001f & ((temp) >> 3)) << 11;
            color = color | (((0x003f) & ((temp) >> 2)) << 5);
            color = color | (0x001f & ((temp) >> 3));
            Write_Data_16bit(color);
        }
    }
}

/*
 *  @brief      �����(�Ҷ�����ͷ)Һ��������ʾ����
 *  @param      *p              ͼ�������ַ
 *  @param      width           ͼ����
 *  @param      height          ͼ��߶�
 *  @param      dis_width       ͼ����ʾ���  1 -��IPS_114_X_MAX��
 *  @param      dis_height      ͼ����ʾ�߶�  1 -��IPS_114_Y_MAX��
 *  @return     void
 *  @since      v1.0
 *  Sample usage:               Displayimage_032_zoom(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, MT9V03X_CSI_W, MT9V03X_CSI_H)//��ʾ�Ҷ�����ͷ ͼ��
 *  @note       ͼ��Ŀ���������Һ���Ŀ�ȣ����Զ�����������ʾ������������ʾȫ��Ұ
 */
void IPS_114::Displayimage_032_zoom (uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i, j;

    uint16 color = 0;
    uint16 temp = 0;

    Set_Region(0, 0, dis_width - 1, dis_height - 1); //������ʾ����

    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            temp = *(p + (j * height / dis_height) * width + i * width / dis_width); //��ȡ���ص�
            color = (0x001f & ((temp) >> 3)) << 11;
            color = color | (((0x003f) & ((temp) >> 2)) << 5);
            color = color | (0x001f & ((temp) >> 3));
            Write_Data_16bit(color);
        }
    }
}

/*
 *  @brief      �����(�Ҷ�����ͷ)Һ��������ʾ����
 *  @param      *p              ͼ�������ַ
 *  @param      width           ͼ����
 *  @param      height          ͼ��߶�
 *  @param      start_x         ������ʾ����x������
 *  @param      start_y         ������ʾ����y������
 *  @param      dis_width       ͼ����ʾ���  1 -��IPS_114_X_MAX��
 *  @param      dis_height      ͼ����ʾ�߶�  1 -��IPS_114_Y_MAX��
 *  @return     void
 *  @since      v1.0
 *  Sample usage:               Displayimage_032_zoom1(mt9v03x_csi_image[0], MT9V03X_CSI_W, MT9V03X_CSI_H, 0, 0, MT9V03X_CSI_W, MT9V03X_CSI_H)//��ʾ�Ҷ�����ͷ ͼ��
 */
void IPS_114::Displayimage_032_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
        uint16 dis_width, uint16 dis_height)
{
    uint32 i, j;

    uint16 color = 0;
    uint16 temp = 0;

    //������õĲ����Ƿ񳬹���Ļ�ķֱ���
    if ((start_x + dis_width) > IPS_114_X_MAX)
        ZF_ASSERT(0);
    if ((start_y + dis_height) > IPS_114_Y_MAX)
        ZF_ASSERT(0);
    Set_Region(start_x, start_y, start_x + dis_width - 1, start_y + dis_height - 1); //������ʾ����

    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            temp = *(p + (j * height / dis_height) * width + i * width / dis_width); //��ȡ���ص�
            color = (0x001f & ((temp) >> 3)) << 11;
            color = color | (((0x003f) & ((temp) >> 2)) << 5);
            color = color | (0x001f & ((temp) >> 3));
            Write_Data_16bit(color);
        }
    }
}

/*
 *  @brief      ��ͫ(��ɫ����ͷ)Һ��������ʾ����
 *  @param      *p              ͼ�������ַ
 *  @param      width           ͼ����
 *  @param      height          ͼ��߶�
 *  @param      dis_width       ͼ����ʾ���  0 -��TFT_X_MAX-1��
 *  @param      dis_height      ͼ����ʾ�߶�  0 -��TFT_Y_MAX-1��
 *  @return     void
 *  @since      v1.0
 *  Sample usage:               Displayimage_8660_zoom(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 320, 240)//��ʾ��ɫ����ͷ ͼ��
 */
void IPS_114::Displayimage_8660_zoom (uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height)
{
    uint32 i, j;
    uint16 color = 0;

    Set_Region(0, 0, dis_width - 1, dis_height - 1); //������ʾ����

    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            color = *(p + (j * height / dis_height) * width + i * width / dis_width); //��ȡ���ص�
            color = ((color & 0xff) << 8) | (color >> 8);
            Write_Data_16bit(color);
        }
    }
}

/*
 *  @brief      ��ͫ(��ɫ����ͷ)Һ��������ʾ����
 *  @param      *p              ͼ�������ַ
 *  @param      width           ͼ����
 *  @param      height          ͼ��߶�
 *  @param      start_x         ������ʾ����x������
 *  @param      start_y         ������ʾ����y������
 *  @param      dis_width       ͼ����ʾ���  1 -��TFT_X_MAX��
 *  @param      dis_height      ͼ����ʾ�߶�  1 -��TFT_Y_MAX��
 *  @return     void
 *  @since      v1.0
 *  Sample usage:               Displayimage_8660_zoom1(scc8660_csi_image[0], SCC8660_CSI_PIC_W, SCC8660_CSI_PIC_H, 0, 0, 320, 240);
 */
void IPS_114::Displayimage_8660_zoom1 (uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y,
        uint16 dis_width, uint16 dis_height)
{
    uint32 i, j;

    uint16 color = 0;

    //������õĲ����Ƿ񳬹���Ļ�ķֱ���
    if ((start_x + dis_width) > IPS_114_X_MAX)
        ZF_ASSERT(0);
    if ((start_y + dis_height) > IPS_114_Y_MAX)
        ZF_ASSERT(0);

    Set_Region(start_x, start_y, start_x + dis_width - 1, start_y + dis_height - 1); //������ʾ����

    for (j = 0; j < dis_height; j++)
    {
        for (i = 0; i < dis_width; i++)
        {
            color = *(p + (j * height / dis_height) * width + i * width / dis_width); //��ȡ���ص�
            color = ((color & 0xff) << 8) | (color >> 8);
            Write_Data_16bit(color);
        }
    }
}

/*
 *  @brief      С���(��ֵ������ͷ)Һ����ʾ����
 *  @param      *p              ͼ�������ַ
 *  @param      width           ͼ����
 *  @param      height          ͼ��߶�
 *  @return     void
 *  @since      v1.0
 *  @note       ͼ��ֱ�����Ҫ������120(��)*160(��)����
 */
void IPS_114::Displayimage_7725 (uint8 *p, uint16 width, uint16 height)
{
    int i, j;

    uint16 temp = 0;
    Set_Region(0, 0, width - 1, height - 1);
    for (i = 0; i < height * (width / 8); i++)
    {
        temp = *p;
        p++;
        for (j = 0; j < 8; j++)
        {
            if ((temp << j) & 0x80)
                Write_Data_16bit(WHITE);
            else
                Write_Data_16bit(BLACK);
        }
    }
}

/*
 *  @brief      ������ʾ
 *  @param      x       ������ 0-��IPS114_X_MAX-1��
 *  @param      y       ������ 0-��IPS114_Y_MAX-1��
 *  @param      size    ȡģ��ʱ�����õĺ��������С��Ҳ����һ������ռ�õĵ��󳤿�Ϊ���ٸ��㣬ȡģ��ʱ����Ҫ������һ���ġ�
 *  @param      *p      ��Ҫ��ʾ�ĺ�������
 *  @param      number  ��Ҫ��ʾ����λ
 *  @param      color   ��ʾ��ɫ
 *  @return     void
 *  @since      v1.0
 *  Sample usage:       ips114_display_chinese(0,0,16,chinese_test[0],4,RED);//��ʾfont�ļ������ ʾ��
 *  @Note       ʹ��PCtoLCD2002���ȡģ           ���롢����ʽ��˳��   16*16
 */
void IPS_114::Display_Chinese (uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, IPS_114_Color color)
{
    int i, j, k;
    uint8 temp, temp1, temp2;
    const uint8 *p_data;

    temp2 = size / 8;

    Set_Region(x, y, number * size - 1 + x, y + size - 1);

    for (i = 0; i < size; i++)
    {
        temp1 = number;
        p_data = p + i * temp2;
        while (temp1--)
        {
            for (k = 0; k < temp2; k++)
            {
                for (j = 8; j > 0; j--)
                {
                    temp = (*p_data >> (j - 1)) & 0x01;
                    if (temp)
                        Write_Data_16bit(color);
                    else
                        Write_Data_16bit(Param.IPS_114_BGCOLOR);
                }
                p_data++;
            }
            p_data = p_data - temp2 + temp2 * size;
        }
    }
}

/*
 * @brief       IPS_114Indexд
 * @param       void
 * @return      null
 */
void IPS_114::Write_Index (uint8 dat)
{
    IPS_114_DC_PIN->Set_PinVal(0);
    MOSI_Send(&dat, NULL, 1, 1);
}

/*
 * @brief       IPS_114д����
 * @param       void
 * @return      null
 */
void IPS_114::Write_Data (uint8 dat)
{
    IPS_114_DC_PIN->Set_PinVal(1);
    MOSI_Send(&dat, NULL, 1, 1);
}

/*
 * @brief       IPS_114д16λ����
 * @param       void
 * @return      null
 */
void IPS_114::Write_Data_16bit (uint16 dat)
{
    uint8 dat1[2];
    dat1[0] = dat >> 8;
    dat1[1] = (uint8) dat;

    IPS_114_DC_PIN->Set_PinVal(1);
    MOSI_Send(dat1, NULL, 2, 1);  //д������  ��λ��ǰ  ��λ�ں�
}

/*
 * @brief       IPS_114����ԭʼ��ַ
 * @param       void
 * @return      null
 */
void IPS_114::Set_Region (uint16 x1, uint16 y1, uint16 x2, uint16 y2)
{
    if (Param.Dir == Direction0)
    {
        Write_Index(0x2a);  //�е�ַ����
        Write_Data_16bit(x1 + 52);
        Write_Data_16bit(x2 + 52);
        Write_Index(0x2b);  //�е�ַ����
        Write_Data_16bit(y1 + 40);
        Write_Data_16bit(y2 + 40);
        Write_Index(0x2c);  //������д
    }
    else if (Param.Dir == Direction1)
    {
        Write_Index(0x2a);  //�е�ַ����
        Write_Data_16bit(x1 + 53);
        Write_Data_16bit(x2 + 53);
        Write_Index(0x2b);  //�е�ַ����
        Write_Data_16bit(y1 + 40);
        Write_Data_16bit(y2 + 40);
        Write_Index(0x2c);  //������д
    }
    else if (Param.Dir == Direction2)
    {
        Write_Index(0x2a);  //�е�ַ����
        Write_Data_16bit(x1 + 40);
        Write_Data_16bit(x2 + 40);
        Write_Index(0x2b);  //�е�ַ����
        Write_Data_16bit(y1 + 53);
        Write_Data_16bit(y2 + 53);
        Write_Index(0x2c);  //������д
    }
    else if (Param.Dir == Direction3)
    {
        Write_Index(0x2a);  //�е�ַ����
        Write_Data_16bit(x1 + 40);
        Write_Data_16bit(x2 + 40);
        Write_Index(0x2b);  //�е�ַ����
        Write_Data_16bit(y1 + 52);
        Write_Data_16bit(y2 + 52);
        Write_Index(0x2c);  //������д
    }
}
