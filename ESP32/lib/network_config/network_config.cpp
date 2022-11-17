#include <network_config.h>
#include <WiFi.h>
#include <Preferences.h>
#include <task.h>
#include <Serial_LCD.h>
#include <GBK_SOURCE.h>

wl_status_t last_network_state = WL_IDLE_STATUS;

void setup_wifi()
{
    Preferences prefs;     // 声明Preferences对象
    prefs.begin("config"); // 打开命名空间config
    WiFi.mode(WIFI_AP_STA);
    String wifi_ssid = prefs.getString("ssid", "");     // 读取ssid
    String wifi_passwd = prefs.getString("passwd", ""); // 读取passwd
    if (wifi_ssid != "" && wifi_passwd != "")
    {
        WiFi.begin(wifi_ssid.c_str(), wifi_passwd.c_str());
        PLATFORM_PRINTLN("[网络管理]:WIFI连接到:" + wifi_ssid);
    }
    else
    {
        PLATFORM_PRINTLN("[网络管理]:没有读取到WIFI数据，不启动网络");
    }
    prefs.end(); // 关闭命名空间config
}

void network_config_Task(void *parameter)
{
    PLATFORM_PRINTLN("[线程管理]:启动SmartConfig配网线程");
    Preferences prefs;     // 声明Preferences对象
    prefs.begin("config"); // 打开命名空间config
    WiFi.beginSmartConfig();
    // Wait for SmartConfig packet from mobile
    PLATFORM_PRINTLN("[网络管理]:等待SmartConfig配网");
    while (!WiFi.smartConfigDone())
    {
        LCD_print("network.t0.txt=\"—\"");
        delay(500);
        LCD_print("network.t0.txt=\"|\"");
        delay(500);
    }
    prefs.putString("ssid", WiFi.SSID());  // 写入ssid
    prefs.putString("passwd", WiFi.psk()); // 写入passwd
    prefs.end();                           // 关闭命名空间config
    PLATFORM_PRINTLN("[网络管理]:配网完成，等待30秒重启");
    show_tips(network_config_suceess_msg, "WIFI: " + WiFi.SSID() + pass_msg + WiFi.psk() + "\\rIP: " + WiFi.localIP().toString(), "0"); // 显示提示
    delay(30000);
    ESP.restart();
}

void network_config_begin()
{
    xTaskCreate(
        network_config_Task,   /* Task function. */
        "network_config_Task", /* String with name of task. */
        10000,                 /* Stack size in bytes. */
        NULL,                  /* Parameter passed as input of the task */
        1,                     /* Priority of the task. */
        NULL);                 /* Task handle. */
    Task_Die();                // 先把所有线程全部结束
}

void Network_while()
{
    if (WiFi.status() != last_network_state)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            // 联网成功回调
            Serial.print("[网络管理]:联网成功，IP:");
            PLATFORM_PRINTLN(WiFi.localIP().toString());
            configTime(60 * 60 * 8, 0, "ntp3.aliyun.com"); // 用的阿里云的服务器
            // 既然已经联网成功了，那为什么不挂载 MQTT 呢
            // mqtt_int();
        }
        else
        {
            // 网络断开回调
            PLATFORM_PRINTLN("[网络管理]:网络断开");
            // mqtt_disable();
        }
    }
    last_network_state = WiFi.status();
    if (WiFi.status() == WL_CONNECTED)
    {
        // mqtt_while();
    }
}
