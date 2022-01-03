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
void  LCD12864_clear_DDRAM();                                  //��������ַ
void  LCD12864_sendbyte(uchar);                                //�����ֽ�,�Ӹߵ���
void  LCD12864_write_cmd(uchar);                               //дָ��,RS=L,RW=L
void  LCD12864_write_data(uchar);                              //д����,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);                               //�ַ�λ��,�������ַ�16*16����Ϊ��λ
void  LCD12864_init();                                         //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
void  LCD12864_GPIO_init();                                    //GPIO��ʼ��
void  LCD12864_check_busy();                                   //�ж�12864�Ƿ���æ,һ��Ҫ��,������ܵ������ݶ�ʧ
void  LCD12864_SET_CGRAM(uchar,uchar*);                        //д��CGRAM
void  LCD12864_display_CGRAM(uchar,uchar,uchar);               //��ʾCGRAM
void  LCD12864_showstring(uchar*,uint,uint);                   //��ָ��λ����ʾ�ַ���,���ܰ�vscode������ʾ�ĺ�����ռλ������ʵ��λ�����������ľ���ռ2���ֽڵ�
void  LCD12864_display_image(uchar*);                          //GDRAM��ͼģʽ          
void  LCD12864_clear_GDRAM();                                  //���GDRAM
void  LCD12864_set_GDRAMadd(uchar,uchar);                      //����GDRAM�ĵ�ַ
uchar LCD12864_read_data();                                    //������,RS=H,RW=H(���ڲ�֧�����)
uchar LCD12864_receivebyte();                                  //��ȡ�ֽ�,�Ӹߵ���
uchar LCD12864_read_status();                                  //��״̬,RS=L,RW=H

#endif /*__BSP_12864LIBS_CHUAN_H*/

