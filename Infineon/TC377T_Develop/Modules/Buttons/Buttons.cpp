#include "Buttons.h"
Button Button1;
Button Button2;
Button Button3;
Button Button4;
//��ť��ʼ��
void Buttons_Init ()
{
    Button1_Init();
    Button2_Init();
    Button3_Init();
    Button4_Init();
}

void Button1_Init ()
{
    //��ť1���ò���
    Button1.Set_Param(P22_0);
    //��ť1��ʼ��
    Button1.Init();
    //��ť1���Ӻ���
    Button1.attachClick(Button1_Click1);
    Button1.attachDoubleClick(Button1_DoubleClick1);
    Button1.attachDuringLongPress(Button1_DuringLongPress1);
    Button1.attachLongPressStart(Button1_LongPressStart1);
    Button1.attachLongPressStop(Button1_LongPressStop1);
    Button1.attachMultiClick(Button1_MultiClick1);
}
void Button2_Init ()
{
    //��ť2���ò���
    Button2.Set_Param(P22_2);
    //��ť2��ʼ��
    Button2.Init();
    //��ť2���Ӻ���
    Button2.attachClick(Button2_Click1);
    Button2.attachDoubleClick(Button2_DoubleClick1);
    Button2.attachDuringLongPress(Button2_DuringLongPress1);
    Button2.attachLongPressStart(Button2_LongPressStart1);
    Button2.attachLongPressStop(Button2_LongPressStop1);
    Button2.attachMultiClick(Button2_MultiClick1);
}
void Button3_Init ()
{
    //��ť3���ò���
    Button3.Set_Param(P22_1);
    //��ť3��ʼ��
    Button3.Init();
    //��ť3���Ӻ���
    Button3.attachClick(Button3_Click1);
    Button3.attachDoubleClick(Button3_DoubleClick1);
    Button3.attachDuringLongPress(Button3_DuringLongPress1);
    Button3.attachLongPressStart(Button3_LongPressStart1);
    Button3.attachLongPressStop(Button3_LongPressStop1);
    Button3.attachMultiClick(Button3_MultiClick1);
}
void Button4_Init ()
{
    //��ť4���ò���
    Button4.Set_Param(P22_3);
    //��ť4��ʼ��
    Button4.Init();
    //��ť4���Ӻ���
    Button4.attachClick(Button4_Click1);
    Button4.attachDoubleClick(Button4_DoubleClick1);
    Button4.attachDuringLongPress(Button4_DuringLongPress1);
    Button4.attachLongPressStart(Button4_LongPressStart1);
    Button4.attachLongPressStop(Button4_LongPressStop1);
    Button4.attachMultiClick(Button4_MultiClick1);
}
//���а�ť���к���
void Buttons_Tick ()
{
    Button1_Tick();
    Button2_Tick();
    Button3_Tick();
    Button4_Tick();
}
//��ť1���к���
void Button1_Tick ()
{
    Button1.tick();
}
//��ť2���к���
void Button2_Tick ()
{
    Button2.tick();
}
//��ť3���к���
void Button3_Tick ()
{
    Button3.tick();
}
//��ť4���к���
void Button4_Tick ()
{
    Button4.tick();
}
