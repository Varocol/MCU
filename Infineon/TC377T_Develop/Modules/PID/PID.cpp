#include "PID.h"

//pid初始化
void PID_Init ()
{
    //左轮pid初始化
    Left_ctr.kp = 0.071f; //0.071f;   //0.071f
    Left_ctr.ki = 0.95f; //0.095f;    //0.95f
    Left_ctr.kd = 0.0f; //0.00f;

    //右轮pid初始化
    Right_ctr.kp = 0.071f; //0.071f;
    Right_ctr.ki = 0.95f; //0.095f;
    Right_ctr.kd = 0.0f; //0.00f;

    //左轮位置式pid初始化
    l_pid_location.val_target = 0;
    l_pid_location.error_now = 0;
    l_pid_location.error_last = 0;
    l_pid_location.integral = 0;
    l_pid_location.kp = 0;
    l_pid_location.ki = 0;
    l_pid_location.kd = 0;

    //右轮位置式p i d初始化
    r_pid_location.val_target = 0;
    r_pid_location.error_now = 0;
    r_pid_location.error_last = 0;
    r_pid_location.integral = 0;
    r_pid_location.kp = 0;
    r_pid_location.ki = 0;
    r_pid_location.kd = 0;

    //左轮速度pid初始化
    l_pid_speed.val_target = 0;
    l_pid_speed.error_now = 0;
    l_pid_speed.error_last = 0;
    l_pid_speed.integral = 0;
    l_pid_speed.kp = 0;
    l_pid_speed.ki = 0;
    l_pid_speed.kd = 0;

    //右轮速度pid初始化
    r_pid_speed.val_target = 0;
    r_pid_speed.error_now = 0;
    r_pid_speed.error_last = 0;
    r_pid_speed.integral = 0;
    r_pid_speed.kp = 0;
    r_pid_speed.ki = 0;
    r_pid_speed.kd = 0;

    //舵机pid初始化
    ServoTurn.val_target = 0;
    ServoTurn.error_now = 0;
    ServoTurn.error_last = 0;
    ServoTurn.integral = 0;
    ServoTurn.kp = 5.3;
    ServoTurn.ki = 0;
    ServoTurn.kd = 0.33;
    ServoTurn.kp_out = 0;
    ServoTurn.ki_out = 0;
    ServoTurn.kd_out = 0;
}

