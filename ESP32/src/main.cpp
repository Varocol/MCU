#include <System/System.h>

void setup()
{
  //门禁硬件初始化
  Hardware_Init();
  Software_Init();
}

void loop()
{
  System_Menu();
  delay(1);
}