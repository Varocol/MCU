#include<REG52.H>
#include"12864libs.h"
uchar  code str1[]=
{
0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFE,0x00,0x00,0x00,0x00/*"��"*/
};
uchar code str2[]=
{
0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x11,0x00,0x11,0xF8,
0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11,0x00,0xFF,0xFE,0x00,0x00/*"��"*/
};
void main()
{
     LCD12864_init();
     //LCD12864_SET_CGRAM(0,str1);
     //LCD12864_SET_CGRAM(1,str2);
     LCD12864_display_CGRAM(0,0,0);
     LCD12864_display_CGRAM(1,0,1);
}