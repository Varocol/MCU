#include "LCD_12864_Parallel.h"

/**
 * @brief  LCD12864并行-空构造方法
 * @param  None
 * @retval None
 */
LCD_12864_Parallel::LCD_12864_Parallel()
{
}

/**
 * @brief  LCD12864并行-传参构造方法
 * @param  Param        LCD12864并行参数列表
 * @retval None
 */
LCD_12864_Parallel::LCD_12864_Parallel(LCD_12864_Param_Parallel Param)
{
      Set_Param(Param);
}

/**
 * @brief  LCD12864并行-设置参数方法
 * @param  Param        LCD12864并行参数列表
 * @retval None
 */
void LCD_12864_Parallel::Set_Param(LCD_12864_Param_Parallel Param)
{
      this->Param = Param;
}

/**
 * @brief  LCD12864并行-更新参数方法
 * @param  Param        LCD12864并行参数列表
 * @retval None
 */
void LCD_12864_Parallel::Update(LCD_12864_Param_Parallel Param)
{
      Set_Param(Param);
      Init();
}

/**
 * @brief  LCD12864并行-清除DDRAM方法
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Clear_DDRAM()
{
      Write_Cmd(0x01);
      Write_Cmd(0x03);
}

/**
 * @brief  LCD12864并行-空方法(给串行用的)
 * @param  Data         需要发送的字节
 * @retval None
 */
void LCD_12864_Parallel::Send_Byte(uchar Data)
{
}

/**
 * @brief  LCD12864并行-写屏幕指令方法
 * @param  cmd          指令
 * @retval None
 */
void LCD_12864_Parallel::Write_Cmd(uchar cmd)
{
      Check_Busy();
      IO.Set_Port_Val(cmd);
      RS.Set_Pin_Val(0);
      RW.Set_Pin_Val(0);
      EN.Set_Pin_Val(1);
      EN.Set_Pin_Val(0);
}

/**
 * @brief  LCD12864并行-写屏幕数据方法
 * @param  Data         数据
 * @retval None
 */
void LCD_12864_Parallel::Write_Data(uchar Data)
{
      Check_Busy();
      IO.Set_Port_Val(Data);
      RS.Set_Pin_Val(1);
      RW.Set_Pin_Val(0);
      EN.Set_Pin_Val(1);
      EN.Set_Pin_Val(0);
}

/**
 * @brief  LCD12864并行-写位置方法
 * @param  x            行号
 * @param  y            列号
 * @retval None
 */
void LCD_12864_Parallel::Pos(uchar x, uchar y)
{
      switch (x)
      {
      case 0:
            x = 0x80;
            break;
      case 1:
            x = 0x90;
            break;
      case 2:
            x = 0x88;
            break;
      case 3:
            x = 0x98;
            break;
      }
      Write_Cmd(x + y);
}

/**
 * @brief  LCD12864并行-初始化方法(含GPIO)
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Init()
{
      Pin_Init();
      Write_Cmd(0x33);
      Write_Cmd(0x30);
      Write_Cmd(0x01);
      Write_Cmd(0x0C);
      Write_Cmd(0x06);
      Write_Cmd(0x03);
}

/**
 * @brief  LCD12864并行-GPIO初始化方法
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Pin_Init()
{
      //初始化RS RW EN IOgpio口
      RS = GPIO(Param.RS_PIN);
      RW = GPIO(Param.RW_PIN);
      EN = GPIO(Param.EN_PIN);
      IO = GPIO(Param.IO_PIN);
      RS.IN_MODE();
      RW.IN_MODE();
      EN.IN_MODE();
      IO.IN_MODE();
      RS.OUT_MODE();
      RW.OUT_MODE();
      EN.OUT_MODE();
      IO.OUT_MODE();
}

/**
 * @brief  LCD12864并行-判忙方法
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Check_Busy()
{
      uint8_t value;
      IO.Set_Port_Val(0xff);
      RS.Set_Pin_Val(0);
      RW.Set_Pin_Val(1);
      EN.Set_Pin_Val(1);
      do
      {
            IO.IN_MODE();
            value = (uint8_t)IO.Get_Input_Port();
            IO.OUT_MODE();
      } while (value & 0x80);
      EN.Set_Pin_Val(0);
}

/**
 * @brief  LCD12864并行-设置CGRAM方法
 * @param  num          编号
 * @param  p            数据指针
 * @retval None
 */
