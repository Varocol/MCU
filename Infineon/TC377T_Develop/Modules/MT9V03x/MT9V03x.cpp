#include "MT9V03x.h"

//获取总钻风摄像头配置信息
void MT9V03x_Get_Conf ()
{
    get_config(MT9V03X_COF_UART, GET_CFG);
}

//获取总钻风版本号
uint16 MT9V03x_Get_Version ()
{
    //获取配置
    return get_version(MT9V03X_COF_UART);
}

//设置总钻风配置信息
void MT9V03x_Set_Conf ()
{
    set_config(MT9V03X_COF_UART, MT9V03X_CFG);
}

//设置总钻风曝光时间
void MT9V03x_Set_exposure_time (uint16 light)
{
    set_exposure_time(MT9V03X_COF_UART, light);
}

//通过RT-Thread Finsh 显示总钻风摄像头配置信息(cpu1,cpu2无法使用)
void MT9V03x_Show_Conf ()
{
    platform_printf("\n");
    platform_printf("***********摄像头配置信息***********\n");
    platform_printf("自动曝光：               \t%d\n", GET_CFG[0][1]);
    platform_printf("曝光时间：               \t%d\n", GET_CFG[1][1]);
    platform_printf("图像帧率：               \t%d\n", GET_CFG[2][1]);
    platform_printf("图像列数量：           \t%d\n", GET_CFG[3][1]);
    platform_printf("图像行数量：           \t%d\n", GET_CFG[4][1]);
    platform_printf("图像左右偏移量：    \t%d\n", GET_CFG[5][1]);
    platform_printf("图像上下偏移量：    \t%d\n", GET_CFG[6][1]);
    platform_printf("图像增益：               \t%d\n", GET_CFG[7][1]);
    platform_printf("摄像头是否初始化:：\t%s\n", MT9V03X_CFG[8][1] ? "是" : "否");
}

//通过RT-Thread Finsh 显示总钻风摄像头所有信息(输出格式已经过对齐,请勿改动,cpu1,cpu2无法使用)
void MT9V03x_Show_Info ()
{
    //显示总钻风固件版本
    platform_printf("\n");
    platform_printf("总钻风固件版本：\t%d\n", MT9V03x_Get_Version());
    //显示总钻风引脚配置
    platform_printf("\n");
    platform_printf("***********引脚配置信息***********\n");
    platform_printf("串口：                 \tUART0\n");
    platform_printf("UART TX：            \tP02_2\n");
    platform_printf("UART RX：            \tP02_3\n");
    platform_printf("场中断引脚：          \tP02_0\n");
    platform_printf("D0引脚：               \tP02_0\n");
    platform_printf("像素时钟引脚：         \tP02_1\n");
    platform_printf("DMA通道：              \tDMA5\n");
    //显示总钻风摄像头配置信息
    platform_printf("\n");
    platform_printf("***********摄像头配置信息***********\n");
    platform_printf("自动曝光：              \t%d\n", GET_CFG[0][1]);
    platform_printf("曝光时间：              \t%d\n", GET_CFG[1][1]);
    platform_printf("图像帧率：              \t%d\n", GET_CFG[2][1]);
    platform_printf("图像列数量：          \t%d\n", GET_CFG[3][1]);
    platform_printf("图像行数量：          \t%d\n", GET_CFG[4][1]);
    platform_printf("图像左右偏移量：        \t%d\n", GET_CFG[5][1]);
    platform_printf("图像上下偏移量：        \t%d\n", GET_CFG[6][1]);
    platform_printf("图像增益：              \t%d\n", GET_CFG[7][1]);
    platform_printf("摄像头是否初始化：       \t%s\n", MT9V03X_CFG[8][1] ? "是" : "否");
    //显示总钻风摄像头指令列表
    platform_printf("\n");
    platform_printf("***********摄像头指令列表***********\n");
    platform_printf("摄像头初始化命令：       \t%d\n", INIT);
    platform_printf("自动曝光命令：              \t%d\n", AUTO_EXP);
    platform_printf("曝光时间命令：              \t%d\n", EXP_TIME);
    platform_printf("摄像头帧率命令：          \t%d\n", FPS);
    platform_printf("图像列命令：          \t%d\n", SET_COL);
    platform_printf("图像行命令：          \t%d\n", SET_ROW);
    platform_printf("图像左右偏移命令：       \t%d\n", LR_OFFSET);
    platform_printf("图像上下偏移命令：       \t%d\n", UD_OFFSET);
    platform_printf("图像偏移命令：              \t%d\n", GAIN);
    platform_printf("单独设置曝光时间命令：     \t%d\n", SET_EXP_TIME);
    platform_printf("获取摄像头配置命令：   \t%d\n", GET_STATUS);
    platform_printf("固件版本号命令：          \t%d\n", GET_VERSION);
    platform_printf("寄存器地址命令：          \t%d\n", SET_ADDR);
    platform_printf("寄存器数据命令：          \t%d\n", SET_DATA);
}

//总钻风初始化
void MT9V03x_Init ()
{
    mt9v03x_init();
}

//发送一帧图像至上位机
void MT9V03x_Sendimg_To_PC (uint8 *image, uint16 width, uint16 height)
{
    seekfree_sendimg_03x(MT9V03X_COF_UART, image, width, height);
}

//判断缓冲区是否有图像
bool MT9V03x_IMG_Complete ()
{
    return mt9v03x_finish_flag;
}

//清除标志位
void MT9V03x_Clear_Flag ()
{
    mt9v03x_finish_flag = 0;
}
