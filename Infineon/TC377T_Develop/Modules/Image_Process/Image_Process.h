#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
//һ��Ҫע��궨��ʹ�����⣺���������i�ĵط�ʹ�ñ��ʽ�����ʽһ��Ҫ�����ţ��������Ϊ��������ȼ�����������
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"

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
#define Gray_Max 0xff
#define Gray_Min 0

//ͼ�����ࣺDigital Image Processing Class
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
        //���ܳ�ͼ�����㷨����
        static void Car_Img_Process (uint8*, uint8*, uint16, uint16);

};

extern uint8 Histogram[IPS114_H][IPS114_W];
#endif /*__OJ_IMAGE_PROCESS_H*/
