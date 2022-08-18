#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
//һ��Ҫע��궨��ʹ�����⣺���������i�ĵط�ʹ�ñ��ʽ�����ʽһ��Ҫ�����ţ��������Ϊ��������ȼ�����������
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"
#include "Variables.h"
#include "Platform.h"
//�����ĻҶȱ任����
//�Ҷȱ任
//�Ҷȱ任-��ȱ任(s=c)
//�Ҷȱ任-ͼ��ת(L-1-r)
//�Ҷȱ任-�����任(s=clog(r+1))
//�Ҷȱ任-���ɱ任(s=cr^��)
//�Ҷȱ任-ֱ��ͼ����(s=T(r)=(L-1)��Pr(w)dw=(L-1)/MN*��(nj))

//ƽ���ռ��˲���
//ƽ�������˲���-��ֵ�˲���(1/9*��zi)
//ƽ�������˲���-��˹�˲���(1/16*��zi)
//ͳ�������˲���-��ֵ�˲���(�����ȡ��ֵ)

//�񻯿ռ��˲���
//�񻯿ռ��˲���-������˹����(����΢������)
//�񻯿ռ��˲���-�����ڱκ͸������˲�
//�񻯿ռ��˲���-Sobel����(һ��΢������)

//ģ������
//ģ������-�Ҷȱ任
//ģ������-��Ե��ǿ

//ͼ��ָ�
//ͼ��ָ�-������ļ��
//ͼ��ָ�-�߼��
//ͼ��ָ�-����ȫ����ֵ����(������)
//ͼ��ָ�-Otsu���ȫ����ֵ����(�׳ƴ��)
//ͼ��ָ�-Otsu�����ܳ��Ż��汾

//���ܳ����������㷨
//����Ѱ��

//ͼ����Լ������
//�涨�Ҷ�ֵ��Χ0~255


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

//���ܳ�ͼ�����㷨����
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
void DrawLine(int16 x0,int16 y0,int16 x1,int16 y1);///����ֵ��ͼ��ĺ�ֱ��

void DrawLine1(int16 x0,int16 y0,int16 x1,int16 y1);///���Ҷ�ͼ��ĺ����Լ����ڲ���

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

//ch��ͼ���㷨
#define ROW 120
#define COL 188
#define IMG_BLACK 0
#define IMG_WHITE 1
#define ROAD_CENTER_POINT 46//��·����������Ϊ��63��
#define BASE_LINE 5  //���һ��
#define ERR_USEROW 5 //ȡ������ǰ(64-ERR_USEROW)����ƫ�� ��BASE_LINEһ��
#define GETEDGE_START 59 //�ӽ�����GETEDGE_START�п�ʼ����
#define ROAD_CENTER_POINT 46//��·����������Ϊ��63��
#define iFilterW 3
#define iFilterH 3
#define iFilterMX 2
#define iFilterMY 2
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)



extern int gray_difference;
extern int crossroad_flag;
extern int fork_flag;
extern uint8 found_num;

void get_edge_center_new(void);//���ûҶȲ�Ⱥ���߽�
void crossroad_pass(void);//ʮ�ּ��
void crossroad_patch(void);//ʮ�ֲ���
void fork_check(void);//�����
void get_center(void);
int16 adapt_otsuThreshold(int16 *image, int16 col, int16 row);   //ע�������ֵ��һ��Ҫ��ԭͼ��
unsigned char GetMedianNum(int * bArray, int iFilterLen);
void MedianFilter(unsigned char *pImg1,unsigned char *pImg,int nWidth,int nHeight);
void gray_to_ori(uint16 image_ori[ROW][COL]);
void get_longest_whiteline();

#endif /*__OJ_IMAGE_PROCESS_H*/
