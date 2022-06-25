#include "core0_main.h"

void core0_setup ()
{
    Buttons_Init();
}
void core0_loop ()
{
    Buttons_Tick();
}

