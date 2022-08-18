#include "Variables.h"
//显示帧率所需的变量
uint32 start, end;

int Test = 5;

/*********图像提取相关初始化**********/
volatile uint16 Image_Use[RowMax][ColumnMax];           //压缩后图像数据
volatile uint32 Pixel[RowMax][ColumnMax];       //二值化后用于OLED显示的数据//
volatile uint16 Image_Sobel[RowMax][ColumnMax];         //Sobel图像数据

/*********图像处理相关初始化**********/
int16 Threshold;
int16 FilterThreshold = 225;
int16 Camera_scan_finish = 0;
const int Width[RowMax + 1] =                      //图像每行直道对应行宽 ///镜头限制高度后可能行宽也要做相应的改变，也就是说数据需要手动更新。
        {
        /* 0 */1, 1, 1, 1, 1, 1, 1, 2, 3, 3,
        /* 1 */10, 10, 10, 10, 16, 17, 17, 19, 29, 31,
        /* 2 */33, 35, 37, 39, 41, 42, 44, 46, 48, 50,
        /* 3 */52, 54, 56, 57, 58, 60, 62, 63, 65, 66,
        /* 4 */67, 69, 70, 71, 72, 73, 75, 75, 77, 77,
        /* 5 */79, 79, 80, 81, 82, 82, 82, 82, 82, 82, 88};

float Weight[60] =                               //舵机打角权重（最近处不压线,用于弯道）
        {
        /* 0 */0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
        /* 1 */0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.2, 1.4, 1.4, 1.5,
        /* 2 */1.8, 2.0, 2.1, 2.3, 2.5, 2.6, 2.8, 2.9, 3.0, 3.2,
        /* 3 */3.4, 3.6, 3.8, 4.0, 4.2, 4.3, 4.4, 4.2, 4.0, 3.8,
        /* 4 */3.6, 3.4, 3.2, 3.0, 2.8, 2.6, 2.4, 2.2, 2.0, 1.8,
        /* 5 */1.6, 1.6, 1.5, 1.5, 1.4, 1.4, 1.2, 1.2, 1.0, 0.8};

float AverageCenter = 0;                        //归一中线数值
float LastAverageCenter = 0;                    //上一次中线
int16 LastAverageError[5] = {0};               //中线偏差保存
int16 LeftLose = 0;                     //仅左丢线行数
int16 RightLose = 0;                     //仅右丢线行数
int16 AllLose = 0;                     //两边全丢白线行数（十字）
int16 WhiteLose = 0;                     //两边全丢黑线行数（丢失赛道）
int16 LeftLoseStart = 0;                     //记录左边丢线的开始行
int16 RightLoseStart = 0;                     //记录右边边丢线的开始行
int16 WhiteLoseStart = 0;                     //记录全丢白线的开始行
int16 FirstLoseAllLine = 0;                     //全丢白开始行///这个开始行需要重新定义
int16 LastLoseAllLine = 0;                      //全丢白结束行
int16 StartLineCount = 0;                     //起跑线检测计数
int16 LastLine = 0;                           //扫描最后一行,动态前瞻
int16 AvaliableLines = 0;                     //扫描有效行数
int16 SearchErrorFlag = 0;

int Foresight = 0;                   //前瞻
int Last_Foresight = 0;                   //上一次前瞻
int16 Fictitious_Num = 0;                   //虚拟直线拟合求取的偏差
int Track_ImgCount = 0;                   //赛道判断间隔计数
int Track_Type = 0;                   //赛道种类

