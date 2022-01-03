#include "LCD_12864_Serial.h"
/**
  * @brief  空构造函数
  * @param  None
  * @retval None
  */
LCD_12864_Serial::LCD_12864_Serial()
{
}

/**
  * @brief  传参构造函数
  * @param  None
  * @retval None
  */
LCD_12864_Serial::LCD_12864_Serial(LCD_12864_Param_Serial Param)
{
  Set_Param(Param);
}

/**
  * @brief  设置参数函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Set_Param(LCD_12864_Param_Serial Param)
{
  this->Param = Param;
}

/**
  * @brief  更新参数函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Update(LCD_12864_Param_Serial Param)
{
  Set_Param(Param);
  Init();
}

/**
  * @brief  LCD12864清屏函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Clear_DDRAM()
{
  Write_Cmd(0x01);
  Write_Cmd(0x03);
}

/**
  * @brief  LCD12864发送单字节函数
  * @param  Data:需要发送的字节
  * @retval None
  */
void LCD_12864_Serial::Send_Byte(uchar Data)
{
  uchar i;

  for (i = 0; i < 8; i++)
  {
    SCK.Set_Pin(0);
    SysTick_Operate::Delay_us(6);
    SID.Set_Pin(Data >> 7);
    SysTick_Operate::Delay_us(6);
    Data <<= 1;
    SysTick_Operate::Delay_us(6);
    SCK.Set_Pin(1);
    SysTick_Operate::Delay_us(6);
    SCK.Set_Pin(0);
  }
}

/**
  * @brief  LCD12864写指令函数
  * @param  cmd:需要发送的指令
  * @retval None
  */
void LCD_12864_Serial::Write_Cmd(uchar cmd)
{
  CS.Set_Pin(1);
  Check_Busy();
  Send_Byte(0xf8);
  Send_Byte(0xf0 & cmd);
  Send_Byte(0xf0 & cmd << 4);
  CS.Set_Pin(0);
}

/**
  * @brief  LCD12864写数据函数
  * @param  Data:需要发送的数据
  * @retval None
  */
void LCD_12864_Serial::Write_Data(uchar Data)
{
  CS.Set_Pin(1);
  Check_Busy();
  Send_Byte(0xfa);
  Send_Byte(0xf0 & Data);
  Send_Byte(0xf0 & Data << 4);
  CS.Set_Pin(0);
}

/**
  * @brief  LCD12864调节输入位置函数
  * @param  x:行数(0~3)
  * @param  y:列数(0~7)
  * @retval None
  */
void LCD_12864_Serial::Pos(uchar x, uchar y)
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
  * @brief  LCD12864初始化函数(含GPIO)
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Init()
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
  * @brief  LCD12864 GPIO引脚初始化函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Pin_Init()
{
  CS = GPIO(Param.GPIO_CS_PORT, Param.CS_PIN);
  SID = GPIO(Param.GPIO_SID_PORT, Param.SID_PIN);
  SCK = GPIO(Param.GPIO_SCK_PORT, Param.SCK_PIN);

  CS.IN_MODE();
  SID.IN_MODE();
  SCK.IN_MODE();

  CS.OUT_MODE();
  SID.OUT_MODE();
  SCK.OUT_MODE();

  // GPIO_InitTypeDef g =
  // {
  //   GPIO_Pin_5,
  //   GPIO_Speed_50MHz,
  //   GPIO_Mode_Out_PP
  // };
  // GPIO a(GPIOB,g);
  // a.Init();
  // a.PinOff();
  // while(1);
}

/**
  * @brief  LCD12864判忙函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Check_Busy()
{
  do
    ;
  while (Read_Status() & 0x80);
}

/**
  * @brief  LCD12864写入CGRAM函数
  * @param  num:编号(0-3)
  * @param  p:存放字数据的指针
  * @retval None
  */
void LCD_12864_Serial::Set_CGRAM(uchar num, uchar *p)
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
  * @brief  LCD12864呈现CGRAM函数
  * @param  num:编号(0-3)
  * @param  x:行号
  * @param  y:列号
  * @retval None
  */
