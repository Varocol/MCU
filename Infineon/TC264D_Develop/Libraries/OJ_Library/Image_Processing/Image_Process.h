#ifndef __OJ_IMAGE_PROCESS_H
#define __OJ_IMAGE_PROCESS_H
#define Pixel(Output,i,j) *(Output + i*col + j)
#include "headfile.h"

//图像处理约定参数
//规定灰度值范围0~255
#define Gray_Max 0xff
#define Gray_Min 0

//图像处理类：Digital Image Processing Class
class DIP
{
    private:
    public:
        static void Grayscale_Identity (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Reverse (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Logarithm (uint8*, uint8*, uint16, uint16);
        static void Grayscale_Pow (double, uint8*, uint8*, uint16, uint16);
        static void Grayscale_Equalization(uint8*, uint8*, uint16, uint16);
};

#endif /*__OJ_IMAGE_PROCESS_H*/
