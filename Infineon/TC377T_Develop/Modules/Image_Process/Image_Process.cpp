#include "Image_Process.h"
uint8 Histogram[IPS114_H][IPS114_W];
/*
 * @brief       ����log����
 * @param       num         ��Ҫ�������
 * @param       bnum        ����
 * @return      ���
 */
double log (double num, double bnum)
{
    return log(num) / log(bnum);
}

/*
 * @brief       ���˹���ߺ��������ڼ����ֵ������
 * @param       gray_Delta
 * @return      ��������ֵ����yֵ
 */
double membership (int16 gray_Delta)
{
    return exp(-pow(gray_Delta / 16.0, 2));
}

/*
 * @brief       ͼ��ָ�-Otsu���ȫ����ֵ��������ܳ��Ż��汾��ȡ��ֵ
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
uint8 DIP::Global_Otsu_Better_threshold (uint8 *Input, uint16 row, uint16 col)
{
    //ͼ���ֱ��ͼ����
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    //���������ֵk����������������ֵ��ֵ��P1(��Pi)��Q1(��iPi)��ȫ��ƽ���Ҷȣ����ֵ�ۼ�
    uint8 cnt = 0;
    uint16 k;
    uint16 Pixel_Sum = (row * col) / 4;
    uint32 Gray_Sum = 0;
    float P1 = 0, Q1 = 0, mg;
    //����Ҽ���䷽��
    float variance = 0, temp;
    //�Ż�һ�����һ��һ��ȡ���أ��ֶ���Сͼ����������
    for (uint16 i = 0; i < row; i += 2)
        for (uint16 j = 0; j < col; j += 2)
        {
            histogram[Pixel(Input, i, j)]++;
            Gray_Sum += Pixel(Input, i, j);
        }
    mg = (float) Gray_Sum / Pixel_Sum;
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        P1 += (float) histogram[i] / Pixel_Sum;
        Q1 += (float) histogram[i] / Pixel_Sum * i;
        if (histogram[i] != 0)
        {
            temp = P1 * (1 - P1) * pow(Q1 / P1 - (mg - Q1) / (1 - P1), 2);
            if (temp > variance)
            {
                variance = temp;
                k = i;
                cnt = 1;
            }
            else if (temp == variance)
            {
                k += i;
                cnt++;
            }
        }
    }
    k /= cnt;
//    k = (int16) k + Offset < 0 ? 0 : k + Offset > Gray_Max ? Gray_Max : k + Offset;
    delete[] histogram;
    return k;
}

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
            Pixel(Output,i,j) = Gray_Max * log(Pixel(Input, i, j) + 1, Gray_Max + 1);
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
    double c = pow(Gray_Max, 1 - Gamma);
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
    uint16 Pixel_Freq[Gray_Max + 1] = {};
    //ͳ�Ƹ�������Ƶ��
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Freq[Pixel(Input, i, j)]++;
        }
    //�ó���(nj)
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        Pixel_Freq[i + 1] += Pixel_Freq[i];
    }
    //�����(L-1)/MNϵ��
    float coefficient = Gray_Max * 1.0 / (row * col);
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = Pixel_Freq[Pixel(Input, i, j)] * coefficient;
        }
}

/*
 * @brief       �Ҷȱ任-��ֵ��
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Grayscale_Binarization (uint8 *Input, uint8 *Output, uint8 threshold, uint16 row, uint16 col)
{
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = Pixel(Input,i,j) <= threshold ? 0 : Gray_Max;
        }
}

/*
 * @brief       ƽ�������˲���-��ֵ�˲���1
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Filter_Mean (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    uint8 filter[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    float coefficient = 1.0 / 9;
    uint32 Pixel_Sum;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Sum = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
            {
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                        Pixel_Sum += (uint16) filter[m][n] * (Pixel(Input, (i + m - 1), (j + n - 1)));
                }
            }
            Pixel_Sum *= coefficient;
            Pixel(Output,i,j) = Pixel_Sum > Gray_Max ? Gray_Max : Pixel_Sum < 0 ? 0 : Pixel_Sum;
        }
}

/*
 * @brief       ƽ�������˲���-��˹�˲���
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Filter_Gaussian (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    uint8 filter[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}; //(��ʵ�����Ǹ���˹ƽ���˲���ģ��)
    float coefficient = 1.0 / 16;
    uint32 Pixel_Sum;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Sum = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
            {
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                        Pixel_Sum += (uint16) filter[m][n] * (Pixel(Input, (i + m - 1), (j + n - 1)));
                }
            }
            Pixel_Sum *= coefficient;
            Pixel(Output,i,j) = Pixel_Sum > Gray_Max ? Gray_Max : Pixel_Sum < 0 ? 0 : Pixel_Sum;
        }
}

/*
 * @brief       ͳ�������˲���-��ֵ�˲���(�����ȡ��ֵ)
 * @param       size        �����˲�����С
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Filter_Median (uint8 size, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //����һ��size^2��С������
    uint16 Arr_Max = (size * size + 1) / 2;
    uint16 count;
    uint8 *temp = new uint8[Arr_Max];
    //��С���ܳ���row��col�н�С��һ��
    if (size > row || size > col)
    {
        Grayscale_Identity(Input, Output, row, col);
    }
    //��ʼ����ɸѡ
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            count = 0;
            for (int16 m = -size / 2; m <= size / 2 && i + m < row; m++)
            {
                for (int16 n = -size / 2; i + m >= 0 && n <= size / 2 && j + n < col; n++)
                {
                    if (j + n >= 0)
                    {
                        int16 k = count <= Arr_Max ? count - 1 : Arr_Max - 1;
                        while (k >= 0 && temp[k] > (Pixel(Input, (i + m - 1), (j + n - 1))))
                        {
                            if (k + 1 < Arr_Max)
                            {
                                temp[k + 1] = temp[k];
                            }
                            k--;
                        }
                        temp[k + 1] = Pixel(Input, (i + m - 1), (j + n - 1));
                        count++;
                    }
                }
            }
            //ɸѡ���Ҷ�ֵ
            Pixel(Output, i, j) = temp[(count - 1) / 2];
        }
//�ͷ��ڴ�
    delete[] temp;
}

/*
 * @brief       �񻯿ռ��˲���-������˹����
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Fliter_Laplace (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    int8 Fliter1[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    int8 Fliter2[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    int16 Pixel_Sum;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Sum = Pixel(Input, i, j);
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                        Pixel_Sum += (int16) Fliter1[m][n] * (Pixel(Input, (i + m - 1), (j + n - 1)));
                }
            Pixel(Output, i, j) = Pixel_Sum > Gray_Max ? Gray_Max : Pixel_Sum < 0 ? 0 : Pixel_Sum;
        }
}

/*
 * @brief       �񻯿ռ��˲���-�����ڱκ͸������˲�
 * @param       Origin      ԭʼͼ��
 * @param       Blur        ģ��ͼ��(����ʹ�ø�˹ģ��)
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Fliter_Unsharp (uint8 *Origin, uint8 *Blur, uint8 *Output, uint16 row, uint16 col)
{
    float k = 4.5;
    int16 temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            temp = Pixel(Origin, i, j) + k * (Pixel(Origin, i, j) - Pixel(Blur, i, j));
            Pixel (Output,i,j) = temp < 0 ? 0 : temp > Gray_Max ? Gray_Max : temp;
        }
}

/*
 * @brief       �񻯿ռ��˲���-Sobel����
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 **�÷��������ͼ��ΪSobelͼ�񣬼��ݶ�ͼ��ͻ���˱�Ե����
 */