void LCD_12864_Serial::Display_CGRAM(uchar num, uchar x, uchar y)
{
  Pos(x, y);
  Write_Data(0x00); //CGRAM当作数据调用
  Write_Data(num * 2);
}

/**
  * @brief  空函数(给并行用的)
  * @retval None
  */
void LCD_12864_Serial::Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
}

/**
  * @brief  空函数(给并行用的)
  * @retval None
  */
void LCD_12864_Serial::Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
}

/**
  * @brief  空函数(给并行用的)
  * @retval None
  */
void LCD_12864_Serial::Draw_Point(uchar x, uchar y, uchar flag)
{
}

/**
  * @brief  LCD12864呈现CGRAM函数
  * @param  p:所需显示的字符串的指针
  * @param  row:行号
  * @param  col:列号
  * @retval None
  */
void LCD_12864_Serial::Show_String(uchar *p, uint16_t row, uint16_t col)
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
  * @brief  LCD12864绘图函数
  * @param  p:所需显示的字符串的指针
  * @retval None
  */
void LCD_12864_Serial::Display_Image(uchar *p)
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
  * @brief  LCD12864清空GDRAM函数
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Clear_GDRAM()
{
  uchar i, j;
  Write_Cmd(0x34); //扩充指令集,绘图模式关
  for (i = 0; i < 32; i++)
  {
    Write_Cmd(0x80 + i);
    Write_Cmd(0x80);
    for (j = 0; j < 16; j++)
    {
      Write_Data(0x00);
    }
  }
  for (i = 0; i < 32; i++)
  {
    Write_Cmd(0x80 + i);
    Write_Cmd(0x88);
    for (j = 0; j < 16; j++)
    {
      Write_Data(0x00);
    }
  }
  Write_Cmd(0x36);
  Write_Cmd(0x30);
}

/**
  * @brief  空函数(给并行用的)
  * @param  x:列号
  * @param  y:行号
  * @retval None
  */
void LCD_12864_Serial::Read_GDRAM(uchar x, uchar y)
{
}

/**
  * @brief  LCD12864设置GDRAM地址函数
  * @param  x:行号
  * @param  y:列号
  * @retval None
  */
void LCD_12864_Serial::Set_GDRAMadd(uchar x, uchar y)
{
  Write_Cmd(y + 0x80);
  Write_Cmd(x + 0x80);
}

/**
  * @brief  LCD12864读屏幕数据函数
  *         该函数串口不可用(串口无法读取屏幕数据)
  * @param  None
  * @retval None
  */
uchar LCD_12864_Serial::Read_Data()
{
  Send_Byte(0xfe);
  return Receive_Byte();
}

/**
  * @brief  LCD12864接受屏幕字节函数
  * @param  None
  * @retval None
  */
uchar LCD_12864_Serial::Receive_Byte()
{
  uchar tmp1, tmp2, i;
  tmp1 = 0;
  tmp2 = 0;
  for (i = 0; i < 8; i++)
  {
    tmp1 <<= 1;
    SysTick_Operate::Delay_us(5);
    SCK.Set_Pin(0);
    SysTick_Operate::Delay_us(5);
    SCK.Set_Pin(1);
    SysTick_Operate::Delay_us(5);
    SCK.Set_Pin(0);
    SysTick_Operate::Delay_us(5);
    if (SID.Get_Input_Pin())
      tmp1++;
  }
  for (i = 0; i < 8; i++)
  {
    tmp2 <<= 1;
    SCK.Set_Pin(0);
    SysTick_Operate::Delay_us(5);
    SCK.Set_Pin(1);
    SysTick_Operate::Delay_us(5);
    SCK.Set_Pin(0);
    SysTick_Operate::Delay_us(5);
    if (SID.Get_Input_Pin())
      tmp2++;
  }
  return (tmp1 & 0xf0) | (tmp2 >> 4);
}

/**
  * @brief  LCD12864读屏幕状态函数
  * @param  None
  * @retval None
  */
uchar LCD_12864_Serial::Read_Status()
{
  Send_Byte(0xfc);
  return Receive_Byte();
}