uint32 MiddleLine[RowMax + 1];                    //中线存放数组
uint32 RightEdge[RowMax + 1];                     //右边线存放数
uint32 LeftEdge[RowMax + 1];                  //左边线存放数组
uint32 RealWidth[RowMax + 1];                 //赛道实际宽度
uint32 Left_Add_Line[RowMax + 1];             //左补线存放数组
uint32 Right_Add_Line[RowMax + 1];                //右补线存放数组
uint32 Left_Add_Flag[RowMax];                   //左补线标志位
uint32 Right_Add_Flag[RowMax];                  //右补线标志位
uint32 Width_Add[RowMax + 1];                  ///uint32 Width_Add[RowMax];//补线宽度数组
uint32 Width_Min;                               //赛道最小宽度
int16 Line_Count;                           //记录成功识别到的赛道行数
uint32 Left_Add_Start = 0;                      //左补线起始
uint32 Left_Add_Stop = 0;                       //左补线结束行
uint32 Right_Add_Start = 0;                 //右补线起始
uint32 Right_Add_Stop = 0;                      //右补线结束行
float Left_Ka = 0, Right_Ka = 0;            //最小二乘法参数
float Left_Kb = 1, Right_Kb = ColumnMax - 1;

/*********截止行提取变量初始化**********/
int16 BlackEndMR = 0;
int16 BlackEndML = 0;
int16 BlackEndLLL = 0;
int16 BlackEndLL = 0;
int16 BlackEndRRR = 0;
int16 BlackEndRR = 0;
int16 BlackEndL = 0;
int16 BlackEndM = 0;
int16 BlackEndR = 0;
int16 BlackEndMin = 0;

int16 EndMArray[5];
int16 EndMLArray[5];
int16 EndMRArray[5];

int16 LastBlackEndLL = 0;
int16 LastBlackEndRR = 0;
int16 LastBlackEndLLL = 0;
int16 LastBlackEndRRR = 0;

/*********十字处理变量初始化**********/
unsigned char CrossFlag = 0;                  //十字标志
unsigned char LastCrossFlag = 0;
unsigned char LastLastCrossFlag = 0;
unsigned char CrossNumber = 0;
unsigned char LoseCrossNumber = 0;
unsigned char CrossEnterFlag = 0;
float CrossKL = 0, CrossKR = 0;

/*********环岛处理变量初始化**********/
float Cirlce_Angle = 0.0;               //环岛角度
float CircleDistance = 0.0;
float OutCircleDistance = 0.0;
int16 RightOvalFlag = 0;
int16 LeftOvalFlag = 0;
int16 LeftCircleFlag = 0;             //左环岛识别标志位
int16 RightCircleFlag = 0;            //右环岛识别标志位
int16 DrawOvalFlag = 0;                 //画环岛标志
int16 SalationFlag = 0;
int16 LLSalationLine = 0;             //左边线左跳变起始行
int16 LRSalationLine = 0;             //左边线右跳变起始行
int16 RLSalationLine = 0;             //右边线左跳变起始行
int16 RRSalationLine = 0;             //右边线右跳变起始行

int16 Onlyonce = 1;             ///自加变量

/*********断路变量初始化**********/
float StationAngle = 0.0;
int StationLineNum = 0;
extern int16 LeftWheelSpeed;
//extern int16 RightWheelSpeed;

/*********三岔路变量**********/
///
unsigned char Road_widening = 0;

unsigned char Road_vanish = 0;

int16 spurroadtriangle_i = 0;

int16 spurroadtriangle_j = 0;

int16 left_right_lost_i = 0;                      ///左右全丢结束行

unsigned char SpurroadFlag = 0;                  //三岔口标志

unsigned char LastSpurroadFlag = 0;

unsigned char LastLastSpurroadFlag = 0;

float SpurroadKL = 0, SpurroadKR = 0;

/*********其它变量初始化**********/
int StartFlag = WithoutRun;                      //起跑线标志位

static uint16 g_mid_x = 0;
static uint16 g_left_curve = 0;
static uint16 g_right_curve = 0;
static uint16 g_left_count = 0;
static uint16 g_right_count = 0;
static uint16 g_left_line[IMAGE_HEIGHT];
static uint16 g_right_line[IMAGE_HEIGHT];
static uint16 g_mid_line[IMAGE_HEIGHT];
static uint16 g_err_weight[IMAGE_HEIGHT] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   //111-120
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
static uint16 g_weight_sum = 0;
static uint16 x_conditon_left = 0;
static uint16 x_conditon_right = 0;
/**********************************************************/