void DIP::Fliter_Sobel (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //����ֻ�ǽ������ӵ�һ�֣�Ҳ���Բ���3,10,3�����, Ч�����������
    //x������΢�ֵ���ɢ��������
    int8 Fliter_gx[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //y������΢�ֵ���ɢ��������
    int8 Fliter_gy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //΢��gx��gy�Ļ���
    int16 gx_tmp, gy_tmp;
    //�������ػ���
    int16 temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            gx_tmp = 0;
            gy_tmp = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                    {
                        gx_tmp += (int16) Fliter_gx[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                        gy_tmp += (int16) Fliter_gy[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                    }
                }
            gx_tmp = gx_tmp < 0 ? -gx_tmp : gx_tmp;
            gy_tmp = gy_tmp < 0 ? -gy_tmp : gy_tmp;
            temp = gx_tmp + gy_tmp;
            Pixel(Output, i, j) = temp > Gray_Max ? Gray_Max : temp < 0 ? 0 : temp;
        }
}

/*
 * @brief       ģ������-�Ҷȱ任
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 **���������¹���
 **1.����������ǰ��ģ���ʹ��Ϊ�ڡ�
 **2.����������ǻҵģ���ʹ��Ϊ�ҡ�
 **3.��������������ģ���ʹ��Ϊ�ס�
 */
void DIP::Fuzzy_GrayValue (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //����������Ⱥ���
    uint8 u_dark_out = 0, u_gray_out = 127, u_bright_out = 255;
    //����������Ⱥ���
    float u_dark, u_gray, u_bright;
    //����ֵ
    uint8 temp;
    //���ֵ
    float pixel_out;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            temp = Pixel(Input, i, j);
            u_dark = temp < 79 ? 1 : temp > 127 ? 0 : (127 - temp) * 1.0 / 64;
            u_gray = temp < 79 || temp > 175 ? 0 : temp < 127 ? (temp - 79) * 1.0 / 64 : (175 - temp) * 1.0 / 64;
            u_bright = temp < 127 ? 0 : temp > 175 ? 1 : (temp - 127) * 1.0 / 64;
            pixel_out = (u_dark * u_dark_out + u_gray * u_gray_out + u_bright * u_bright_out)
                    / (u_dark + u_gray + u_bright);
            Pixel(Output,i,j) = pixel_out > 255 ? 255 : pixel_out < 0 ? 0 : (uint8) pixel_out;
        }
}

