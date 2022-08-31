#include "System.h"
void Setup();
void Test();
void End();
void Show_Time();
void Alter_Time();
void Timestamp_To_Time();
void Time_To_Timestamp();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    //初始化系统
    system_init();
}
void Test()
{
    int option;
    while (1)
    {
        printf("-----------请选择需要进行的操作-----------\n");
        printf("1.显示系统时间                           \n");
        printf("2.修改系统时间                           \n");
        printf("3.UNIX时间戳转普通时间                   \n");
        printf("4.普通时间转UNIX时间戳                   \n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            Show_Time();
            break;
        case 2:
            Alter_Time();
            break;
        case 3:
            Timestamp_To_Time();
            break;
        case 4:
            Time_To_Timestamp();
            break;
        default:
            printf("输入的选项有误,请重新输入!\n");
            break;
        }
    }
}
void End()
{
}

void Show_Time()
{
    printf("-----------显示系统时间-----------\n");
    printf("按下Q返回菜单\n");
    RTC_x.ITConfig(RTC_IT_SEC, ENABLE);
    char c;
    while (1)
    {
        scanf("%c", &c);
        printf("%c\n", c);
        if (c == 'Q')
            break;
    }
    RTC_x.ITConfig(RTC_IT_SEC, DISABLE);
}
void Alter_Time()
{
    printf("-----------修改系统时间-----------\n");
    while (1)
    {
        printf("请输入年份(1970~2106):\n");
        scanf("%d", &timeinfo.tm_year);
        if (timeinfo.tm_year <= 2106 && timeinfo.tm_year >= 1970)
        {
            printf("%d\n", timeinfo.tm_year);
            timeinfo.tm_year -= 1900;
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入月份(1~12):\n");
        scanf("%d", &timeinfo.tm_mon);
        if (timeinfo.tm_mon <= 12 && timeinfo.tm_mon >= 1)
        {
            printf("%d\n", timeinfo.tm_mon);
            timeinfo.tm_mon -= 1;
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入日期:\n");
        scanf("%d", &timeinfo.tm_mday);
        if (timeinfo.tm_mday <= days_in_months(timeinfo.tm_year + 1900, timeinfo.tm_mon) && timeinfo.tm_mon >= 1)
        {
            printf("%d\n", timeinfo.tm_mday);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入小时(0~23):\n");
        scanf("%d", &timeinfo.tm_hour);
        if (timeinfo.tm_hour <= 23 && timeinfo.tm_hour >= 0)
        {
            printf("%d\n", timeinfo.tm_hour);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入分钟(0~59):\n");
        scanf("%d", &timeinfo.tm_min);
        if (timeinfo.tm_min <= 59 && timeinfo.tm_min >= 0)
        {
            printf("%d\n", timeinfo.tm_min);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入秒(0~59):\n");
        scanf("%d", &timeinfo.tm_sec);
        if (timeinfo.tm_sec <= 59 && timeinfo.tm_sec >= 0)
        {
            printf("%d\n", timeinfo.tm_sec);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    RTC_Operate::Set_Time(timeinfo);
    printf("修改成功!\n");
}
void Timestamp_To_Time()
{
    printf("-----------UNIX时间戳转普通时间-----------\n");
    printf("请输入UNIX时间戳:\n");
    scanf("%llu\n", &timestamp);
    _localtime_r(&timestamp, &timeinfo);
    strftime(timestr, sizeof(timestr) / sizeof(char), "%Y-%m-%d %H:%M:%S", &timeinfo);
    printf("Time:\n%s\n", timestr);
}
void Time_To_Timestamp()
{
    printf("-----------普通时间转UNIX时间戳-----------\n");
    while (1)
    {
        printf("请输入年份(1970~2106):\n");
        scanf("%d", &timeinfo.tm_year);
        if (timeinfo.tm_year <= 2106 && timeinfo.tm_year >= 1970)
        {
            printf("%d\n", timeinfo.tm_year);
            timeinfo.tm_year -= 1900;
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入月份(1~12):\n");
        scanf("%d", &timeinfo.tm_mon);
        if (timeinfo.tm_mon <= 12 && timeinfo.tm_mon >= 1)
        {
            printf("%d\n", timeinfo.tm_mon);
            timeinfo.tm_mon -= 1;
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入日期:\n");
        scanf("%d", &timeinfo.tm_mday);
        if (timeinfo.tm_mday <= days_in_months(timeinfo.tm_year + 1900, timeinfo.tm_mon) && timeinfo.tm_mon >= 1)
        {
            printf("%d\n", timeinfo.tm_mday);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入小时(0~23):\n");
        scanf("%d", &timeinfo.tm_hour);
        if (timeinfo.tm_hour <= 23 && timeinfo.tm_hour >= 0)
        {
            printf("%d\n", timeinfo.tm_hour);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入分钟(0~59):\n");
        scanf("%d", &timeinfo.tm_min);
        if (timeinfo.tm_min <= 59 && timeinfo.tm_min >= 0)
        {
            printf("%d\n", timeinfo.tm_min);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    while (1)
    {
        printf("请输入秒(0~59):\n");
        scanf("%d", &timeinfo.tm_sec);
        if (timeinfo.tm_sec <= 59 && timeinfo.tm_sec >= 0)
        {
            printf("%d\n", timeinfo.tm_sec);
            break;
        }
        printf("输入有误,请重新输入!\n");
    }
    printf("Timestamp:\n%llu\n", mktime(&timeinfo));
}
