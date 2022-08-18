#include "Libraries.h"
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
    LED_1.Init();
    LED_2.Init();
    LED_3.Init();
}
void Test()
{

}
void End()
{
    
}