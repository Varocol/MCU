#include "bsp_12864libs����.h"

/**
  * @brief  LCD12864��������
  * @param  None
  * @retval None
  */
void  LCD12864_clear_DDRAM()
{
      LCD12864_write_cmd(0x01);
      LCD12864_write_cmd(0x03);
}

/**
  * @brief  LCD12864���͵��ֽں���
  * @param  Data:��Ҫ���͵��ֽ�
  * @retval None
  */
void  LCD12864_sendbyte(uchar Data)
{
      uchar i;
      
      for(i=0;i<8;i++)
      {
          LCD_SCK_OUT=0;
          SysTick_Delay_us(5);
          LCD_SID_OUT=Data>>7;
          SysTick_Delay_us(5);          
          Data<<=1;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=1;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=0;
      }
}

/**
  * @brief  LCD12864дָ���
  * @param  cmd:��Ҫ���͵�ָ��
  * @retval None
  */
void  LCD12864_write_cmd(uchar cmd)
{
      LCD_CS_OUT=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xf8);
      LCD12864_sendbyte(0xf0&cmd);
      LCD12864_sendbyte(0xf0&cmd<<4);
      LCD_CS_OUT=0;
}

/**
  * @brief  LCD12864д���ݺ���
  * @param  Data:��Ҫ���͵�����
  * @retval None
  */
void  LCD12864_write_data(uchar Data)
{
      LCD_CS_OUT=1;
      LCD12864_check_busy();
      LCD12864_sendbyte(0xfa);
      LCD12864_sendbyte(0xf0&Data);
      LCD12864_sendbyte(0xf0&Data<<4);
      LCD_CS_OUT=0;
}

/**
  * @brief  LCD12864��������λ�ú���
  * @param  x:����(0~3)
  * @param  y:����(0~7)
  * @retval None
  */
void  LCD12864_pos(uchar x,uchar y)
{
    switch (x)
    {
    case 0:x=0x80;
           break;
    case 1:x=0x90;
           break;
    case 2:x=0x88;
           break;
    case 3:x=0x98;
           break;
    }
    LCD12864_write_cmd(x+y);
}

/**
  * @brief  LCD12864��ʼ����Ļ����
  * @param  None
  * @retval None
  */
void  LCD12864_init()
{
      LCD12864_write_cmd(0x33);
      LCD12864_write_cmd(0x30);
      LCD12864_write_cmd(0x01);      
      LCD12864_write_cmd(0x0C);
      LCD12864_write_cmd(0x06);
      LCD12864_write_cmd(0x03);
}

/**
  * @brief  LCD12864 STM32GPIO��ʼ������
  * @param  None
  * @retval None
  */
void  LCD12864_GPIO_init()
{
      //GPIO_Common_In_Struct.GPIO_Speed =  GPIO_Speed_10MHz;
      //GPIO_Common_Out_Struct.GPIO_Speed = GPIO_Speed_10MHz;
      LCD_CS_IN_MODE; 
      LCD_SID_IN_MODE;
      LCD_SCK_IN_MODE;
      LCD_CS_OUT_MODE;
      LCD_SID_OUT_MODE;
      LCD_SCK_OUT_MODE;
}

/**
  * @brief  LCD12864��æ����
  * @param  None
  * @retval None
  */
void  LCD12864_check_busy()
{
      do ;
      while(LCD12864_read_status()&0x80);
}

/**
  * @brief  LCD12864д��CGRAM����
  * @param  num:���(0-3)
  * @param  p:��������ݵ�ָ��
  * @retval None
  */
void  LCD12864_SET_CGRAM(uchar num,uchar *p)
{
      uchar i,firstadd;
      LCD12864_write_cmd(0x34);             //����ָ�
      LCD12864_write_cmd(0x02);             //��13��,��������CGRAM��ַ
      LCD12864_write_cmd(0x30);             //�ص�����ָ�
      firstadd=(0x40|num<<4);
      for(i=0;i<16;i++)
      {
          LCD12864_write_cmd(firstadd+i);   //����������
          LCD12864_write_data(p[i*2]);
          LCD12864_write_data(p[i*2+1]);
      }
}

