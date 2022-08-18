#include "Image_Process.h"

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
 * @brief       图像分割-Otsu最佳全局阈值处理
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
uint8 Global_Otsu_threshold (uint8 *Input, uint16 row, uint16 col)
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
    delete[] histogram;
    delete[] m;
    //最大阈值取平均
    k /= cnt;
    return k;
}

/*
 * @brief       图像分割-Otsu最佳全局阈值处理的智能车优化版本获取阈值
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
uint8 Global_Otsu_Better_threshold (uint8 *Input, uint16 row, uint16 col)
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
void Grayscale_Identity (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Reverse (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Logarithm (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
 * @brief       灰度变换-直方图均衡(s=T(r)=(L-1)∫Pr(w)dw=(L-1)/MN*Σ(nj))
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void Grayscale_Equalization (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Grayscale_Binarization (uint8 *Input, uint8 *Output, uint8 threshold, uint16 row, uint16 col)
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
 * @brief       平滑线性滤波器-高斯滤波器
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 */
void Filter_Gaussian (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Filter_Median (uint8 size, uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
 * @brief       锐化空间滤波器-非锐化掩蔽和高提升滤波
 * @param       Origin      原始图像
 * @param       Blur        模糊图像(建议使用高斯模糊)
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
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
 * @brief       锐化空间滤波器-Sobel算子
 * @param       Input       输入图像
 * @param       Output      输出图像
 * @param       row         图像行数
 * @param       col         图像列数
 * @return      null
 **该方法输出的图像为Sobel图像，即梯度图像，突出了边缘部分
 */
void Fliter_Sobel (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fuzzy_GrayValue (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Fuzzy_EdgeEnhance (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Segmentation_Point (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Segmentation_Line (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_threshold (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_Otsu (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Global_Otsu_Better (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Sobel_Recognizer (uint8 *Input, uint8 *Output, uint16 row, uint16 col)
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
void Get_Histogram (uint8 *Input, uint8 *Output, uint16 Input_row, uint16 Input_col, uint16 Output_row,
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
 * @brief       记录计算帧率所用到的开始时间
 * @param       null
 * @return      null
 */
void FPS_Start ()
{
    start = platform_getval_ms();
}

/*
 * @brief       记录计算帧率所用到的结束时间
 * @param       null
 * @return      null
 */
void FPS_End ()
{
    end = platform_getval_ms();
}

/*
 * @brief       输出帧率到串口
 * @param       null
 * @return      null
 */
void Show_FPS ()
{
    platform_printf("Present Fps = %d\n", end - start ? 1000 / (end - start) : 0);
}

/*
 * @brief       获取处理图像
 * @param       null
 * @return      null
 */
void Get_Use_Image ()
{
    for (int i = 0, row = 0; i < IMAGEH; row++, i += 2)  //120行，每2行采集一行，///只取原图像的1/2
    {
        for (int j = 0, col = 0; j < IMAGEW; col++, j += 2) //188，
        {
            Image_Use[row][col] = mt9v03x_image[i][j];
        }
    }
}

/*
 * @brief       自加
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
 * @brief       岔路处理函数
 * @param       null
 * @return      null
 */
void SpurroadConduct ()
{
    int j = 0, k = 0;
    int L1, L2, R1, R2;
    LastLastSpurroadFlag = LastSpurroadFlag; //记录上上次是否是十字
    LastSpurroadFlag = SpurroadFlag; //记录上一次是否是十字
    //SpurroadFlag=0;//清零

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
 * @brief       中心偏差滤波
 * @param       null
 * @return      null
 */
void Zebra_Filter ()
{
    int16 ZebraFilterLoc[StartLine + 2][40];    //没有那么多跳变点      ///57*40的数组
    int16 i = 0, j = 0, k = 0, num = 1;
    for (i = StartLine + 1; i >= FinishLine - 1; i--) ///58到18
    {
        for (j = 25; j < ColumnMax - 25 - 1; j++) ///25到67
        {
            if (CheckWhitePixle(i, j)) ///如果是白点
                ZebraFilterLoc[i][num++] = j; //第二位开始存单行跳变点位置///将j记录到该点对应坐标数组里
        }
        for (k = num; k < 40; k++)
            ZebraFilterLoc[i][k] = 0; ///如果白点的数量大于40，不执行这条语句，否则num前面到40全清零
        ZebraFilterLoc[i][0] = num - 1;     //第一位存跳变点数量
        num = 1;
    }
    for (i = StartLine + 1; i >= FinishLine - 1; i--) ///58到18
    {
        for (j = 1; j <= ZebraFilterLoc[i][0]; j++) ///1到白点总数
        {
            if (ZebraFilterLoc[i][ZebraFilterLoc[i][0]] != 0 &&                         //如果最后一个点是0一定就是没找到跳变点
                    ABS(ZebraFilterLoc[i][ZebraFilterLoc[i][0]]-ZebraFilterLoc[i][1]) < 30) ///最后一个点不等于0且与第一个的差值小于30则
            {
                for (k = ZebraFilterLoc[i][1]; k <= ZebraFilterLoc[i][ZebraFilterLoc[i][0]]; k++) ///从第一个到最后白点
                {
                    Image_Sobel[i][k] = 0;
                }
            }
        }
    }
}

/*
 * @brief       斑马线滤波
 * @param       middle_err 中线误差
 * @return      null
 */
float Middle_Err_Filter (float middle_err)
{
    float Middle_Err_Fltered;
    Middle_Err_Fltered = middle_err * 0.8 + LastAverageCenter * 0.2; ///这次取0.8和上次的0.2求和
    return Middle_Err_Fltered;
}

/*
 * @brief       路径判断
 * @param       null
 * @return      null
 */
void TrackJudge ()
{
    //使用最远行偏差和加权偏差确定前瞻
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
    //弯道入直道
    if (LastAverageError[0] > 7 && LastAverageError[1] > 6 && LastAverageError[2] > 5 && LastAverageError[4] < 4
            && BlackEndM > 30 && ABS(Fictitious_Num) < 30)
    {
        Track_Type = CurveToStraight;
    }
    //直道
    else if (LastAverageError[0] < 4 && LastAverageError[1] < 4 && LastAverageError[2] < 4 && Foresight <= 5)
    {
        Track_Type = InStraight;
    }
    //直道入弯道
    else if (LastAverageError[0] < 6 && LastAverageError[1] < 6 && LastAverageError[2] < 6 && Foresight >= 5)
    {
        Track_Type = StraightToCurve;
    }
    //弯道中
    else
    {
        Track_Type = InCurve;
    }
}

/*
 * @brief       全行扫描和边缘结合提取赛道的中线
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
    //全局变量清零
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
    //复位补线起始行坐标
    Left_Add_Start = 0;
    Right_Add_Start = 0;
    Left_Add_Stop = 0;
    Right_Add_Stop = 0;
    //复位第60行数据
    MiddleLine[RowMax - 1] = ColumnMax / 2; ///47
    LeftEdge[RowMax - 1] = 0;
    RightEdge[RowMax - 1] = ColumnMax; ///94

    OnlyOnce(); ///自加

    /*************************************************************************************/
    /*                           一次遍历开始（全行+边缘）                                                          */
    /*************************************************************************************/
    for (i = StartLine; i > DivideLine; i--) ///57到47                //首先找前N行，全行扫描
    {

        //左右边界都从中线位置往一侧找
        /***********************************先找左边界********************************************/
        if (i == StartLine)
            j = MiddleLine[RowMax]; //首行就以上一场图像首行作为扫描起点///如果i=StartLine时，MiddleLine[RowMax]无有效数据，可能需要debug
        else if (AllLose > 5)
            j = ColumnMax / 2;
        else
            j = MiddleLine[i + 1]; //否则就以上一行中点的位置作为本行扫描起点
        if (j < 3)
            j = 3; //j>=3有效范围内搜线
        while (j >= 3) //j>=3有效范围内进行搜寻
        {
            //从右向左找到白黑黑跳变
            if (CheckLeft(i, j))
            {
                LeftEdge[i] = j;                        //找到则赋值 找不到保持原值0
                break;                        //跳出本行寻线
            }
            j--;                                        //列数往左移动
        }
        if (j < 3)
            LeftEdge[i] = 1;                                 //找不到左边线就令其为1
        /***********************************再找右边界********************************************/
        if (i == StartLine)
            j = MiddleLine[RowMax]; //首行就以上一场图像首行作为扫描起点
        else if (AllLose > 5)
            j = ColumnMax / 2;
        else
            j = MiddleLine[i + 1]; //否则从上一行中心位置开始搜寻
        if (j > ColumnMax - 3)
            j = ColumnMax - 3; //j <=ColumnMax-3有效范围内搜线
        while (j <= ColumnMax - 3)
        {
            //从左向右找到白黑黑跳变点
            if (CheckRight(i, j))
            {
                RightEdge[i] = j;                   //找到则赋值   找不到保持原值
                break;                   //跳出本行寻线
            }
            j++;                                        //列数往右移动
        }
        if (j >= ColumnMax - 3)
            RightEdge[i] = ColumnMax - 1;                 //找不到右边线就令其为ColumnMax-1

        /************************************滤波********************************************/
        if (LeftEdge[i] == 1 && LeftEdge[i + 1] == 1 && LeftEdge[i + 2] == 1 && LeftEdge[i + 3] == 1
                && LeftEdge[i + 4] == 1)
        ///一直找不到左边线
        {
            LeftFilterStart = i;                 ///LeftFilterStart记为i左边界滤波开始行
        }
        if (RightEdge[i] == ColumnMax - 1 && RightEdge[i + 1] == ColumnMax - 1 && RightEdge[i + 2] == ColumnMax - 1
                && RightEdge[i + 3] == ColumnMax - 1 && RightEdge[i + 4] == ColumnMax - 1)
        ///一直找不到右边线
        {
            RightFilterStart = i;
        }
        /************************************丢线判断********************************************/
        Left_Add_Line[i] = LeftEdge[i];                     //记录实际左边界为补线左边界
        Right_Add_Line[i] = RightEdge[i];                     //记录实际右边界为补线左边界
        if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 2) && i < StartLine)           //不满足畸变
        ///((RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+2) && i<StartLine)
        {
            Left_Add_Flag[i] = 1;                ///这一行左补线标志置1
            Right_Add_Flag[i] = 1;
            AllLose++;                ///这行不满足畸变用来判断十字
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];                //用上一行
        }
        else if ((LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //全丢
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
        else if (LeftEdge[i] != 1 && RightEdge[i] != ColumnMax - 1)    //没有丢线
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 0;
            MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;    ///中线记为两边线中点
            if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 1) && i < StartLine)    //不满足畸变
                MiddleLine[i] = MiddleLine[i + 1];    //用上一行
        }
        else if (LeftEdge[i] == 1 && RightEdge[i] != ColumnMax - 1)    //丢了左线
        {
            if (!LeftLoseStart)
                LeftLoseStart = i;    ///记录左边丢线的开始行
            Left_Add_Flag[i] = 1;    ///这一行左补线标志置1
            Right_Add_Flag[i] = 0;    ///这一行右补线标志置0
            if (i <= RowMax - 1 && RightEdge[i] > Width[i] / 2 + 1)    //正常的话就用半宽补///右边界大于每行道路边界的一半视为正常。
            ///个人觉得右边界也应该小于width[i]///当左边界丢失时，右边界不可能大于width[i]。
                MiddleLine[i] = RightEdge[i] - Width[i] / 2;
            else
                //越界则以左界代替
                MiddleLine[i] = 1;            ///中线定为1意为需要疯狂向左转了
            LeftLose++;       ///仅左丢线行数
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] == ColumnMax - 1)    //丢了右线
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 1;
            if (!RightLoseStart)
                RightLoseStart = i;
            if (i <= RowMax - 1 && LeftEdge[i] + Width[i] / 2 < ColumnMax - 1)      //正常的话就用半宽补
                MiddleLine[i] = LeftEdge[i] + Width[i] / 2;
            else
                //越界则以右界代替
                MiddleLine[i] = ColumnMax - 1;
            BlackEndM++;      //记录只有右线丢的数量///按对称来说应为下面这行代码
            RightLose++;      ///仅右丢线行数
        }
        else if ((LeftEdge[i] == 1 && RightEdge[i] == ColumnMax - 1)) //全丢
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            LastLoseAllLine = i; ///全丢结束行会随着i的减少而变化到结束行。
            left_right_lost_i = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        if (Left_Add_Flag[i])                                                        //左边界需要补线
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                                                    //前6行
                Left_Add_Line[i] = LeftEdge[StartLine - 1];                                                    //使用底行数据
            else if (i < StartLine - 6)                                                    //剩下的
                Left_Add_Line[i] = Left_Add_Line[i + 1];                                               //使用前1行左边界作为本行左边界
        }
        if (Right_Add_Flag[i])                                                       //右边界需要补线
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                                                    //前6行
                Right_Add_Line[i] = RightEdge[StartLine - 1];                                                   //使用底行数据
            else if (i < StartLine - 6)                                                    //剩下的
                Right_Add_Line[i] = Right_Add_Line[i + 1];                                             //使用前1行右边界作为本行右边界
        }
        if (RightEdge[i] > LeftEdge[i])
            RealWidth[i] = RightEdge[i] - LeftEdge[i];  //计算实际赛道宽度
        else
            RealWidth[i] = 0;
        if (Right_Add_Line[i] > Left_Add_Line[i])  //计算补线赛道宽度
            Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i];
        else
            Width_Add[i] = 0;

        if (!RRSalationLine && i < StartLine - 5
                &&  ///正常情况下RightEdge[i]始终是最小的，如果不是只能说明不满足畸变，遇到了跳变点。目前来看只运行一次。
                RightEdge[i] == MIN(MIN(RightEdge[i + 4], RightEdge[i + 3]), RightEdge[i + 2])
                && RightEdge[i] == MIN(MIN(RightEdge[i], RightEdge[i + 1]), RightEdge[i + 2]))
        {
            RRSalationLine = i + 2;                                    ///右边线右跳变起始行
        }
        else if (!LLSalationLine && i < StartLine - 5
                && LeftEdge[i] == MAX(MAX(LeftEdge[i + 4], LeftEdge[i + 3]), LeftEdge[i + 2])
                && LeftEdge[i] == MAX(MAX(LeftEdge[i + 2], LeftEdge[i + 1]), LeftEdge[i]))
        {
            LLSalationLine = i + 2;
        }
        /*******************************起始行数据处理**************************************/
        if (i == StartLine)                                    ///只有在起始行运行
        {
            LeftEdge[RowMax] = LeftEdge[StartLine];     ///数据保存到60行对应的列
            RightEdge[RowMax] = RightEdge[StartLine];
            Left_Add_Line[RowMax] = Left_Add_Line[StartLine];
            Right_Add_Line[RowMax] = Right_Add_Line[StartLine];
            Left_Add_Line[StartLine + 1] = Left_Add_Line[StartLine];
            Right_Add_Line[StartLine + 1] = Right_Add_Line[StartLine];

            if (Left_Add_Flag[StartLine] && Right_Add_Flag[StartLine])     ///开始行左右需要补线
            {
                MiddleLine[StartLine] = MiddleLine[RowMax];     ///用60行的中线代替开始行
                FirstLoseAllLine = 0;     ///全丢白开始行清零
            }
            else
            {
                MiddleLine[RowMax] = MiddleLine[StartLine]; // 更新第60行虚拟中点，便于下一帧图像使用
            }

            MiddleLine[RowMax] = RANGE16(MiddleLine[RowMax], 15, 80); ///中线限幅到15至80之间

            RealWidth[RowMax] = RealWidth[StartLine];

            Width_Add[RowMax] = Width_Add[StartLine];

            Width_Add[StartLine + 1] = Width_Add[StartLine];

            Width_Min = Width_Add[StartLine]; //Width_Min其实是第一行赛道宽度也就是
            //没有进行梯形矫正图像的赛道最长宽度
        }
    }
    /*——————————————————分割线————————————————————*/
    for (i = DivideLine; i >= FinishLine; i -= StepLine)                //查找剩余行///47到18
    {
        LastLine = i;                ///扫描最后一行
        /*******************************判断左右边界反常延伸*************************************/
        if ((!SearchErrorFlag) && ((LeftEdge[i + 1] >= ColumnMax / 2 + 5) || (RightEdge[i + 1] <= ColumnMax / 2 - 5)))
        {
            ///ColumnMax/2+5=52,ColumnMax/2-5=42///左边界或右边界异常
            if (LeftEdge[i + 1] >= ColumnMax / 2 + 10 || RightEdge[i + 1] <= ColumnMax / 2 - 10)     ///左边界大于57或者右边界小于37
            {
                SearchErrorFlag = i + 2;                ///记录异常行，之后退出循环。
                break;
            }
            else if (LeftEdge[i + 1] >= ColumnMax / 2 + 5)                ///52
            {
                if (RightEdge[i + 1] == ColumnMax - 1)                ///93///未找到右边界
                {
                    FinishColumn = ColumnMax - 1;
                    while (FinishColumn >= LeftEdge[i + 1])                ///从右向左找左边界
                    {
                        if (CheckLeft(i, FinishColumn))
                        {
                            LeftEdge[i] = FinishColumn;                ///找到就记录下来
                            break;
                        }
                        FinishColumn--;
                    }
                    if (FinishColumn < LeftEdge[i + 1])                ///否则就用上一行的左边界
                        LeftEdge[i] = LeftEdge[i + 1];
                }
                else
                {
                    LeftEdge[i] = LeftEdge[i + 1];                ///找到右边界，左边界用上一行的
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
        /***************************上一行没找到边界，全部全行扫描*******************************/
        if ((LeftEdge[i + 1] == 1 && RightEdge[i + 1] == ColumnMax - 1) || LeftLose > 5 || RightLose > 5 || AllLose > 5)
        {
            ////////////////////////先通过全行扫描找左边界///////////////////////////
            if (AllLose > 5)
                FinishColumn = MiddleLine[RowMax];                ///如果全丢用60里的数据
            else
                FinishColumn = MiddleLine[i + 1];                ///否则用上一行的数据
            if (FinishColumn <= 2)
            {
                FinishColumn = 3;
            }
            while (FinishColumn >= 3)
            {
                if (CheckLeft(i, FinishColumn))
                {
                    LeftEdge[i] = FinishColumn;                ///找得到保存数据
                    break;
                }
                FinishColumn--;
                if (FinishColumn < 3)
                    LeftEdge[i] = 1;                ///否则用最左边
            }
            ////////////////////////再通过全行扫描找右边界///////////////////////////
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

#if 0//我自己屏蔽的这一部分

        /***************************上一行两边都找到 全部边沿扫描*******************************/
        else if(LeftEdge[i+1]!=1 && RightEdge[i+1]!=ColumnMax-1)
        {
            //////////////////////////////先找左边界///////////////////////////////////
            FinishColumn = ((LeftEdge[i+1]+10) >= ColumnMax-3)? ColumnMax-3:(LeftEdge[i+1]+10);///比ColumnMax-3大用ColumnMax-3
            StartColumn = ((LeftEdge[i+1]-5) <= 3)? 3:(LeftEdge[i+1]-5);///比3小用3
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
            //////////////////////////////再找右边界///////////////////////////////////
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
        /***************************上一行只找到左边界 边沿+全行扫描*******************************/
        else if(LeftEdge[i+1]!=1 && RightEdge[i+1]==ColumnMax-1)
        {
            ////////////////////////先通过边沿扫描找左边界///////////////////////////
            FinishColumn = ((LeftEdge[i+1]+10) >=ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);///比ColumnMax-2大用ColumnMax-2
            StartColumn = ((LeftEdge[i+1]-5) <= 1)? 1:(LeftEdge[i+1]-5);///比1小用1
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
            ////////////////////////再通过全行扫描找右边界///////////////////////////
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
        /***************************上一行只找到右边界 边沿+全行扫描*******************************/
        else if(LeftEdge[i+1]==1 && RightEdge[i+1]!=ColumnMax-1)
        {
            ////////////////////////先通过边沿扫描找右边界//////////////////////////
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
            ////////////////////////再通过全行扫描找左边界///////////////////////////
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

        /************************************丢线判断********************************************/
        Left_Add_Line[i] = LeftEdge[i];                     //记录实际左边界为补线左边界
        Right_Add_Line[i] = RightEdge[i];                     //记录实际右边界为补线左边界
        if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i + 1] - LeftEdge[i + 1] + 3) ///(RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+3
        && i < StartLine)                     //不满足畸变
        {
            if (LeftLose > 10 || RightLose > 10 || AllLose > 10)                   ///不满足畸变且全丢线大于10
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
            MiddleLine[i] = MiddleLine[i + 1];                   //用上一行
        }
        else if ((LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //全丢
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
        else if (LeftEdge[i] != 1 && RightEdge[i] != ColumnMax - 1)    //没有丢线
        {
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 0;
            MiddleLine[i] = (LeftEdge[i] + RightEdge[i]) / 2;
        }
        else if (LeftEdge[i] == 1 && RightEdge[i] != ColumnMax - 1)    //丢了左线
        {
            if (!LeftLoseStart)
                LeftLoseStart = i;
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 0;
            if (i <= RowMax - 1 && RightEdge[i] > Width[i] / 2 + 1)    //正常的话就用半宽补
                MiddleLine[i] = RightEdge[i] - Width[i] / 2;
            else
                //越界则以左界代替
                MiddleLine[i] = 1;
            LeftLose++;
        }
        else if (LeftEdge[i] != 1 && RightEdge[i] == ColumnMax - 1)    //丢了右线
        {
            if (!RightLoseStart)
                RightLoseStart = i;
            Left_Add_Flag[i] = 0;
            Right_Add_Flag[i] = 1;
            if (i <= RowMax - 1 && LeftEdge[i] + Width[i] / 2 < ColumnMax - 1)      //正常的话就用半宽补
                MiddleLine[i] = LeftEdge[i] + Width[i] / 2;
            else
                //越界则以右界代替
                MiddleLine[i] = ColumnMax - 1;
            RightLose++;      //记录只有右线丢的数量
        }
        else if ((LeftEdge[i] == 1 && RightEdge[i] == ColumnMax - 1)
                || (LLSalationLine && RightEdge[i] == ColumnMax - 1) || (RRSalationLine && LeftEdge[i] == 1))     //全丢
        {
            Left_Add_Flag[i] = 1;
            Right_Add_Flag[i] = 1;
            AllLose++;
            if (AllLose >= 2 || AllLose <= 5)
                FirstLoseAllLine = i;
            MiddleLine[i] = MiddleLine[i + 1];
        }
        if (Left_Add_Flag[i])                                                    //左边界需要补线
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                            //前6行使用底行数据
                Left_Add_Line[i] = LeftEdge[StartLine - 1];
            else if (i < StartLine - 6)                            //后6行使用前1行左边界作为本行左边界
                Left_Add_Line[i] = Left_Add_Line[i + 1];
        }
        if (Right_Add_Flag[i])                                                   //右边界需要补线
        {
            if (i >= StartLine - 6 && i < StartLine - 1)                            //前6行使用底行数据
                Right_Add_Line[i] = RightEdge[StartLine - 1];
            else if (i < StartLine - 6)                            //后6行使用前1行左边界作为本行左边界
                Right_Add_Line[i] = Right_Add_Line[i + 1];
        }
        if (RightEdge[i] > LeftEdge[i])
            RealWidth[i] = RightEdge[i] - LeftEdge[i];  //计算实际赛道宽度
        else
            RealWidth[i] = 0;  //若越界则直接置0
        if (Right_Add_Line[i] > Left_Add_Line[i])  //计算补线赛道宽度
            Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i];
        else
            Width_Add[i] = 0;

        SearchErrorFlag = 0;
    }
    /*************************************************************************************/
    /*                              一次遍历结束                                         */
    /*************************************************************************************/
    /*************************************************************************************/
    /*                      二次遍历开始（进行补线+动态前瞻）                             */
    /*************************************************************************************/
    // for(i=StartLine; i>LastLine; i-=StepLine) ///从57到0
    // {
    //     /********************************* 补线检测开始 *************************************/
    //     if (RealWidth[i] > Width_Min+1)  // 赛道宽度变宽，可能是十字或环路，///或则是三岔路
    //     {
    //         //Width_Min其实是第一行赛道宽度也就是
    //         //没有进行梯形矫正图像的赛道最长宽度
    //         Road_widening = 1;///道路变宽标志，用于判断三岔路
    //         if (Left_Add_Line[i] < Left_Add_Line[i+2] &&
    //                 Left_Add_Line[i+2] < Left_Add_Line[i+4] && i<StartLine)  //正常的是赛道远处宽度窄即Left_Add_Line[i]比较近处的大
    //         {
    //             if (!Left_Add_Flag[i])
    //                 Left_Add_Flag[i] = 1;    //上面误判为0则强制认定为需要补线
    //         }
    //         if (Right_Add_Line[i] > Right_Add_Line[i+2] &&
    //                 Right_Add_Line[i+2] > Right_Add_Line[i+4] &&i<StartLine)     //与上面相反
    //         {
    //             if (!Right_Add_Flag[i])
    //                 Right_Add_Flag[i] = 1;   //上面误判为0则强制认定为需要补线
    //         }
    //         if ((Left_Add_Flag[i] || Right_Add_Flag[i] || SearchErrorFlag == i) && (i<FinishLine+10))///(Left_Add_Flag[i] || Right_Add_Flag[i] || SearchErrorFlag == i && i<FinishLine+10)
    //         {
    //             if (Left_Add_Stop || Right_Add_Stop || SearchErrorFlag == i)
    //             {
    //                 break;
    //             }
    //         }
    //     }
    //     /******************************** 第一轮补线开始 ************************************/
    //     if (Left_Add_Flag[i] && i<StartLine) // 左侧需要补线
    //     {
    //         if (i >= StartLine-3 && i < StartLine)   // 前三行补线不算
    //         {
    //             if (!Left_Add_Start && Left_Add_Flag[i-1] && Left_Add_Flag[i-2])///i在54到56之间且前两行需要补线
    //             {
    //                 Left_Add_Start = i;  // 记录补线开始行
    //                 Left_Ka = 0;
    //                 Left_Kb = Left_Add_Line[i];
    //             }
    //             Left_Add_Line[i] = Calculate_Add(i, Left_Ka, Left_Kb); ///按照程序对称原则自加
    //         }
    //         else if(i < StartLine-3)///i小于54
    //         {
    //             if (!Left_Add_Start && Left_Add_Flag[i-1] && Left_Add_Flag[i-2]) // 之前没有补线
    //             {
    //                 Left_Add_Start = i;  // 记录左侧补线开始行
    //                 Curve_Fitting(&Left_Ka, &Left_Kb, &Left_Add_Start, Left_Add_Line, Left_Add_Flag, 1); // 使用两点法拟合直线///获得新的Ka和Kb
    //             }
    //         }
    //         Left_Add_Line[i] = Calculate_Add(i, Left_Ka, Left_Kb);   // 使用前一行图像左边界斜率补线///加一个画线程序，画一个点
    //     }
    //     else
    //     {
    //         if (Left_Add_Start)  // 已经开始补线而且开始不丢线
    //         {
    //             if (!Left_Add_Stop &&
    //                     !Left_Add_Flag[i+2*StepLine] &&
    //                     !Left_Add_Flag[i+4*StepLine]
    //                     && i<StartLine-5*StepLine)///第后两行和后四行不丢线且i小于52
    //             {
    //                 if ((Left_Add_Line[i] >= Left_Add_Line[i+2*StepLine] &&
    //                         Left_Add_Line[i+2*StepLine] >= Left_Add_Line[i+4*StepLine]&&
    //                         Left_Add_Line[i]!=1 &&
    //                         Left_Add_Line[i+1*StepLine]!=1 &&
    //                         Left_Add_Line[i+2*StepLine]!=1))///第i，i+1，i+2行左边线不是1且第i，i+2,i+4行的左边线依次变大，说明满足畸变
    //                 {
    //                     Left_Add_Stop = i+4*StepLine;    // 记录左侧补线结束行
    //                     //Line_Repair(Left_Add_Start, Left_Add_Stop, LeftEdge, Left_Add_Line, Left_Add_Flag, 1);
    //                 }
    //             }
    //         }
    //     }
    //     if (Right_Add_Flag[i] && i<StartLine)    // 右侧需要补线
    //     {
    //         if (i >= StartLine-3 && i < StartLine)   // 前三行补线不算
    //         {
    //             if (!Right_Add_Start && Right_Add_Flag[i-1] && Right_Add_Flag[i-2])
    //             {
    //                 Right_Add_Start = i; // 记录补线开始行
    //                 Right_Ka = 0;
    //                 Right_Kb = Right_Add_Line[i];
    //             }
    //             Right_Add_Line[i] = Calculate_Add(i, Right_Ka, Right_Kb);    // 使用前一帧图像右边界斜率补线
    //         }
    //         else if(i < StartLine-3)
    //         {
    //             if (!Right_Add_Start)    // 之前没有补线
    //             {
    //                 Right_Add_Start = i; // 记录右侧补线开始行
    //                 Curve_Fitting(&Right_Ka, &Right_Kb, &Right_Add_Start, Right_Add_Line, Right_Add_Flag, 2);    // 使用两点法拟合直线
    //             }
    //             Right_Add_Line[i] = Calculate_Add(i, Right_Ka, Right_Kb);    // 补线完成
    //         }
    //     }
    //     else
    //     {
    //         if (Right_Add_Start) // 已经开始补线
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
    //                     Right_Add_Stop = i+4*StepLine;   // 记录右侧补线结束行
    //                     //Right_Add_Start = 0;
    //                     //Line_Repair(Right_Add_Start, Right_Add_Stop, RightEdge, Right_Add_Line, Right_Add_Flag, 2);
    //                 }
    //             }
    //         }
    //     }
    //     /********************************* 第一轮补线结束 **********************************/
    //     if(Right_Add_Line[i] >= Left_Add_Line[i])
    //         Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i]; // 重新计算赛道宽度
    //     else
    //         Width_Add[i] = 0;
    //     if ((Left_Add_Flag[i] && Right_Add_Flag[i]) || (!Left_Add_Flag[i] && !Right_Add_Flag[i]))///左右同时需要补线或者同时不需要
    //         MiddleLine[i] = (Right_Add_Line[i] + Left_Add_Line[i]) / 2;  // 计算中线
    //     else if(i<StartLine)
    //         MiddleLine[i] = MiddleLine[i+StepLine];
    //     if (Width_Add[i] < Width_Min)
    //     {
    //         Width_Min = Width_Add[i];                // 更新最小赛道宽度
    //     }
    //     Line_Count = i;                              //Line_Count更新
    // }
    // /*************************************************************************************/
    // /*                              二次遍历结束                                         */
    // /*************************************************************************************/
    // /*************************************************************************************/
    // /*                     三次遍历开始（边线修复+中线修复）                              */
    // /*************************************************************************************/
    // /******************************* 补线修复开始 ********************************/
    // if (Left_Add_Start)      // 左边界需要补线
    // {
    //     Line_Repair(Left_Add_Start, Left_Add_Stop, LeftEdge, Left_Add_Line, Left_Add_Flag, 1);
    // }
    // if (Right_Add_Start) // 右边界需要补线
    // {
    //     Line_Repair(Right_Add_Start, Right_Add_Stop, RightEdge, Right_Add_Line, Right_Add_Flag, 2);
    // }
    // /******************************* 补线修复结束 ********************************/
    // /******************************* 中线修复开始 ********************************/
    // for(i=StartLine; i>=Line_Count; i-=StepLine)
    // {
    //     MiddleLine[i] = (Right_Add_Line[i] + Left_Add_Line[i]) / 2;  // 计算赛道中点
    //     if(Right_Add_Line[i] >= Left_Add_Line[i])
    //         Width_Add[i] = Right_Add_Line[i] - Left_Add_Line[i]; // 重新计算赛道宽度
    //     else
    //         Width_Add[i] = 0;
    //     if(SearchErrorFlag == i || CheckEnd(i-1,MiddleLine[i]) || i == FinishLine)///用这个动态前瞻判断三岔口的三角
    //     {
    //         LastLine = i;//最后一行，动态前瞻
    //         spurroadtriangle_i = i;
    //         spurroadtriangle_j = MiddleLine[i];
    //         AvaliableLines = StartLine - i;//有效行数
    //         break;
    //     }
    // }
    /*************************************************************************************/
    /*                              三次遍历结束                                         */
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
 * @brief       提取图像的特征，获取黑线截止行
 * @param       null
 * @return      null
 */
void GetBlackEndParam ()
{
    unsigned char LLLEndFlag = 0;    ///白点标志位
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

//清零
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
            BlackEndL++;//左黑线截至行
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*2/8) && CheckBlackPixle(i-2,ColumnMax*2/8))
            LEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*3/8) && !MLEndFlag)//10
            BlackEndML++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*3/8) && CheckBlackPixle(i-2,ColumnMax*3/8))
            MLEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*4/8) && !MEndFlag)//10
            BlackEndM++;//中黑线截至行
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*4/8) && CheckBlackPixle(i-2,ColumnMax*4/8))
            MEndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*5/8) && !MREndFlag)//10
            BlackEndMR++;
        else if(i > 1 && CheckBlackPixle(i-1,ColumnMax*5/8) && CheckBlackPixle(i-2,ColumnMax*5/8))
            MREndFlag = 1;

        if(CheckWhitePixle(i,ColumnMax*6/8) && !REndFlag)//10
            BlackEndR++;//右黑线截至行
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
    for (i = RowMax - 1; i > 0; i--)    ///从59到0行///找到白点后再找到黑点,黑点行数计数
    {
        if (CheckBlackPixle(i,ColumnMax/12) && !LLLEndFlag)    //94/12=7.83
            BlackEndLLL++;    //第i行，第7列是黑点
        else if (i > 1 && CheckEnd(i, ColumnMax/12))
            LLLEndFlag = 1;    //第i行，第7列是白点

        if (CheckBlackPixle(i,ColumnMax/8) && !LLEndFlag)    //94/8=11.75
            BlackEndLL++;
        else if (i > 1 && CheckEnd(i, ColumnMax/8))
            LLEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*2/8) && !LEndFlag)    //23.5
            BlackEndL++;    //左黑线截至行
        else if (i > 1 && CheckEnd(i, ColumnMax*2/8))
            LEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*3/8) && !MLEndFlag)    //35.25
            BlackEndML++;
        else if (i > 1 && CheckEnd(i, ColumnMax*3/8))
            MLEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*4/8) && !MEndFlag)    ///47
            BlackEndM++;    //中黑线截至行
        else if (i > 1 && CheckEnd(i, ColumnMax*4/8))
            MEndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*5/8) && !MREndFlag)    ///58.75
            BlackEndMR++;
        else if (i > 1 && CheckEnd(i, ColumnMax*5/8))
            MREndFlag = 1;

        if (CheckBlackPixle(i,ColumnMax*6/8) && !REndFlag)    ///70.5
            BlackEndR++;    //右黑线截至行
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
        BlackEndLLL = 0;    ///清零

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
    BlackEndMin = MIN(BlackEndL, BlackEndM);    //取大值
    BlackEndMin = MIN(BlackEndMin, BlackEndR);
}

