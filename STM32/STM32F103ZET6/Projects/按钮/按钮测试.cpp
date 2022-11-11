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
    //初始化系统
    system_init();
    //初始化按钮
    Key1.Init();
    //设置按钮触发函数
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