/**
  * @brief  LCD12864����CGRAM����
  * @param  num:���(0-3)
  * @param  x:�к�
  * @param  y:�к�
  * @retval None
  */
void  LCD12864_display_CGRAM(uchar num,uchar x,uchar y)
{
      LCD12864_pos(x,y);
      LCD12864_write_data(0x00);            //CGRAM�������ݵ���
      LCD12864_write_data(num*2);
}

/**
  * @brief  LCD12864����CGRAM����
  * @param  p:������ʾ���ַ�����ָ��
  * @param  row:�к�
  * @param  col:�к�
  * @retval None
  */
void  LCD12864_showstring(uchar*p,uint row,uint col)
{
      uchar i;
      LCD12864_pos(row,col);
      switch (row)
      {
      case 0:row=0x80;
             break;
      case 1:row=0x90;
             break;
      case 2:row=0x88;
             break;
      case 3:row=0x98;
             break;
      }
      row+=col;
      for(i=0;p[i]!='\0';i++)
      {
            LCD12864_write_data(p[i]);
            if(i%2)
            { 
               row++;
               switch (row)
               {
               case 0x88:row=0x90;
                         LCD12864_write_cmd(row);
                         break;
               case 0x98:row=0x88;
                         LCD12864_write_cmd(row);
                         break;
               case 0x90:row=0x98;
                         LCD12864_write_cmd(row);
                         break;
               }
               if(row==0xa0)break;
            }
      }
}

/**
  * @brief  LCD12864��ͼ����
  * @param  p:������ʾ���ַ�����ָ��
  * @retval None
  */
void  LCD12864_display_image(uchar*p)
{
      uchar i,j;
      LCD12864_write_cmd(0x34);              //����ָ�,��ͼģʽ��               
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x80);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(*p);
                  p++;
                }       
      }
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x88);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(*p);
                  p++;
                }       
      }
      LCD12864_write_cmd(0x36);
      LCD12864_write_cmd(0x30);
}

/**
  * @brief  LCD12864���GDRAM����
  * @param  None
  * @retval None
  */
void  LCD12864_clear_GDRAM()
{
      uchar i,j;
      LCD12864_write_cmd(0x34);              //����ָ�,��ͼģʽ��
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x80);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(0x00);
                }       
      }
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x88);
            for(j=0;j<16;j++)
                {
                  LCD12864_write_data(0x00);
                }       
      }
      LCD12864_write_cmd(0x36);
      LCD12864_write_cmd(0x30);
}

/**
  * @brief  LCD12864����GDRAM��ַ����
  * @param  x:�к�
  * @param  y:�к�
  * @retval None
  */
void  LCD12864_set_GDRAMadd(uchar x,uchar y)
{
      LCD12864_write_cmd(y+0x80);
      LCD12864_write_cmd(x+0x80);
}

/**
  * @brief  LCD12864����Ļ���ݺ���
  *         �ú������ڲ�����(�����޷���ȡ��Ļ����)
  * @param  None
  * @retval None
  */
uchar LCD12864_read_data()                                     
{   
      LCD12864_sendbyte(0xfe);
      return LCD12864_receivebyte();
}

/**
  * @brief  LCD12864������Ļ�ֽں���
  * @param  None
  * @retval None
  */
uchar LCD12864_receivebyte()
{
      uchar tmp1,tmp2,i;
      tmp1=0;
      tmp2=0;
      for(i=0;i<8;i++)
      {          
          tmp1<<=1;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=0;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=1;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=0;
          SysTick_Delay_us(5);
          if(LCD_SID_IN)tmp1++;
      }
      for(i=0;i<8;i++)
      {          
          tmp2<<=1;
          LCD_SCK_OUT=0;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=1;
          SysTick_Delay_us(5);
          LCD_SCK_OUT=0;
          SysTick_Delay_us(5);
          if(LCD_SID_IN)tmp2++;
      }
      return (tmp1&0xf0)|(tmp2>>4);
}

/**
  * @brief  LCD12864����Ļ״̬����
  * @param  None
  * @retval None
  */
uchar LCD12864_read_status()
{
      LCD12864_sendbyte(0xfc);
      return LCD12864_receivebyte();
}