#include "Image_Process.h"
uint8 Histogram[IPS114_H][IPS114_W];
/*
 * @brief       自制log函数
 * @param       num         需要计算的数
 * @param       bnum        底数
 * @return      结果
 */
double log (double num, double bnum)
{
    return log(num) / log(bnum);
}

/*
 * @brief       类高斯曲线函数，用于计算差值隶属度
 * @param       gray_Delta
 * @return      函数返回值，即y值
 */
double membership (int16 gray_Delta)
{
    return exp(-pow(gray_Delta / 16.0, 2));
}

/*
 * @brief       图像分割-Otsu最佳全局阈值处理的智能车优化版本获取阈值
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
uint8 DIP::Global_Otsu_Better_threshold (uint8 *Input, uint16 row, uint16 col)
{
    //图像的直方图数组
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    //缓存最佳阈值k，像素总数，像素值总值，P1(ΣPi)，Q1(ΣiPi)，全局平均灰度，最大值累计
    uint8 cnt = 0;
    uint16 k;
    uint16 Pixel_Sum = (row * col) / 4;
    uint32 Gray_Sum = 0;
    float P1 = 0, Q1 = 0, mg;
    //缓存σ即类间方差
    float variance = 0, temp;
    //优化一：间隔一行一列取像素，手动缩小图像像素数量
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
            Pixel(Output,i,j) = Gray_Max * log(Pixel(Input, i, j) + 1, Gray_Max + 1);
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
    double c = pow(Gray_Max, 1 - Gamma);
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
    uint16 Pixel_Freq[Gray_Max + 1] = {};
    //统计各个像素频率
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel_Freq[Pixel(Input, i, j)]++;
        }
    //得出Σ(nj)
    for (uint8 i = 0; i < Gray_Max; i++)
    {
        Pixel_Freq[i + 1] += Pixel_Freq[i];
    }
    //计算出(L-1)/MN系数
    float coefficient = Gray_Max * 1.0 / (row * col);
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = Pixel_Freq[Pixel(Input, i, j)] * coefficient;
        }
}

/*
 * @brief       灰度变换-二值化
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       平滑线性滤波器-均值滤波器1
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       平滑线性滤波器-高斯滤波器
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Filter_Gaussian (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    uint8 filter[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}}; //(这实际上是个高斯平滑滤波器模板)
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
            //筛选出灰度值
            Pixel(Output, i, j) = temp[(count - 1) / 2];
        }
//释放内存
    delete[] temp;
}

/*
 * @brief       锐化空间滤波器-拉普拉斯算子
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       锐化空间滤波器-非锐化掩蔽和高提升滤波
 * @param       Origin      原始图像
 * @param       Blur        模糊图像(建议使用高斯模糊)
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       锐化空间滤波器-Sobel算子
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 **该方法输出的图像为Sobel图像，即梯度图像，突出了边缘部分
 */
