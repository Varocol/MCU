#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
//一定要注意宏定义使用问题：例如如果将i的地方使用表达式，表达式一定要用括号，否则会因为运算符优先级出错！！！！
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"
#include "Variables.h"
#include "Platform.h"
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


void Grayscale_Identity (uint8*, uint8*, uint16, uint16);
void Grayscale_Reverse (uint8*, uint8*, uint16, uint16);
void Grayscale_Logarithm (uint8*, uint8*, uint16, uint16);
void Grayscale_Pow (double, uint8*, uint8*, uint16, uint16);
void Grayscale_Equalization (uint8*, uint8*, uint16, uint16);
void Grayscale_Binarization (uint8*, uint8*, uint8, uint16, uint16);
void Filter_Mean (uint8*, uint8*, uint16, uint16);
void Filter_Gaussian (uint8*, uint8*, uint16, uint16);
void Filter_Median (uint8, uint8*, uint8*, uint16, uint16);
void Fliter_Laplace (uint8*, uint8*, uint16, uint16);
void Fliter_Unsharp (uint8*, uint8*, uint8*, uint16, uint16);
void Fliter_Sobel (uint8*, uint8*, uint16, uint16);
void Fuzzy_GrayValue (uint8*, uint8*, uint16, uint16);
void Fuzzy_EdgeEnhance (uint8*, uint8*, uint16, uint16);
void Segmentation_Point (uint8*, uint8*, uint16, uint16);
void Segmentation_Line (uint8*, uint8*, uint16, uint16);
void Global_threshold (uint8*, uint8*, uint16, uint16);
void Global_Otsu (uint8*, uint8*, uint16, uint16);
void Global_Otsu_Better (uint8*, uint8*, uint16, uint16);
void Sobel_Recognizer (uint8*, uint8*, uint16, uint16);
void Get_Histogram (uint8*, uint8*, uint16, uint16, uint16, uint16);
void Show_FPS ();
void FPS_Start ();
void FPS_End ();

//智能车图像处理算法部分
void OnlyOnce();
void Zebra_Filter();
float Middle_Err_Filter(float);
void TrackJudge();
void SearchCenterBlackline();
void GetBlackEndParam();
void SpurroadConduct();
void NormalCrossConduct();
void CircleConduct();
void StartCheck();
void WeightedAverageCalc(uint32 AdvanceNum);
void BinaryImage(uint32 tmImage[IMAGEH][IMAGEW],uint32 ThresholdV);

int16 FindOvalPoint(int16 col,int16 flag);
void DrawLine(int16 x0,int16 y0,int16 x1,int16 y1);///画二值化图像的黑直线

void DrawLine1(int16 x0,int16 y0,int16 x1,int16 y1);///画灰度图像的红线自加用于测试

void Draw_Road(void);
void Get_Use_Image(void);
void Get_01_Value(int limit,int height,int width);
void Pixle_Filter(int16 threshold);

int16 Sobel(int16 start,int16 finish);
float Image_Process(void);

uint32 CountRowW2BSalation(uint32 line,uint32 start,uint32 finish);
uint32 CountRowB2WSalation(uint32 line,uint32 start,uint32 finish);

int16 adapt_otsuThreshold(int16 *image, int16 col, int16 row);

#define CameraInit()                    mt9v03x_init();
#define ShowZoomImage(src,x,y,x1,y1)    ips200_displayimage032_zoom(&mt9v03x_image[0],x,y,x1,y1);
#define ShowZoomImage_gray(src,x,y,x1,y1)   ips200_displayimage032_zoom(&gray_filter[0],x,y,x1,y1);

//ch的图像算法
#define ROW 120
#define COL 188
#define IMG_BLACK 0
#define IMG_WHITE 1
#define ROAD_CENTER_POINT 46//道路理想中心线为第63列
#define BASE_LINE 5  //最近一行
#define ERR_USEROW 5 //取近处起前(64-ERR_USEROW)行算偏差 与BASE_LINE一致
#define GETEDGE_START 59 //从近处第GETEDGE_START行开始搜线
#define ROAD_CENTER_POINT 46//道路理想中心线为第63列
#define iFilterW 3
#define iFilterH 3
#define iFilterMX 2
#define iFilterMY 2
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)



extern int gray_difference;
extern int crossroad_flag;
extern int fork_flag;
extern uint8 found_num;

void get_edge_center_new(void);//利用灰度差比和求边界
void crossroad_pass(void);//十字检测
void crossroad_patch(void);//十字补线
void fork_check(void);//检测岔口
void get_center(void);
int16 adapt_otsuThreshold(int16 *image, int16 col, int16 row);   //注意计算阈值的一定要是原图像
unsigned char GetMedianNum(int * bArray, int iFilterLen);
void MedianFilter(unsigned char *pImg1,unsigned char *pImg,int nWidth,int nHeight);
void gray_to_ori(uint16 image_ori[ROW][COL]);
void get_longest_whiteline();

#endif /*__OJ_IMAGE_PROCESS_H*/
