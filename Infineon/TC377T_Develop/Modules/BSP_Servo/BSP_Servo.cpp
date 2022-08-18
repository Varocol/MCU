#include "BSP_Servo.h"
Servo_Param Param = {ATOM0_CH1_P33_9, 50, 2.12, 0.92, 1.563, 1.320, 10000, 0};
Servo Servo;

//初始化时会根据舵机参数自动回中
void Servo_Init ()
{
    Servo.Set_Param(Param);
    Servo.Init();
    Mid_Angle = (Param.MAP_MIN + Param.MAP_MAX) / 2;
    //初始化时舵机会转向两侧检测角度是否合适
    Servo.Turn(Param.MAP_MIN);
    platform_delay_ms(500);
    Servo.Turn(Param.MAP_MAX);
    platform_delay_ms(500);
    //舵机回中
    Servo.Turn(Mid_Angle);
}

//获取CDF表
void Get_CDF_Table ()
{
#if 1 //0在30行
    for (int i = 0; i < 60; i++)
        CDFTable[i] = -0.00003 * i * i + 0.002 * i + 0.0785;
#endif

#if 0 //0在14行,b = 50
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = -0.0002 * i * i + 0.0058 * i + 0.0744;
#endif

#if 0 //0在14行
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = -0.00004 * i * i + 0.0011 * i + 0.0953;
#endif

#if 0 //0在11行
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = -0.00004 * i * i + 0.0008 * i + 0.099;
#endif

#if 0
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = -0.017 * i + 0.7549; //(15 - A:A)/22.5
#endif

#if 0
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = 0.0000005 * i * i * i - 0.004 * i * i + 0.0315 * i + 0.9394; //除以7.5
#endif

#if 0           //效果还行 2m
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00005* i * i * i - 0.0033 * i * i + 0.0214 * i + 0.9527; //除以8
#endif

#if 0
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00002* i * i * i - 0.0013 * i * i - 0.0047 * i + 0.9305; //除以13
#endif

#if 0
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00002* i * i * i - 0.0013 * i * i - 0.0013 * i + 0.9386; //除以13 + 0.5
#endif

#if 0
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00001* i * i * i - 0.001 * i * i + 0.0013 * i + 0.9524; //除以15 + 0.5
#endif

#if 0
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00001* i * i * i - 0.0014 * i * i + 0.0165 * i + 0.954; //(30 - A:A) / 10
#endif

#if 0           //归一化
  for(int i = 0; i <= 40; i++)
    CDFTable[i] = 0.00001* i * i * i - 0.0014 * i * i + 0.0165 * i + 0.954; //(20 - A:A) / 8,然后进行了归一化
#endif

#if 0
  for(int i = 0; i <= 30; i++)
    CDFTable[i] = -2.0 / 900.0 * i + 2.0 / 30.0; //(20 - A:A) / 8,然后进行了归一化
#endif

}

//获取中线偏差
void Get_Mid_Bias ()
{
    float k = 0.7;
    float index_add = 0.0;
    float Max = 0;
    float Min = 0;
    float Add = 0;
    static int index;
    static float bias_add_Filter[10];   //滤波用
    float bias_k[5] = {0.01647543, 0.06681116, 0.18161157, 0.330917856, 0.404183982};
    static float last_mid_bias_add;
    //初始化
    L_bias_add = 0;
    R_bias_add = 0;
    M_bias_add = 0;
    last_mid_bias_add = mid_bias_add;
    //计算偏差
    //  如果左边线存在，计算左边线偏差
    if (left_findflag)
    {
        for (int i = 1; i < L_edge_count; i++)
        {
            if (L_edge[i].row > 60)
                L_bias_add = L_bias_add
                        + (float) ((CDFTable[Image_H - L_edge[i].row])
                                * (1.0 * (L_edge[i].col - L_edge[1].col) * 100.0 / (L_edge[i].col + L_edge[1].col)));
        }
    }
    //  如果右边线存在，计算右边线偏差
    if (right_findflag)
    {
        for (int i = 1; i < R_edge_count; i++)
        {
            if (R_edge[i].row > 60)
                R_bias_add = R_bias_add
                        + (float) ((CDFTable[Image_H - R_edge[i].row])
                                * ((R_edge[i].col - R_edge[1].col) * 100.0 / (R_edge[i].col + R_edge[1].col)));
        }
    }
    //  计算中线偏差
    for (int i = 1; i < Mid_count; i++)
    {
        if (Mid_Line[i].row > 60)
            M_bias_add = M_bias_add
                    + (float) ((CDFTable[Image_H - Mid_Line[i].row])
                            * ((Mid_Line[i].col - Mid_Line[1].col) * 100.0 / (Mid_Line[i].col + Mid_Line[1].col)));
    }
    testx = M_bias_add;
    mid_bias_add = 0;

    //  计算中线与图像中线的偏差
    for (int i = 1; i < Mid_count; i++)
    {
        if (Mid_Line[i].row > 60)
            mid_bias_add = mid_bias_add
                    + (float) ((CDFTable[Image_H - Mid_Line[i].row])
                            * ((Mid_Line[i].col - Image_W / 2) * 100.0 / (Mid_Line[i].col + Image_W / 2)));
    }
    mid_bias_add = mid_bias_add + (1 - 1.0 * Mid_count / Image_H) * mid_bias_add;
    testx = mid_bias_add;
    //优化丢边界
    if (1)   //如果不是环岛 HuanDao_FLAG==0
    {
        if (left_findflag && !right_findflag)
            mid_bias_add = mid_bias_add + R_Drop_k * (L_bias_add + mid_bias_add) / 2;
        else if (!left_findflag && right_findflag)
            mid_bias_add = mid_bias_add + L_Drop_k * (R_bias_add + mid_bias_add) / 2;
    }
    //优化环岛转向
    //优化车库转向
    //优化坡道转向
    //滤波
    for (int i = 0; i < 4; i++)
        bias_add_Filter[i] = bias_add_Filter[i + 1];
    bias_add_Filter[4] = mid_bias_add;
    mid_bias_add = 0;
    for (int i = 0; i < 5; i++)  //高斯滤波
        mid_bias_add += (bias_k[i] * bias_add_Filter[i]);
    //限幅
    mid_bias_add = (mid_bias_add > Max_bias ? Max_bias : mid_bias_add);
    mid_bias_add = (mid_bias_add < Min_bias ? Min_bias : mid_bias_add);
}

