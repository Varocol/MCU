#ifndef  __BSP_12864LIBS_BING_H
#define  __BSP_12864LIBS_BING_H
#include "bsp_conf.h"
#ifndef  uchar
#define  uchar uint8_t
#endif
#ifndef  uint
#define  uint  uint16_t
#endif

#define  LCD12864_GPIO_IO_PORT  GPIOA
#define  LCD12864_GPIO_RS_PORT  GPIOB
#define  LCD12864_GPIO_RW_PORT  GPIOB
#define  LCD12864_GPIO_EN_PORT  GPIOB
#define  LCD12864_GPIO_BASE     GPIOB_BASE
#define  GPIO_ODR_Addr          (LCD12864_GPIO_BASE + 12)
#define  GPIO_IDR_Addr          (LCD12864_GPIO_BASE + 8)
#define  LCD_RS_PIN             GPIO_Pin_7
#define  LCD_RW_PIN             GPIO_Pin_6
#define  LCD_EN_PIN             GPIO_Pin_5
#define  LCD_RS_OUT             BIT_ADDR(GPIO_ODR_Addr,7)
#define  LCD_RW_OUT             BIT_ADDR(GPIO_ODR_Addr,6)
#define  LCD_EN_OUT             BIT_ADDR(GPIO_ODR_Addr,5)
#define  LCD_RS_IN              BIT_ADDR(GPIO_IDR_Addr,7)
#define  LCD_RW_IN              BIT_ADDR(GPIO_IDR_Addr,6)
#define  LCD_EN_IN              BIT_ADDR(GPIO_IDR_Addr,5)
#define  LCD_RS_OUT_MODE        GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_RS_PIN; \
                                GPIO_Config(LCD12864_GPIO_RS_PORT,GPIO_Common_Out_Struct) 
#define  LCD_RW_OUT_MODE        GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_RW_PIN; \
                                GPIO_Config(LCD12864_GPIO_RW_PORT,GPIO_Common_Out_Struct)
#define  LCD_EN_OUT_MODE        GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = LCD_EN_PIN; \
                                GPIO_Config(LCD12864_GPIO_EN_PORT,GPIO_Common_Out_Struct)
#define  LCD_RS_IN_MODE         GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin  = LCD_RS_PIN; \
                                GPIO_Config(LCD12864_GPIO_RS_PORT,GPIO_Common_In_Struct)
#define  LCD_RW_IN_MODE         GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin  = LCD_RW_PIN; \
                                GPIO_Config(LCD12864_GPIO_RW_PORT,GPIO_Common_In_Struct)
#define  LCD_EN_IN_MODE         GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin  = LCD_EN_PIN; \
                                GPIO_Config(LCD12864_GPIO_EN_PORT,GPIO_Common_In_Struct)
#define  LCD_IO_IN_MODE         GPIO_Common_In_Struct.GPIO_Mode = GPIO_Mode_IPU;\
                                GPIO_Common_In_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_In_Struct.GPIO_Pin  = GPIO_Pin_All;\
                                GPIO_Config(LCD12864_GPIO_IO_PORT,&GPIO_Common_In_Struct)
#define  LCD_IO_OUT_MODE        GPIO_Common_Out_Struct.GPIO_Mode = GPIO_Mode_Out_PP;\
                                GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_50MHz;\
                                GPIO_Common_Out_Struct.GPIO_Pin = GPIO_Pin_All;\
                                GPIO_Config(LCD12864_GPIO_IO_PORT,&GPIO_Common_Out_Struct)
#define  LCD_IO_IN              GPIO_ReadInputData(LCD12864_GPIO_IO_PORT)
#define  LCD_IO_OUT(cmd)        GPIO_Write(LCD12864_GPIO_IO_PORT,(uint16_t)cmd)
//#define  LCD_PSB_IN             BIT_ADDR(GPIO_IDR_Addr,4)
//#define  LCD_PSB_OUT            BIT_ADDR(GPIO_ODR_Addr,4)
void  LCD12864_clear_DDRAM();                                  //??????????
void  LCD12864_write_cmd(uchar);                               //??????,RS=L,RW=L
void  LCD12864_write_data(uchar);                              //??????,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);                               //????????,??????????16*16??????????
void  LCD12864_init();                                         //??????,????????(??????????12864????????)
void  LCD12864_GPIO_init();                                    //GPIO??????
void  LCD12864_check_busy();                                   //????12864????????,????????,????????????????????
void  LCD12864_SET_CGRAM(uchar,uchar*);                        //????CGRAM
void  LCD12864_display_CGRAM(uchar,uchar,uchar);               //????CGRAM
void  LCD12864_showstring(uchar*,uint,uint);                   //????????????????????,??????vscode??????????????????????????????????????????????????2????????
void  LCD12864_display_image(uchar*);                          //GDRAM????????
void  LCD12864_drawrectangle(uchar,uchar,uchar,uchar,uchar);   //??????????????????(????????????) 
void  LCD12864_drawrectangle1(uchar,uchar,uchar,uchar,uchar);  //????????????   
void  LCD12864_drawpoint(uchar,uchar,uchar);                   //????
void  LCD12864_clear_GDRAM();                                  //????GDRAM
void  LCD12864_read_GDRAM(uchar,uchar);                        //????GDRAM????
void  LCD12864_set_GDRAMadd(uchar,uchar);                      //????GDRAM??????
uchar LCD12864_read_data();                                    //??????,RS=H,RW=H(??????????????)


#endif /*__BSP_12864LIBS_BING_H*/