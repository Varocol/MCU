#include "Image_Process.h"

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
 * @brief       ͼ��ָ�-Otsu���ȫ����ֵ����
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
uint8 Global_Otsu_threshold (uint8 *Input, uint16 row, uint16 col)
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
    delete[] histogram;
    delete[] m;
    //�����ֵȡƽ��
    k /= cnt;
    return k;
}

/*
 * @brief       ͼ��ָ�-Otsu���ȫ����ֵ��������ܳ��Ż��汾��ȡ��ֵ
 * @param       Input       ����ͼ��
 * @param       Output      ���ͼ��
 * @param       row         ͼ������
 * @param       col         ͼ������
 * @return      null
 */
uint8 Global_Otsu_Better_threshold (uint8 *Input, uint16 row, uint16 col)
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
void Grayscale_Identity (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Reverse (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Logarithm (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Pow (double Gamma, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Equalization (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Binarization (uint8 *Input, uint8 *Output, uint8 threshold, uint16 row, uint16 col)
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
void Filter_Mean (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Filter_Gaussian (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Filter_Median (uint8 size, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fliter_Laplace (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fliter_Unsharp (uint8 *Origin, uint8 *Blur, uint8 *Output, uint16 row, uint16 col)
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
void Fliter_Sobel (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fuzzy_GrayValue (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fuzzy_EdgeEnhance (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Segmentation_Point (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Segmentation_Line (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_threshold (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_Otsu (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_Otsu_Better (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Sobel_Recognizer (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Get_Histogram (uint8 *Input, uint8 *Output, uint16 Input_row, uint16 Input_col, uint16 Output_row,
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
 * @brief       ��¼����֡�����õ��Ŀ�ʼʱ��
 * @param       null
 * @return      null
 */
void FPS_Start ()
{
    start = platform_getval_ms();
}

/*
 * @brief       ��¼����֡�����õ��Ľ���ʱ��
 * @param       null
 * @return      null
 */
void FPS_End ()
{
    end = platform_getval_ms();
}

/*
 * @brief       ���֡�ʵ�����
 * @param       null
 * @return      null
 */
void Show_FPS ()
{
    platform_printf("Present Fps = %d\n", end - start ? 1000 / (end - start) : 0);
}

/*
 * @brief       ��ȡ����ͼ��
 * @param       null
 * @return      null
 */
void Get_Use_Image ()
{
    for (int i = 0, row = 0; i < IMAGEH; row++, i += 2)  //120�У�ÿ2�вɼ�һ�У�///ֻȡԭͼ���1/2
    {
        for (int j = 0, col = 0; j < IMAGEW; col++, j += 2) //188��
        {
            Image_Use[row][col] = mt9v03x_image[i][j];
        }
    }
}

/*
 * @brief       �Լ�
 * @param       null
 * @return      null
 */
void OnlyOnce ()
{
    if (Onlyonce)
    {
        MiddleLine[RowMax] = ColumnMax / 2;
        LeftEdge[RowMax] = 0;
        RightEdge[RowMax] = ColumnMax;
        MiddleLine[57] = ColumnMax / 2;
        LeftEdge[57] = 0;
        RightEdge[57] = ColumnMax;
        MiddleLine[58] = ColumnMax / 2;
        LeftEdge[58] = 0;
        RightEdge[58] = ColumnMax;
        MiddleLine[56] = ColumnMax / 2;
        LeftEdge[56] = 0;
        RightEdge[56] = ColumnMax;
    }
    Onlyonce = 0;
}

/*
 * @brief       ��·������
 * @param       null
 * @return      null
 */
void SpurroadConduct ()
{
    int j = 0, k = 0;
    int L1, L2, R1, R2;
    LastLastSpurroadFlag = LastSpurroadFlag; //��¼���ϴ��Ƿ���ʮ��
    LastSpurroadFlag = SpurroadFlag; //��¼��һ���Ƿ���ʮ��
    //SpurroadFlag=0;//����

    if (Road_widening == 1 && Road_vanish == 1 && (AvaliableLines < 20))
    {
        Road_widening = 0;
        Road_vanish = 0;
        SpurroadFlag = 1;
    }

    if (SpurroadFlag)
    {
        SpurroadKL = (float) ((LeftEdge[FirstLoseAllLine] - LeftEdge[LastLoseAllLine]))
                / (FirstLoseAllLine - LastLoseAllLine);
        SpurroadKR = (float) ((RightEdge[FirstLoseAllLine] - RightEdge[LastLoseAllLine]))
                / (FirstLoseAllLine - LastLoseAllLine);
        for (j = FirstLoseAllLine - 1; j > LastLoseAllLine; j--)
        {
            Pixle[j][MiddleLine[j]] = White_Point;
            MiddleLine[j] = (((int) ((j - FirstLoseAllLine) * SpurroadKL) + LeftEdge[FirstLoseAllLine])
                    + ((int) ((j - FirstLoseAllLine) * SpurroadKR) + RightEdge[FirstLoseAllLine])) / 2;
        }
    }
}

/*
 * @brief       ����ƫ���˲�
 * @param       null
 * @return      null
 */
void Zebra_Filter ()
{
    int16 ZebraFilterLoc[StartLine + 2][40];    //û����ô�������      ///57*40������
    int16 i = 0, j = 0, k = 0, num = 1;
    for (i = StartLine + 1; i >= FinishLine - 1; i--) ///58��18
    {
        for (j = 25; j < ColumnMax - 25 - 1; j++) ///25��67
        {
            if (CheckWhitePixle(i, j)) ///����ǰ׵�
                ZebraFilterLoc[i][num++] = j; //�ڶ�λ��ʼ�浥�������λ��///��j��¼���õ��Ӧ����������
        }
        for (k = num; k < 40; k++)
            ZebraFilterLoc[i][k] = 0; ///����׵����������40����ִ��������䣬����numǰ�浽40ȫ����
        ZebraFilterLoc[i][0] = num - 1;     //��һλ�����������
        num = 1;
    }
    for (i = StartLine + 1; i >= FinishLine - 1; i--) ///58��18
    {
        for (j = 1; j <= ZebraFilterLoc[i][0]; j++) ///1���׵�����
        {
            if (ZebraFilterLoc[i][ZebraFilterLoc[i][0]] != 0 &&                         //������һ������0һ������û�ҵ������
                    ABS(ZebraFilterLoc[i][ZebraFilterLoc[i][0]]-ZebraFilterLoc[i][1]) < 30) ///���һ���㲻����0�����һ���Ĳ�ֵС��30��
            {
                for (k = ZebraFilterLoc[i][1]; k <= ZebraFilterLoc[i][ZebraFilterLoc[i][0]]; k++) ///�ӵ�һ�������׵�
                {
                    Image_Sobel[i][k] = 0;
                }
            }
        }
    }
}

/*
 * @brief       �������˲�
 * @param       middle_err �������
 * @return      null
 */
float Middle_Err_Filter (float middle_err)
{
    float Middle_Err_Fltered;
    Middle_Err_Fltered = middle_err * 0.8 + LastAverageCenter * 0.2; ///���ȡ0.8���ϴε�0.2���
    return Middle_Err_Fltered;
}

/*
 * @brief       ·���ж�
 * @param       null
 * @return      null
 */
void TrackJudge ()
{
    //ʹ����Զ��ƫ��ͼ�Ȩƫ��ȷ��ǰհ
    Foresight = 0.7 * ABS(MiddleLine[LastLine+2]-ColumnMax/2) + 0.3 * ABS(AverageCenter-ColumnMax/2);
    Last_Foresight = Foresight;

    Fictitious_Num = Fictitious_Beeline();
    Track_ImgCount++;
    if (Track_ImgCount == 5)
    {
        Track_ImgCount = 0;
        LastAverageError[0] = LastAverageError[1];
        LastAverageError[1] = LastAverageError[2];
        LastAverageError[2] = LastAverageError[3];
        LastAverageError[3] = LastAverageError[4];
        LastAverageError[4] = ABS(AverageCenter-ColumnMax/2);
    }
    //�����ֱ��
    if (LastAverageError[0] > 7 && LastAverageError[1] > 6 && LastAverageError[2] > 5 && LastAverageError[4] < 4
            && BlackEndM > 30 && ABS(Fictitious_Num) < 30)
    {
        Track_Type = CurveToStraight;
    }
    //ֱ��
    else if (LastAverageError[0] < 4 && LastAverageError[1] < 4 && LastAverageError[2] < 4 && Foresight <= 5)
    {
        Track_Type = InStraight;
    }
    //ֱ�������
    else if (LastAverageError[0] < 6 && LastAverageError[1] < 6 && LastAverageError[2] < 6 && Foresight >= 5)
    {
        Track_Type = StraightToCurve;
    }
    //�����
    else
    {
        Track_Type = InCurve;
    }
}

/*
 * @brief       ȫ��ɨ��ͱ�Ե�����ȡ����������
 * @param       null
 * @return      null
 */
void SearchCenterBlackline ()
{
    int16 i = 0, j = 0, k = 0;
    int16 LeftFilterStart = 0;
    int16 RightFilterStart = 0;
    int16 StartColumn = 0;
    int16 FinishColumn = 0;
    int16 numfind = 0;
    //ȫ�ֱ�������
    LeftLose = 0;
    RightLose = 0;
    AllLose = 0;
    StartLineCount = 0;
    SearchErrorFlag = 0;
    WhiteLose = 0;
    WhiteLoseStart = 0;
    LeftLoseStart = 0;
    RightLoseStart = 0;
    FirstLoseAllLine = 0;
    LastLoseAllLine = 0;
    Line_Count = 0;
    SalationFlag = 0;
    //��λ������ʼ������
    Left_Add_Start = 0;
    Right_Add_Start = 0;
    Left_Add_Stop = 0;
    Right_Add_Stop = 0;
    //��λ��60������
    MiddleLine[RowMax - 1] = ColumnMax / 2; ///47
    LeftEdge[RowMax - 1] = 0;
    RightEdge[RowMax - 1] = ColumnMax; ///94

    OnlyOnce(); ///�Լ�

    /*************************************************************************************/
    /*                           һ�α�����ʼ��ȫ��+��Ե��                                                          */
    /*************************************************************************************/
    for (i = StartLine; i > DivideLine; i--) ///57��47                //������ǰN�У�ȫ��ɨ��
    {

        //���ұ߽綼������λ����һ����
        /***********************************������߽�********************************************/
        if (i == StartLine)
            j = MiddleLine[RowMax]; //���о�����һ��ͼ��������Ϊɨ�����///���i=StartLineʱ��MiddleLine[RowMax]����Ч���ݣ�������Ҫdebug
        else if (AllLose > 5)
            j = ColumnMax / 2;
        else
            j = MiddleLine[i + 1]; //���������һ���е��λ����Ϊ����ɨ�����
        if (j < 3)
            j = 3; //j>=3��Ч��Χ������
        while (j >= 3) //j>=3��Ч��Χ�ڽ�����Ѱ
        {
            //���������ҵ��׺ں�����
            if (CheckLeft(i, j))
            {
                LeftEdge[i] = j;                        //�ҵ���ֵ �Ҳ�������ԭֵ0
                break;                        //��������Ѱ��
            }
            j--;                                        //���������ƶ�
        }
        if (j < 3)
            LeftEdge[i] = 1;                                 //�Ҳ�������߾�����Ϊ1
        /***********************************�����ұ߽�********************************************/
        if (i == StartLine)
            j = MiddleLine[RowMax]; //���о�����һ��ͼ��������Ϊɨ�����
        else if (AllLose > 5)
            j = ColumnMax / 2;
        else
            j = MiddleLine[i + 1]; //�������һ������λ�ÿ�ʼ��Ѱ
        if (j > ColumnMax - 3)
            j = ColumnMax - 3; //j <=ColumnMax-3��Ч��Χ������
        while (j <= ColumnMax - 3)
        {
            //���������ҵ��׺ں������
            if (CheckRight(i, j))
            {
                RightEdge[i] = j;                   //�ҵ���ֵ   �Ҳ�������ԭֵ
                break;                   //��������Ѱ��
            }
            j++;                                        //���������ƶ�
        }
        if (j >= ColumnMax - 3)
            RightEdge[i] = ColumnMax - 1;                 //�Ҳ����ұ��߾�����ΪColumnMax-1

        /************************************�˲�********************************************/
        if (LeftEdge[i] == 1 && LeftEdge[i + 1] == 1 && LeftEdge[i + 2] == 1 && LeftEdge[i + 3] == 1
                && LeftEdge[i + 4] == 1)
        ///һֱ�Ҳ��������
        {
            LeftFilterStart = i;                 ///LeftFilterStart��Ϊi��߽��˲���ʼ��
        }
        if (RightEdge[i] == ColumnMax - 1 && RightEdge[i + 1] == ColumnMax - 1 && RightEdge[i + 2] == ColumnMax - 1
                && RightEdge[i + 3] == ColumnMax - 1 && RightEdge[i + 4] == ColumnMax - 1)
        ///һֱ�Ҳ����ұ���
        {
            RightFilterStart = i;
        }
        /************************************�����ж�********************************************/
        Left_Add_Line[i] = LeftEdge[i];                     //��¼ʵ����߽�Ϊ������߽�
        Right_Add_Line[i] = RightEdge[i];                     //��¼ʵ���ұ߽�Ϊ������߽�
        if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 2) && i < StartLine)           //���������
        ///((RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+2) && i<StartLine)
        {
            Left_Add_Flag[i] = 1;                ///��һ�����߱�־��1
            Right_Add_Flag[i] = 1;
            AllLose++;                ///���в�������������ж�ʮ��
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];                //����һ��
        }
        else if ((LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //ȫ��
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            LastLoseAllLine = i;
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] != ColumnMax - 1)    //û�ж���
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 0;
            MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;    ///���߼�Ϊ�������е�
            if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 1) && i < StartLine)    //���������
                MiddleLine[i] = MiddleLine[i + 1];    //����һ��
        }
        else if (LeftEdge[i] == 1 && RightEdge[i] != ColumnMax - 1)    //��������
        {
            if (!LeftLoseStart)
                LeftLoseStart = i;    ///��¼��߶��ߵĿ�ʼ��
            Left_Add_Flag[i] = 1;    ///��һ�����߱�־��1
            Right_Add_Flag[i] = 0;    ///��һ���Ҳ��߱�־��0
            if (i <= RowMax - 1 && RightEdge[i] > Width[i] / 2 + 1)    //�����Ļ����ð��///�ұ߽����ÿ�е�·�߽��һ����Ϊ������
            ///���˾����ұ߽�ҲӦ��С��width[i]///����߽綪ʧʱ���ұ߽粻���ܴ���width[i]��
                MiddleLine[i] = RightEdge[i] - Width[i] / 2;
            else
                //Խ������������
                MiddleLine[i] = 1;            ///���߶�Ϊ1��Ϊ��Ҫ�������ת��
            LeftLose++;       ///����������
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] == ColumnMax - 1)    //��������
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 1;
            if (!RightLoseStart)
                RightLoseStart = i;
            if (i <= RowMax - 1 && LeftEdge[i] + Width[i] / 2 < ColumnMax - 1)      //�����Ļ����ð��
                MiddleLine[i] = LeftEdge[i] + Width[i] / 2;
            else
                //Խ�������ҽ����
                MiddleLine[i] = ColumnMax - 1;
            BlackEndM++;      //��¼ֻ�����߶�������///���Գ���˵ӦΪ�������д���
            RightLose++;      ///���Ҷ�������
        }
        else if ((LeftEdge[i] == 1 && RightEdge[i] == ColumnMax - 1)) //ȫ��
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            LastLoseAllLine = i; ///ȫ�������л�����i�ļ��ٶ��仯�������С�
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        if (Left_Add_Flag[i])                                                        //��߽���Ҫ����
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                                                    //ǰ6��
                Left_Add_Line[i] = LeftEdge[StartLine - 1];                                                    //ʹ�õ�������
            else if (i < StartLine - 6)                                                    //ʣ�µ�
                Left_Add_Line[i] = Left_Add_Line[i + 1];                                               //ʹ��ǰ1����߽���Ϊ������߽�
        }
        if (Right_Add_Flag[i])                                                       //�ұ߽���Ҫ����
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                                                    //ǰ6��
                Right_Add_Line[i] = RightEdge[StartLine - 1];                                                   //ʹ�õ�������
            else if (i < StartLine - 6)                                                    //ʣ�µ�
                Right_Add_Line[i] = Right_Add_Line[i + 1];                                             //ʹ��ǰ1���ұ߽���Ϊ�����ұ߽�
        }
        if (RightEdge[i] > LeftEdge[i])
            RealWidth[i] = RightEdge[i] - LeftEdge[i];  //����ʵ���������
        else
            RealWidth[i] = 0;
        if (Right_Add_Line[i] > Left_Add_Line[i])  //���㲹���������
            Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i];
        else
            Width_Add[i] = 0;

        if (!RRSalationLine && i < StartLine - 5
                &&  ///���������RightEdge[i]ʼ������С�ģ��������ֻ��˵����������䣬����������㡣Ŀǰ����ֻ����һ�Ρ�
                RightEdge[i] == MIN(MIN(RightEdge[i + 4], RightEdge[i + 3]), RightEdge[i + 2])
                && RightEdge[i] == MIN(MIN(RightEdge[i], RightEdge[i + 1]), RightEdge[i + 2]))
        {
            RRSalationLine = i + 2;                                    ///�ұ�����������ʼ��
        }
        else if (!LLSalationLine && i < StartLine - 5
                && LeftEdge[i] == MAX(MAX(LeftEdge[i + 4], LeftEdge[i + 3]), LeftEdge[i + 2])
                && LeftEdge[i] == MAX(MAX(LeftEdge[i + 2], LeftEdge[i + 1]), LeftEdge[i]))
        {
            LLSalationLine = i + 2;
        }
        /*******************************��ʼ�����ݴ���**************************************/
        if (i == StartLine)                                    ///ֻ������ʼ������
        {
            LeftEdge[RowMax] = LeftEdge[StartLine];     ///���ݱ��浽60�ж�Ӧ����
            RightEdge[RowMax] = RightEdge[StartLine];
            Left_Add_Line[RowMax] = Left_Add_Line[StartLine];
            Right_Add_Line[RowMax] = Right_Add_Line[StartLine];
            Left_Add_Line[StartLine + 1] = Left_Add_Line[StartLine];
            Right_Add_Line[StartLine + 1] = Right_Add_Line[StartLine];

            if (Left_Add_Flag[StartLine] && Right_Add_Flag[StartLine])     ///��ʼ��������Ҫ����
            {
                MiddleLine[StartLine] = MiddleLine[RowMax];     ///��60�е����ߴ��濪ʼ��
                FirstLoseAllLine = 0;     ///ȫ���׿�ʼ������
            }
            else
            {
                MiddleLine[RowMax] = MiddleLine[StartLine]; // ���µ�60�������е㣬������һ֡ͼ��ʹ��
            }

            MiddleLine[RowMax] = RANGE16(MiddleLine[RowMax], 15, 80); ///�����޷���15��80֮��

            RealWidth[RowMax] = RealWidth[StartLine];

            Width_Add[RowMax] = Width_Add[StartLine];

            Width_Add[StartLine + 1] = Width_Add[StartLine];

            Width_Min = Width_Add[StartLine]; //Width_Min��ʵ�ǵ�һ���������Ҳ����
            //û�н������ν���ͼ�����������
        }
    }
    /*�������������������������������������ָ��ߡ���������������������������������������*/
    for (i = DivideLine; i >= FinishLine; i -= StepLine)                //����ʣ����///47��18
    {
        LastLine = i;                ///ɨ�����һ��
        /*******************************�ж����ұ߽練������*************************************/
        if ((!SearchErrorFlag) && ((LeftEdge[i + 1] >= ColumnMax / 2 + 5) || (RightEdge[i + 1] <= ColumnMax / 2 - 5)))
        {
            ///ColumnMax/2+5=52,ColumnMax/2-5=42///��߽���ұ߽��쳣
            if (LeftEdge[i + 1] >= ColumnMax / 2 + 10 || RightEdge[i + 1] <= ColumnMax / 2 - 10)     ///��߽����57�����ұ߽�С��37
            {
                SearchErrorFlag = i + 2;                ///��¼�쳣�У�֮���˳�ѭ����
                break;
            }
            else if (LeftEdge[i + 1] >= ColumnMax / 2 + 5)                ///52
            {
                if (RightEdge[i + 1] == ColumnMax - 1)                ///93///δ�ҵ��ұ߽�
                {
                    FinishColumn = ColumnMax - 1;
                    while (FinishColumn >= LeftEdge[i + 1])                ///������������߽�
                    {
                        if (CheckLeft(i, FinishColumn))
                        {
                            LeftEdge[i] = FinishColumn;                ///�ҵ��ͼ�¼����
                            break;
                        }
                        FinishColumn--;
                    }
                    if (FinishColumn < LeftEdge[i + 1])                ///���������һ�е���߽�
                        LeftEdge[i] = LeftEdge[i + 1];
                }
                else
                {
                    LeftEdge[i] = LeftEdge[i + 1];                ///�ҵ��ұ߽磬��߽�����һ�е�
                }
            }
            else if (RightEdge[i + 1] <= ColumnMax / 2 - 5)                ///42
            {
                if (LeftEdge[i + 1] == 1)
                {
                    FinishColumn = 1;
                    while (FinishColumn <= RightEdge[i + 1])
                    {
                        if (CheckRight(i, FinishColumn))
                        {
                            RightEdge[i] = FinishColumn;
                            break;
                        }
                        FinishColumn++;
                    }
                    if (FinishColumn > RightEdge[i + 1])
                        RightEdge[i] = RightEdge[i + 1];
                }
                else
                {
                    RightEdge[i] = RightEdge[i + 1];
                }
            }
        }
        /***************************��һ��û�ҵ��߽磬ȫ��ȫ��ɨ��*******************************/
        if ((LeftEdge[i + 1] == 1 && RightEdge[i + 1] == ColumnMax - 1) || LeftLose > 5 || RightLose > 5 || AllLose > 5)
        {
            ////////////////////////��ͨ��ȫ��ɨ������߽�///////////////////////////
            if (AllLose > 5)
                FinishColumn = MiddleLine[RowMax];                ///���ȫ����60�������
            else
                FinishColumn = MiddleLine[i + 1];                ///��������һ�е�����
            if (FinishColumn <= 2)
            {
                FinishColumn = 3;
            }
            while (FinishColumn >= 3)
            {
                if (CheckLeft(i, FinishColumn))
                {
                    LeftEdge[i] = FinishColumn;                ///�ҵõ���������
                    break;
                }
                FinishColumn--;
                if (FinishColumn < 3)
                    LeftEdge[i] = 1;                ///�����������
            }
            ////////////////////////��ͨ��ȫ��ɨ�����ұ߽�///////////////////////////
            if (AllLose > 5)
                FinishColumn = MiddleLine[RowMax];
            else
                FinishColumn = MiddleLine[i + 1];
            if (FinishColumn < LeftEdge[i])
                FinishColumn = LeftEdge[i] + 1;
            if (FinishColumn >= ColumnMax - 3)
            {
                FinishColumn = ColumnMax - 3;
            }
            while (FinishColumn <= ColumnMax - 3)
            {
                if (CheckRight(i, FinishColumn))
                {
                    RightEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn++;
                if (FinishColumn > ColumnMax - 3)
                    RightEdge[i] = ColumnMax - 1;
            }
        }

#if 0//���Լ����ε���һ����

        /***************************��һ�����߶��ҵ� ȫ������ɨ��*******************************/
        else if(LeftEdge[i+1]!=1 && RightEdge[i+1]!=ColumnMax-1)
        {
            //////////////////////////////������߽�///////////////////////////////////
            FinishColumn = ((LeftEdge[i+1]+10) >= ColumnMax-3)? ColumnMax-3:(LeftEdge[i+1]+10);///��ColumnMax-3����ColumnMax-3
            StartColumn = ((LeftEdge[i+1]-5) <= 3)? 3:(LeftEdge[i+1]-5);///��3С��3
            while(FinishColumn >= StartColumn)
            {
                if(CheckLeft(i,FinishColumn))
                {
                    LeftEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn--;
                if(FinishColumn < StartColumn)
                LeftEdge[i] = 1;
            }
            //////////////////////////////�����ұ߽�///////////////////////////////////
            FinishColumn = ((RightEdge[i+1]-10) <= 3)? 3:(RightEdge[i+1]-10);
            StartColumn = ((RightEdge[i+1]+5) >= ColumnMax-3)? ColumnMax-3:(RightEdge[i+1]+5);
            while(FinishColumn <= StartColumn)
            {
                if(CheckRight(i,FinishColumn))
                {
                    RightEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn++;
                if(FinishColumn > StartColumn)
                RightEdge[i] = ColumnMax - 1;
            }
        }
        /***************************��һ��ֻ�ҵ���߽� ����+ȫ��ɨ��*******************************/
        else if(LeftEdge[i+1]!=1 && RightEdge[i+1]==ColumnMax-1)
        {
            ////////////////////////��ͨ������ɨ������߽�///////////////////////////
            FinishColumn = ((LeftEdge[i+1]+10) >=ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);///��ColumnMax-2����ColumnMax-2
            StartColumn = ((LeftEdge[i+1]-5) <= 1)? 1:(LeftEdge[i+1]-5);///��1С��1
            while(FinishColumn >= StartColumn)
            {
                if(CheckLeft(i,FinishColumn))
                {
                    LeftEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn--;
                if(FinishColumn < StartColumn)
                LeftEdge[i] = 1;
            }
            ////////////////////////��ͨ��ȫ��ɨ�����ұ߽�///////////////////////////
            FinishColumn = MiddleLine[i+1];
            if(FinishColumn<LeftEdge[i]) FinishColumn = LeftEdge[i]+1;
            if(FinishColumn >= ColumnMax-3)
            {
                FinishColumn = ColumnMax-3;
            }
            while(FinishColumn <= ColumnMax-3)
            {
                if(CheckRight(i,FinishColumn))
                {
                    RightEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn++;
                if(FinishColumn > ColumnMax-3)
                RightEdge[i] = ColumnMax - 1;
            }
        }
        /***************************��һ��ֻ�ҵ��ұ߽� ����+ȫ��ɨ��*******************************/
        else if(LeftEdge[i+1]==1 && RightEdge[i+1]!=ColumnMax-1)
        {
            ////////////////////////��ͨ������ɨ�����ұ߽�//////////////////////////
            FinishColumn = ((RightEdge[i+1]-10) <= 1)? 1:(RightEdge[i+1]-10);
            StartColumn = ((RightEdge[i+1]+5) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+5);
            while(FinishColumn <= StartColumn)
            {
                if(CheckRight(i,FinishColumn))
                {
                    RightEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn++;
                if(FinishColumn > StartColumn)
                RightEdge[i] = ColumnMax - 1;
            }
            ////////////////////////��ͨ��ȫ��ɨ������߽�///////////////////////////
            FinishColumn = MiddleLine[i+1];
            if(FinishColumn>RightEdge[i]) FinishColumn = RightEdge[i]-1;
            if(FinishColumn <= 2)
            {
                FinishColumn= 3;
            }
            while(FinishColumn >= 3)
            {
                if(CheckLeft(i,FinishColumn))
                {
                    LeftEdge[i] = FinishColumn;
                    break;
                }
                FinishColumn--;
                if(FinishColumn < 3)
                LeftEdge[i] = 1;
            }
        }
#endif

        /************************************�����ж�********************************************/
        Left_Add_Line[i] = LeftEdge[i];                     //��¼ʵ����߽�Ϊ������߽�
        Right_Add_Line[i] = RightEdge[i];                     //��¼ʵ���ұ߽�Ϊ������߽�
        if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 3) ///(RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+3
        && i < StartLine)                     //���������
        {
            if (LeftLose > 10 || RightLose > 10 || AllLose > 10)                   ///�����������ȫ���ߴ���10
                SalationFlag = 1;
        }
        if (SalationFlag)
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            LeftEdge[i] = LeftEdge[i + 1];
            RightEdge[i] = RightEdge[i + 1];
            MiddleLine[i] = MiddleLine[i + 1];                   //����һ��
        }
        else if ((LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //ȫ��
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            LastLoseAllLine = i;
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] != ColumnMax - 1)    //û�ж���
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 0;
            MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;
        }
        else if (LeftEdge[i] == 1 && RightEdge[i] != ColumnMax - 1)    //��������
        {
            if (!LeftLoseStart)
                LeftLoseStart = i;
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 0;
            if (i <= RowMax - 1 && RightEdge[i] > Width[i] / 2 + 1)    //�����Ļ����ð��
                MiddleLine[i] = RightEdge[i] - Width[i] / 2;
            else
                //Խ������������
                MiddleLine[i] = 1;
            LeftLose++;
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] == ColumnMax - 1)    //��������
        {
            if (!RightLoseStart)
                RightLoseStart = i;
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 1;
            if (i <= RowMax - 1 && LeftEdge[i] + Width[i] / 2 < ColumnMax - 1)      //�����Ļ����ð��
                MiddleLine[i] = LeftEdge[i] + Width[i] / 2;
            else
                //Խ�������ҽ����
                MiddleLine[i] = ColumnMax - 1;
            RightLose++;      //��¼ֻ�����߶�������
        }
        else if ((LeftEdge[i] == 1 && RightEdge[i] == ColumnMax - 1)
                || (LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //ȫ��
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        if (Left_Add_Flag[i])                                                    //��߽���Ҫ����
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                            //ǰ6��ʹ�õ�������
                Left_Add_Line[i] = LeftEdge[StartLine - 1];
            else if (i < StartLine - 6)                            //��6��ʹ��ǰ1����߽���Ϊ������߽�
                Left_Add_Line[i] = Left_Add_Line[i + 1];
        }
        if (Right_Add_Flag[i])                                                   //�ұ߽���Ҫ����
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                            //ǰ6��ʹ�õ�������
                Right_Add_Line[i] = RightEdge[StartLine - 1];
            else if (i < StartLine - 6)                            //��6��ʹ��ǰ1����߽���Ϊ������߽�
                Right_Add_Line[i] = Right_Add_Line[i + 1];
        }
        if (RightEdge[i] > LeftEdge[i])
            RealWidth[i] = RightEdge[i] - LeftEdge[i];  //����ʵ���������
        else
            RealWidth[i] = 0;  //��Խ����ֱ����0
        if (Right_Add_Line[i] > Left_Add_Line[i])  //���㲹���������
            Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i];
        else
            Width_Add[i] = 0;

        SearchErrorFlag = 0;
    }
    /*************************************************************************************/
    /*                              һ�α�������                                         */
    /*************************************************************************************/
    /*************************************************************************************/
    /*                      ���α�����ʼ�����в���+��̬ǰհ��                             */
    /*************************************************************************************/
    // for(i=StartLine; i>LastLine; i-=StepLine) ///��57��0
    // {
    //     /********************************* ���߼�⿪ʼ *************************************/
    //     if (RealWidth[i] > Width_Min+1)  // ������ȱ��������ʮ�ֻ�·��///����������·
    //     {
    //         //Width_Min��ʵ�ǵ�һ���������Ҳ����
    //         //û�н������ν���ͼ�����������
    //         Road_widening = 1;///��·����־�������ж�����·
    //         if (Left_Add_Line[i] < Left_Add_Line[i+2] &&
    //                 Left_Add_Line[i+2] < Left_Add_Line[i+4] && i<StartLine)  //������������Զ�����խ��Left_Add_Line[i]�ȽϽ����Ĵ�
    //         {
    //             if (!Left_Add_Flag[i])
    //                 Left_Add_Flag[i] = 1;    //��������Ϊ0��ǿ���϶�Ϊ��Ҫ����
    //         }
    //         if (Right_Add_Line[i] > Right_Add_Line[i+2] &&
    //                 Right_Add_Line[i+2] > Right_Add_Line[i+4] &&i<StartLine)     //�������෴
    //         {
    //             if (!Right_Add_Flag[i])
    //                 Right_Add_Flag[i] = 1;   //��������Ϊ0��ǿ���϶�Ϊ��Ҫ����
    //         }
    //         if ((Left_Add_Flag[i] || Right_Add_Flag[i] || SearchErrorFlag == i) && (i<FinishLine+10))///(Left_Add_Flag[i] || Right_Add_Flag[i] || SearchErrorFlag == i && i<FinishLine+10)
    //         {
    //             if (Left_Add_Stop || Right_Add_Stop || SearchErrorFlag == i)
    //             {
    //                 break;
    //             }
    //         }
    //     }
    //     /******************************** ��һ�ֲ��߿�ʼ ************************************/
    //     if (Left_Add_Flag[i] && i<StartLine) // �����Ҫ����
    //     {
    //         if (i >= StartLine-3 && i < StartLine)   // ǰ���в��߲���
    //         {
    //             if (!Left_Add_Start && Left_Add_Flag[i-1] && Left_Add_Flag[i-2])///i��54��56֮����ǰ������Ҫ����
    //             {
    //                 Left_Add_Start = i;  // ��¼���߿�ʼ��
    //                 Left_Ka = 0;
    //                 Left_Kb = Left_Add_Line[i];
    //             }
    //             Left_Add_Line[i] = Calculate_Add(i, Left_Ka, Left_Kb); ///���ճ���Գ�ԭ���Լ�
    //         }
    //         else if(i < StartLine-3)///iС��54
    //         {
    //             if (!Left_Add_Start && Left_Add_Flag[i-1] && Left_Add_Flag[i-2]) // ֮ǰû�в���
    //             {
    //                 Left_Add_Start = i;  // ��¼��ಹ�߿�ʼ��
    //                 Curve_Fitting(&Left_Ka, &Left_Kb, &Left_Add_Start, Left_Add_Line, Left_Add_Flag, 1); // ʹ�����㷨���ֱ��///����µ�Ka��Kb
    //             }
    //         }
    //         Left_Add_Line[i] = Calculate_Add(i, Left_Ka, Left_Kb);   // ʹ��ǰһ��ͼ����߽�б�ʲ���///��һ�����߳��򣬻�һ����
    //     }
    //     else
    //     {
    //         if (Left_Add_Start)  // �Ѿ���ʼ���߶��ҿ�ʼ������
    //         {
    //             if (!Left_Add_Stop &&
    //                     !Left_Add_Flag[i+2*StepLine] &&
    //                     !Left_Add_Flag[i+4*StepLine]
    //                     && i<StartLine-5*StepLine)///�ں����кͺ����в�������iС��52
    //             {
    //                 if ((Left_Add_Line[i] >= Left_Add_Line[i+2*StepLine] &&
    //                         Left_Add_Line[i+2*StepLine] >= Left_Add_Line[i+4*StepLine]&&
    //                         Left_Add_Line[i]!=1 &&
    //                         Left_Add_Line[i+1*StepLine]!=1 &&
    //                         Left_Add_Line[i+2*StepLine]!=1))///��i��i+1��i+2������߲���1�ҵ�i��i+2,i+4�е���������α��˵���������
    //                 {
    //                     Left_Add_Stop = i+4*StepLine;    // ��¼��ಹ�߽�����
    //                     //Line_Repair(Left_Add_Start, Left_Add_Stop, LeftEdge, Left_Add_Line, Left_Add_Flag, 1);
    //                 }
    //             }
    //         }
    //     }
    //     if (Right_Add_Flag[i] && i<StartLine)    // �Ҳ���Ҫ����
    //     {
    //         if (i >= StartLine-3 && i < StartLine)   // ǰ���в��߲���
    //         {
    //             if (!Right_Add_Start && Right_Add_Flag[i-1] && Right_Add_Flag[i-2])
    //             {
    //                 Right_Add_Start = i; // ��¼���߿�ʼ��
    //                 Right_Ka = 0;
    //                 Right_Kb = Right_Add_Line[i];
    //             }
    //             Right_Add_Line[i] = Calculate_Add(i, Right_Ka, Right_Kb);    // ʹ��ǰһ֡ͼ���ұ߽�б�ʲ���
    //         }
    //         else if(i < StartLine-3)
    //         {
    //             if (!Right_Add_Start)    // ֮ǰû�в���
    //             {
    //                 Right_Add_Start = i; // ��¼�Ҳಹ�߿�ʼ��
    //                 Curve_Fitting(&Right_Ka, &Right_Kb, &Right_Add_Start, Right_Add_Line, Right_Add_Flag, 2);    // ʹ�����㷨���ֱ��
    //             }
    //             Right_Add_Line[i] = Calculate_Add(i, Right_Ka, Right_Kb);    // �������
    //         }
    //     }
    //     else
    //     {
    //         if (Right_Add_Start) // �Ѿ���ʼ����
    //         {
    //             if (!Right_Add_Stop &&
    //                     !Right_Add_Flag[i+StepLine] &&
    //                     !Right_Add_Flag[i+2*StepLine] &&
    //                     i<StartLine-5*StepLine)
    //             {
    //                 if ((Right_Add_Line[i] <= Right_Add_Line[i+1*StepLine] &&
    //                         Right_Add_Line[i+1*StepLine] <= Right_Add_Line[i+2*StepLine]
    //                         && Right_Add_Line[i]!=ColumnMax-1
    //                         && Right_Add_Line[i+1*StepLine]!=ColumnMax-1
    //                         && Right_Add_Line[i+2*StepLine]!=ColumnMax-1))
    //                 {
    //                     Right_Add_Stop = i+4*StepLine;   // ��¼�Ҳಹ�߽�����
    //                     //Right_Add_Start = 0;
    //                     //Line_Repair(Right_Add_Start, Right_Add_Stop, RightEdge, Right_Add_Line, Right_Add_Flag, 2);
    //                 }
    //             }
    //         }
    //     }
    //     /********************************* ��һ�ֲ��߽��� **********************************/
    //     if(Right_Add_Line[i] >= Left_Add_Line[i])
    //         Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i]; // ���¼����������
    //     else
    //         Width_Add[i] = 0;
    //     if ((Left_Add_Flag[i] && Right_Add_Flag[i]) || (!Left_Add_Flag[i] && !Right_Add_Flag[i]))///����ͬʱ��Ҫ���߻���ͬʱ����Ҫ
    //         MiddleLine[i] = (Right_Add_Line[i] + Left_Add_Line[i]) / 2;  // ��������
    //     else if(i<StartLine)
    //         MiddleLine[i] = MiddleLine[i+StepLine];
    //     if (Width_Add[i] < Width_Min)
    //     {
    //         Width_Min = Width_Add[i];                // ������С�������
    //     }
    //     Line_Count = i;                              //Line_Count����
    // }
    // /*************************************************************************************/
    // /*                              ���α�������                                         */
    // /*************************************************************************************/
    // /*************************************************************************************/
    // /*                     ���α�����ʼ�������޸�+�����޸���                              */
    // /*************************************************************************************/
    // /******************************* �����޸���ʼ ********************************/
    // if (Left_Add_Start)      // ��߽���Ҫ����
    // {
    //     Line_Repair(Left_Add_Start, Left_Add_Stop, LeftEdge, Left_Add_Line, Left_Add_Flag, 1);
    // }
    // if (Right_Add_Start) // �ұ߽���Ҫ����
    // {
    //     Line_Repair(Right_Add_Start, Right_Add_Stop, RightEdge, Right_Add_Line, Right_Add_Flag, 2);
    // }
    // /******************************* �����޸����� ********************************/
    // /******************************* �����޸���ʼ ********************************/
    // for(i=StartLine; i>=Line_Count; i-=StepLine)
    // {
    //     MiddleLine[i] = (Right_Add_Line[i] + Left_Add_Line[i]) / 2;  // ���������е�
    //     if(Right_Add_Line[i] >= Left_Add_Line[i])
    //         Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i]; // ���¼����������
    //     else
    //         Width_Add[i] = 0;
    //     if(SearchErrorFlag == i || CheckEnd(i-1,MiddleLine[i]) || i == FinishLine)///�������̬ǰհ�ж�����ڵ�����
    //     {
    //         LastLine = i;//���һ�У���̬ǰհ
    //         spurroadtriangle_i = i;
    //         spurroadtriangle_j = MiddleLine[i];
    //         AvaliableLines = StartLine - i;//��Ч����
    //         break;
    //     }
    // }
    /*************************************************************************************/
    /*                              ���α�������                                         */
    /*************************************************************************************/
    for (k = FinishLine; k <= StartLine; k++)
    {
        for (j = 0; j < ColumnMax; j++)
        {
            if (j == MiddleLine[k] || k == LastLine)

                Pixle[k][j] = 1;
        }

    }
}

/*
 * @brief       ��ȡͼ�����������ȡ���߽�ֹ��
 * @param       null
 * @return      null
 */
void GetBlackEndParam ()
{
    unsigned char LLLEndFlag = 0;    ///�׵��־λ
    unsigned char LLEndFlag = 0;
    unsigned char LEndFlag = 0;
    unsigned char MLEndFlag = 0;
    unsigned char MEndFlag = 0;
    unsigned char MREndFlag = 0;
    unsigned char REndFlag = 0;
    unsigned char RREndFlag = 0;
    unsigned char RRREndFlag = 0;

    int i = 0;

    LastBlackEndLL = BlackEndLL;
    LastBlackEndLLL = BlackEndLLL;
    LastBlackEndRR = BlackEndRR;
    LastBlackEndRRR = BlackEndRRR;

//����
    BlackEndLLL = 0;
    BlackEndLL = 0;
    BlackEndL = 0;
    BlackEndML = 0;
    BlackEndM = 0;
    BlackEndMR = 0;
    BlackEndR = 0;
    BlackEndRR = 0;
    BlackEndRRR = 0;

#if ImageMode<=1
    for (i = StartLine; i >0; i--)
    {
        if(CheckWhitePixle(i,ColumnMax/12) && !LLLEndFlag )//10
            BlackEndLLL++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax/12) && CheckBlackPixle(i-2,ColumnMax/12))
            LLLEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax/8) && !LLEndFlag)//10
            BlackEndLL++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax/8) && CheckBlackPixle(i-2,ColumnMax/8))
            LLEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*2/8) && !LEndFlag)//10
            BlackEndL++;//����߽�����
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*2/8) && CheckBlackPixle(i-2,ColumnMax*2/8))
            LEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*3/8) && !MLEndFlag)//10
            BlackEndML++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*3/8) && CheckBlackPixle(i-2,ColumnMax*3/8))
            MLEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*4/8) && !MEndFlag)//10
            BlackEndM++;//�к��߽�����
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*4/8) && CheckBlackPixle(i-2,ColumnMax*4/8))
            MEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*5/8) && !MREndFlag)//10
            BlackEndMR++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*5/8) && CheckBlackPixle(i-2,ColumnMax*5/8))
            MREndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*6/8) && !REndFlag)//10
            BlackEndR++;//�Һ��߽�����
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*6/8) && CheckBlackPixle(i-2,ColumnMax*6/8))
            REndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*7/8) && !RREndFlag)//10
            BlackEndRR++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*7/8) && CheckBlackPixle(i-2,ColumnMax*7/8))
            RREndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*11/12) && !RRREndFlag)//10
            BlackEndRRR++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*11/12) && CheckBlackPixle(i-2,ColumnMax*11/12))
            RRREndFlag = 1;
    }
