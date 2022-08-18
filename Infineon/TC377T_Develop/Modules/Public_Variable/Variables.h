#ifndef __VARIALBES_H
#define __VARIALBES_H
#include "headfile.h"
#define Gray_Max 0xff
#define Gray_Min 0

#define White_Point     1
#define Black_Point     0

#define IMAGEH  MT9V03X_H
#define IMAGEW  MT9V03X_W

#define RowMax              60  //120  //行数
#define ColumnMax           94   //188  //列数

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

#define StartLine       57              //中线扫描起始行

#define FinishLine      18              //中线扫描结束行

#define StepLine        1               //边缘追踪扫描间隔行

#define DivideLine      StartLine-10    //全行扫描和边缘追踪分隔行///47

#define MIDVALUE        48

#define ImageMode           2           //选择图像模式（0-OSTU/1-ITERATION/2-Sobel）

#define CheckWhitePixle(x,y) Image_Sobel[x][y] >= Threshold //白点判断
#define CheckBlackPixle(x,y) Image_Sobel[x][y] < Threshold  //黑点判断
#define CheckLeft(x,y)  CheckBlackPixle(x,y) && CheckWhitePixle(x,y-1) //&& CheckWhitePixle(x,y-2)
#define CheckRight(x,y) CheckBlackPixle(x,y) && CheckWhitePixle(x,y+1) //&& CheckWhitePixle(x,y+2)
#define CheckEnd(x,y)   CheckWhitePixle(x,y) //&& CheckWhitePixle(x-1,y)
#define pi 3.14

/*************************wzy的变量***********************/
#define ABS(a) (a > 0 ? a: -a)
#define DELT(a, b) (a - b)
#define ABS_DELT(a, b) (a > b ? a - b: b - a)
#define DIFFER(a, b) ((a - b) * 100 / (a + b))
#define FAST_DIFFER(a, b) (((a - b) << 7 ) / (a + b + 1))
#define ABS_DIFFER(a, b) a >= b ? (((a - b) << 7 ) / (a + b + 1) : ((b - a) << 7 ) / (a + b + 1))

#define CameraInit()                    mt9v03x_init()
#define ShowZoomImage(src,x,y,x1,y1)    ips200_displayimage032_zoom(&mt9v03x_image[0],x,y,x1,y1);

//wzy的图像算法
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

//图像变量区
extern int Test;
extern volatile uint16 Image_Use[RowMax][ColumnMax];
extern volatile uint32 Pixel[RowMax][ColumnMax];
extern volatile uint16 Image_Sobel[RowMax][ColumnMax];
extern int16 Threshold;
extern int16 FilterThreshold;
extern int16 Camera_scan_finish;
extern const int Width[RowMax + 1];
extern float Weight[60];

extern float AverageCenter;                        //归一中线数值
extern float LastAverageCenter;                    //上一次中线
extern extern int16 LastAverageError[5];               //中线偏差保存
extern int16 LeftLose;                     //仅左丢线行数
extern int16 RightLose;                     //仅右丢线行数
extern int16 AllLose;                     //两边全丢白线行数（十字）
extern int16 WhiteLose;                     //两边全丢黑线行数（丢失赛道）
extern int16 LeftLoseStart;                     //记录左边丢线的开始行
extern int16 RightLoseStart;                     //记录右边边丢线的开始行
extern int16 WhiteLoseStart;                     //记录全丢白线的开始行
extern int16 FirstLoseAllLine;                     //全丢白开始行///这个开始行需要重新定义
extern int16 LastLoseAllLine;                      //全丢白结束行
extern int16 StartLineCount;                     //起跑线检测计数
extern int16 LastLine;                           //扫描最后一行,动态前瞻
extern int16 AvaliableLines;                     //扫描有效行数
extern int16 SearchErrorFlag;

extern int Foresight;                   //前瞻
extern int Last_Foresight;                   //上一次前瞻
extern int16 Fictitious_Num;                   //虚拟直线拟合求取的偏差
extern int Track_ImgCount;                   //赛道判断间隔计数
extern int Track_Type;                   //赛道种类

extern uint32 MiddleLine[RowMax + 1];                    //中线存放数组
extern uint32 RightEdge[RowMax + 1];                     //右边线存放数
extern uint32 LeftEdge[RowMax + 1];                  //左边线存放数组
extern uint32 RealWidth[RowMax + 1];                 //赛道实际宽度
extern uint32 Left_Add_Line[RowMax + 1];             //左补线存放数组
extern uint32 Right_Add_Line[RowMax + 1];                //右补线存放数组
extern uint32 Left_Add_Flag[RowMax];                   //左补线标志位
extern uint32 Right_Add_Flag[RowMax];                  //右补线标志位
extern uint32 Width_Add[RowMax + 1];                  ///uint32 Width_Add[RowMax];//补线宽度数组
extern uint32 Width_Min;                               //赛道最小宽度
extern int16 Line_Count;                           //记录成功识别到的赛道行数
extern uint32 Left_Add_Start;                      //左补线起始
extern uint32 Left_Add_Stop;                       //左补线结束行
extern uint32 Right_Add_Start;                 //右补线起始
extern uint32 Right_Add_Stop;                      //右补线结束行
extern float Left_Ka, Right_Ka;            //最小二乘法参数
extern float Left_Kb, Right_Kb;

/*********截止行提取变量初始化**********/
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

/*********十字处理变量初始化**********/
extern unsigned char CrossFlag;                  //十字标志
extern unsigned char LastCrossFlag;
extern unsigned char LastLastCrossFlag;
extern unsigned char CrossNumber;
extern unsigned char LoseCrossNumber;
extern unsigned char CrossEnterFlag;
extern float CrossKL, CrossKR;

/*********环岛处理变量初始化**********/
extern float Cirlce_Angle;               //环岛角度
extern float CircleDistance;
extern float OutCircleDistance;
extern int16 RightOvalFlag;
extern int16 LeftOvalFlag;
extern int16 LeftCircleFlag;             //左环岛识别标志位
extern int16 RightCircleFlag;            //右环岛识别标志位
extern int16 DrawOvalFlag;                 //画环岛标志
extern int16 SalationFlag;
extern int16 LLSalationLine;             //左边线左跳变起始行
extern int16 LRSalationLine;             //左边线右跳变起始行
extern int16 RLSalationLine;             //右边线左跳变起始行
extern int16 RRSalationLine;             //右边线右跳变起始行

extern int16 Onlyonce;
///自加变量

/*********断路变量初始化**********/
extern float StationAngle;
extern int StationLineNum;
//extern extern int16 LeftWheelSpeed;
//extern int16 RightWheelSpeed;

/*********三岔路变量**********/
///
extern unsigned char Road_widening;

extern unsigned char Road_vanish;

extern int16 spurroadtriangle_i;

extern int16 spurroadtriangle_j;

extern int16 left_right_lost_i;                      ///左右全丢结束行

extern unsigned char SpurroadFlag;                  //三岔口标志

extern unsigned char LastSpurroadFlag;

extern unsigned char LastLastSpurroadFlag;

extern float SpurroadKL = 0, SpurroadKR;

/*********其它变量初始化**********/
extern int StartFlag = WithoutRun;                      //起跑线标志位

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
