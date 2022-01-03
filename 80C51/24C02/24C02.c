#include"24C02.h" 
#include"COM.h"
#include"delay.h"
uchar c[2];
void main()
{
      COM_init();
      LCD12864_init();
      AT24C02_Reset();
      AT24C02_Write_data(0xA0,0,'a');
      AT24C02_delay5ms();
      c[0]=AT24C02_Read_data(0xA0,0);
      c[1]='\0';    
      LCD12864_showstring(c,0,0);
      while(1)
      {
            COM_send(c);
            delay1ms(1000);
      }
}