#else
    for (i = RowMax - 1; i > 0; i--)    ///��59��0��///�ҵ��׵�����ҵ��ڵ�,�ڵ���������
    {
        if (CheckBlackPixle(i,ColumnMax/12) && !LLLEndFlag)    //94/12=7.83
            BlackEndLLL++;    //��i�У���7���Ǻڵ�
        else if (i > 1 && CheckEnd(i, ColumnMax/12))
            LLLEndFlag = 1;    //��i�У���7���ǰ׵�

        if (CheckBlackPixle(i,ColumnMax/8) && !LLEndFlag)    //94/8=11.75
            BlackEndLL++;
        else if (i > 1 && CheckEnd(i, ColumnMax/8))
            LLEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*2/8) && !LEndFlag)    //23.5
            BlackEndL++;    //����߽�����
        else if (i > 1 && CheckEnd(i, ColumnMax*2/8))
            LEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*3/8) && !MLEndFlag)    //35.25
            BlackEndML++;
        else if (i > 1 && CheckEnd(i, ColumnMax*3/8))
            MLEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*4/8) && !MEndFlag)    ///47
            BlackEndM++;    //�к��߽�����
        else if (i > 1 && CheckEnd(i, ColumnMax*4/8))
            MEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*5/8) && !MREndFlag)    ///58.75
            BlackEndMR++;
        else if (i > 1 && CheckEnd(i, ColumnMax*5/8))
            MREndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*6/8) && !REndFlag)    ///70.5
            BlackEndR++;    //�Һ��߽�����
        else if (i > 1 && CheckEnd(i, ColumnMax*6/8))
            REndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*7/8) && !RREndFlag)    ///82.25
            BlackEndRR++;
        else if (i > 1 && CheckEnd(i, ColumnMax*7/8))
            RREndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*11/12) && !RRREndFlag)    ///86.17
            BlackEndRRR++;
        else if (i > 1 && CheckEnd(i, ColumnMax*11/12))
            RRREndFlag = 1;
    }

    if (!LLLEndFlag)
        BlackEndLLL = 0;    ///����

    if (!LLEndFlag)
        BlackEndLL = 0;

    if (!LEndFlag)
        BlackEndL = 0;

    if (!MLEndFlag)
        BlackEndML = 0;

    if (!MEndFlag)
        BlackEndM = 0;

    if (!MREndFlag)
        BlackEndMR = 0;

    if (!REndFlag)
        BlackEndR = 0;

    if (!RREndFlag)
        BlackEndRR = 0;

    if (!RRREndFlag)
        BlackEndRRR = 0;

