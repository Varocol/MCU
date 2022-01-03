#include<REG52.H>
#include<INTRINS.H>
#ifndef uchar
#define uchar unsigned char
#endif
#ifndef uint
#define uint unsigned int
#endif
#define LCD_IO P2

/*��������*/
uchar temp,Hbit,Lbit;
/*���Ŷ���*/

sbit  LCD_RS  =P1^7;                                           //RS
sbit  LCD_RW  =P1^6;                                           //RW
sbit  LCD_EN  =P1^5;                                           //EN
sbit  LCD_PSB =P1^4;                                           //PSB

/*��������*/
void  LCD12864_clear_DDRAM();                                  //��������ַ
void  LCD12864_write_cmd(uchar);                               //дָ��,RS=L,RW=L
void  LCD12864_write_data(uchar);                              //д����,RS=H,RW=L
void  LCD12864_pos(uchar,uchar);                               //�ַ�λ��,�������ַ�16*16����Ϊ��λ
void  LCD12864_init();                                         //��ʼ��,���ò���(��Щ�ͺŵ�12864��������)
void  LCD12864_check_busy();                                   //�ж�12864�Ƿ���æ,һ��Ҫ��,������ܵ������ݶ�ʧ
void  LCD12864_SET_CGRAM(uchar,uchar*);                        //д��CGRAM
void  LCD12864_display_CGRAM(uchar,uchar,uchar);               //��ʾCGRAM
void  LCD12864_showstring(uchar*,uint,uint);                   //��ָ��λ����ʾ�ַ���,���ܰ�vscode������ʾ�ĺ�����ռλ������ʵ��λ�����������ľ���ռ2���ֽڵ�
void  LCD12864_display_image(uchar*);                          //GDRAM��ͼģʽ
void  LCD12864_drawrectangle(uchar,uchar,uchar,uchar,uchar);   //�������ֽڻ��ƾ���(����Ч���Ը�) 
void  LCD12864_drawrectangle1(uchar,uchar,uchar,uchar,uchar);  //�Ե���ƾ���   
void  LCD12864_drawpoint(uchar,uchar,uchar);        
void  LCD12864_clear_GDRAM();                                  //���GDRAM
void  LCD12864_read_GDRAM(uchar,uchar);                        //��ȡGDRAM����
void  LCD12864_set_GDRAMadd(uchar,uchar);                      //����GDRAM�ĵ�ַ
uchar LCD12864_read_data();                                    //������,RS=H,RW=H(���ڲ�֧�����)