//左轮PID实现
void PID_Realize_L_Speed ()
{
    float k = 0.0;
    float Out_Max = 10000.0;
    float Out_Min = -10000.0;
    int IOut_Max = 8000;
    int IOut_Min = -8000;
    static float SP = 0.0; //实现参数隔离
    static float SI = 0.0;
    float SD = 0.0;
    static float L_POut;
    static float L_IOut;
    static float L_Wout;
    float L_DOut;
    static float L_last_real_speed;
    static float L_curr_real_speed;
    static float L_curr_speed_bias;
    static float L_last_speed_bias;
    static float L_last_targetspeed = 0;
    static float L_targetspeed = 0.0;

    if (stop_flag == 1 && run_flag == 1)
    {
        SP = 100 * Left_ctr.kp; //扩大参数保证迅速停车
        SI = 100 * Left_ctr.ki;
        L_targetspeed = 0.0;
        L_last_real_speed = L_curr_real_speed;
        L_curr_real_speed = Left_ctr.currspeed;
    }
    else
    {
        L_last_targetspeed = L_targetspeed;
        L_targetspeed = (float) Left_ctr.goalspeed;
        L_last_real_speed = L_curr_real_speed;
        L_curr_real_speed = (float) Left_ctr.currspeed;

        k = (L_targetspeed - L_curr_real_speed) / L_targetspeed;
        k = (k < 0 ? -k : k); //k的范围 0 - 1， 越接近预设速度，k越小
        SP = Left_ctr.kp * (1 + 5.5 * k);
        SI = Left_ctr.ki * (1 + 5.5 * k);
        if (k < 0.3) //当实际速度与预期速度比较接近时加入D
            SD = Left_ctr.kd;
        else
            SD = 0;
    }

    L_last_speed_bias = L_curr_speed_bias;
    L_curr_speed_bias = (L_targetspeed - L_curr_real_speed) * 0.1; //缩小误差，便于调参

    L_POut = SP * L_curr_speed_bias;

    /* if(L_last_targetspeed != L_targetspeed && k > 0.1) //第一次变速时，加快积分
     L_IOut = L_targetspeed * 9.0;
     else
     L_IOut += SI * L_curr_speed_bias;
     */

    if (k > 0.1) //加快积分
    {
        if (L_targetspeed >= 0) //当前速度 > 0
        {
            if (L_curr_real_speed < L_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                L_IOut += L_targetspeed * k * 3.1;
            else if (L_curr_real_speed > L_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                L_IOut -= L_targetspeed * k * 3.1;
        }
        else if (L_targetspeed < 0) //目标速度  < 0
        {
            if (L_curr_real_speed > L_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                L_IOut += L_targetspeed * k * 3.2;
            else if (L_curr_real_speed < L_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                L_IOut -= L_targetspeed * k * 3.2;
        }
    }
    else
        L_IOut += SI * L_curr_speed_bias;

    L_IOut = (L_IOut > IOut_Max ? IOut_Max : L_IOut);     //积分限幅，防止积分过饱和
    L_IOut = (L_IOut < IOut_Min ? IOut_Min : L_IOut);

    L_DOut = SD * (L_curr_speed_bias - L_last_speed_bias);

    Left_ctr.out = L_POut + L_IOut + L_DOut + L_Wout;

    Left_ctr.out = (Left_ctr.out > Out_Max ? Out_Max : Left_ctr.out);
    Left_ctr.out = (Left_ctr.out < Out_Min ? Out_Min : Left_ctr.out);
}

//右轮pid实现
void PID_Realize_R_Speed ()
{
    float k = 0.0;
    float Out_Max = 10000.0;
    float Out_Min = -10000.0;
    int IOut_Max = 8000;
    int IOut_Min = -8000;
    static float SP = 0.0;     //实现参数隔离
    static float SI = 0.0;
    static float SD = 0.0;
    static float R_POut;
    static float R_IOut;
    static float R_DOut;
    static float R_last_real_speed;
    static float R_curr_real_speed;
    static float R_curr_speed_bias;
    static float R_last_speed_bias;
    static float R_last_targetspeed = 0;
    static float R_targetspeed = 0.0;
    static float I_speed = 0.0;
    int Iout_flag = 0;

    if (stop_flag == 1 && run_flag == 1)
    {
        SP = 100 * Right_ctr.kp; //扩大参数保证迅速停车
        SI = 100 * Right_ctr.ki;
        R_targetspeed = 0.0;
        R_last_real_speed = R_curr_real_speed;
        R_curr_real_speed = (float) Right_ctr.currspeed;
    }
    else
    {
        R_last_targetspeed = R_targetspeed;
        R_targetspeed = (float) Right_ctr.goalspeed;
        R_last_real_speed = R_curr_real_speed;
        R_curr_real_speed = (float) Right_ctr.currspeed;

        k = (R_targetspeed - R_curr_real_speed) / R_targetspeed;
        k = (k < 0 ? -k : k); //k的范围 0 - 1， 越接近预设速度，k越小
        SP = Right_ctr.kp * (1 + 5.5 * k);
        SI = Right_ctr.ki * (1 + 5.1 * k);
        if (k < 0.3) //当实际速度与预期速度比较接近时加入D
            SD = Right_ctr.kd;
        else
            SD = 0;
    }

    R_last_speed_bias = R_curr_speed_bias;
    R_curr_speed_bias = (R_targetspeed - R_curr_real_speed) * 0.1; //缩小误差，便于调参

    R_POut = SP * R_curr_speed_bias;

    if (k > 0.1) //加快积分
    {
        if (R_targetspeed >= 0) //当前速度 > 0
        {
            if (R_curr_real_speed < R_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                R_IOut += R_targetspeed * k * 3;
            else if (R_curr_real_speed > R_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                R_IOut -= R_targetspeed * k * 3;
        }
        else if (R_targetspeed < 0) //目标速度  < 0
        {
            if (R_curr_real_speed > R_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                R_IOut += R_targetspeed * k * 3;
            else if (R_curr_real_speed < R_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                R_IOut -= R_targetspeed * k * 3;
        }
    }
    else
        R_IOut += SI * R_curr_speed_bias;

    R_IOut = (R_IOut > IOut_Max ? IOut_Max : R_IOut);     //积分限幅，防止积分过饱和
    R_IOut = (R_IOut < IOut_Min ? IOut_Min : R_IOut);

    R_DOut = SD * (R_curr_speed_bias - R_last_speed_bias);

    Right_ctr.out = R_POut + R_IOut + R_DOut;

    Right_ctr.out = (Right_ctr.out > Out_Max ? Out_Max : Right_ctr.out);
    Right_ctr.out = (Right_ctr.out < Out_Min ? Out_Min : Right_ctr.out);
}
//左轮pid实现
void pid_realize_l_speed ()
{
    float k = 0.0;
    float Out_Max = 10000.0;
    float Out_Min = -10000.0;
    int IOut_Max = 8000;
    int IOut_Min = -8000;
    static float SP = 0.0;     //实现参数隔离
    static float SI = 0.0;
    static float SD = 0.0;
    static float L_POut;
    static float L_IOut;
    static float L_DOut;
    static float L_last_real_speed;
    static float L_curr_real_speed;
    static float L_curr_speed_bias;
    static float L_last_speed_bias;
    static float L_last_targetspeed = 0;
    static float L_targetspeed = 0.0;
    static float II_speed = 0.0;
    int Iout_flag = 0;

    if (stop_flag == 1 && run_flag == 1)
    {
        SP = 100 * Right_ctr.kp; //扩大参数保证迅速停车
        SI = 100 * Right_ctr.ki;
        L_targetspeed = 0.0;
        L_last_real_speed = L_curr_real_speed;
        L_curr_real_speed = (float) Left_ctr.currspeed;
    }
    else
    {
        L_last_targetspeed = L_targetspeed;
        L_targetspeed = (float) Left_ctr.goalspeed;
        L_last_real_speed = L_curr_real_speed;
        L_curr_real_speed = (float) Left_ctr.currspeed;

        k = (L_targetspeed - L_curr_real_speed) / L_targetspeed;
        k = (k < 0 ? -k : k); //k的范围 0 - 1， 越接近预设速度，k越小
        SP = Right_ctr.kp * (1 + 5.5 * k);
        SI = Right_ctr.ki * (1 + 5.1 * k);
        if (k < 0.3) //当实际速度与预期速度比较接近时加入D
            SD = Right_ctr.kd;
        else
            SD = 0;
    }

    L_last_speed_bias = L_curr_speed_bias;
    L_curr_speed_bias = (L_targetspeed - L_curr_real_speed) * 0.1; //缩小误差，便于调参

    L_POut = SP * L_curr_speed_bias;

    if (k > 0.1) //加快积分
    {
        if (L_targetspeed >= 0) //当前速度 > 0
        {
            if (L_curr_real_speed < L_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                L_IOut += L_targetspeed * k * 3;
            else if (L_curr_real_speed > L_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                L_IOut -= L_targetspeed * k * 3;
        }
        else if (L_targetspeed < 0) //目标速度  < 0
        {
            if (L_curr_real_speed > L_targetspeed) //目标速度 > 实际速度，加速过程，加快积分
                L_IOut += L_targetspeed * k * 3;
            else if (L_curr_real_speed < L_targetspeed) //目标速度 < 实际速度，减速速过程，减小积分
                L_IOut -= L_targetspeed * k * 3;
        }
    }
    else
        L_IOut += SI * L_curr_speed_bias;

    L_IOut = (L_IOut > IOut_Max ? IOut_Max : L_IOut);     //积分限幅，防止积分过饱和
    L_IOut = (L_IOut < IOut_Min ? IOut_Min : L_IOut);

    L_DOut = SD * (L_curr_speed_bias - L_last_speed_bias);

    Left_ctr.out = L_POut + L_IOut + L_DOut;

    Left_ctr.out = (Left_ctr.out > Out_Max ? Out_Max : Left_ctr.out);
    Left_ctr.out = (Left_ctr.out < Out_Min ? Out_Min : Left_ctr.out);
}
