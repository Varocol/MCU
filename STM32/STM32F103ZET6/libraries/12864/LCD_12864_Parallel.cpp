#include "LCD_12864_Parallel.h"

/**
 * @brief  LCD12864����-�չ��췽��
 * @param  None
 * @retval None
 */
LCD_12864_Parallel::LCD_12864_Parallel()
{
}

/**
 * @brief  LCD12864����-���ι��췽��
 * @param  Param        LCD12864���в����б�
 * @retval None
 */
LCD_12864_Parallel::LCD_12864_Parallel(LCD_12864_Param_Parallel Param)
{
      Set_Param(Param);
}

/**
 * @brief  LCD12864����-���ò�������
 * @param  Param        LCD12864���в����б�
 * @retval None
 */
void LCD_12864_Parallel::Set_Param(LCD_12864_Param_Parallel Param)
{
      this->Param = Param;
}

/**
 * @brief  LCD12864����-���²�������
 * @param  Param        LCD12864���в����б�
 * @retval None
 */
void LCD_12864_Parallel::Update(LCD_12864_Param_Parallel Param)
{
      Set_Param(Param);
      Init();
}

/**
 * @brief  LCD12864����-���DDRAM����
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Clear_DDRAM()
{
      Write_Cmd(0x01);
      Write_Cmd(0x03);
}

/**
 * @brief  LCD12864����-�շ���(�������õ�)
 * @param  Data         ��Ҫ���͵��ֽ�
 * @retval None
 */
void LCD_12864_Parallel::Send_Byte(uchar Data)
{
}

/**
 * @brief  LCD12864����-д��Ļָ���
 * @param  cmd          ָ��
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
 * @brief  LCD12864����-д��Ļ���ݷ���
 * @param  Data         ����
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
 * @brief  LCD12864����-дλ�÷���
 * @param  x            �к�
 * @param  y            �к�
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
 * @brief  LCD12864����-��ʼ������(��GPIO)
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
 * @brief  LCD12864����-GPIO��ʼ������
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Pin_Init()
{
      //��ʼ��RS RW EN IOgpio��
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
 * @brief  LCD12864����-��æ����
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
 * @brief  LCD12864����-����CGRAM����
 * @param  num          ���
 * @param  p            ����ָ��
 * @retval None
 */
void LCD_12864_Parallel::Set_CGRAM(uchar num, uchar *p)
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
 * @brief  LCD12864����-����CGRAM����
 * @param  num          ���
 * @param  x            �к�
 * @param  y            �к�
 * @retval None
 */
void LCD_12864_Parallel::Display_CGRAM(uchar num, uchar x, uchar y)
{
      Pos(x, y);
      Write_Data(0x00); // CGRAM�������ݵ���
      Write_Data(num * 2);
}

/**
 * @brief  LCD12864����-д�ַ���
 * @param  p            ����ָ��
 * @param  row          �к�
 * @param  col          �к�
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
 * @brief  LCD12864����-����ͼƬ
 * @param  p            ����ָ��
 * @retval None
 */
void LCD_12864_Parallel::Display_Image(uchar *p)
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
 * @brief  LCD12864����-���ٻ�����
 * @param  x1           ���ϽǺ�����
 * @param  y1           ���Ͻ�������
 * @param  x2           ���½Ǻ�����
 * @param  y2           ���½�������
 * @param  flag         ���״̬
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
      Write_Cmd(0x36); //����ָ�,��ͼģʽ��(���ùر����ٿ�,�����Ƶ��)
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
                              Write_Data(fill | Lbit); // GDRAM���������ֽ�Ϊ��λ�����
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
 * @brief  LCD12864����-���ٻ�����
 * @param  x1           ���ϽǺ�����
 * @param  y1           ���Ͻ�������
 * @param  x2           ���½Ǻ�����
 * @param  y2           ���½�������
 * @param  flag         ���״̬
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
 * @brief  LCD12864����-���
 * @param  x            �������
 * @param  y            ��������
 * @param  flag         ���״̬
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
                  Write_Data(Lbit & (~(fill >> (x % 16 - 8)))); //'~'���ȼ�����'>>'������
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
 * @brief  LCD12864����-���GDRAM
 * @param  None
 * @retval None
 */
void LCD_12864_Parallel::Clear_GDRAM()
{
      uchar i, j;
      Write_Cmd(0x36); //����ָ�,��ͼģʽ��
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
 * @brief  LCD12864����-����GDRAM��ַ
 * @param  x            �к�
 * @param  y            �к�
 * @retval None
 */
void LCD_12864_Parallel::Set_GDRAMadd(uchar x, uchar y)
{
      Write_Cmd(y + 0x80);
      Write_Cmd(x + 0x80);
}

/**
 * @brief  LCD12864����-��ȡGDRAM����
 * @param  x            �к�
 * @param  y            �к�
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
 * @brief  LCD12864����-��ȡ��Ļ����
 * @param  None
 * @retval ��Ļ����
 */
uchar LCD_12864_Parallel::Read_Data() //���в�����
{
      Check_Busy(); //��æ����һ��Ҫ�ӣ�����
      IO.Set_Port_Val(0xff);
      RS.Set_Pin_Val(1); // RS=1 RW=1 E=������
      RW.Set_Pin_Val(1);
      EN.Set_Pin_Val(1);
      IO.IN_MODE();
      temp = (uint8_t)IO.Get_Input_Port();
      EN.Set_Pin_Val(0);
      return temp;
}

/**
 * @brief  LCD12864����-�շ���(�������õ�)
 * @param  None
 * @retval ���յ����ֽ�
 */
uchar LCD_12864_Parallel::Receive_Byte()
{
      return 0;
}

/**
 * @brief  LCD12864����-�շ���(�������õ�)
 * @param  None
 * @retval LCD��״̬
 */
uchar LCD_12864_Parallel::Read_Status()
{
      return 0;
}