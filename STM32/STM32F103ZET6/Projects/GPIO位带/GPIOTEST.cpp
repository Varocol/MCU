#include "System.h"
int main()
{
    GPIO a = GPIO(PA7, GPIO_Mode_IPU);
    a.Init();
    a.Update(PA7);
    a.Update(PB12);
    PBout(12) = 1;
    while (1)
    {
        if (!PAin(7))
        {
            PBout(12) = 0;
        }
        else if (PAin(7))
        {
            PBout(12) = 1;
        }
    }
}