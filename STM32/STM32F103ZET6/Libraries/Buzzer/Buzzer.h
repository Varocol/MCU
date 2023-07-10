#ifndef __OJ_BUZZER_H
#define __OJ_BUZZER_H
#include "PWM.h"
/*
   以下模板详见:
  https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/beep-player
*/

/*蜂鸣器音乐参数*/
#define SONG_NAME_LENGTH_MAX 30
#define SONG_DATA_LENGTH_MAX 500
#define SOUND_SPACE 0.8
/*音调*/
typedef enum
{
    C,
    uC,
    D,
    uD,
    E,
    F,
    uF,
    G,
    uG,
    A,
    uA,
    B
    /*对应C、#C、D、#D、E、F、#F、G、A、#A、B调*/
} Tone;
/*乐曲信息*/
struct beep_song
{
    const uint8_t volume;                     // 音量
    const uint16_t Basicspeed;                // 这里的基础节拍是以全音符为单位，例如40表示一分钟40个全音符
    const Tone tone;                        // 基础音调
    const uint8_t name[SONG_NAME_LENGTH_MAX]; //歌曲名
    const uint8_t data[SONG_DATA_LENGTH_MAX]; //歌曲编码
};
/*每一个音符的信息*/
struct beep_song_data
{
    uint16_t freq;        //音符频率
    uint16_t sound_len;   //音符有声长度
    uint16_t nosound_len; //音符无声长度
};
/*C调基础频率表*/
static const uint16_t freq_tab[12] = {262, 277, 294, 311, 330, 349, 369, 392, 415, 440, 466, 494}; //频率表 CDEFGAB
/*1~7在频率表中的位置*/
static const uint8_t sign_tab[7] = {0, 2, 4, 5, 7, 9, 11};
/*几分音符 2^0,2^1,2^2,2^3...*/
static const uint8_t length_tab[7] = {1, 2, 4, 8, 16, 32, 64};

class Buzzer : public PWM
{
private:
    void Beep_On();
    void Beep_Off();
    void Beep_Set(uint16_t freq, uint8_t volume);
    void Beep_Song_Decode(uint16_t tone, uint16_t length, uint16_t Basicspeed, struct beep_song_data *data);
    void Beep_Song_Decode_new_freq(uint8_t signature, int8_t octachord);
    void Beep_Song_Get_Data(const struct beep_song *song, uint16_t index, struct beep_song_data *data);
    static uint16_t Beep_Song_Get_Len(const struct beep_song *song);
    static void Beep_Song_Get_Name(const struct beep_song *song, char *name);
    /*变调后的频率表*/
    uint16_t freq_tab_new[12]; //新的频率表
public:
    Buzzer();
    Buzzer(TIMx_Channelx_enum pwmch);
    ~Buzzer();
    void Set_Buzzer_Param(TIMx_Channelx_enum pwmch);
    void Music(const struct beep_song *song);
};

#endif /*__OJ_BUZZER_H*/