#endif

    EndMArray[4] = EndMArray[3];
    EndMArray[3] = EndMArray[2];
    EndMArray[2] = EndMArray[1];
    EndMArray[1] = EndMArray[0];
    EndMArray[0] = BlackEndM;

    EndMLArray[4] = EndMLArray[3];
    EndMLArray[3] = EndMLArray[2];
    EndMLArray[2] = EndMLArray[1];
    EndMLArray[1] = EndMLArray[0];
    EndMLArray[0] = BlackEndML;

    EndMRArray[4] = EndMRArray[3];
    EndMRArray[3] = EndMRArray[2];
    EndMRArray[2] = EndMRArray[1];
    EndMRArray[1] = EndMRArray[0];
    EndMRArray[0] = BlackEndMR;
    BlackEndMin = MIN(BlackEndL, BlackEndM);    //ȡ��ֵ
    BlackEndMin = MIN(BlackEndMin, BlackEndR);
}

/*
 * @brief       ��ʮ�ֽ���ʶ��ͽ������⴦��
 * @param       null
 * @return      null
 */
void NormalCrossConduct ()
{
    ///unsigned char i;
    int j = 0;
    LastLastCrossFlag = LastCrossFlag;    //��¼���ϴ��Ƿ���ʮ��
    LastCrossFlag = CrossFlag;    //��¼��һ���Ƿ���ʮ��
    CrossFlag = 0;    //����

    if ((AllLose >= 5))    //����ͬʱ����
    {
        CrossFlag = 1;    //���ʮ��

        Road_vanish = 1;    ///�ж�����·����·��ʧ��
    }
    if ((AllLose <= 1))    //���Ҳ�ͬʱ����
    {
        CrossFlag = 0;    //������ʮ��

        Road_vanish = 0;    ///�������·��·��ʧ��־

        if (CrossNumber > 3)
            LoseCrossNumber++;       //�������ʮ�ּ������е��������
    }
    if (CrossFlag && LastCrossFlag && LastLastCrossFlag)  //�������Ҷ���
    {
        CrossNumber++;                                    //ʮ�ּ���
    }
    if (LoseCrossNumber > 3)                                //�Ѿ�����Բ����
    {
        CrossEnterFlag = 1;                               //��Բ����־λ����
        CrossNumber = 0;                                  //Բ��ͳ�����

    }
    if (CrossEnterFlag && CrossNumber > 3)                  //��Բ��
    {

    }

    if (CrossFlag)
    {
        CrossKL = (float) ((LeftEdge[FirstLoseAllLine] - LeftEdge[LastLoseAllLine]))
                / (FirstLoseAllLine - LastLoseAllLine);
        CrossKR = (float) ((RightEdge[FirstLoseAllLine] - RightEdge[LastLoseAllLine]))
                / (FirstLoseAllLine - LastLoseAllLine);

        for (j = FirstLoseAllLine - 1; j > LastLoseAllLine; j--)
        {
            Pixel[j][MiddleLine[j]] = White_Point;
            MiddleLine[j] = (((int) ((j - FirstLoseAllLine) * CrossKL) + LeftEdge[FirstLoseAllLine])
                    + ((int) ((j - FirstLoseAllLine) * CrossKR) + RightEdge[FirstLoseAllLine])) / 2;
        }
    }
}

