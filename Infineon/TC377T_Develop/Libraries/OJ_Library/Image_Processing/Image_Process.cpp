#include "Image_Process.h"

/*
 * @brief       自制log函数
 * @param       num         需要计算的数
 * @param       bnum        底数
 * @return      null
 */
double log (double num, double bnum)
{
    return log(num) / log(bnum);
}

/*
 * @brief       灰度变换-恒等变换(s=c)
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       灰度变换-图像反转(L-1-r)
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       灰度变换-对数变换(s=clog(r+1))
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Grayscale_Logarithm (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //以s=(L-1)log(r+1),底数为L,为例(L是灰度级数)
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output,i,j) = (Gray_Max - 1) * log(Pixel(Input, i, j) + 1, Gray_Max);
        }
}

/*
 * @brief       灰度变换-幂律变换(s=cr^γ)
 * @param       Gamma       幂指数(可以理解为对比度)
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       灰度变换-直方图均衡(s=T(r)=(L-1)∫Pr(w)dw=(L-1)/MN*Σ(nj))
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Grayscale_Equalization (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //统计像素频率的数组
    uint16 Pixel_Freq[Gray_Max] = {};
    //统计各个像素频率
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Freq[Pixel(Input, i, j)]++;
        }
    //得出Σ(nj)
    for (uint16 i = 1; i < Gray_Max - 1; i++)
    {
        Pixel_Freq[i + 1] += Pixel_Freq[i];
    }
    //计算出(L-1)/MN系数
    double coefficient = (Gray_Max - 1) * 1.0 / (row * col);
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = Pixel_Freq[Pixel(Input, i, j)] * coefficient;
        }
}

/*
 * @brief       平滑线性滤波器-均值滤波器1
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Filter_Mean1 (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    double filter[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    double coefficient = 1.0 / 9;
    double Pixel_Sum;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Sum = 0;
            for (uint8 m = 0; m < 3; m++)
            {
                for (uint8 n = 0; i + m - 1 >= 0 && i + m - 1 < row && n < 3; n++)
                {
                    if (j + n - 1 >= 0 && j + n - 1 < col)
                    {
                        Pixel_Sum = Pixel_Sum + filter[m][n] * (Pixel(Input, (i + m - 1), (j + n - 1)));
                    }
                }
            }
            Pixel_Sum *= coefficient;
            Pixel(Output,i,j) = Pixel_Sum;
        }
}

/*
 * @brief       平滑线性滤波器-均值滤波器2
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Filter_Mean2 (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    double filter[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    double coefficient = 0.0625;
    double Pixel_Sum;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Sum = 0;
            for (uint8 m = 0; m < 3; m++)
            {
                for (uint8 n = 0; i + m - 1 >= 0 && i + m - 1 < row && n < 3; n++)
                {
                    if (j + n - 1 >= 0 && j + n - 1 < col)
                        Pixel_Sum += filter[m][n] * (Pixel(Input, (i + m - 1), (j + n - 1)));
                }
            }
            Pixel_Sum = Pixel_Sum * coefficient;
            Pixel(Output,i,j) = Pixel_Sum;
        }
}

/*
 * @brief       统计排序滤波器-中值滤波器(排序后取中值)
 * @param       size        方形滤波器大小
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Filter_Median (uint8 size, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //创建一个size^2大小的数组
    uint16 Arr_Max = (size * size + 1) / 2;
    uint16 count;
    uint16 tmp;
    uint8 *temp = new uint8[Arr_Max];
    //大小不能超过row和col中较小的一个
    if (size > row || size > col)
    {
        Grayscale_Identity(Input, Output, row, col);
    }
    //开始排序筛选
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            count = 0;
            for (int16 m = -size / 2; m <= size / 2; m++)
            {
                for (int16 n = -size / 2; i + m >= 0 && i + m < row && n <= size / 2; n++)
                {
                    if (j + n >= 0 && j + n < col)
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
            //筛选出灰度值
            Pixel(Output, i, j) = temp[(count - 1) / 2];
        }
//释放内存
    delete[] temp;
}

