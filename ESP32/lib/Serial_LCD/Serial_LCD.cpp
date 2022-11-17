#include "Serial_LCD.h"
#include "LCD_callback.h"
#include "HardwareSerial.h"
#include "LCD_keypad.h"
#include "network_config.h"
#include "debug.h"
#include "WiFi.h"
#include <GBK_SOURCE.h>

extern int page_position;
int page_state;               // 屏幕当前页面ID标记
HardwareSerial LCD_Serial(1); //屏幕软串口

void LCD_debug(String str)
{
  PLATFORM_PRINTLN("[LCD屏幕]:" + str); //打印comdata数据
}

void LCD_setup()
{
  LCD_Serial.begin(115200, SERIAL_8N1, 22, 23);
  //因为串口屏开机会发送88 ff ff ff,所以要清空串口缓冲区
  while (LCD_Serial.read() >= 0)
    ;                               //清空串口缓冲区
  LCD_Serial.print("\xff\xff\xff"); //过滤数据
  page_state = 0;
  LCD_print("page 13");
  LCD_debug("屏幕初始化成功");
}

void LCD_print(String out_data)
{
  out_data = "\xff\xff\xff" + out_data + "\xff\xff\xff";
  LCD_Serial.print(out_data);
}

void LCD_while()
{
  if (LCD_Serial.available() > 0) //判读是否串口有数据
  {
    String raw_data = "";              //缓存清零
    while (LCD_Serial.available() > 0) //循环串口是否有数据
    {
      raw_data += char(LCD_Serial.read()); //叠加数据到raw_data
      delay(2);                            //延时等待响应
    }
    if (raw_data.length() > 0) //如果raw_data有数据
    {
      deal_lcd_cmd(raw_data);
    }
  }
}

void star_ota()
{
  delay(100);
  LCD_print("t0.txt=\"" + WiFi.localIP().toString() + "\"");
}

void deal_lcd_cmd(String raw_data)
{
  vector<String> raw_data_arry;
  int index = 0;
  int last_index = 0;
  while (1)
  {
    index = raw_data.indexOf("|", last_index);
    if (index == -1)
    {
      break;
    }
    String temp = raw_data.substring(last_index, index);
    raw_data_arry.push_back(temp);
    last_index = last_index + index + 1;
  }

  if (raw_data_arry.size() < 1)
  {
    LCD_debug("无效的屏幕串口数据");
    return;
  }

  if (raw_data_arry.at(0) == "add")
  {
    add_user(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "del")
  {
    // 预删除，弹出提示框
    show_confirm(tip_msg, delete_confirm_msg + raw_data_arry.at(1) + question_msg, "2", "delR|" + raw_data_arry.at(1) + "|0");
  }
  if (raw_data_arry.at(0) == "delR")
  {
    delete_user(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "adm")
  {
    set_admin(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "chp")
  {
    // 预设置用户密码，弹出提示框
    show_confirm(tip_msg, user_pass_confirm_msg + raw_data_arry.at(1) + question_msg, "6", "chpR|" + raw_data_arry.at(1) + "|0");
  }
  if (raw_data_arry.at(0) == "chpR")
  {
    change_user_password(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "cha")
  {
    // 预设置管理密码，弹出提示框
    show_confirm(tip_msg, admin_pass_confirm_msg + raw_data_arry.at(1) + question_msg, "6", "chaR|" + raw_data_arry.at(1) + "|0");
  }
  if (raw_data_arry.at(0) == "chaR")
  {
    change_admin_password(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "clk")
  {
    unlock(raw_data_arry.at(1));
  }
  if (raw_data_arry.at(0) == "page")
  {
    page_state = raw_data_arry.at(1).toInt();
    LCD_debug("屏幕切换到" + String(page_state));
    if (page_state == 14)
    {
      page_position = 0;
      Show_finger_list();
    }
  }
  if (raw_data_arry.at(0) == "net")
  {
    LCD_print("page 10");
    network_config_begin();
  }
  if (raw_data_arry.at(0) == "dbg")
  {
    if (raw_data_arry.at(1) == "lcd")
    {
      debug_LCD();
    }
    if (raw_data_arry.at(1) == "fig")
    {
      debug_finger();
    }
  }
  if (raw_data_arry.at(0) == "clean")
  {
    Return_to_factory();
  }
  if (raw_data_arry.at(0) == "ota")
  {
    star_ota();
  }
  if (raw_data_arry.at(0) == "turn")
  {
    if (raw_data_arry.at(1) == "up")
    {
      if (page_position >= 5)
        page_position = page_position - 5;
    }
    else if (raw_data_arry.at(1) == "down")
    {
      page_position = page_position + 5;
    }
    Show_finger_list();
  }
}

/**
 * 控制屏幕返回主页面
 * @return 空
 */
void back_home_page()
{
  LCD_print("page 0");
}

/**
 * 弹出对话框
 * @param title 标题
 * @param center 正文
 * @param last_page 返回页面ID
 * @param cmd 点击确认执行的命令
 * @return 空
 */
void show_confirm(String title, String center, String last_page, String cmd)
{
  LCD_print("confirm.title.txt=\"" + title + "\"");
  LCD_print("confirm.center.txt=\"" + center + "\"");
  LCD_print("confirm.last_page.val=" + last_page);
  LCD_print("confirm.cmd.txt=\"" + cmd + "\"");
  LCD_print("page 3");
}

/**
 * 弹出提示框
 * @param title 标题
 * @param center 正文
 * @param last_page 返回页面ID
 * @return 空
 */
void show_tips(String title, String center, String last_page)
{
  LCD_print("tips.title.txt=\"" + title + "\"");
  LCD_print("tips.center.txt=\"" + center + "\"");
  LCD_print("tips.last_page.val=" + last_page);
  LCD_print("page 4");
}

/**
 * 进入管理员菜单
 * @param password 解锁密码
 * @return 空
 */
void show_admin(String password)
{
  LCD_print("admin.passwd.txt=\"" + password + "\"");
  LCD_print("page 7");
}
/**
 * 进入选择菜单
 * @return 空
 */
void show_menu()
{
  delay(800);
  //检测GPIO0电平（消抖）
  if (digitalRead(0) == 0)
  {
    if (page_state == 0)
      LCD_print("page 1");
  }
}

/**
 * 开机画面
 * @return 空
 */
void show_first()
{
  LCD_print("page 13");
}