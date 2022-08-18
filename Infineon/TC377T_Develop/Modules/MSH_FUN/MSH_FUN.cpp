#include "MSH_FUN.h"
#include "Libraries.h"
#include "Modules.h"
//这里包含OJ_Library.h是因为需要用到里面的库，同时也包含了MSH_FUN.h
long LED_Test (void)
{
    LED led1 = LED(P20_8, Low_level_lighting);
    led1.Init();
    led1.Pin_Toggle();
    return 0;
}

long Car_Run_Test (void)
{
    //发车标志
    run_flag = 1;
    //工作信号灯初始化
    Sinal_Light_Init();
    platform_printf("工作信号灯已初始化\n");
    //屏幕初始化
    Screen_Init();
    platform_printf("屏幕已初始化\n");
    //摄像头初始化
    MT9V03x_Init();
    platform_printf("摄像头已初始化\n");
    //编码器初始化
    Encoder_Init();
    platform_printf("编码器已初始化\n");
    //电机初始化
    Motor_Init();
    platform_printf("电机已初始化\n");
    //舵机初始化
    Servo_Init();
    platform_printf("舵机已初始化\n");
    //PID初始化
    PID_Init();
    platform_printf("PID已初始化\n");
    //获取CDF表
    Get_CDF_Table();
    //获取总钻风摄像头配置信息
    MT9V03x_Get_Conf();
    //通过RT-Thread Finsh 显示总钻风摄像头所有信息
    MT9V03x_Show_Info();
    return 0;
}