void LCD_12864_Parallel::Set_CGRAM(uchar num, uchar *p)
{
      uchar i, firstadd;
      Write_Cmd(0x34); //扩充指令集
      Write_Cmd(0x02); //第13条,允许设置CGRAM地址
      Write_Cmd(0x30); //回到基本指令集
      firstadd = (0x40 | num << 4);
      for (i = 0; i < 16; i++)
      {
            Write_Cmd(firstadd + i); //设置纵坐标
            Write_Data(p[i * 2]);
            Write_Data(p[i * 2 + 1]);
      }
}

/**
 * @brief  LCD12864并行-呈现CGRAM方法
 * @param  num          编号
 * @param  x            行号
 * @param  y            列号
 * @retval None
 */
void LCD_12864_Parallel::Display_CGRAM(uchar num, uchar x, uchar y)
{
      Pos(x, y);
      Write_Data(0x00); // CGRAM当作数据调用
      Write_Data(num * 2);
}

/**
 * @brief  LCD12864并行-写字符串
 * @param  p            数据指针
 * @param  row          行号
 * @param  col          列号
 * @retval None
 */
void LCD_12864_Parallel::Show_String(uchar *p, uint16_t row, uint16_t col)
{
      uchar i;
      Pos(row, col);
      switch (row)
      {
      case 0:
            row = 0x80;
            break;
      case 1:
            row = 0x90;
            break;
      case 2:
            row = 0x88;
            break;
      case 3:
            row = 0x98;
            break;
      }
      row += col;
      for (i = 0; p[i] != '\0'; i++)
      {
            Write_Data(p[i]);
            if (i % 2)
            {
                  row++;
                  switch (row)
                  {
                  case 0x88:
                        row = 0x90;
                        Write_Cmd(row);
                        break;
                  case 0x98:
                        row = 0x88;
                        Write_Cmd(row);
                        break;
                  case 0x90:
                        row = 0x98;
                        Write_Cmd(row);
                        break;
                  }
                  if (row == 0xa0)
                        break;
            }
      }
}

/**
 * @brief  LCD12864并行-呈现图片
 * @param  p            数据指针
 * @retval None
 */
void LCD_12864_Parallel::Display_Image(uchar *p)
{
      uchar i, j;
      Write_Cmd(0x34); //扩充指令集,绘图模式关
      for (i = 0; i < 32; i++)
      {
            Write_Cmd(0x80 + i);
            Write_Cmd(0x80);
            for (j = 0; j < 16; j++)
            {
                  Write_Data(*p);
                  p++;
            }
      }
      for (i = 0; i < 32; i++)
      {
            Write_Cmd(0x80 + i);
            Write_Cmd(0x88);
            for (j = 0; j < 16; j++)
            {
                  Write_Data(*p);
                  p++;
            }
      }
      Write_Cmd(0x36);
      Write_Cmd(0x30);
}

/**
 * @brief  LCD12864并行-高速画矩形
 * @param  x1           左上角横坐标
 * @param  y1           左上角纵坐标
 * @param  x2           右下角横坐标
 * @param  y2           右下角纵坐标
 * @param  flag         点的状态
 * @retval None
 */
