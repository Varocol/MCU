#ifndef __VARIABLES_H
#define __VARIABLES_H
#include <Preferences.h>
#include <map>
#include <Arduino.h>
#include <AS608_Fingerprint.h>
#include <SoftwareSerial.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
using namespace std;
#define PLATFORM_FINGER Finger
#define PLATFORM_SERIAL Serial
#define SOCKET_PRINTF(...) websocket.printfAll(__VA_ARGS__)
#define SOCKET_PRINTLN(fmt,...) websocket.printfAll(String(fmt).c_str(),##__VA_ARGS__)
#define SERIAL_PRINTF(...) PLATFORM_SERIAL.printf(__VA_ARGS__)
#define SERIAL_PRINTLN(...) PLATFORM_SERIAL.println(__VA_ARGS__)
#define PLATFORM_PRINTF(...)\
        SOCKET_PRINTF(__VA_ARGS__);\
        SERIAL_PRINTF(__VA_ARGS__)
    #define PLATFORM_PRINTLN(...)\
        SOCKET_PRINTLN(__VA_ARGS__);\
        SERIAL_PRINTLN(__VA_ARGS__)

typedef struct
{
    uint8_t Tx;                // Tx引脚
    uint8_t Rx;                // Rx引脚
    uint32_t Password;         //指纹模块密码
    uint32_t SoftwareBaudrate; //软串口波特率
    uint8_t Baudrate;          //指纹模块波特率
    uint16_t PacketSize;       //指纹模块包大小
    uint8_t SecurityLevel;     //指纹模块安全等级
} FingerPrint_Param;

typedef struct
{
    uint32_t Baudrate; //串口波特率
} Serial_Param;

extern DynamicJsonDocument finger_data;
extern FingerPrint_Param fingerprint_param;
extern HardwareSerial mySerial;
extern AS608_Fingerprint Finger;
extern Serial_Param serial_param;
extern File finger_file;
extern File finger_backup_file;
extern AsyncWebSocket websocket;
#endif /*__VARIABLES_H*/