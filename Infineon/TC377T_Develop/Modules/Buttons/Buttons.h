#ifndef __BUTTONS_H
#define __BUTTONS_H
#include "Libraries.h"
#include "Button_Function.h"
//TC377T��ťģ��
//����(��ť����˳��Ϊ��������)��
//      ��ť1
//      ���ţ�P22_0
//      ģʽ��activeLow (���´���)
//      ��������
//
//      ��ť2
//      ���ţ�P22_2
//      ģʽ��activeLow (���´���)
//      ��������
//
//      ��ť3
//      ���ţ�P22_1
//      ģʽ��activeLow (���´���)
//      ��������
//
//      ��ť4
//      ���ţ�P22_3
//      ģʽ��activeLow (���´���)
//      ��������

//��ť��ʼ��
void Buttons_Init ();
void Button1_Init ();
void Button2_Init ();
void Button3_Init ();
void Button4_Init ();
//��ť����
void Buttons_Tick ();
void Button1_Tick ();
void Button2_Tick ();
void Button3_Tick ();
void Button4_Tick ();

#endif /*__BUTTONS_H*/
