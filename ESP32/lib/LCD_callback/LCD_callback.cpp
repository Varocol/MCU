#include "LCD_callback.h"
#include "Serial_LCD.h"
#include <Preferences.h>
#include <Unclock_Servo.h>
#include <FINGERPrint.h>
#include <Variables.h>
#include <GBK_SOURCE.h>

/**
 * 添加用户
 * @param school_id 屏幕传回来的学号
 * @return 空
 */
void add_user(String school_id)
{
  LCD_debug("添加用户: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips(tip_msg, school_id_len_error_msg, "6");
    return;
  }
  // 调用欧阳的指纹录入接口
  FingerPrint_Enroll(school_id);
}

/**
 * 删除用户
 * @param school_id 屏幕传回来的学号
 * @return 空
 */
void delete_user(String school_id)
{
  LCD_debug("删除用户: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips(tip_msg, school_id_len_error_msg, "6");
    return;
  }
  // 调用欧阳的指纹删除接口
  FingerPrint_Delete(school_id);
}

/**
 * 设置管理员
 * @param school_id 屏幕传回来的学号
 * @return 空
 */
void set_admin(String school_id)
{
  LCD_debug("设置管理员: " + school_id);
  if (school_id.length() < 1 || school_id.length() > 20)
  {
    show_tips(tip_msg, school_id_len_error_msg, "6");
    return;
  }
  show_tips(tip_msg, function_invalid_msg, "6");
}

/**
 * 修改用户密码
 * @param password 屏幕传回来的解锁密码
 * @return 空
 */
void change_user_password(String password)
{
  LCD_debug("修改解锁密码: " + password);
  if (password.length() != 6)
  {
    show_tips(tip_msg, password_len_error_msg, "6");
    return;
  }
  Preferences prefs;                                           // 声明Preferences对象
  prefs.begin("config");                                       // 打开命名空间config
  String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
  if (password == real_admin_password)
  {
    show_tips(tip_msg, password_invalid_msg_1, "6");
    return;
  }
  prefs.putString("user_k", password); // 写入解锁密码
  prefs.end();                         // 关闭命名空间
  show_tips(tip_msg, alert_pass_success_msg, "6");
}

/**
 * 修改管理密码
 * @param password 屏幕传回来的解锁密码
 * @return 空
 */
void change_admin_password(String password)
{
  LCD_debug("修改管理密码: " + password);
  if (password.length() != 6)
  {
    show_tips(tip_msg, password_len_error_msg, "6");
    return;
  }
  Preferences prefs;                                         // 声明Preferences对象
  prefs.begin("config");                                     // 打开命名空间config
  String real_user_password = prefs.getString("user_k", ""); // 读取用户密码
  if (password == real_user_password)
  {
    show_tips(tip_msg, password_invalid_msg_2, "6");
    return;
  }
  prefs.putString("admin_k", password); // 写入解锁密码
  prefs.end();                          // 关闭命名空间
  show_tips(tip_msg, alert_pass_success_msg, "6");
}

/**
 * 密码解锁回调
 * @param password 解锁密码
 * @return 空
 */
void unlock(String password)
{
  LCD_debug("密码解锁: " + password);
  //解锁逻辑
  Preferences prefs;                                           // 声明Preferences对象
  prefs.begin("config");                                       // 打开命名空间config
  String real_user_password = prefs.getString("user_k", "");   // 读取用户密码
  String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
  prefs.end();

  //判断是否为空
  if (real_user_password == "" || real_admin_password == "")
  {
    LCD_debug("密码为空");
    show_tips(pass_error_msg, pass_unset_msg, "0");
    return;
  }
  //判断是否为管理员密码
  if (password == real_admin_password)
  {
    LCD_debug("管理员密码解锁");
    LCD_print("page 1");
    unclock_servo_open();
    return;
  }
  //判断是否为用户密码
  if (password == real_user_password)
  {
    LCD_debug("用户密码解锁");
    show_tips(unlock_success_msg, pass_unlock_msg, "0");
    unclock_servo_open();
    return;
  }
  show_tips(tip_msg, invalid_pass_msg, "0");
}

/**
 * 恢复出厂回调
 * @param 空
 * @return 空
 */
void Return_to_factory()
{
  LCD_print("t0.txt=\"" + wait_msg + "\"");
  Preferences prefs;     // 声明Preferences对象
  prefs.begin("config"); // 打开命名空间config
  prefs.clear();         // 清除数据
  FingerPrint_ClearDB(); //清空指纹库
  Store_Format();        //格式化存储器
  ESP.restart();
}

/**
 * 显示指纹列表回调
 * @param 空
 * @return 空
 */
int page_position = 0;
void Show_finger_list()
{
  uint16_t cost = PLATFORM_FINGER.IndexTable.size();
  if (cost == 0)
  {
    show_tips(tip_msg, fingerprint_empty_msg, "0");
    return;
  }
  LCD_print("t10.txt=\"" + String((page_position / 5) + 1) + "\"");
  for (int m = 0; m < 5; m = m + 1)
  {
    int tp = page_position + m;
    if (tp >= cost)
    {
      LCD_print("t" + String(m) + ".txt=\"\"");
      LCD_print("va" + String(m) + ".val=-1");
      continue;
    }
    String temp = "ID:" + String(tp) + school_id_msg_1 + finger_data[String(tp)][finger_keys.school_id].as<String>() + cnt_msg + finger_data[String(tp)][finger_keys.operations_cnt].as<String>();
    LCD_print("t" + String(m) + ".txt=\"" + temp + "\"");
    LCD_print("va" + String(m) + ".val=" + String(tp));
  }
}
