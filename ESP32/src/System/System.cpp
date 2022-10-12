#include <System/System.h>
/**
 * @author  @Varocol
 * @brief   系统硬件初始化
 * @param   None
 * @return  None
 */
void Hardware_Init()
{
    Serial_Init();
    Button_Init();
    FingerPrint_Init();
    LoudSpeaker_Init();
    Screen_Init();
}
/**
 * @author  @Varocol
 * @brief   系统软件初始化
 * @param   None
 * @return  None
 */
void Software_Init()
{
    Store_Init();
}
/**
 * @author  @Varocol
 * @brief   工程菜单
 * @param   None
 * @return  None
 */
void System_Menu()
{
    PLATFORM_SERIAL.printf(
        "<------------工程菜单------------>\n"
        "%d.指纹录入\n"
        "%d.指纹搜索\n"
        "%d.指纹删除\n"
        "%d.指纹修改\n"
        "%d.指纹列表\n"
        "%d.指纹库清空\n"
        "%d.格式化SPIFFS文件系统\n",
        Enroll,
        Search,
        Delete,
        Alert,
        ShowList,
        ClearDB,
        Format);
    PLATFORM_SERIAL.println("请输入需要测试的功能:");
    switch (ReadOption().toInt())
    {
    case Enroll:
        FingerPrint_Enroll();
        break;
    case Search:
        FingerPrint_Search();
        break;
    case Delete:
        FingerPrint_Delete();
        break;
    case Alert:
        FingerPrint_Alert();
        break;
    case ShowList:
        FingerPrint_ShowList();
        break;
    case ClearDB:
        FingerPrint_ClearDB();
        break;
    case Format:
        Store_Format();
        break;
    default:
        System_NoOption();
        break;
    }
}
/**
 * @author  @Varocol
 * @brief   没有该功能
 * @param   None
 * @return  None
 */
void System_NoOption()
{
    PLATFORM_SERIAL.println("没有该功能");
}
/**
 * @author  @Varocol
 * @brief   文件系统格式化
 * @param   None
 * @return  None
 */
void Store_Init()
{
    PLATFORM_SERIAL.println("<-------------检测文件系统------------->");
    PLATFORM_SERIAL.print("打开SPIFFS");
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (!SPIFFS.begin() && time_limit)
    {
        PLATFORM_SERIAL.print("...");
        time_limit--;
    }
    PLATFORM_SERIAL.println();
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("SPIFFS无法打开");
    }
    else
    {
        PLATFORM_SERIAL.println("SPIFFS打开成功");
    }
    PLATFORM_SERIAL.println("<---------------------------------------->");
    SPIFFS.end();
}
/**
 * @author  @Varocol
 * @brief   文件系统格式化
 * @param   None
 * @return  None
 */
void Store_Format()
{
    PLATFORM_SERIAL.println("<-------------文件系统格式化------------->");
    //询问是否需要格式化
    PLATFORM_SERIAL.println("是否需要格式化?(y/n)");
    while (!PLATFORM_SERIAL.available())
        ;
    String option = ReadOption();
    if (option.length() == 1)
    {
        option.toLowerCase();
        switch (option[0])
        {
        case 'y':
            PLATFORM_SERIAL.println("正在执行格式化操作...");
            SPIFFS.format();
            break;
        default:
            PLATFORM_SERIAL.println("无法执行格式化操作...");
            break;
        }
    }
    PLATFORM_SERIAL.println("<---------------------------------------->");
}
