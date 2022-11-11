#ifndef __OJ_DEBUG_H
#define __OJ_DEBUG_H
#include "stdio.h"
//用于调试
#define DEBUG_OUT_PUT 1
#define DEBUG_ERROR_INFO(fmt, ...) \
    if (DEBUG_OUT_PUT)             \
    printf("<--- ERROR INFO --->\nFILE: [%s]\nLINE: [%d]\n<--- ERROR MESSAGE --->\n" fmt " \n", __FILE__, __LINE__, ##__VA_ARGS__)
#define DEBUG_MESSAGE_INFO(fmt, ...) \
    if (DEBUG_OUT_PUT)               \
    printf("<--- MESSAGE INFO --->\nFILE: [%s]\nLINE: [%d]\n<--- ERROR MESSAGE --->\n" fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#endif /*__OJ_DEBUG_H*/