//由图像中线偏差拟合半径并得到预期转向角速度
void MidBias_FitTurnR ()
{
    float bias = 0.0;
    int car_rel_speed = 0;

    if (0)  //如果入库 In_CheKu_flag!=0
        car_rel_speed = 400;
    else
        car_rel_speed = (Left_ctr.currspeed + Right_ctr.currspeed) / 2;

//    if(In_CheKu_R_DaSi_flag == 1) //入库右打死
//        mid_bias_add = R_In_CK_bias;
    bias = mid_bias_add / 10.0;

    if (bias < 0)
        Track_R = 1.0 / (-0.00003 * bias * bias - 0.0016 * bias);
    else if (bias > 0)
        Track_R = -1.0 / (-0.00003 * bias * bias + 0.0016 * bias);
    else
        Track_R = 99999;

    TargetTurnAngSpeed = GetTargetTurnAngleSpeed(car_rel_speed, Track_R);
}

//由车速和转向半径计算预期转向角速度
float GetTargetTurnAngleSpeed (float car_speed, float steer_R)
{
    int PMin_steerR = Min_SteerR;                                 //左转最小转向半径
    int NMin_steerR = -Min_SteerR;                                //右转最小转向半径
    float Max_carspeed = Max_Car_Speed;                             //最大车速 3.5m/s
    float Min_steerR = Min_SteerR;                                  //最小转向半径
    float PMax_SteerAngleSpeed = Max_carspeed / Min_steerR;         //左转最大转向角速度
    float NMax_SteerAngleSpeed = -PMax_SteerAngleSpeed;             //右转最大转向角速度
    float steer_anglespeed = 0.0;                                   //转向角速度
    //限幅
    if (steer_R > 0 && steer_R < PMin_steerR)
        steer_R = PMin_steerR;
    else if (steer_R < 0 && steer_R > NMin_steerR)
        steer_R = NMin_steerR;
    steer_anglespeed = car_speed / steer_R;
    //限幅
    steer_anglespeed = (steer_anglespeed > PMax_SteerAngleSpeed ? PMax_SteerAngleSpeed : steer_anglespeed);
    steer_anglespeed = (steer_anglespeed < NMax_SteerAngleSpeed ? NMax_SteerAngleSpeed : steer_anglespeed);

    return steer_anglespeed;
}

//舵机转向函数,范围为映射的最小值到最大值，根据上面参数给的对应的范围是0 ~ 100
void Servo_Control ()
{
    static float P_bias_k = 0.0;
    float bias;
    //    if(In_CheKu_flag!=0)
    //    {
    //        if 入库右打死标志为TRUE
    //            mid_bias_add = 入库固定打角值。
    //        if 入库直走标志为TRUE
    //            mid_biass_add = 0;
    //    }
    bias = -mid_bias_add;
    if (bias < 0)
        P_bias_k = -0.000005 * bias * bias - 0.0029 * bias + 0.6;
    else
        P_bias_k = -0.000005 * bias * bias + 0.0029 * bias + 0.6;
    ServoTurn.error_last = ServoTurn.error_now;
    ServoTurn.error_now = bias;

    ServoTurn.kp_out = 1.0 * ServoTurn.kp * ServoTurn.error_now / 10.0;
    ServoTurn.kd_out = 1.0 * ServoTurn.kd * (ServoTurn.error_now - ServoTurn.error_last);

    ServoTurn.last_out = ServoTurn.output_val;
    ServoTurn.output_val = (ServoTurn.kp_out + ServoTurn.kd_out);
    Servo.Turn(ServoTurn.output_val * 100 + Mid_Angle);
}

