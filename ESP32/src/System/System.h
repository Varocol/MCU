#ifndef __SYSTEM_H
#define __SYSTEM_H
#include <Libraries.h>
#include <System/Admin.h>
#include <System/User.h>
typedef enum
{
    Enroll = 1,
    Search,
    Delete,
    Alert,
    ShowList,
    ClearDB,
    Format
} System_Menu_Options;

void Hardware_Init();
void Software_Init();
void System_Menu();
void System_NoOption();
void Store_Format();
void Store_Init();
#endif /*__SYSTEM_H*/