void LCD_12864_Parallel::Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
      uchar i, j;
      uchar x, y, z;
      uchar fill;
      int k;
      fill = 0xFF;
      k = x1 % 16 ? x1 + 16 - x1 % 16 : x1;
      k = x2 % 16 == 15 ? (x2 + 1 - k) / 16 : (x2 - x2 % 16 - k) / 16;
      Write_Cmd(0x36); //扩充指令集,绘图模式开(不用关闭了再开,否则会频闪)
      for (i = 0; i <= y2 - y1; i++)
      {
            y = (y1 + i) % 32;
            x = x1 / 16 + (y1 + i) / 32 * 8;
            z = x;
            Set_GDRAMadd(z, y);
            if (k >= 0)
            {
                  if (x1 % 16)
                  {
                        Read_GDRAM(z, y);
                        Set_GDRAMadd(z, y);
                        if (flag)
                              Write_Data(fill >> (x1 % 16) | Hbit);
                        else
                              Write_Data((~(fill >> (x1 % 16))) & Hbit);
                        if (x1 % 16 > 8)
                        {
                              if (flag)
                                    Write_Data(fill >> (x1 % 16 - 8) | Lbit);
                              else
                                    Write_Data((~(fill >> (x1 % 16 - 8))) & Lbit);
                        }
                        else
                        {
                              if (flag)
                                    Write_Data(fill | Lbit);
                              else
                                    Write_Data((~fill) & Lbit);
                        }
                        z++;
                  }
                  for (j = 0; j < k; j++)
                  {
                        Read_GDRAM(z, y);
                        Set_GDRAMadd(z, y);
                        if (flag)
                        {
                              Write_Data(fill | Hbit);
                              Write_Data(fill | Lbit); // GDRAM是以两个字节为单位输入的
                        }
                        else
                        {
                              Write_Data((~fill) & Hbit);
                              Write_Data((~fill) & Lbit);
                        }
                        z++;
                  }
                  if (x2 % 16 != 15)
                  {
                        Read_GDRAM(z, y);
                        Set_GDRAMadd(z, y);
                        if (x2 % 16 > 7)
                        {
                              if (flag)
                                    Write_Data(fill | Hbit);
                              else
                                    Write_Data((~fill) & Hbit);
                        }
                        else
                        {
                              if (flag)
                                    Write_Data(fill << (7 - x2 % 16) | Hbit);
                              else
                                    Write_Data((~(fill << (7 - x2 % 16))) & Hbit);
                        }
                        if (flag)
                              Write_Data(fill << (15 - x2 % 16) | Lbit);
                        else
                              Write_Data((~(fill << (15 - x2 % 16))) & Lbit);
                  }
            }
            else
            {
                  Read_GDRAM(z, y);
                  Set_GDRAMadd(z, y);
                  if (x2 % 16 > 7)
                  {
                        if (x1 % 16 <= 7)
                        {
                              if (flag)
                              {
                                    Write_Data(fill >> (x1 % 16) | Hbit);
                                    Write_Data(fill << (15 - x2 % 16) | Lbit);
                              }
                              else
                              {
                                    Write_Data((~(fill >> (x1 % 16))) & Hbit);
                                    Write_Data((~(fill << (15 - x2 % 16))) & Lbit);
                              }
                        }
                        else
                        {
                              Write_Data(Hbit);
                              if (flag)
                                    Write_Data((fill >> (x1 % 16 - 8) & fill << (15 - x2 % 16)) | Lbit);
                              else
                                    Write_Data((~(fill >> (x1 % 16 - 8) & fill << (15 - x2 % 16))) & Lbit);
                        }
                  }
                  else
                  {
                        if (flag)
                              Write_Data((fill >> (x1 % 16) & fill << (7 - x2 % 16)) | Hbit);
                        else
                              Write_Data((~(fill >> (x1 % 16) & fill << (7 - x2 % 16))) & Hbit);
                        Write_Data(Lbit);
                  }
            }
      }
      Write_Cmd(0x30);
}

/**
 * @brief  LCD12864并行-低速画矩形
 * @param  x1           左上角横坐标
 * @param  y1           左上角纵坐标
 * @param  x2           右下角横坐标
 * @param  y2           右下角纵坐标
 * @param  flag         点的状态
 * @retval None
 */
