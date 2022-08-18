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
void Screen_Show_Running_Info ()
{
    Screen_Draw_Line();
    Screen_Show_FPS ();
}

/*
 * @brief       ��Ļ��ʾͼ��
 * @param       null
 * @return      null
 */
void Screen_Show_Img ()
{
    Screen.Displayimage_032(Screen_IMG, Screen_IMG_W, Screen_IMG_H);
}

/*
 * @brief       ��Ļ��ʾ֡��
 * @param       null
 * @return      null
 */
void Screen_Show_FPS ()
{
    uint16 FPS_X = 100;
    uint16 FPS_Y = 10;
    Screen.Show_Num(FPS_X, FPS_Y, end - start ? 1000 / (end - start) : 0);
}

/*
 * @brief       ��Ļ��ʾ������
 * @param       null
 * @return      null
 */
void Screen_Draw_Line ()
{
    if (left_findflag)  //�����߽��ߴ��ڣ��򻭳���߽���
    {
        for (int i = 0; i < L_edge_count; i++)
        {
            Screen.Draw_Point(L_edge[i].col, L_edge[i].row, IPS_BLUE);
        }
    }
    if (right_findflag)  //����ұ߽��ߴ��ڣ��򻭳��ұ߽���
    {
        for (int i = 0; i < R_edge_count; i++)
        {
            Screen.Draw_Point(R_edge[i].col, R_edge[i].row, IPS_RED);
        }
    }
    if (Mid_count > 0)
    {
        for (int i = 0; i < Mid_count; i++)
            Screen.Draw_Point(Mid_Line[i].col, Mid_Line[i].row, IPS_BLACK);
    }
    if (L_corner_flag)   //������յ�
    {
        if (L_corner_col - 2 > 0 && L_corner_row - 2 > 0 && L_corner_row + 2 < Image_W && L_corner_col + 2 < Image_W)
        {
            Screen.Draw_Point(L_corner_col - 2, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 1, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 1, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row - 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col + 1, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 1, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row + 2, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row + 1, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row - 1, IPS_RED);
            Screen.Draw_Point(L_corner_col - 2, L_corner_row, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row - 1, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row, IPS_RED);
            Screen.Draw_Point(L_corner_col + 2, L_corner_row + 1, IPS_RED);
        }
    }
    if (R_corner_flag)   //�����ҹյ�
    {
        if (R_corner_col - 2 > 0 && R_corner_row - 2 > 0 && R_corner_row + 2 < Image_W && R_corner_col + 2 < Image_W)
        {
            Screen.Draw_Point(R_corner_col - 2, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 1, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 1, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row - 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 1, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 1, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row + 2, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row + 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row - 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col - 2, R_corner_row, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row - 1, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row, IPS_BLUE);
            Screen.Draw_Point(R_corner_col + 2, R_corner_row + 1, IPS_BLUE);
        }
    }
}

