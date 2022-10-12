#include "System.h"
/*
    测试独立模式
        扫描
        规则触发 (软件触发)
        注入触发 (软件触发)
        规则间断
        注入间断
        自动注入
        连续转换
        看门狗
        内部温度
        DMA

*/

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
    system_init();
    ADC_1.Init();
}
void Test()
{
}
void End()
{
}