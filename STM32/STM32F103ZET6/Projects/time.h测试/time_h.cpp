#include "Libraries.h"
/*
    测试time.h中函数,用于RTC类的开发。
    time():
        time()函数内传递空指针则会返回当前系统时间戳(自1970-1-1 00:00:00经过的秒数)值,如果不是空指针,则会把值赋给指针所指向的内存空间。
    mktime():
        mktime()会根据传入的时间结构体算出当前时区下的时间戳值。
    asctime():
        asctime()会根据传入的时间结构体生成一个显示时间的字符串并返回。
    clock():
        clock()返回程序执行起（一般为程序的开头），处理器时钟所使用的时间。
    ctime():
        根据输入的时间戳生成一个显示时间的字符串并返回。
    difftime():
        返回时间差。
    localtime():
        根据传入的时间戳返回当前时区下的时间结构体。
    gmtime():
        根据传入的时间戳返回GMT时区下的时间结构体。
    strftime():
        传入时间结构体,传出格式化后的字符串。

    经过测试得知time()、clock()以及gmtime()三个函数没有实际的实体可用,即需要重定向三个函数以实现适配STM32
    平台。
    所以后面对这些函数进行适配。
    适配结果如下：
    除了gmtime()无法正常使用之外其他的都没有问题。
*/
void Setup();
void Test();
void End();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    // 串口初始化
    USART_1.Init();
    // LED初始化
    LED_1.Init();
    // RTC初始化
    RTC_x.Init();
}
void Test()
{
    //测试time()函数
    printf("time():\n%llu\n", time(0));
    //测试localtime()、mktime()函数
    time(&timestamp);
    tm temp;
    printf("time()->localtime()->mktime():\n%llu\n", mktime(localtime(&timestamp)));
    //测试asctime()函数
    printf("asctime():\n%s\n", asctime(localtime(&timestamp)));
    //测试clock()函数
    clock_t start = clock();
    SysTick_Operate::Delay_ms(10000);
    clock_t end = clock();
    printf("start:\n%llu\n", start);
    printf("end:\n%llu\n", end);
    //测试difftime()函数
    printf("difftime():\n%f\n", difftime(end, start));
    //测试ctime()函数
    printf("ctime():\n%s\n", ctime(&timestamp));
    // temp = gmtime(&t);
    //测试gmtime()函数
    // if (temp != NULL)
    //     printf("gmtime():\n%s\n", asctime(temp));
    //测试strftime()函数
    strftime(timestr, sizeof(timestr) / sizeof(char), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    printf("strftime():\n%s\n", timestr);
    while (1)
        ;
}
void End()
{
}