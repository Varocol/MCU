#include "Image_Process.h"

/*
 * @brief       ����log����
 * @param       num         ��Ҫ�������
 * @param       bnum        ����
 * @return      null
 */
double log (double num, double bnum)
{
    return log(num) / log(bnum);
}

//�����ĻҶȱ任����
//�Ҷȱ任-��ȱ任(s=c)
//�Ҷȱ任-ͼ��ת(L-1-r)
//�Ҷȱ任-�����任(s=clog(r+1))
//�Ҷȱ任-���ɱ任(s=cr^��)
//�Ҷȱ任-ֱ��ͼ����(s=T(r)=(L-1)��Pr(w)dw=(L-1)/MN*��(nj))
/*
 * @brief       �Ҷȱ任-��ȱ任(s=c)
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Identity (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = Pixel(Input, i, j);
        }
}

/*
 * @brief       �Ҷȱ任-ͼ��ת(L-1-r)
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Reverse (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = Gray_Max - Pixel(Input, i, j);
        }
}

/*
 * @brief       �Ҷȱ任-�����任(s=clog(r+1))
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Logarithm (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //��s=(L-1)log(r+1),����ΪL,Ϊ��(L�ǻҶȼ���)
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = (Gray_Max - 1) * log(Pixel(Input,i,j) + 1, Gray_Max);
        }
}

/*
 * @brief       �Ҷȱ任-���ɱ任(s=cr^��)
 * @param       Gamma       ��ָ��(�������Ϊ�Աȶ�)
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Pow (double Gamma, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    double c = pow(Gray_Max - 1, 1 - Gamma);
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = c * pow(Pixel(Input, i, j), Gamma);
        }
}

/*
 * @brief       �Ҷȱ任-ֱ��ͼ����(s=T(r)=(L-1)��Pr(w)dw=(L-1)/MN*��(nj))
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Equalization (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //ͳ������Ƶ�ʵ�����
    uint16 Pixel_Freq[Gray_Max] = {};
    //ͳ�Ƹ�������Ƶ��
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Freq[Pixel(Input, i, j)]++;
        }
    //�ó���(nj)
    for (uint16 i = 1; i < Gray_Max - 1; i++)
    {
        Pixel_Freq[i + 1] += Pixel_Freq[i];
    }
    //�����(L-1)/MNϵ��
    double coefficient = (Gray_Max - 1) * 1.0 / (row * col);
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = Pixel_Freq[Pixel(Input, i, j)] * coefficient;
        }
}

