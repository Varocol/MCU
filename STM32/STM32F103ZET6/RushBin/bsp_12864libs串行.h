#ifndef __BSP_12864LIBS_CHUAN_H
#define __BSP_12864LIBS_CHUAN_H
#ifndef uchar
#define uchar uint8_t
#endif
#ifndef uint
#define uint uint16_t
#endif
#include "bsp_conf.h"
#define  LCD12864_GPIO_CS_PORT  GPIOB
#define  LCD12864_GPIO_SID_PORT GPIOB
#define  LCD12864_GPIO_SCK_PORT GPIOB
#define  LCD12864_GPIO_BASE     GPIOB_BASE
#define  GPIO_ODR_Addr          (LCD12864_GPIO_BASE + 12)
#define  GPIO_IDR_Addr          (LCD12864_GPIO_BASE + 8)
#define  LCD_CS_PIN             GPIO_Pin_7
#define  LCD_SID_PIN            GPIO_Pin_6
#define  LCD_SCK_PIN            GPIO_Pin_5
#define  LCD_CS_OUT             BIT_ADDR(GPIO_ODR_Addr,7)
#define  LCD_SID_OUT            BIT_ADDR(GPIO_ODR_Addr,6)
#define  LCD_SCK_OUT            BIT_ADDR(GPIO_ODR_Addr,5)
#define  LCD_PSB_OUT            BIT_ADDR(GPIO_ODR_Addr,4)
#define  LCD_CS_IN              BIT_ADDR(GPIO_IDR_Addr,7)
#define  LCD_SID_IN             BIT_ADDR(GPIO_IDR_Addr,6)
#define  LCD_SCK_IN             BIT_ADDR(GPIO_IDR_Addr,5)
#define  LCD_PSB_IN             BIT_ADDR(GPIO_IDR_Addr,4) 
#define  LCD_CS_OUT_MODE        GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_CS_PIN;\
                                GPIO_Config(LCD12864_GPIO_CS_PORT,GPIO_Common_Out_Struct)
#define  LCD_SID_OUT_MODE       GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_SID_PIN;\
                                GPIO_Config(LCD12864_GPIO_SID_PORT,GPIO_Common_Out_Struct)
#define  LCD_SCK_OUT_MODE       GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_SCK_PIN;\
                                GPIO_Config(LCD12864_GPIO_SCK_PORT,GPIO_Common_Out_Struct) 
#define  LCD_CS_IN_MODE         GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin = LCD_CS_PIN;\
                                GPIO_Config(LCD12864_GPIO_CS_PORT,GPIO_Common_In_Struct)
#define  LCD_SID_IN_MODE        GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin = LCD_SID_PIN;\
                                GPIO_Config(LCD12864_GPIO_SID_PORT,GPIO_Common_In_Struct)
#define  LCD_SCK_IN_MODE        GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin = LCD_SCK_PIN;\
                                GPIO_Config(LCD12864_GPIO_SCK_PORT,GPIO_Common_In_Struct)
void  LCD12864_clear_DDRAM();                                  //清屏并归址
void  LCD12864_sendbyte(uchar);                                //发送字节,从高到低
void  LCD12864_write_cmd(uchar);                               //写指令,RS=L,RW=L
void  LCD12864_write_data(uchar);                              //写数据,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);                               //字符位置,以中文字符16*16点阵为单位
void  LCD12864_init();                                         //初始化,设置并口(有些型号的12864分左右屏)
void  LCD12864_GPIO_init();                                    //GPIO初始化
void  LCD12864_check_busy();                                   //判断12864是否在忙,一定要有,否则可能导致数据丢失
void  LCD12864_SET_CGRAM(uchar,uchar*);                        //写入CGRAM
void  LCD12864_display_CGRAM(uchar,uchar,uchar);               //显示CGRAM
void  LCD12864_showstring(uchar*,uint,uint);                   //在指定位置显示字符串,不能把vscode里面显示的汉字所占位数当作实际位数！！！中文就是占2个字节的
void  LCD12864_display_image(uchar*);                          //GDRAM绘图模式          
void  LCD12864_clear_GDRAM();                                  //清空GDRAM
void  LCD12864_set_GDRAMadd(uchar,uchar);                      //设置GDRAM的地址
uchar LCD12864_read_data();                                    //读数据,RS=H,RW=H(串口不支持输出)
uchar LCD12864_receivebyte();                                  //读取字节,从高到低
uchar LCD12864_read_status();                                  //读状态,RS=L,RW=H

#endif /*__BSP_12864LIBS_CHUAN_H*/

