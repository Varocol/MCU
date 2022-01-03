//由于该硬件已配置中断函数，所以不好封装，只对其重写
#ifndef __OJ_MT9V03X_H
#define __OJ_MT9V03X_H
#include "OJ_Library.h"
#include "headfile.h"

//获取总钻风摄像头配置信息
void MT9V03x_Get_Conf ();
//获取总钻风版本号
uint16 MT9V03x_Get_Version ();
//设置总钻风配置信息
void MT9V03x_Set_Conf ();
//设置总钻风曝光时间
void MT9V03x_Set_exposure_time (uint16 light);
//通过RT-Thread Finsh 显示总钻风摄像头配置信息,cpu1,cpu2无法使用
void MT9V03x_Show_Conf ();
//通过RT-Thread Finsh 显示总钻风摄像头所有信息,cpu1,cpu2无法使用
void MT9V03x_Show_Info ();
//总钻风初始化
void MT9V03x_Init ();
//发送一帧图像至上位机
void MT9V03x_Sendimg_To_PC (uint8 *image, uint16 width, uint16 height);
//发送一帧图像至IPS114屏幕
void MT9V03x_Sendimg_To_IPS114 (IPS_114 &Screen, uint8 *image, uint16 width, uint16 height);
//判断缓冲区是否有图像
bool MT9V03x_IMG_Complete ();
//标志位清零
void MT9V03x_Clear_Flag ();

#endif  /*__OJ_MT9V03X_H*/
