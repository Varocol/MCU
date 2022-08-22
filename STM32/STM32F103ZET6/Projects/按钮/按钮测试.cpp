#include "System.h"
#include "Button_Funs.h"
void Setup();
void Test();
void End();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    //��ʼ��ϵͳ
    system_init();
    //��ʼ����ť
    Key1.Init();
    //���ð�ť��������
    Key1.attachClick(Click1);
    Key1.attachDoubleClick(DoubleClick1);
    Key1.attachDuringLongPress(DuringLongPress1);
    Key1.attachLongPressStart(LongPressStart1);
    Key1.attachLongPressStop(LongPressStop1);
    Key1.attachMultiClick(MultiClick1);
}
void Test()
{
    while (1)
    {
        Key1.tick();
    }
}
void End()
{
}