void LCD_12864_Parallel::Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
      uchar i, j;
      for (i = y1; i <= y2; i++)
            for (j = x1; j <= x2; j++)
            {
                  Draw_Point(j, i, flag);
            }
}

/**
 * @brief  LCD12864并行-描点
 * @param  x            点横坐标
 * @param  y            点纵坐标
 * @param  flag         点的状态
 * @retval None
 */
void LCD_12864_Parallel::Draw_Point(uchar x, uchar y, uchar flag)
{
      uchar fill = 0x80;
      Write_Cmd(0x36);
      Write_Cmd(0x80 + y % 32);
      Write_Cmd(0x80 + y / 32 * 8 + x / 16);
      Read_GDRAM(y / 32 * 8 + x / 16, y % 32);
      if (x % 16 >= 8)
      {
            Write_Data(Hbit);
            if (flag)
                  Write_Data(Lbit | fill >> (x % 16 - 8));
            else
                  Write_Data(Lbit & (~(fill >> (x % 16 - 8)))); //'~'优先级大于'>>'！！！
      }
      else
      {
            if (flag)
                  Write_Data(Hbit | fill >> (x % 16));
            else
                  Write_Data(Hbit & (~(fill >> (x % 16))));
            Write_Data(Lbit);
      }
      Write_Cmd(0x30);
}

/**
 * @brief  LCD12864并行-清除GDRAM
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Clear_GDRAM()
{
      uchar i, j;
      Write_Cmd(0x36); //扩充指令集,绘图模式关
      for (i = 0; i < 32; i++)
      {
            Write_Cmd(0x80 + i);
            Write_Cmd(0x80);
            for (j = 0; j < 8; j++)
            {
                  Write_Data(0x00);
                  Write_Data(0x00);
            }
      }
      for (i = 0; i < 32; i++)
      {
            Write_Cmd(0x80 + i);
            Write_Cmd(0x88);
            for (j = 0; j < 8; j++)
            {
                  Write_Data(0x00);
                  Write_Data(0x00);
            }
      }
      Write_Cmd(0x30);
}

/**
 * @brief  LCD12864并行-设置GDRAM地址
 * @param  x            列号
 * @param  y            行号
 * @retval None
 */
void LCD_12864_Parallel::Set_GDRAMadd(uchar x, uchar y)
{
      Write_Cmd(y + 0x80);
      Write_Cmd(x + 0x80);
}

/**
 * @brief  LCD12864并行-读取GDRAM数据
 * @param  x            列号
 * @param  y            行号
 * @retval None
 */
void LCD_12864_Parallel::Read_GDRAM(uchar x, uchar y)
{
      Set_GDRAMadd(x, y);
      Read_Data();
      Hbit = Read_Data();
      Lbit = Read_Data();
      Set_GDRAMadd(x, y);
}

/**
 * @brief  LCD12864并行-读取屏幕数据
 * @param  None
 * @retval 屏幕数据
 */
uchar LCD_12864_Parallel::Read_Data() //串行不可用
{
      Check_Busy(); //判忙方法一定要加！！！
      IO.Set_Port_Val(0xff);
      RS.Set_Pin_Val(1); // RS=1 RW=1 E=高脉冲
      RW.Set_Pin_Val(1);
      EN.Set_Pin_Val(1);
      IO.IN_MODE();
      temp = (uint8_t)IO.Get_Input_Port();
      EN.Set_Pin_Val(0);
      return temp;
}

/**
 * @brief  LCD12864并行-空方法(给串行用的)
 * @param  None
 * @retval 接收到的字节
 */
uchar LCD_12864_Parallel::Receive_Byte()
{
      return 0;
}

/**
 * @brief  LCD12864并行-空方法(给串行用的)
 * @param  None
 * @retval LCD的状态
 */
uchar LCD_12864_Parallel::Read_Status()
{
      return 0;
}