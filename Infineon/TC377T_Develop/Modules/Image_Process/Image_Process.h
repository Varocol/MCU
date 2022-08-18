#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
//一定要注意宏定义使用问题：例如如果将i的地方使用表达式，表达式一定要用括号，否则会因为运算符优先级出错！！！！
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"

//基本的灰度变换函数
//灰度变换
//灰度变换-恒等变换(s=c)
//灰度变换-图像反转(L-1-r)
//灰度变换-对数变换(s=clog(r+1))
//灰度变换-幂律变换(s=cr^γ)
//灰度变换-直方图均衡(s=T(r)=(L-1)∫Pr(w)dw=(L-1)/MN*Σ(nj))

//平滑空间滤波器
//平滑线性滤波器-均值滤波器(1/9*Σzi)
//平滑线性滤波器-高斯滤波器(1/16*Σzi)
//统计排序滤波器-中值滤波器(排序后取中值)

//锐化空间滤波器
//锐化空间滤波器-拉普拉斯算子(二阶微分算子)
//锐化空间滤波器-非锐化掩蔽和高提升滤波
//锐化空间滤波器-Sobel算子(一阶微分算子)

//模糊集合
//模糊集合-灰度变换
//模糊集合-边缘增强

//图像分割
//图像分割-孤立点的检测
//图像分割-线检测
//图像分割-基本全局阈值处理(迭代法)
//图像分割-Otsu最佳全局阈值处理(俗称大津法)
//图像分割-Otsu的智能车优化版本

//智能车赛道处理算法
//赛道寻线

//图像处理约定参数
//规定灰度值范围0~255
#define Gray_Max 0xff
#define Gray_Min 0

//图像处理类：Digital Image Processing Class
class DIP
{
    private:
        static uint8 Global_Otsu_Better_threshold (uint8*, uint16, uint16);
    public:
        static void Grayscale_Identity (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Reverse (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Logarithm (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Pow (double, uint8*, uint8*, uint16, uint16);
        static void Grayscale_Equalization (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Binarization (uint8*, uint8*, uint8, uint16, uint16);
        static void Filter_Mean (uint8*, uint8*, uint16, uint16);
        static void Filter_Gaussian (uint8*, uint8*, uint16, uint16);
        static void Filter_Median (uint8, uint8*, uint8*, uint16, uint16);
        static void Fliter_Laplace (uint8*, uint8*, uint16, uint16);
        static void Fliter_Unsharp (uint8*, uint8*, uint8*, uint16, uint16);
        static void Fliter_Sobel (uint8*, uint8*, uint16, uint16);
        static void Fuzzy_GrayValue (uint8*, uint8*, uint16, uint16);
        static void Fuzzy_EdgeEnhance (uint8*, uint8*, uint16, uint16);
        static void Segmentation_Point (uint8*, uint8*, uint16, uint16);
        static void Segmentation_Line (uint8*, uint8*, uint16, uint16);
        static void Global_threshold (uint8*, uint8*, uint16, uint16);
        static void Global_Otsu (uint8*, uint8*, uint16, uint16);
        static void Global_Otsu_Better (uint8*, uint8*, uint16, uint16);
        static void Sobel_Recognizer (uint8*, uint8*, uint16, uint16);
        static void Get_Histogram (uint8*, uint8*, uint16, uint16, uint16, uint16);
        static void Show_FPS ();
        static void FPS_Start ();
        static void FPS_End ();
        //智能车图像处理算法部分
        static void Car_Img_Process (uint8*, uint8*, uint16, uint16);

};

extern uint8 Histogram[IPS114_H][IPS114_W];
#endif /*__OJ_IMAGE_PROCESS_H*/
