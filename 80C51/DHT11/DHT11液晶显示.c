#include"DHT11Һ����ʾ.h"
void main()
{
    LCD12864_init();
    DHT11_init();         //lcd12864һ��Ҫ��ǰ��������DHT11��ʱ��
    if(!flag)
    {
        
        byte1=DHT11_readbyte();
        byte2=DHT11_readbyte();
        byte3=DHT11_readbyte();
        byte4=DHT11_readbyte();
        byte5=DHT11_readbyte();
        LCD12864_showstring("��ʼ���ɹ���",0,1);
        DHT11_check();
        if(flag)
        {
            LCD12864_showstring("У��ɹ���",1,1);

            LCD12864_showstring("�¶�",2,0);
            LCD12864_showstring(DHT11_string(byte3,byte4),2,2);
            LCD12864_showstring("��",2,5);
              
            LCD12864_showstring("ʪ��",3,0);
            LCD12864_showstring(DHT11_string(byte1,byte2),3,2);
            LCD12864_showstring("��",3,5);
        }
        else
        {
            LCD12864_showstring("У��ʧ�ܣ�",1,2);
        }  
    }
    DHT11_delay1s();
}