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

//基本的灰度变换函数
//灰度变换-恒等变换(s=c)
//灰度变换-图像反转(L-1-r)
//灰度变换-对数变换(s=clog(r+1))
//灰度变换-幂律变换(s=cr^γ)
//灰度变换-直方图均衡(s=T(r)=(L-1)∫Pr(w)dw=(L-1)/MN*Σ(nj))
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
            Pixel(Output,i,j) = (Gray_Max - 1) * log(Pixel(Input,i,j) + 1, Gray_Max);
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

