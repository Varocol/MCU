#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
//一定要注意宏定义使用问题：例如如果将i的地方使用表达式，表达式一定要用括号，否则会因为运算符优先级出错！！！！
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"

//基本的灰度变换函数
//灰度变换-恒等变换(s=c)
//灰度变换-图像反转(L-1-r)
//灰度变换-对数变换(s=clog(r+1))
//灰度变换-幂律变换(s=cr^γ)
//灰度变换-直方图均衡(s=T(r)=(L-1)∫Pr(w)dw=(L-1)/MN*Σ(nj))

//平滑空间滤波器
//平滑线性滤波器-均值滤波器1(1/9*Σzi)
//平滑线性滤波器-均值滤波器2(1/16*Σzi)
//统计排序滤波器-中值滤波器(排序后取中值)

//图像处理约定参数
//规定灰度值范围0~255
#define Gray_Max 0xff
#define Gray_Min 0

//图像处理类：Digital Image Processing Class
class DIP
{
    private:
    public:
        static void Grayscale_Identity (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Reverse (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Logarithm (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Pow (double, uint8*, uint8*, uint16, uint16);
        static void Grayscale_Equalization (uint8*, uint8*, uint16, uint16);
        static void Filter_Mean1 (uint8*, uint8*, uint16, uint16);
        static void Filter_Mean2 (uint8*, uint8*, uint16, uint16);
        static void Filter_Median (uint8, uint8*, uint8*, uint16, uint16);
};

#endif /*__OJ_IMAGE_PROCESS_H*/
