//主文件用来组装不同模块
#include"DS18B20.h"

void main()
{
    //读取数据并处理的过程
    COM_init();
    DS18B20_init();
    DS18B20_write(0xcc);
    DS18B20_write(0x4e);//WRITE SCRATCHPAD
    DS18B20_write(0x14);//TL 20℃
    DS18B20_write(0x1e);//TH 30℃
    DS18B20_write(bit11);//9位精度
    DS18B20_init();
    DS18B20_write(0xcc);//SKIPROM
    DS18B20_write(0x44);//CONVERT T
    DS18B20_delay750ms();//最多需要750ms
    DS18B20_init();
    DS18B20_write(0xcc);
    DS18B20_write(0xbe);//读scratchpad
    LS=DS18B20_read();
    MS=DS18B20_read();
    TEMP_convert();
    //发送数据到电脑
    COM_send("当前温度是:");
    COM_send(DS18B20_string(temp));
    COM_send("℃\n");
    pause();
}