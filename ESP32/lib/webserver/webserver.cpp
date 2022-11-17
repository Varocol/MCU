#include "webserver.h"
#include "Unclock_Servo.h"
#include "FingerPrint.h"
#include <Preferences.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <WiFi.h>
#include <Variables.h>

AsyncWebServer server(80);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    if (type == WS_EVT_CONNECT)
    {
        // client connected
        SERIAL_PRINTF("ws[%s][%u] connect\n", server->url(), client->id());
        client->printf("Hello Client %u :)", client->id());
        client->ping();
    }
    else if (type == WS_EVT_DISCONNECT)
    {
        // client disconnected
        SERIAL_PRINTF("ws[%s][%u] disconnect: %u\n", server->url(), client->id());
    }
    else if (type == WS_EVT_ERROR)
    {
        // error was received from the other end
        SERIAL_PRINTF("ws[%s][%u] error(%u): %s\n", server->url(), client->id(), *((uint16_t *)arg), (char *)data);
    }
    else if (type == WS_EVT_PONG)
    {
        // pong message was received (in response to a ping request maybe)
        SERIAL_PRINTF("ws[%s][%u] pong[%u]: %s\n", server->url(), client->id(), len, (len) ? (char *)data : "");
    }
    else if (type == WS_EVT_DATA)
    {
        // data packet
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->final && info->index == 0 && info->len == len)
        {
            // the whole message is in a single frame and we got all of it's data
            SERIAL_PRINTF("ws[%s][%u] %s-message[%llu]: ", server->url(), client->id(), (info->opcode == WS_TEXT) ? "text" : "binary", info->len);
            if (info->opcode == WS_TEXT)
            {
                data[len] = 0;
                SERIAL_PRINTF("%s\n", (char *)data);
            }
            else
            {
                for (size_t i = 0; i < info->len; i++)
                {
                    SERIAL_PRINTF("%02x ", data[i]);
                }
                SERIAL_PRINTF("\n");
            }
            if (info->opcode == WS_TEXT)
                client->text("I got your text message");
            else
                client->binary("I got your binary message");
        }
        else
        {
            // message is comprised of multiple frames or the frame is split into multiple packets
            if (info->index == 0)
            {
                if (info->num == 0)
                    SERIAL_PRINTF("ws[%s][%u] %s-message start\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
                SERIAL_PRINTF("ws[%s][%u] frame[%u] start[%llu]\n", server->url(), client->id(), info->num, info->len);
            }

            SERIAL_PRINTF("ws[%s][%u] frame[%u] %s[%llu - %llu]: ", server->url(), client->id(), info->num, (info->message_opcode == WS_TEXT) ? "text" : "binary", info->index, info->index + len);
            if (info->message_opcode == WS_TEXT)
            {
                data[len] = 0;
                SERIAL_PRINTF("%s\n", (char *)data);
            }
            else
            {
                for (size_t i = 0; i < len; i++)
                {
                    SERIAL_PRINTF("%02x ", data[i]);
                }
                SERIAL_PRINTF("\n");
            }

            if ((info->index + len) == info->len)
            {
                SERIAL_PRINTF("ws[%s][%u] frame[%u] end[%llu]\n", server->url(), client->id(), info->num, info->len);
                if (info->final)
                {
                    SERIAL_PRINTF("ws[%s][%u] %s-message end\n", server->url(), client->id(), (info->message_opcode == WS_TEXT) ? "text" : "binary");
                    if (info->message_opcode == WS_TEXT)
                        client->text("I got your text message");
                    else
                        client->binary("I got your binary message");
                }
            }
        }
    }
}
void int_web()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/html", main_HTML); });

    server.on("/unlock", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key")) {
                String inputMessage1;
                inputMessage1 = request->getParam("admin_key")->value();
                //解锁逻辑
                Preferences prefs;                                           // 声明Preferences对象
                prefs.begin("config");                                       // 打开命名空间config
                String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                prefs.end();
                if(inputMessage1 == real_admin_password){
                     unclock_servo_open();
                    back_data = "{\"e\":\"开锁成功\"}";
                }else{
                    back_data = "{\"e\":\"管理员密码错误\"}";
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码\"}";
            }
            request->send(200, "application/json", back_data); });

    server.on("/getlist", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key")) {
                String inputMessage1;
                inputMessage1 = request->getParam("admin_key")->value();
                //解锁逻辑
                Preferences prefs;                                           // 声明Preferences对象
                prefs.begin("config");                                       // 打开命名空间config
                String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                prefs.end();
                if(inputMessage1 == real_admin_password){
                    back_data = FingerPrint_GetDataJson();
                }else{
                    back_data = "{\"e\":\"管理员密码错误\"}";
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码\"}";
            }
            request->send(200, "application/json", back_data); });

    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key")) {
                String inputMessage1;
                inputMessage1 = request->getParam("admin_key")->value();
                //解锁逻辑
                Preferences prefs;                                           // 声明Preferences对象
                prefs.begin("config");                                       // 打开命名空间config
                String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                prefs.end();
                if(inputMessage1 == real_admin_password){
                    back_data = "{\"e\":\"连接成功 MAC:" + WiFi.macAddress() + "\"}";
                }else{
                    back_data = "{\"e\":\"管理员密码错误\"}";
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码\"}";
            }
            request->send(200, "application/json", back_data); });

    server.on("/set_user_key", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key") && request->hasParam("new_user_key")) {
                String inputMessage1;
                String inputMessage2;
                inputMessage1 = request->getParam("admin_key")->value();
                inputMessage2 = request->getParam("new_user_key")->value();
                //判断inputMessage2是否为6位数字
                if (inputMessage2.length() != 6)
                {
                    back_data = "{\"e\":\"新用户密码必须为6位数字\"}";
                }
                else
                {
                    //解锁逻辑
                    Preferences prefs;                                           // 声明Preferences对象
                    prefs.begin("config");                                       // 打开命名空间config
                    String real_user_password = prefs.getString("user_k", "");   // 读取用户密码
                    String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                    prefs.end();
                    if(inputMessage1 == real_admin_password){
                        if (inputMessage2 != real_admin_password)
                        {
                            Preferences prefs;                                           // 声明Preferences对象
                            prefs.begin("config");                                       // 打开命名空间config
                            prefs.putString("user_k", inputMessage2); // 写入解锁密码
                            prefs.end();                         // 关闭命名空间
                            back_data = "{\"e\":\"设置成功\"}";
                        }else{
                            back_data = "{\"e\":\"用户密码不能和管理员密码相同\"}";
                        }
                    }else{
                        back_data = "{\"e\":\"管理员密码错误\"}";
                    }
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码和新用户密码\"}";
            }
            request->send(200, "application/json", back_data); });

    server.on("/set_admin_key", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key") && request->hasParam("new_admin_key")) {
                String inputMessage1;
                String inputMessage2;
                inputMessage1 = request->getParam("admin_key")->value();
                inputMessage2 = request->getParam("new_admin_key")->value();
                //判断inputMessage2是否为6位数字
                if (inputMessage2.length() != 6)
                {
                    back_data = "{\"e\":\"新管理员密码必须为6位数字\"}";
                }
                else
                {
                    //解锁逻辑
                    Preferences prefs;                                           // 声明Preferences对象
                    prefs.begin("config");                                       // 打开命名空间config
                    String real_user_password = prefs.getString("user_k", "");   // 读取用户密码
                    String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                    prefs.end();
                    if(inputMessage1 == real_admin_password){
                        if (inputMessage2 != real_user_password)
                        {
                            Preferences prefs;                                           // 声明Preferences对象
                            prefs.begin("config");                                       // 打开命名空间config
                            prefs.putString("admin_k", inputMessage2); // 写入解锁密码
                            prefs.end();                         // 关闭命名空间
                            back_data = "{\"e\":\"设置成功\"}";
                        }else{
                            back_data = "{\"e\":\"管理员密码不能和用户密码相同\"}";
                        }
                    }else{
                        back_data = "{\"e\":\"管理员密码错误\"}";
                    }
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码和新用户密码\"}";
            }
            request->send(200, "application/json", back_data); });
    server.on("/del_finger", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key") && request->hasParam("list")) {
                String inputMessage1;
                String inputMessage2;
                inputMessage1 = request->getParam("admin_key")->value();
                inputMessage2 = request->getParam("list")->value();
                //判断list和new_id不为空
                if (inputMessage2.isEmpty())
                {
                    back_data = "{\"e\":\"未选中任何指纹\"}";
                }
                else
                {
                    //解锁逻辑
                    Preferences prefs;                                           // 声明Preferences对象
                    prefs.begin("config");                                       // 打开命名空间config
                    String real_user_password = prefs.getString("user_k", "");   // 读取用户密码
                    String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                    prefs.end();
                    if(inputMessage1 == real_admin_password){
                        FingerPrint_Delete(inputMessage2);
                        back_data = "{\"e\":\"删除成功\"}";
                    }else{
                        back_data = "{\"e\":\"管理员密码错误\"}";
                    }
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码\"}";
            }
            request->send(200, "application/json", back_data); });
    server.on("/alert_finger", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                String back_data;
            if (request->hasParam("admin_key") && request->hasParam("list")&& request->hasParam("new_id")) {
                String inputMessage1;
                String inputMessage2;
                String inputMessage3;
                inputMessage1 = request->getParam("admin_key")->value();
                inputMessage2 = request->getParam("list")->value();
                inputMessage3 = request->getParam("new_id")->value();
                //判断list和new_id不为空
                if (inputMessage2.isEmpty())
                {
                    back_data = "{\"e\":\"未选中任何指纹\"}";
                }
                else if (inputMessage3.length() > 20 || inputMessage3.length() < 1)
                {
                    back_data = "{\"e\":\"学号长度为1-20位\"}";
                }
                else
                {
                    //解锁逻辑
                    Preferences prefs;                                           // 声明Preferences对象
                    prefs.begin("config");                                       // 打开命名空间config
                    String real_user_password = prefs.getString("user_k", "");   // 读取用户密码
                    String real_admin_password = prefs.getString("admin_k", ""); // 读取管理员密码
                    prefs.end();
                    if(inputMessage1 == real_admin_password){
                        FingerPrint_Alert(inputMessage2, inputMessage3);
                        back_data = "{\"e\":\"修改成功\"}";
                    }else{
                        back_data = "{\"e\":\"管理员密码错误\"}";
                    }
                }
            }
            else {
                back_data = "{\"e\":\"请输入管理员密码\"}";
            }
            request->send(200, "application/json", back_data); });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    AsyncElegantOTA.begin(&server); // Start AsyncElegantOTA
    websocket.onEvent(onEvent);
    server.addHandler(&websocket);
    server.begin();
}