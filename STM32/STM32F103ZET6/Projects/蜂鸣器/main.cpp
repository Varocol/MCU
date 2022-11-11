#include "System.h"

struct beep_song test_song =
    {
        .Basicspeed = 80,
        .volume = 100 / 4,
        .tone = E,
        .name = "两只老虎",
        .data = {0x15, 0x02, 0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x15, 0x02,
                 0x16, 0x02, 0x17, 0x02, 0x15, 0x02, 0x17, 0x02, 0x18, 0x02,
                 0x19, 0x01, 0x17, 0x02, 0x18, 0x02, 0x19, 0x01, 0x19, 0x03,
                 0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02, 0x15, 0x16,
                 0x19, 0x03, 0x1A, 0x03, 0x19, 0x03, 0x18, 0x03, 0x17, 0x02,
                 0x15, 0x16, 0x15, 0x02, 0x0F, 0x02, 0x15, 0x01, 0x15, 0x02,
                 0x0F, 0x02, 0x15, 0x01, 0x00, 0x00}};

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
}
void Test()
{
    while (1)
    {
        Beep.Music(&test_song);
    }
}
void End()
{
}