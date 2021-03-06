#include "bsp_12864libs并行.h"

uchar temp,Hbit,Lbit;
/**
  * @brief  LCD12864清除DDRAM函数
  * @param  None
  * @retval None
  */
void  LCD12864_clear_DDRAM()
{
      LCD12864_write_cmd(0x01);
      LCD12864_write_cmd(0x03);
}
/**
  * @brief  LCD12864写屏幕指令函数
  * @param  cmd:指令
  * @retval None
  */
void  LCD12864_write_cmd(uchar cmd)
{
      LCD12864_check_busy();
      LCD_IO_OUT(cmd);
      LCD_RS_OUT=0;
      LCD_RW_OUT=0;
      LCD_EN_OUT=1;
      LCD_EN_OUT=0;
}

/**
  * @brief  LCD12864写屏幕数据函数
  * @param  Data:数据
  * @retval None
  */
void  LCD12864_write_data(uchar Data)
{
      LCD12864_check_busy();
      LCD_IO_OUT(Data);
      LCD_RS_OUT=1;
      LCD_RW_OUT=0;
      LCD_EN_OUT=1;
      LCD_EN_OUT=0;
}

/**
  * @brief  LCD12864写位置函数
  * @param  x:行号
  * @param  y:列号
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
  * @brief  LCD12864初始化函数
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
  * @brief  LCD12864GPIO初始化函数
  * @param  None
  * @retval None
  */
void  LCD12864_GPIO_init()
{
      //初始化RS RW EN gpio口
      LCD_RS_IN_MODE;
      LCD_RW_IN_MODE;
      LCD_EN_IN_MODE;
      
      LCD_RS_OUT_MODE;
      LCD_RW_OUT_MODE;
      LCD_EN_OUT_MODE;
      //初始化数据口
      LCD_IO_IN_MODE;
      LCD_IO_OUT_MODE;
}

/**
  * @brief  LCD12864判忙
  * @param  None
  * @retval None
  */
void  LCD12864_check_busy()
{
      uint8_t value;
      LCD_IO_OUT(0xff);
      LCD_RS_OUT=0;
      LCD_RW_OUT=1;
      LCD_EN_OUT=1;
      do 
      {
         LCD_IO_IN_MODE;
         value = (uint8_t)LCD_IO_IN;  
         LCD_IO_OUT_MODE;
      }
      while(value & 0x80);
      LCD_EN_OUT=0;
}

/**
  * @brief  LCD12864设置CGRAM函数
  * @param  num:编号
  * @param  p:数据指针
  * @retval None
  */
void  LCD12864_SET_CGRAM(uchar num,uchar *p)
{
      uchar i,firstadd;
      LCD12864_write_cmd(0x34);             //扩充指令集
      LCD12864_write_cmd(0x02);             //第13条,允许设置CGRAM地址
      LCD12864_write_cmd(0x30);             //回到基本指令集
      firstadd=(0x40|num<<4);
      for(i=0;i<16;i++)
      {
          LCD12864_write_cmd(firstadd+i);   //设置纵坐标
          LCD12864_write_data(p[i*2]);
          LCD12864_write_data(p[i*2+1]);
      }
}

/**
  * @brief  LCD1286呈现CGRAM函数
  * @param  num:编号
  * @param  x:行号
  * @param  y:列号
  * @retval None
  */
void  LCD12864_display_CGRAM(uchar num,uchar x,uchar y)
{
      LCD12864_pos(x,y);
      LCD12864_write_data(0x00);            //CGRAM当作数据调用
      LCD12864_write_data(num*2);
}

/**
  * @brief  LCD12864写字符串
  * @param  p:数据指针
  * @param  row:行号
  * @param  col:列号
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
  * @brief  LCD12864呈现图片
  * @param  p:数据指针
  * @retval None
  */
void  LCD12864_display_image(uchar*p)
{
      uchar i,j;
      LCD12864_write_cmd(0x34);              //扩充指令集,绘图模式关               
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
  * @brief  LCD12864高速画矩形
  * @param  x1:左上角横坐标
  * @param  y1:左上角纵坐标
  * @param  x2:右下角横坐标
  * @param  y2:右下角纵坐标
  * @param  flag:点的状态
  * @retval None
  */
void  LCD12864_drawrectangle(uchar x1,uchar y1,uchar x2,uchar y2,uchar flag)
{
      uchar i,j;
      uchar x,y,z;
      uchar fill;
      char  k;
      fill=0xFF;
      k=x1%16?x1+16-x1%16:x1;
      k=x2%16==15?(x2+1-k)/16:(x2-x2%16-k)/16;
      LCD12864_write_cmd(0x36);                  //扩充指令集,绘图模式开(不用关闭了再开,否则会频闪)
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
                        LCD12864_write_data(fill|Lbit);//GDRAM是以两个字节为单位输入的
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

/**
  * @brief  LCD12864低速画矩形
  * @param  x1:左上角横坐标
  * @param  y1:左上角纵坐标
  * @param  x2:右下角横坐标
  * @param  y2:右下角纵坐标
  * @param  flag:点的状态
  * @retval None
  */
void  LCD12864_drawrectangle1(uchar x1,uchar y1,uchar x2,uchar y2,uchar flag) 
{
      uchar i,j;
      for(i=y1;i<=y2;i++)
      for(j=x1;j<=x2;j++)
      {
           LCD12864_drawpoint(j,i,flag);
      }
}

/**
  * @brief  LCD12864描点
  * @param  x:点横坐标
  * @param  y:点纵坐标
  * @param  flag:点的状态
  * @retval None
  */
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
            LCD12864_write_data(Lbit&(~(fill>>(x%16-8))));//'~'优先级大于'>>'！！！
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

/**
  * @brief  LCD12864请除GDRAM
  * @param  None
  * @retval None
  */
void  LCD12864_clear_GDRAM()
{
      uchar i,j;
      LCD12864_write_cmd(0x36);              //扩充指令集,绘图模式关
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

/**
  * @brief  LCD12864设置GDRAM地址
  * @param  x:列号
  * @param  y:行号
  * @retval None
  */
void  LCD12864_set_GDRAMadd(uchar x,uchar y)
{
      LCD12864_write_cmd(y+0x80);
      LCD12864_write_cmd(x+0x80);
}

/**
  * @brief  LCD12864读取GDRAM数据
  * @param  x:列号
  * @param  y:行号
  * @retval None
  */
void  LCD12864_read_GDRAM(uchar x,uchar y)
{
      LCD12864_set_GDRAMadd(x,y);
      LCD12864_read_data();
      Hbit=LCD12864_read_data();
      Lbit=LCD12864_read_data();
      LCD12864_set_GDRAMadd(x,y);
}

/**
  * @brief  LCD12864读取屏幕数据
  * @param  None
  * @retval None
  */
uchar LCD12864_read_data()                                     //串口不可用
{   
      LCD12864_check_busy();                 //判忙函数一定要加！！！
      LCD_IO_OUT(0xff);
      LCD_RS_OUT=1;                          //RS=1 RW=1 E=高脉冲
	LCD_RW_OUT=1;
	LCD_EN_OUT=1;
      LCD_IO_IN_MODE;
	temp =(uint8_t) LCD_IO_IN ;
	LCD_EN_OUT = 0;
	return temp;
}