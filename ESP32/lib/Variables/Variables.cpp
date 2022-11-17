#include <Variables.h>
//指纹模块变量区
/*
json格式
{
    "1":{
        "school_id":
        "operations_cnt":
    },
    "2":{
        ...
    },
    ...
}
*/
//预分配2k空间
DynamicJsonDocument finger_data(2048);
FingerPrint_Param fingerprint_param = {
    .Tx = 16,
    .Rx = 17,
    .Password = 0,
    .SoftwareBaudrate = 9600,
    .Baudrate = FINGERPRINT_BAUDRATE_9600,
    .PacketSize = FINGERPRINT_PACKET_SIZE_256,
    .SecurityLevel = FINGERPRINT_SECURITY_LEVEL_1};
HardwareSerial mySerial(2);
AS608_Fingerprint Finger(&mySerial);

//串口变量区
Serial_Param serial_param = {
    .Baudrate = 115200};

//文件系统变量
File finger_file;
File finger_backup_file;

//舵机驱动变量
bool servo_flag = false;

// websocket
AsyncWebSocket websocket("/ws");