/*
 * @brief       ģ������-��Ե��ǿ
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 **���������¹���
 **IF d2��0  AND d6��0 THEN z5�ǰ�ɫ
 **IF d6��0  AND d8��0 THEN z5�ǰ�ɫ
 **IF d8��0  AND d4��0 THEN z5�ǰ�ɫ
 **IF d4��0  AND d2��0 THEN z5�ǰ�ɫ
 **ELSE z5�Ǻ�ɫ
 **| z1 | z2 | z3 |
 **| z4 | z5 | z6 |
 **| z7 | z8 | z9 |
 **     ԭͼ��
 **| d1 | d2 | d3 |
 **| d4 | d5 | d6 |
 **| d7 | d8 | d9 |
 **      ��ֵ
 **dx = z5 - zx,����d5 = 0��
 */
void DIP::Fuzzy_EdgeEnhance (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //dx(����)�����������
    float *d = new float[4];
    //dx�δ��
    float d_max_output;
    //�ڰ�(���ֵ)�����������
    float bl_output, wh_output;
    //����ֵ
    float temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            d_max_output = d[0] = d[1] = d[2] = d[3] = 0;
            //d2�ļ���
            if (i - 1 >= 0)
            {
                d[0] = membership(Pixel(Input,i,j) - Pixel(Input, (i - 1), j));
            }
            //d6�ļ���
            if (j + 1 < col)
            {
                d[1] = membership(Pixel(Input,i,j) - Pixel(Input, i, (j + 1)));
            }
            //d8�ļ���
            if (i + 1 < row)
            {
                d[2] = membership(Pixel(Input,i,j) - Pixel(Input, (i + 1), j));
            }
            //d4�ļ���
            if (j - 1 >= 0)
            {
                d[3] = membership(Pixel(Input,i,j) - Pixel(Input, i, (j - 1)));
            }
            for (uint8 m = 0; m < 2; m++)
            {
                for (uint8 n = 0; n < 3 - m; n++)
                {
                    if (d[n] < d[n + 1])
                    {
                        float d_temp = d[n];
                        d[n] = d[n + 1];
                        d[n + 1] = d_temp;
                    }
                }
            }
            d_max_output = d[2];
            delete[] d;
            wh_output = d_max_output;
            bl_output = 1 - d_max_output;
            //���������
            if (bl_output < 1.0 / 3)
            {
                //z�ֵ�һ����
                temp = (191.25 * bl_output + 63.75) / 2;
                //z�ֵڶ�����
                temp += (255 - 191.25 * wh_output + 63.75) / 2;
                //z�ֵ�������
                temp += 106.25;
            }
            else
            {
                //v�ֵ�һ����
                temp = (191.25 * bl_output + 63.75) / 2;
                //v�ֵڶ�����
                temp += (255 - 191.25 * wh_output + 63.75) / 2;
                //v�ֵ�������
                temp += 116.875 + 63.75 * wh_output;
            }
            Pixel(Output,i,j) = temp > 255 ? 255 : temp < 0 ? 0 : (uint8) temp;
        }
}