void DIP::Fliter_Sobel (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //下面只是近似算子的一种，也可以采用3,10,3的组合, 效果会更加明显
    //x方向上微分的离散近似算子
    int8 Fliter_gx[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //y方向上微分的离散近似算子
    int8 Fliter_gy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //微分gx和gy的缓存
    int16 gx_tmp, gy_tmp;
    //单个像素缓存
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
 * @brief       模糊集合-灰度变换
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 **定义了如下规则：
 **1.如果该像素是暗的，则使它为黑。
 **2.如果该像素是灰的，则使它为灰。
 **3.如果该像素是亮的，则使它为白。
 */
void DIP::Fuzzy_GrayValue (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //输出的隶属度函数
    uint8 u_dark_out = 0, u_gray_out = 127, u_bright_out = 255;
    //输入的隶属度函数
    float u_dark, u_gray, u_bright;
    //缓存值
    uint8 temp;
    //输出值
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
 * @brief       模糊集合-边缘增强
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 **定义了如下规则：
 **IF d2是0  AND d6是0 THEN z5是白色
 **IF d6是0  AND d8是0 THEN z5是白色
 **IF d8是0  AND d4是0 THEN z5是白色
 **IF d4是0  AND d2是0 THEN z5是白色
 **ELSE z5是黑色
 **| z1 | z2 | z3 |
 **| z4 | z5 | z6 |
 **| z7 | z8 | z9 |
 **     原图像
 **| d1 | d2 | d3 |
 **| d4 | d5 | d6 |
 **| d7 | d8 | d9 |
 **      差值
 **dx = z5 - zx,其中d5 = 0。
 */
void DIP::Fuzzy_EdgeEnhance (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //dx(条件)的输出隶属度
    float *d = new float[4];
    //dx次大的
    float d_max_output;
    //黑白(输出值)的输出隶属度
    float bl_output, wh_output;
    //缓存值
    float temp;
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            d_max_output = d[0] = d[1] = d[2] = d[3] = 0;
            //d2的计算
            if (i - 1 >= 0)
            {
                d[0] = membership(Pixel(Input,i,j) - Pixel(Input, (i - 1), j));
            }
            //d6的计算
            if (j + 1 < col)
            {
                d[1] = membership(Pixel(Input,i,j) - Pixel(Input, i, (j + 1)));
            }
            //d8的计算
            if (i + 1 < row)
            {
                d[2] = membership(Pixel(Input,i,j) - Pixel(Input, (i + 1), j));
            }
            //d4的计算
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
            //分两种情况
            if (bl_output < 1.0 / 3)
            {
                //z字第一部分
                temp = (191.25 * bl_output + 63.75) / 2;
                //z字第二部分
                temp += (255 - 191.25 * wh_output + 63.75) / 2;
                //z字第三部分
                temp += 106.25;
            }
            else
            {
                //v字第一部分
                temp = (191.25 * bl_output + 63.75) / 2;
                //v字第二部分
                temp += (255 - 191.25 * wh_output + 63.75) / 2;
                //v字第三部分
                temp += 116.875 + 63.75 * wh_output;
            }
            Pixel(Output,i,j) = temp > 255 ? 255 : temp < 0 ? 0 : (uint8) temp;
        }
}

/*
 * @brief       图像分割-孤立点的检测
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Segmentation_Point (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //拉普拉斯算子
    int8 Filter[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    //阈值
    float Point_Max = 0.9 * Gray_Max;
    //缓存值
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
 * @brief       图像分割-线的检测
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Segmentation_Line (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //拉普拉斯算子
    int8 Filter[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}};
    //缓存值
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
 * @brief       图像分割-基本全局阈值处理(迭代法)
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Global_threshold (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
////  第一种算法
//    //用于缓存求和和计算均值
//    uint32 *sum1 = new uint32;
//    uint32 *sum2 = new uint32;
//    uint16 *cnt1 = new uint16;
//    uint16 *cnt2 = new uint16;
//    //缓存T和ΔT
//    uint8 T1, T2, T = 1;
//    //设置T的初始值为平均灰度
//    *sum1 = 0;
//    for (uint16 i = 0; i < row; i++)
//        for (uint16 j = 0; j < col; j++)
//        {
//            (*sum1) += Pixel(Input, i, j);
//        }
//    T1 = 0;
//    T2 = (*sum1) / (row * col);
//    //迭代运算,T1用于存储上一次的阈值T,T2用于存储计算得到的阈值，最终得到我们想要的阈值
//    while (T1 - T2 > T || T2 - T1 > T)
//    {
//        T1 = T2;
//        *sum1 = *sum2 = 0;
//        *cnt1 = *cnt2 = 0;
//        for (uint16 i = 0; i < row; i++)
//            for (uint16 j = 0; j < col; j++)
//            {
//                //计算第一部分的灰度总和
//                if (Pixel(Input,i,j) <= T1)
//                {
//                    (*sum1) += Pixel(Input, i, j);
//                    (*cnt1)++;
//                }
//                //计算第二部分的灰度总和
//                else
//                {
//                    (*sum2) += Pixel(Input, i, j);
//                    (*cnt2)++;
//                }
//            }
//        //得到新值T
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

//  第二种算法(采用平均灰度m=Σip(i)/MN计算)
    //用于存放直方图的向上积分形式(Σp(i))
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    //用于存放Σip(i)
    uint32 *sum = new uint32[Gray_Max + 1]{};
    //缓存T和ΔT
    uint8 T1, T2, T = 1, m1, m2;
    //初始化上面两个数组
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
    //计算平均灰度
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
    //二值化
    Grayscale_Binarization(Input, Output, T2, row, col);
    delete[] histogram;
    delete[] sum;
}

/*
 * @brief       图像分割-Otsu最佳全局阈值处理
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Global_Otsu (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //图像的直方图积分形式和像素值的积分形式数组
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    uint32 *m = new uint32[Gray_Max + 1]{};
    //缓存全局平均灰度，以及最佳阈值k，和最佳阈值个数，其中全局平均灰度一定要浮点型(会影响后面的结果)
    float mg;
    uint16 cnt;
    uint32 k;
    //缓存σ即类间方差
    float variance, temp;
    //初始化两个数组
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
    //初始化k,mg,cnt,variance
    k = 0;
    cnt = 1;
    //mg这里最好用float型，差别很大
    mg = (float) m[Gray_Max] / histogram[Gray_Max];
    variance = 0;
    //使用公式(mgT1-Q1)^2/T1(MN-T1),其中循环变量i不能取到最大值255，否则分母为0
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
    //最大阈值取平均
    k /= cnt;
    //二值化
    Grayscale_Binarization(Input, Output, k, row, col);
    delete[] histogram;
    delete[] m;
}

/*
 * @brief       图像分割-Otsu最佳全局阈值处理的智能车优化版本
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Global_Otsu_Better (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    uint8 k = Global_Otsu_Better_threshold(Input, row, col);
    //二值化
    Grayscale_Binarization(Input, Output, k, row, col);
}

/*
 * @brief       Sobel算子+Otsu识别赛道
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Sobel_Recognizer (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{
    //下面只是近似算子的一种，也可以采用3,10,3的组合, 效果会更加明显
    //x方向上微分的离散近似算子
    int8 Fliter_gx[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    //y方向上微分的离散近似算子
    int8 Fliter_gy[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    //微分gx和gy的缓存
    int16 gx_tmp, gy_tmp;
    //单个像素缓存
    int16 temp;
    //可优化可不优化
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
 * @brief       获取直方图图像
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       Input_row   输入图像行数
 * @param       Input_col   输入图像列数
 * @param       Output_row  输入图像行数
 * @param       Output_col  输入图像列数
 * @return      null
 */
void DIP::Get_Histogram (uint8 *Input, uint8 *Output, uint16 Input_row, uint16 Input_col, uint16 Output_row,
        uint16 Output_col)
{
    //图像的直方图数组
    uint16 *histogram = new uint16[Gray_Max + 1]{};
    uint16 &row = Input_row;
    uint16 &col = Input_col;
    //通过Otsu获取的阈值
    uint8 k = Global_Otsu_Better_threshold(Input, row, col);
    //记录最大值，用于标定
    uint16 Pixel_Max = 0;
    //横向坐标，绘制个数
    uint16 hposition;
    uint16 num;
    //初始化数组和输出图像
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            histogram[Pixel(Input, i, j)]++;
        }
    row = Output_row;
    col = Output_col;
    //清空Output
    for (uint16 i = 0; i < row; i++)
        for (uint16 j = 0; j < col; j++)
        {
            Pixel(Output, i, j) = 0;
        }
    //统计最大值
    for (uint16 i = 0; i <= Gray_Max; i++)
    {
        Pixel_Max = Pixel_Max < histogram[i] ? histogram[i] : Pixel_Max;
    }
    //绘制图形
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
 * @brief       智能车赛道处理
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void DIP::Car_Img_Process (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
{

}

/*
 * @brief       记录计算帧率所用到的开始时间
 * @param       null
 * @return      null
 */
void DIP::FPS_Start ()
{
    start = platform_getval_ms();
}

/*
 * @brief       记录计算帧率所用到的结束时间
 * @param       null
 * @return      null
 */
void DIP::FPS_End ()
{
    end = platform_getval_ms();
}

/*
 * @brief       输出帧率到串口
 * @param       null
 * @return      null
 */
void DIP::Show_FPS ()
{
    platform_printf("Present Fps = %d\n", end - start ? 1000 / (end - start) : 0);
}
