//���ļ�������װ��ͬģ��
#include"DS18B20.h"

void main()
{
    //��ȡ���ݲ�����Ĺ���
    COM_init();
    DS18B20_init();
    DS18B20_write(0xcc);
    DS18B20_write(0x4e);//WRITE SCRATCHPAD
    DS18B20_write(0x14);//TL 20��
    DS18B20_write(0x1e);//TH 30��
    DS18B20_write(bit11);//9λ����
    DS18B20_init();
    DS18B20_write(0xcc);//SKIPROM
    DS18B20_write(0x44);//CONVERT T
    DS18B20_delay750ms();//�����Ҫ750ms
    DS18B20_init();
    DS18B20_write(0xcc);
    DS18B20_write(0xbe);//��scratchpad
    LS=DS18B20_read();
    MS=DS18B20_read();
    TEMP_convert();
    //�������ݵ�����
    COM_send("��ǰ�¶���:");
    COM_send(DS18B20_string(temp));
    COM_send("��\n");
    pause();
}