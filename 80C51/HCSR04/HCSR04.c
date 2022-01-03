#include"12864libs.h"
#include"HCSR04.h"
#include"string.h"
#include"delay.h"
uchar str[21];
void init();
void main()
{
     init();
     while(1)
     {
         HCSR04_init();
         HCSR04_distance();
         String_numtostring(S,str);
         LCD12864_showstring("µ±«∞æ‡¿Î(CM)",0,1);
         String_mergestring(str,"CM  ",String_strlen(str),String_strlen("CM  "),str);
         LCD12864_showstring(str,1,3);
         delay1ms(500);
     }
}
void init()
{
     LCD12864_init();
     HCSR04_timerset();
}