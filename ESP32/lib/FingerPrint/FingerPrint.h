#ifndef __FINGERPRINT_H
#define __FINGERPRINT_H

#include <Arduino.h>
#include <map>
#include <vector>
using namespace std;

#define FINGER_SETPASSWORD false
#define FINGER_AUTOENROLL true
#define FINGER_AUTOIDENTIFY true
#define FINGER_TIMELIMIT 4
#define FINGER_DATA_PATH "/data.txt"
#define FINGER_DATA_BACKUP_PATH "/backup.txt"
#define FINGER_KEYDEFAULTVALUE "UNKNOW"

struct
{
    String school_id;
    String operations_cnt;
} finger_keys{
    .school_id = "school_id",
    .operations_cnt = "operations_cnt"};

typedef enum
{
    Finger_Delete_FingerPrint = 1,
    Finger_Delete_ID,
} Finger_Delete_Mode;
typedef enum
{
    Finger_Search_FingerPrint = 1,
    Finger_Search_Name,
} Finger_Search_Mode;
//TODO 备份json,上传指纹库,备份指纹库
//功能函数
void FingerPrint_Init();
void FingerPrint_Enroll(String input_id);
void FingerPrint_Delete(String input_id);
void FingerPrint_ShowList();
vector<uint16_t> FingerPrint_Json2List(String list);
void FingerPrint_Alert(String id, String school_id);
void FingerPrint_ClearDB();
void FingerPrint_Search();
String FingerPrint_GetDataJson();
void Store_Format();
void Store_Init();
void Store_Check();
void FingerPrint_Unlock();
void Finger_Check_Task(void *parameter);
//子函数
void FingerPrint_ShowParameters();
const char *FingerPrint_AnalyzeStatus(uint16_t status_code);
void FingerPrint_NumSearch(vector<String> &data, String input_id);
void FingerPrint_GetIndexTable();
void FingerPrint_LoadList();
void FingerPrint_WriteList();
#endif /*__FINGERPRINT_H*/