/*
 * @brief       对十字进行识别和进行特殊处理
 * @param       null
 * @return      null
 */
void NormalCrossConduct ()
{
    ///unsigned char i;
    int j = 0;
    LastLastCrossFlag = LastCrossFlag;    //记录上上次是否是十字
    LastCrossFlag = CrossFlag;    //记录上一次是否是十字
    CrossFlag = 0;    //清零

    if ((AllLose >= 5))    //左右同时丢线
    {
        CrossFlag = 1;    //标记十字

        Road_vanish = 1;    ///判断三岔路，边路消失。
    }
    if ((AllLose <= 1))    //左右不同时丢线
    {
        CrossFlag = 0;    //清除标记十字

        Road_vanish = 0;    ///清除三岔路边路消失标志

        if (CrossNumber > 3)
            LoseCrossNumber++;       //如果左右十字计数从有到无则计数
    }
    if (CrossFlag && LastCrossFlag && LastLastCrossFlag)  //连续左右丢线
    {
        CrossNumber++;                                    //十字计数
    }
    if (LoseCrossNumber > 3)                                //已经进入圆环了
    {
        CrossEnterFlag = 1;                               //进圆环标志位置起
        CrossNumber = 0;                                  //圆环统计清除

    }
    if (CrossEnterFlag && CrossNumber > 3)                  //出圆环
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
 * @brief       对环岛进行处理
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
        if (LeftLose > 15)                  ///仅左丢线行数大于15
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
        else if (CircleDistance > 50)                  ///圆环距离大于50
        {
            LeftCircleFlag = NoCircle;
            RightCircleFlag = NoCircle;
            CircleDistance = 0;
            SpeedParm = SelectMode;
        }
    }

    /*******************左环********************/
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
    /*****************************确认入环**********************************/
    else if (LeftCircleFlag == InCircle)
    {

        if (Cirlce_Angle > 140)
        {
            ImgCount = count = 0;
            LeftCircleFlag = OutCircle;                 //左右都丢线超过十行则开始出岛
        }
    }
    /*****************************判断出环**********************************/
    else if (LeftCircleFlag == OutCircle)
    {
        if (Cirlce_Angle > 240)
        {
            DrawOvalFlag = 0;
            LeftCircleFlag = StopCheckCircle;   //出岛完毕
            ImgCount = count = 0;       //限制为100场图像内更新否则清掉
        }
    }
    /********************出环成功，过段时间再扫标志位**************************/
    else if (LeftCircleFlag == StopCheckCircle)
    {
        if (OutCircleDistance * 2 >= CircleDistance)
        {
            OutCircleDistance = CircleDistance = 0;       ///这个OutCircleDistance好像没有数据
            ImgCount = count = 0;
            LeftCircleFlag = NoCircle;    //一次之后就不判了
        }
    }
    /*******************               右环               ********************/
    /*****************************准备进环***********************************/
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
    /*****************************确认入环**********************************/
    else if (RightCircleFlag == InCircle)
    {
        if (Cirlce_Angle < -140)
        {
            ImgCount = count = 0;
            RightCircleFlag = OutCircle;                    //左右都丢线超过十行则开始出岛
        }
    }
    /*****************************判断出环**********************************/
    else if (RightCircleFlag == OutCircle)
    {
        if (Cirlce_Angle < -240)
        {
            DrawOvalFlag = 0;
            RightCircleFlag = StopCheckCircle;  //出岛完毕
            ImgCount = count = 0;       //限制为100场图像内更新否则清掉
        }
    }
    /********************出环成功，过段时间再扫标志位**************************/
    else if (RightCircleFlag == StopCheckCircle)
    {
        if (OutCircleDistance * 2 >= CircleDistance)
        {
            OutCircleDistance = CircleDistance = 0;
            ImgCount = count = 0;
            RightCircleFlag = NoCircle;   //一次之后就不判了
        }
    }
    ImgCount++;

    if (ImgCount > 1500)
    {
        ImgCount = 0;
    }
}

/*
 * @brief       起跑线检测
 * @param       null
 * @return      null
 */
void StartCheck()
{

}
/*
 * @brief       智能车处理主函数
 * @param       null
 * @return      null
 */
void Image_Process ()
{

}

