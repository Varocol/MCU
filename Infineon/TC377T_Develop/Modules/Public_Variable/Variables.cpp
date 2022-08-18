#include "Variables.h"
//��ʾ֡������ı���
uint32 start, end;

int Test = 5;

/*********ͼ����ȡ��س�ʼ��**********/
volatile uint16 Image_Use[RowMax][ColumnMax];           //ѹ����ͼ������
volatile uint32 Pixel[RowMax][ColumnMax];       //��ֵ��������OLED��ʾ������//
volatile uint16 Image_Sobel[RowMax][ColumnMax];         //Sobelͼ������

/*********ͼ������س�ʼ��**********/
int16 Threshold;
int16 FilterThreshold = 225;
int16 Camera_scan_finish = 0;
const int Width[RowMax + 1] =                      //ͼ��ÿ��ֱ����Ӧ�п� ///��ͷ���Ƹ߶Ⱥ�����п�ҲҪ����Ӧ�ĸı䣬Ҳ����˵������Ҫ�ֶ����¡�
        {
        /* 0 */1, 1, 1, 1, 1, 1, 1, 2, 3, 3,
        /* 1 */10, 10, 10, 10, 16, 17, 17, 19, 29, 31,
        /* 2 */33, 35, 37, 39, 41, 42, 44, 46, 48, 50,
        /* 3 */52, 54, 56, 57, 58, 60, 62, 63, 65, 66,
        /* 4 */67, 69, 70, 71, 72, 73, 75, 75, 77, 77,
        /* 5 */79, 79, 80, 81, 82, 82, 82, 82, 82, 82, 88};

float Weight[60] =                               //������Ȩ�أ��������ѹ��,���������
        {
        /* 0 */0.1, 0.2, 0.3, 0.4, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5,
        /* 1 */0.6, 0.7, 0.8, 0.9, 1.0, 1.2, 1.2, 1.4, 1.4, 1.5,
        /* 2 */1.8, 2.0, 2.1, 2.3, 2.5, 2.6, 2.8, 2.9, 3.0, 3.2,
        /* 3 */3.4, 3.6, 3.8, 4.0, 4.2, 4.3, 4.4, 4.2, 4.0, 3.8,
        /* 4 */3.6, 3.4, 3.2, 3.0, 2.8, 2.6, 2.4, 2.2, 2.0, 1.8,
        /* 5 */1.6, 1.6, 1.5, 1.5, 1.4, 1.4, 1.2, 1.2, 1.0, 0.8};

float AverageCenter = 0;                        //��һ������ֵ
float LastAverageCenter = 0;                    //��һ������
int16 LastAverageError[5] = {0};               //����ƫ���
int16 LeftLose = 0;                     //����������
int16 RightLose = 0;                     //���Ҷ�������
int16 AllLose = 0;                     //����ȫ������������ʮ�֣�
int16 WhiteLose = 0;                     //����ȫ��������������ʧ������
int16 LeftLoseStart = 0;                     //��¼��߶��ߵĿ�ʼ��
int16 RightLoseStart = 0;                     //��¼�ұ߱߶��ߵĿ�ʼ��
int16 WhiteLoseStart = 0;                     //��¼ȫ�����ߵĿ�ʼ��
int16 FirstLoseAllLine = 0;                     //ȫ���׿�ʼ��///�����ʼ����Ҫ���¶���
int16 LastLoseAllLine = 0;                      //ȫ���׽�����
int16 StartLineCount = 0;                     //�����߼�����
int16 LastLine = 0;                           //ɨ�����һ��,��̬ǰհ
int16 AvaliableLines = 0;                     //ɨ����Ч����
int16 SearchErrorFlag = 0;

int Foresight = 0;                   //ǰհ
int Last_Foresight = 0;                   //��һ��ǰհ
int16 Fictitious_Num = 0;                   //����ֱ�������ȡ��ƫ��
int Track_ImgCount = 0;                   //�����жϼ������
int Track_Type = 0;                   //��������

uint32 MiddleLine[RowMax + 1];                    //���ߴ������
uint32 RightEdge[RowMax + 1];                     //�ұ��ߴ����
uint32 LeftEdge[RowMax + 1];                  //����ߴ������
uint32 RealWidth[RowMax + 1];                 //����ʵ�ʿ��
uint32 Left_Add_Line[RowMax + 1];             //���ߴ������
uint32 Right_Add_Line[RowMax + 1];                //�Ҳ��ߴ������
uint32 Left_Add_Flag[RowMax];                   //���߱�־λ
uint32 Right_Add_Flag[RowMax];                  //�Ҳ��߱�־λ
uint32 Width_Add[RowMax + 1];                  ///uint32 Width_Add[RowMax];//���߿������
uint32 Width_Min;                               //������С���
int16 Line_Count;                           //��¼�ɹ�ʶ�𵽵���������
uint32 Left_Add_Start = 0;                      //������ʼ
uint32 Left_Add_Stop = 0;                       //���߽�����
uint32 Right_Add_Start = 0;                 //�Ҳ�����ʼ
uint32 Right_Add_Stop = 0;                      //�Ҳ��߽�����
float Left_Ka = 0, Right_Ka = 0;            //��С���˷�����
float Left_Kb = 1, Right_Kb = ColumnMax - 1;

/*********��ֹ����ȡ������ʼ��**********/
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

/*********ʮ�ִ��������ʼ��**********/
unsigned char CrossFlag = 0;                  //ʮ�ֱ�־
unsigned char LastCrossFlag = 0;
unsigned char LastLastCrossFlag = 0;
unsigned char CrossNumber = 0;
unsigned char LoseCrossNumber = 0;
unsigned char CrossEnterFlag = 0;
float CrossKL = 0, CrossKR = 0;

/*********�������������ʼ��**********/
float Cirlce_Angle = 0.0;               //�����Ƕ�
float CircleDistance = 0.0;
float OutCircleDistance = 0.0;
int16 RightOvalFlag = 0;
int16 LeftOvalFlag = 0;
int16 LeftCircleFlag = 0;             //�󻷵�ʶ���־λ
int16 RightCircleFlag = 0;            //�һ���ʶ���־λ
int16 DrawOvalFlag = 0;                 //��������־
int16 SalationFlag = 0;
int16 LLSalationLine = 0;             //�������������ʼ��
int16 LRSalationLine = 0;             //�������������ʼ��
int16 RLSalationLine = 0;             //�ұ�����������ʼ��
int16 RRSalationLine = 0;             //�ұ�����������ʼ��

int16 Onlyonce = 1;             ///�Լӱ���

/*********��·������ʼ��**********/
float StationAngle = 0.0;
int StationLineNum = 0;
extern int16 LeftWheelSpeed;
//extern int16 RightWheelSpeed;

/*********����·����**********/
///
unsigned char Road_widening = 0;

unsigned char Road_vanish = 0;

int16 spurroadtriangle_i = 0;

int16 spurroadtriangle_j = 0;

int16 left_right_lost_i = 0;                      ///����ȫ��������

unsigned char SpurroadFlag = 0;                  //����ڱ�־

unsigned char LastSpurroadFlag = 0;

unsigned char LastLastSpurroadFlag = 0;

float SpurroadKL = 0, SpurroadKR = 0;

/*********����������ʼ��**********/
int StartFlag = WithoutRun;                      //�����߱�־λ

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
