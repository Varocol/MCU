#ifndef __VARIALBES_H
#define __VARIALBES_H
#include "headfile.h"
#define Gray_Max 0xff
#define Gray_Min 0

#define White_Point     1
#define Black_Point     0

#define IMAGEH  MT9V03X_H
#define IMAGEW  MT9V03X_W

#define RowMax              60  //120  //����
#define ColumnMax           94   //188  //����

#define CurveToStraight     1
#define InStraight          2
#define StraightToCurve     3
#define InCurve             4

#define NoCircle            0
#define StopCheckCircle     1
#define ShouldBeCircle      2
#define MustBeCircle        3
#define ReadyInCircle       4
#define InCircle            5
#define OutCircle           6

#define WithoutRun          1
#define ReadyRun            2
#define StartRun            3
#define InRunning           4
#define FinishRun           5

#define StartLine       57              //����ɨ����ʼ��

#define FinishLine      18              //����ɨ�������

#define StepLine        1               //��Ե׷��ɨ������

#define DivideLine      StartLine-10    //ȫ��ɨ��ͱ�Ե׷�ٷָ���///47

#define MIDVALUE        48

#define ImageMode           2           //ѡ��ͼ��ģʽ��0-OSTU/1-ITERATION/2-Sobel��

#define CheckWhitePixle(x,y) Image_Sobel[x][y] >= Threshold //�׵��ж�
#define CheckBlackPixle(x,y) Image_Sobel[x][y] < Threshold  //�ڵ��ж�
#define CheckLeft(x,y)  CheckBlackPixle(x,y) && CheckWhitePixle(x,y-1) //&& CheckWhitePixle(x,y-2)
#define CheckRight(x,y) CheckBlackPixle(x,y) && CheckWhitePixle(x,y+1) //&& CheckWhitePixle(x,y+2)
#define CheckEnd(x,y)   CheckWhitePixle(x,y) //&& CheckWhitePixle(x-1,y)
#define pi 3.14

/*************************wzy�ı���***********************/
#define ABS(a) (a > 0 ? a: -a)
#define DELT(a, b) (a - b)
#define ABS_DELT(a, b) (a > b ? a - b: b - a)
#define DIFFER(a, b) ((a - b) * 100 / (a + b))
#define FAST_DIFFER(a, b) (((a - b) << 7 ) / (a + b + 1))
#define ABS_DIFFER(a, b) a >= b ? (((a - b) << 7 ) / (a + b + 1) : ((b - a) << 7 ) / (a + b + 1))

#define CameraInit()                    mt9v03x_init()
#define ShowZoomImage(src,x,y,x1,y1)    ips200_displayimage032_zoom(&mt9v03x_image[0],x,y,x1,y1);

//wzy��ͼ���㷨
// image
#define IMAGE_HEIGHT        MT9V03X_H
#define IMAGE_WIDTH         MT9V03X_W

// search
#define SEARCH_LEFT     1
#define SEARCH_RIGHT    (IMAGE_WIDTH - 2)
#define SEARCH_BOT      (MT9V03X_H * 5 / 6)//100
#define SEARCH_TOP  (MT9V03X_H * 1 / 12)//20
#define SEARCH_STEP_Y   1
#define SEARCH_STEP_X   1
#define SEARCH_MARGIN   7

// regression
#define REGRESSION_MIN_N    4

// midline enmu
#define MIDLINE_MAX     1
#define MIDLINE_MIN     2
#define MIDLINE_LEFT    3
#define MIDLINE_RIGHT   4

// downsample
#define DOWNSAMPLE_X    10
#define DOWNSAMPLE_Y    10
#define DOWNSAMPLE_H    ((SEARCH_BOT - SEARCH_TOP + 1) / DOWNSAMPLE_Y)
#define DOWNSAMPLE_W    ((SEARCH_RIGHT - SEARCH_LEFT + 1) / DOWNSAMPLE_Y)
#define DOWNSAMPLE_N    (DOWNSAMPLE_W * DOWNSAMPLE_H)
#define DOWNSAMPLE_C    5                           // color
#define DOWNSAMPLE_S    (256 / DOWNSAMPLE_C + 1)    // color

//ͼ�������
extern int Test;
extern volatile uint16 Image_Use[RowMax][ColumnMax];
extern volatile uint32 Pixel[RowMax][ColumnMax];
extern volatile uint16 Image_Sobel[RowMax][ColumnMax];
extern int16 Threshold;
extern int16 FilterThreshold;
extern int16 Camera_scan_finish;
extern const int Width[RowMax + 1];
extern float Weight[60];

extern float AverageCenter;                        //��һ������ֵ
extern float LastAverageCenter;                    //��һ������
extern extern int16 LastAverageError[5];               //����ƫ���
extern int16 LeftLose;                     //����������
extern int16 RightLose;                     //���Ҷ�������
extern int16 AllLose;                     //����ȫ������������ʮ�֣�
extern int16 WhiteLose;                     //����ȫ��������������ʧ������
extern int16 LeftLoseStart;                     //��¼��߶��ߵĿ�ʼ��
extern int16 RightLoseStart;                     //��¼�ұ߱߶��ߵĿ�ʼ��
extern int16 WhiteLoseStart;                     //��¼ȫ�����ߵĿ�ʼ��
extern int16 FirstLoseAllLine;                     //ȫ���׿�ʼ��///�����ʼ����Ҫ���¶���
extern int16 LastLoseAllLine;                      //ȫ���׽�����
extern int16 StartLineCount;                     //�����߼�����
extern int16 LastLine;                           //ɨ�����һ��,��̬ǰհ
extern int16 AvaliableLines;                     //ɨ����Ч����
extern int16 SearchErrorFlag;