/*��������*/
void  LCD12864_clear_DDRAM()
{
      LCD12864_write_cmd(0x01);
      LCD12864_write_cmd(0x03);
}
void  LCD12864_write_cmd(uchar cmd)
{
      LCD12864_check_busy();
      LCD_IO=cmd;
      LCD_RS=0;
      LCD_RW=0;
      LCD_EN=1;
      _nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
      LCD_EN=0;
}
void  LCD12864_write_data(uchar Data)
{
      LCD12864_check_busy();
      LCD_IO=Data;
      LCD_RS=1;
      LCD_RW=0;
      LCD_EN=1;
      _nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
      LCD_EN=0;
}
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
void  LCD12864_init()
{
      LCD12864_write_cmd(0x33);
      LCD12864_write_cmd(0x30);
      LCD12864_write_cmd(0x01);      
      LCD12864_write_cmd(0x0C);
      LCD12864_write_cmd(0x06);
      LCD12864_write_cmd(0x03);
}
void  LCD12864_check_busy()
{
      LCD_IO=0xff;
      do
        {
         LCD_RS=0;
         LCD_RW=1;
         LCD_EN=1;
        }
      while(LCD_IO & 0x80);
      LCD_EN=0;
}
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
void  LCD12864_display_CGRAM(uchar num,uchar x,uchar y)
{
      LCD12864_pos(x,y);
      LCD12864_write_data(0x00);            //CGRAM�������ݵ���
      LCD12864_write_data(num*2);
}
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
void  LCD12864_drawrectangle(uchar x1,uchar y1,uchar x2,uchar y2,uchar flag)
{
      uchar i,j;
      uchar x,y,z;
      uchar fill;
      char  k;
      fill=0xFF;
      k=x1%16?x1+16-x1%16:x1;
      k=x2%16==15?(x2+1-k)/16:(x2-x2%16-k)/16;
      LCD12864_write_cmd(0x36);                  //����ָ�,��ͼģʽ��(���ùر����ٿ�,�����Ƶ��)
      for(i=0;i<=y2-y1;i++)
      {
          y=(y1+i)%32;
          x=x1/16+(y1+i)/32*8;
          z=x;
          LCD12864_set_GDRAMadd(z,y);
          if(k>=0)
          {
                 if(x1%16)
               {   
                   LCD12864_read_GDRAM(z,y);
                   LCD12864_set_GDRAMadd(z,y);
                   if(flag)
                   LCD12864_write_data(fill>>(x1%16)|Hbit);
                   else
                   LCD12864_write_data((~(fill>>(x1%16)))&Hbit);
                   if(x1%16>8)
                   {
                        if(flag)
                        LCD12864_write_data(fill>>(x1%16-8)|Lbit);
                        else
                        LCD12864_write_data((~(fill>>(x1%16-8)))&Lbit);
                   }
                   else
                   {
                        if(flag)
                        LCD12864_write_data(fill|Lbit);
                        else
                        LCD12864_write_data((~fill)&Lbit);
                   }
                   z++;
               }
               for(j=0;j<k;j++)
               {
                   LCD12864_read_GDRAM(z,y);   
                   LCD12864_set_GDRAMadd(z,y);
                   if(flag)
                   {
                        LCD12864_write_data(fill|Hbit);
                        LCD12864_write_data(fill|Lbit);//GDRAM���������ֽ�Ϊ��λ�����
                   }
                   else
                   {
                        LCD12864_write_data((~fill)&Hbit);
                        LCD12864_write_data((~fill)&Lbit);
                   }
                   z++;         
               }
               if(x2%16!=15)
               {
                   LCD12864_read_GDRAM(z,y);   
                   LCD12864_set_GDRAMadd(z,y);
                   if(x2%16>7)
                   {
                       if(flag)
                       LCD12864_write_data(fill|Hbit);
                       else
                       LCD12864_write_data((~fill)&Hbit);
                   }
                   else
                   {
                       if(flag)
                       LCD12864_write_data(fill<<(7-x2%16)|Hbit);
                       else
                       LCD12864_write_data((~(fill<<(7-x2%16)))&Hbit);
                   }
                   if(flag)
                   LCD12864_write_data(fill<<(15-x2%16)|Lbit);
                   else
                   LCD12864_write_data((~(fill<<(15-x2%16)))&Lbit);
               }
          }
          else
          {
               LCD12864_read_GDRAM(z,y);   
               LCD12864_set_GDRAMadd(z,y);
               if(x2%16>7)
               {
                    if(x1%16<=7)
                       {
                          if(flag)
                          {
                              LCD12864_write_data(fill>>(x1%16)|Hbit);
                              LCD12864_write_data(fill<<(15-x2%16)|Lbit);
                          }
                          else
                          {
                              LCD12864_write_data((~(fill>>(x1%16)))&Hbit);
                              LCD12864_write_data((~(fill<<(15-x2%16)))&Lbit);  
                          }
                       }
                    else
                       {
                          LCD12864_write_data(Hbit);
                          if(flag)
                          LCD12864_write_data((fill>>(x1%16-8)&fill<<(15-x2%16))|Lbit);
                          else
                          LCD12864_write_data((~(fill>>(x1%16-8)&fill<<(15-x2%16)))&Lbit);
                       }
               }
               else
               {
                     if(flag)
                     LCD12864_write_data((fill>>(x1%16)&fill<<(7-x2%16))|Hbit);
                     else
                     LCD12864_write_data((~(fill>>(x1%16)&fill<<(7-x2%16)))&Hbit);
                     LCD12864_write_data(Lbit);
               }
          }
      }
      LCD12864_write_cmd(0x30);
}
void  LCD12864_drawrectangle1(uchar x1,uchar y1,uchar x2,uchar y2,uchar flag) 
{
      uchar i,j;
      for(i=y1;i<=y2;i++)
      for(j=x1;j<=x2;j++)
      {
           LCD12864_drawpoint(j,i,flag);
      }
}
void  LCD12864_drawpoint(uchar x,uchar y,uchar flag)
{
      uchar fill=0x80;
      LCD12864_write_cmd(0x36);
      LCD12864_write_cmd(0x80+y%32);
      LCD12864_write_cmd(0x80+y/32*8+x/16);
      LCD12864_read_GDRAM(y/32*8+x/16,y%32);
      if(x%16>=8)
      {
            LCD12864_write_data(Hbit);
            if(flag)
            LCD12864_write_data(Lbit|fill>>(x%16-8));
            else
            LCD12864_write_data(Lbit&(~(fill>>(x%16-8))));//'~'���ȼ�����'>>'������
      }
      else 
      {
            if(flag)
            LCD12864_write_data(Hbit|fill>>(x%16));
            else
            LCD12864_write_data(Hbit&(~(fill>>(x%16))));
            LCD12864_write_data(Lbit);
      }
      LCD12864_write_cmd(0x30);
}
void  LCD12864_clear_GDRAM()
{
      uchar i,j;
      LCD12864_write_cmd(0x36);              //����ָ�,��ͼģʽ��
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x80);
            for(j=0;j<8;j++)
                {
                  LCD12864_write_data(0x00);
                  LCD12864_write_data(0x00);
                }       
      }
      for(i=0;i<32;i++)
      {
            LCD12864_write_cmd(0x80+i);
            LCD12864_write_cmd(0x88);
            for(j=0;j<8;j++)
                {
                  LCD12864_write_data(0x00);
                  LCD12864_write_data(0x00);
                }       
      }
      LCD12864_write_cmd(0x30);
}
void  LCD12864_set_GDRAMadd(uchar x,uchar y)
{
      LCD12864_write_cmd(y+0x80);
      LCD12864_write_cmd(x+0x80);
}
void  LCD12864_read_GDRAM(uchar x,uchar y)
{
      LCD12864_set_GDRAMadd(x,y);
      LCD12864_read_data();
      Hbit=LCD12864_read_data();
      Lbit=LCD12864_read_data();
      LCD12864_set_GDRAMadd(x,y);
}
uchar LCD12864_read_data()                                     //���ڲ�����
{   
      LCD12864_check_busy();               //��æ����һ��Ҫ�ӣ�����
      LCD_IO=0xff;
      LCD_RS = 1;                          //RS=1 RW=1 E=������
	LCD_RW = 1;
	LCD_EN = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	temp =LCD_IO;
	LCD_EN = 0;
	return temp;
}