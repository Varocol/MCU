#include "Libraries.h"
/*
    ����time.h�к���,����RTC��Ŀ�����
    time():
        time()�����ڴ��ݿ�ָ����᷵�ص�ǰϵͳʱ���(��1970-1-1 00:00:00����������)ֵ,������ǿ�ָ��,����ֵ����ָ����ָ����ڴ�ռ䡣
    mktime():
        mktime()����ݴ����ʱ��ṹ�������ǰʱ���µ�ʱ���ֵ��
    asctime():
        asctime()����ݴ����ʱ��ṹ������һ����ʾʱ����ַ��������ء�
    clock():
        clock()���س���ִ����һ��Ϊ����Ŀ�ͷ����������ʱ����ʹ�õ�ʱ�䡣
    ctime():
        ���������ʱ�������һ����ʾʱ����ַ��������ء�
    difftime():
        ����ʱ��
    localtime():
        ���ݴ����ʱ������ص�ǰʱ���µ�ʱ��ṹ�塣
    gmtime():
        ���ݴ����ʱ�������GMTʱ���µ�ʱ��ṹ�塣
    strftime():
        ����ʱ��ṹ��,������ʽ������ַ�����

    �������Ե�֪time()��clock()�Լ�gmtime()��������û��ʵ�ʵ�ʵ�����,����Ҫ�ض�������������ʵ������STM32
    ƽ̨��
    ���Ժ������Щ�����������䡣
    ���������£�
    ����gmtime()�޷�����ʹ��֮�������Ķ�û�����⡣
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
    // ���ڳ�ʼ��
    USART_1.Init();
    // LED��ʼ��
    LED_1.Init();
    // RTC��ʼ��
    RTC_x.Init();
}
void Test()
{
    //����time()����
    printf("time():\n%llu\n", time(0));
    //����localtime()��mktime()����
    time(&timestamp);
    tm temp;
    printf("time()->localtime()->mktime():\n%llu\n", mktime(localtime(&timestamp)));
    //����asctime()����
    printf("asctime():\n%s\n", asctime(localtime(&timestamp)));
    //����clock()����
    clock_t start = clock();
    SysTick_Operate::Delay_ms(10000);
    clock_t end = clock();
    printf("start:\n%llu\n", start);
    printf("end:\n%llu\n", end);
    //����difftime()����
    printf("difftime():\n%f\n", difftime(end, start));
    //����ctime()����
    printf("ctime():\n%s\n", ctime(&timestamp));
    // temp = gmtime(&t);
    //����gmtime()����
    // if (temp != NULL)
    //     printf("gmtime():\n%s\n", asctime(temp));
    //����strftime()����
    strftime(timestr, sizeof(timestr) / sizeof(char), "%Y-%m-%d %H:%M:%S", localtime(&timestamp));
    printf("strftime():\n%s\n", timestr);
    while (1)
        ;
}
void End()
{
}