/*
 * @brief       �Ի������д���
 * @param       null
 * @return      null
 */
void CircleConduct ()
{
    static int ImgCount = 0, count = 0, LastRight = 0;
    int16 mincol = 0;
    int num1[ColumnMax];

    if ((LeftCircleFlag >= ShouldBeCircle || RightCircleFlag >= ShouldBeCircle))
        SpeedParm = SelectMode;
    if (LeftCircleFlag == ShouldBeCircle && RightCircleFlag == ShouldBeCircle)
    {
        if (LeftLose > 15)                  ///��������������15
        {
            LeftCircleFlag = MustBeCircle;
            RightCircleFlag = NoCircle;
            DrawOvalFlag = 1;
            CircleDistance = 0;
        }
        else if (RightLose > 15)
        {
            RightCircleFlag = MustBeCircle;
            LeftCircleFlag = NoCircle;
            DrawOvalFlag = 1;
            CircleDistance = 0;
        }
        else if (CircleDistance > 50)                  ///Բ���������50
        {
            LeftCircleFlag = NoCircle;
            RightCircleFlag = NoCircle;
            CircleDistance = 0;
            SpeedParm = SelectMode;
        }
    }

    /*******************��********************/
    if (LeftCircleFlag == MustBeCircle)
    {
        if (Cirlce_Angle > 45)
        {
            SpeedParm = SelectMode;
            LeftOvalFlag = 0;
            LeftCircleFlag = InCircle;
            ImgCount = count = 0;
        }
    }
    /*****************************ȷ���뻷**********************************/
    else if (LeftCircleFlag == InCircle)
    {

        if (Cirlce_Angle > 140)
        {
            ImgCount = count = 0;
            LeftCircleFlag = OutCircle;                 //���Ҷ����߳���ʮ����ʼ����
        }
    }
    /*****************************�жϳ���**********************************/
    else if (LeftCircleFlag == OutCircle)
    {
        if (Cirlce_Angle > 240)
        {
            DrawOvalFlag = 0;
            LeftCircleFlag = StopCheckCircle;   //�������
            ImgCount = count = 0;       //����Ϊ100��ͼ���ڸ��·������
        }
    }
    /********************�����ɹ�������ʱ����ɨ��־λ**************************/
    else if (LeftCircleFlag == StopCheckCircle)
    {
        if (OutCircleDistance * 2 >= CircleDistance)
        {
            OutCircleDistance = CircleDistance = 0;       ///���OutCircleDistance����û������
            ImgCount = count = 0;
            LeftCircleFlag = NoCircle;    //һ��֮��Ͳ�����
        }
    }
    /*******************               �һ�               ********************/
    /*****************************׼������***********************************/
    if (RightCircleFlag == MustBeCircle)
    {
        if (Cirlce_Angle < -45)
        {
            SpeedParm = SelectMode;
            RightCircleFlag = InCircle;
            RightOvalFlag = 0;
            ImgCount = count = 0;
        }
    }
    /*****************************ȷ���뻷**********************************/
    else if (RightCircleFlag == InCircle)
    {
        if (Cirlce_Angle < -140)
        {
            ImgCount = count = 0;
            RightCircleFlag = OutCircle;                    //���Ҷ����߳���ʮ����ʼ����
        }
    }
    /*****************************�жϳ���**********************************/
    else if (RightCircleFlag == OutCircle)
    {
        if (Cirlce_Angle < -240)
        {
            DrawOvalFlag = 0;
            RightCircleFlag = StopCheckCircle;  //�������
            ImgCount = count = 0;       //����Ϊ100��ͼ���ڸ��·������
        }
    }
    /********************�����ɹ�������ʱ����ɨ��־λ**************************/
    else if (RightCircleFlag == StopCheckCircle)
    {
        if (OutCircleDistance * 2 >= CircleDistance)
        {
            OutCircleDistance = CircleDistance = 0;
            ImgCount = count = 0;
            RightCircleFlag = NoCircle;   //һ��֮��Ͳ�����
        }
    }
    ImgCount++;

    if (ImgCount > 1500)
    {
        ImgCount = 0;
    }
}

/*
 * @brief       �����߼��
 * @param       null
 * @return      null
 */
void StartCheck()
{

}
/*
 * @brief       ���ܳ�����������
 * @param       null
 * @return      null
 */
void Image_Process ()
{

}