/*
 * @brief       ͼ��ָ�-������ļ��
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Segmentation_Point (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //������˹����
    int8 Filter[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    //��ֵ
    float Point_Max = 0.9 * Gray_Max;
    //����ֵ
    int32 temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            temp = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                    {
                        temp += (int32) Filter[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                    }
                }
            Pixel(Output,i,j) = temp >= Point_Max ? Gray_Max : temp <= -Point_Max ? Gray_Max : 0;
        }
}

/*
 * @brief       ͼ��ָ�-�ߵļ��
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Segmentation_Line (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //������˹����
    int8 Filter[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    //����ֵ
    int32 temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            temp = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                    {
                        temp += (int32) Filter[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                    }
                }
            Pixel(Output,i,j) = temp > Gray_Max ? Gray_Max : 0;
        }
}

/*
 * @brief       ͼ��ָ�-����ȫ����ֵ����(������)
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Global_threshold (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
////  ��һ���㷨
//    //���ڻ�����ͺͼ����ֵ
//    uint32 *sum1 = new uint32;
//    uint32 *sum2 = new uint32;
//    uint16 *cnt1 = new uint16;
//    uint16 *cnt2 = new uint16;
//    //����T�ͦ�T
//    uint8 T1, T2, T = 1;
//    //����T�ĳ�ʼֵΪƽ���Ҷ�
//    *sum1 = 0;
//    for (uint16 i = 0; i < row; i++)
//        for (uint16 j = 0; j < col; j++)
//        {
//            (*sum1) += Pixel(Input, i, j);
//        }
//    T1 = 0;
//    T2 = (*sum1) / (row * col);
//    //��������,T1���ڴ洢��һ�ε���ֵT,T2���ڴ洢����õ�����ֵ�����յõ�������Ҫ����ֵ
//    while (T1 - T2 > T || T2 - T1 > T)
//    {
//        T1 = T2;
//        *sum1 = *sum2 = 0;
//        *cnt1 = *cnt2 = 0;
//        for (uint16 i = 0; i < row; i++)
//            for (uint16 j = 0; j < col; j++)
//            {
//                //�����һ���ֵĻҶ��ܺ�
//                if (Pixel(Input,i,j) <= T1)
//                {
//                    (*sum1) += Pixel(Input, i, j);
//                    (*cnt1)++;
//                }
//                //����ڶ����ֵĻҶ��ܺ�
//                else
//                {
//                    (*sum2) += Pixel(Input, i, j);
//                    (*cnt2)++;
//                }
//            }
//        //�õ���ֵT
//        T2 = ((float) (*sum1) / (*cnt1) + (float) (*sum2) / (*cnt2)) / 2;
//    }
//    for (uint16 i = 0; i < row; i++)
//        for (uint16 j = 0; j < col; j++)
//        {
//            Pixel(Output,i,j) = Pixel(Input,i,j) <= T2 ? 0 : Gray_Max;
//        }
//    delete sum1;
//    delete sum2;
//    delete cnt1;
//    delete cnt2;

//  �ڶ����㷨(����ƽ���Ҷ�m=��ip(i)/MN����)
    //���ڴ��ֱ��ͼ�����ϻ�����ʽ(��p(i))
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    //���ڴ�Ŧ�ip(i)
    uint32 *sum = new uint32[Gray_Max + 1]{};
    //����T�ͦ�T
    uint8 T1, T2, T = 1, m1, m2;
    //��ʼ��������������
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            histogram[Pixel(Input, i, j)]++;
            sum[Pixel(Input, i, j)] += Pixel(Input, i, j);
        }
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        histogram[i + 1] += histogram[i];
        sum[i + 1] += sum[i];
    }
    //����ƽ���Ҷ�
    T1 = 0;
    T2 = sum[Gray_Max] / histogram[Gray_Max];
    while (T1 - T2 > T || T2 - T1 > T)
    {
        T1 = T2;
        m1 = histogram[T1] == 0 ? 0 : sum[T1] / histogram[T1];
        m2 = histogram[Gray_Max] - histogram[T1] == 0 ?
                0 : (sum[Gray_Max] - sum[T1]) / (histogram[Gray_Max] - histogram[T1]);
        T2 = (m1 + m2) / 2;
    }
    //��ֵ��
    Grayscale_Binarization(Input, Output, T2, row, col);
    delete[] histogram;
    delete[] sum;
}

/*
 * @brief       ͼ��ָ�-Otsu���ȫ����ֵ����
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Global_Otsu (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //ͼ���ֱ��ͼ������ʽ������ֵ�Ļ�����ʽ����
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    uint32 *m = new uint32[Gray_Max + 1]{};
    //����ȫ��ƽ���Ҷȣ��Լ������ֵk���������ֵ����������ȫ��ƽ���Ҷ�һ��Ҫ������(��Ӱ�����Ľ��)
    float mg;
    uint16 cnt;
    uint32 k;
    //����Ҽ���䷽��
    float variance, temp;
    //��ʼ����������
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            histogram[Pixel(Input, i, j)]++;
            m[Pixel(Input, i, j)] += Pixel(Input, i, j);
        }
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        histogram[i + 1] += histogram[i];
        m[i + 1] += m[i];
    }
    //��ʼ��k,mg,cnt,variance
    k = 0;
    cnt = 1;
    //mg���������float�ͣ����ܴ�
    mg = (float) m[Gray_Max] / histogram[Gray_Max];
    variance = 0;
    //ʹ�ù�ʽ(mgT1-Q1)^2/T1(MN-T1),����ѭ������i����ȡ�����ֵ255�������ĸΪ0
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        if (histogram[i] != 0)
        {
            temp = (mg * histogram[i] - m[i]) * (mg * histogram[i] - m[i])
                    / (histogram[i] * (histogram[Gray_Max] - histogram[i]));
            if (temp > variance)
            {
                variance = temp;
                k = i;
                cnt = 1;
            }
            else if (temp == variance)
            {
                k += i;
                cnt++;
            }
        }
    }
    //�����ֵȡƽ��
    k /= cnt;
    //��ֵ��
    Grayscale_Binarization(Input, Output, k, row, col);
    delete[] histogram;
    delete[] m;
}

/*
 * @brief       ͼ��ָ�-Otsu���ȫ����ֵ��������ܳ��Ż��汾
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Global_Otsu_Better (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    uint8 k = Global_Otsu_Better_threshold(Input, row, col);
    //��ֵ��
    Grayscale_Binarization(Input, Output, k, row, col);
}

/*
 * @brief       Sobel����+Otsuʶ������
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Sobel_Recognizer (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //����ֻ�ǽ������ӵ�һ�֣�Ҳ���Բ���3,10,3�����, Ч�����������
    //x������΢�ֵ���ɢ��������
    int8 Fliter_gx[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //y������΢�ֵ���ɢ��������
    int8 Fliter_gy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //΢��gx��gy�Ļ���
    int16 gx_tmp, gy_tmp;
    //�������ػ���
    int16 temp;
    //���Ż��ɲ��Ż�
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            gx_tmp = 0;
            gy_tmp = 0;
            for (uint8 m = 0; m < 3 && i + m - 1 < row; m++)
                for (uint8 n = 0; i + m - 1 >= 0 && j + n - 1 < col && n < 3; n++)
                {
                    if (j + n - 1 >= 0)
                    {
                        gx_tmp += (int16) Fliter_gx[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                        gy_tmp += (int16) Fliter_gy[m][n] * Pixel(Input, (i + m - 1), (j + n - 1));
                    }
                }
            gx_tmp = gx_tmp < 0 ? -gx_tmp : gx_tmp;
            gy_tmp = gy_tmp < 0 ? -gy_tmp : gy_tmp;
            temp = gx_tmp + gy_tmp;
            Pixel(Output, i, j) = temp > Gray_Max ? Gray_Max : temp < 0 ? 0 : temp;
        }
    Global_Otsu_Better(Output, Output, MT9V03X_H, MT9V03X_W);
}

/*
 * @brief       ��ȡֱ��ͼͼ��
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       Input_row   ����ͼ������
 * @param       Input_col   ����ͼ������
 * @param       Output_row  ����ͼ������
 * @param       Output_col  ����ͼ������
 * @return      null
 */
