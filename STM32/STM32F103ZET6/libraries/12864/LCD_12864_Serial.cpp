#include "LCD_12864_Serial.h"
/**
  * @brief  �չ��캯��
  * @param  None
  * @retval None
  */
LCD_12864_Serial::LCD_12864_Serial()
{
}

/**
  * @brief  ���ι��캯��
  * @param  None
  * @retval None
  */
LCD_12864_Serial::LCD_12864_Serial(LCD_12864_Param_Serial Param)
{
  Set_Param(Param);
}

/**
  * @brief  ���ò�������
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Set_Param(LCD_12864_Param_Serial Param)
{
  this->Param = Param;
}

/**
  * @brief  ���²�������
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Update(LCD_12864_Param_Serial Param)
{
  Set_Param(Param);
  Init();
}

/**
  * @brief  LCD12864��������
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Clear_DDRAM()
{
  Write_Cmd(0x01);
  Write_Cmd(0x03);
}

/**
  * @brief  LCD12864���͵��ֽں���
  * @param  Data:��Ҫ���͵��ֽ�
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
  * @brief  LCD12864дָ���
  * @param  cmd:��Ҫ���͵�ָ��
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
  * @brief  LCD12864д���ݺ���
  * @param  Data:��Ҫ���͵�����
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
  * @brief  LCD12864��������λ�ú���
  * @param  x:����(0~3)
  * @param  y:����(0~7)
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
  * @brief  LCD12864��ʼ������(��GPIO)
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
  * @brief  LCD12864 GPIO���ų�ʼ������
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
  * @brief  LCD12864��æ����
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
  * @brief  LCD12864д��CGRAM����
  * @param  num:���(0-3)
  * @param  p:��������ݵ�ָ��
  * @retval None
  */
void LCD_12864_Serial::Set_CGRAM(uchar num, uchar *p)
{
  uchar i, firstadd;
  Write_Cmd(0x34); //����ָ�
  Write_Cmd(0x02); //��13��,��������CGRAM��ַ
  Write_Cmd(0x30); //�ص�����ָ�
  firstadd = (0x40 | num << 4);
  for (i = 0; i < 16; i++)
  {
    Write_Cmd(firstadd + i); //����������
    Write_Data(p[i * 2]);
    Write_Data(p[i * 2 + 1]);
  }
}

/**
  * @brief  LCD12864����CGRAM����
  * @param  num:���(0-3)
  * @param  x:�к�
  * @param  y:�к�
  * @retval None
  */
void LCD_12864_Serial::Display_CGRAM(uchar num, uchar x, uchar y)
{
  Pos(x, y);
  Write_Data(0x00); //CGRAM�������ݵ���
  Write_Data(num * 2);
}

/**
  * @brief  �պ���(�������õ�)
  * @retval None
  */
void LCD_12864_Serial::Draw_Rectangle(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
}

/**
  * @brief  �պ���(�������õ�)
  * @retval None
  */
void LCD_12864_Serial::Draw_Rectangle_1(uchar x1, uchar y1, uchar x2, uchar y2, uchar flag)
{
}

/**
  * @brief  �պ���(�������õ�)
  * @retval None
  */
void LCD_12864_Serial::Draw_Point(uchar x, uchar y, uchar flag)
{
}

/**
  * @brief  LCD12864����CGRAM����
  * @param  p:������ʾ���ַ�����ָ��
  * @param  row:�к�
  * @param  col:�к�
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
  * @brief  LCD12864��ͼ����
  * @param  p:������ʾ���ַ�����ָ��
  * @retval None
  */
void LCD_12864_Serial::Display_Image(uchar *p)
{
  uchar i, j;
  Write_Cmd(0x34); //����ָ�,��ͼģʽ��
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
  * @brief  LCD12864���GDRAM����
  * @param  None
  * @retval None
  */
void LCD_12864_Serial::Clear_GDRAM()
{
  uchar i, j;
  Write_Cmd(0x34); //����ָ�,��ͼģʽ��
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
  * @brief  �պ���(�������õ�)
  * @param  x:�к�
  * @param  y:�к�
  * @retval None
  */
void LCD_12864_Serial::Read_GDRAM(uchar x, uchar y)
{
}

/**
  * @brief  LCD12864����GDRAM��ַ����
  * @param  x:�к�
  * @param  y:�к�
  * @retval None
  */
void LCD_12864_Serial::Set_GDRAMadd(uchar x, uchar y)
{
  Write_Cmd(y + 0x80);
  Write_Cmd(x + 0x80);
}

/**
  * @brief  LCD12864����Ļ���ݺ���
  *         �ú������ڲ�����(�����޷���ȡ��Ļ����)
  * @param  None
  * @retval None
  */
uchar LCD_12864_Serial::Read_Data()
{
  Send_Byte(0xfe);
  return Receive_Byte();
}

/**
  * @brief  LCD12864������Ļ�ֽں���
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
  * @brief  LCD12864����Ļ״̬����
  * @param  None
  * @retval None
  */
uchar LCD_12864_Serial::Read_Status()
{
  Send_Byte(0xfc);
  return Receive_Byte();
}