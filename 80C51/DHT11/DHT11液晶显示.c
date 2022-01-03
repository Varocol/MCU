#include"DHT11液晶显示.h"
void main()
{
    LCD12864_init();
    DHT11_init();         //lcd12864一定要在前面否则会打断DHT11的时序
    if(!flag)
    {
        
        byte1=DHT11_readbyte();
        byte2=DHT11_readbyte();
        byte3=DHT11_readbyte();
        byte4=DHT11_readbyte();
        byte5=DHT11_readbyte();
        LCD12864_showstring("初始化成功！",0,1);
        DHT11_check();
        if(flag)
        {
            LCD12864_showstring("校验成功！",1,1);

            LCD12864_showstring("温度",2,0);
            LCD12864_showstring(DHT11_string(byte3,byte4),2,2);
            LCD12864_showstring("℃",2,5);
              
            LCD12864_showstring("湿度",3,0);
            LCD12864_showstring(DHT11_string(byte1,byte2),3,2);
            LCD12864_showstring("％",3,5);
        }
        else
        {
            LCD12864_showstring("校验失败！",1,2);
        }  
    }
    DHT11_delay1s();
}