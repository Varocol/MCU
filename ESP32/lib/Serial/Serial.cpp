#include <Serial.h>
/**
 * @author  @Varocol
 * @brief   串口初始化
 * @param   None
 * @return  None
 */
void Serial_Init()
{
    PLATFORM_SERIAL.begin(serial_param.Baudrate);
}
/**
 * @author  @Varocol
 * @brief   读取菜单选项
 * @param   None
 * @return  菜单选项
 */
String ReadOption()
{
    while (!PLATFORM_SERIAL.available())
    {
        delay(1);
    }
    String data = PLATFORM_SERIAL.readString();
    PLATFORM_SERIAL.println(data);
    return data;
}
