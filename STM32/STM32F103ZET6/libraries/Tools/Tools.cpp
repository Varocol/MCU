#include "Tools.h"

//计算两个年份之间的天数
uint32_t days_between_years(uint32_t year1, uint32_t year2)
{
    if (year1 > year2)
    {
        int tmp = year1;
        year1 = year2;
        year2 = tmp;
    }
    return (uint32_t)year2 * 365 + year2 / 4 + year2 / 400 - year2 / 100 - (year1 * 365 + year1 / 4 + year1 / 400 - year1 / 100);
}

//判断是否为闰年
uint8_t is_leapyear(uint32_t year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
    {
        return 1;
    }
    return 0;
}

//返回某年某月有几天
uint8_t days_in_months(uint32_t year, uint8_t month)
{
    int day;
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        day = 31;
        break;
    case 2:
        if (is_leapyear(year))
            day = 29;
        else
            day = 28;
        break;
    default:
        day = 30;
        break;
    }
    return day;
}