void DIP::Get_Histogram (uint8 *Input, uint8 *Output, uint16 Input_row, uint16 Input_col, uint16 Output_row,
        uint16 Output_col)
{
    //ͼ���ֱ��ͼ����
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    uint16 &row = Input_row;
    uint16 &col = Input_col;
    //ͨ��Otsu��ȡ����ֵ
    uint8 k = Global_Otsu_Better_threshold(Input, row, col);
    //��¼���ֵ�����ڱ궨
    uint16 Pixel_Max = 0;
    //�������꣬���Ƹ���
    uint16 hposition;
    uint16 num;
    //��ʼ����������ͼ��
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            histogram[Pixel(Input, i, j)]++;
        }
    row = Output_row;
    col = Output_col;
    //���Output
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = 0;
        }
    //ͳ�����ֵ
    for (uint16 i = 0; i <= Gray_Max; i++)
    {
        Pixel_Max = Pixel_Max < histogram[i] ? histogram[i] : Pixel_Max;
    }
    //����ͼ��
    for (uint16 i = 0; i <= Gray_Max; i++)
    {
        num = (float) histogram[i] / Pixel_Max * row;
        hposition = (float) i / Gray_Max * col;
        for (uint16 j = 0; j < num; j++)
        {
            Pixel(Output,(row - j),hposition) = hposition > k ? Gray_Max : Gray_Max / 2;
        }
    }
    delete[] histogram;
}

/*
 * @brief       ���ܳ���������
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
void DIP::Car_Img_Process (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{

}

/*
 * @brief       ��¼����֡�����õ��Ŀ�ʼʱ��
 * @param       null
 * @return      null
 */
void DIP::FPS_Start ()
{
    start = platform_getval_ms();
}

/*
 * @brief       ��¼����֡�����õ��Ľ���ʱ��
 * @param       null
 * @return      null
 */
void DIP::FPS_End ()
{
    end = platform_getval_ms();
}

/*
 * @brief       ���֡�ʵ�����
 * @param       null
 * @return      null
 */
void DIP::Show_FPS ()
{
    platform_printf("Present Fps = %d\n", end - start ? 1000 / (end - start) : 0);
}