extern int Foresight;                   //ǰհ
extern int Last_Foresight;                   //��һ��ǰհ
extern int16 Fictitious_Num;                   //����ֱ�������ȡ��ƫ��
extern int Track_ImgCount;                   //�����жϼ������
extern int Track_Type;                   //��������

extern uint32 MiddleLine[RowMax + 1];                    //���ߴ������
extern uint32 RightEdge[RowMax + 1];                     //�ұ��ߴ����
extern uint32 LeftEdge[RowMax + 1];                  //����ߴ������
extern uint32 RealWidth[RowMax + 1];                 //����ʵ�ʿ��
extern uint32 Left_Add_Line[RowMax + 1];             //���ߴ������
extern uint32 Right_Add_Line[RowMax + 1];                //�Ҳ��ߴ������
extern uint32 Left_Add_Flag[RowMax];                   //���߱�־λ
extern uint32 Right_Add_Flag[RowMax];                  //�Ҳ��߱�־λ
extern uint32 Width_Add[RowMax + 1];                  ///uint32 Width_Add[RowMax];//���߿������
extern uint32 Width_Min;                               //������С���
extern int16 Line_Count;                           //��¼�ɹ�ʶ�𵽵���������
extern uint32 Left_Add_Start;                      //������ʼ
extern uint32 Left_Add_Stop;                       //���߽�����
extern uint32 Right_Add_Start;                 //�Ҳ�����ʼ
extern uint32 Right_Add_Stop;                      //�Ҳ��߽�����
extern float Left_Ka, Right_Ka;            //��С���˷�����
extern float Left_Kb, Right_Kb;

/*********��ֹ����ȡ������ʼ��**********/
extern int16 BlackEndMR;
extern int16 BlackEndML;
extern int16 BlackEndLLL;
extern int16 BlackEndLL;
extern int16 BlackEndRRR;
extern int16 BlackEndRR;
extern int16 BlackEndL;
extern int16 BlackEndM;
extern int16 BlackEndR;
extern int16 BlackEndMin;

extern int16 EndMArray[5];
extern int16 EndMLArray[5];
extern int16 EndMRArray[5];

extern int16 LastBlackEndLL;
extern int16 LastBlackEndRR;
extern int16 LastBlackEndLLL;
extern int16 LastBlackEndRRR;

/*********ʮ�ִ��������ʼ��**********/
extern unsigned char CrossFlag;                  //ʮ�ֱ�־
extern unsigned char LastCrossFlag;
extern unsigned char LastLastCrossFlag;
extern unsigned char CrossNumber;
extern unsigned char LoseCrossNumber;
extern unsigned char CrossEnterFlag;
extern float CrossKL, CrossKR;

/*********�������������ʼ��**********/
extern float Cirlce_Angle;               //�����Ƕ�
extern float CircleDistance;
extern float OutCircleDistance;
extern int16 RightOvalFlag;
extern int16 LeftOvalFlag;
extern int16 LeftCircleFlag;             //�󻷵�ʶ���־λ
extern int16 RightCircleFlag;            //�һ���ʶ���־λ
extern int16 DrawOvalFlag;                 //��������־
extern int16 SalationFlag;
extern int16 LLSalationLine;             //�������������ʼ��
extern int16 LRSalationLine;             //�������������ʼ��
extern int16 RLSalationLine;             //�ұ�����������ʼ��
extern int16 RRSalationLine;             //�ұ�����������ʼ��

extern int16 Onlyonce;
///�Լӱ���

/*********��·������ʼ��**********/
extern float StationAngle;
extern int StationLineNum;
//extern extern int16 LeftWheelSpeed;
//extern int16 RightWheelSpeed;

/*********����·����**********/
///
extern unsigned char Road_widening;

extern unsigned char Road_vanish;

extern int16 spurroadtriangle_i;

extern int16 spurroadtriangle_j;

extern int16 left_right_lost_i;                      ///����ȫ��������

extern unsigned char SpurroadFlag;                  //����ڱ�־

extern unsigned char LastSpurroadFlag;

extern unsigned char LastLastSpurroadFlag;

extern float SpurroadKL = 0, SpurroadKR;

/*********����������ʼ��**********/
extern int StartFlag = WithoutRun;                      //�����߱�־λ

extern static uint16 g_mid_x;
extern static uint16 g_left_curve;
extern static uint16 g_right_curve;
extern static uint16 g_left_count;
extern static uint16 g_right_count;
extern static uint16 g_left_line[IMAGE_HEIGHT];
extern static uint16 g_right_line[IMAGE_HEIGHT];
extern static uint16 g_mid_line[IMAGE_HEIGHT];
extern static uint16 g_err_weight[IMAGE_HEIGHT] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //111-120
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //101-110
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //91-100
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,   //81-90
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,   //71-80
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3,   //61-70
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //51-60
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //41-50
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2,   //31-40
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //21-30
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

};
extern static uint16 g_weight_sum;
extern static uint16 x_conditon_left;
extern static uint16 x_conditon_right;

#endif /*__VARIALBES_H*/
