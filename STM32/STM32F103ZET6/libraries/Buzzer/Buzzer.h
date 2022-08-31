#ifndef __OJ_BUZZER_H
#define __OJ_BUZZER_H
#include "PWM.h"
/*
   ����ģ�����:
  https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/beep-player
*/

/*���������ֲ���*/
#define SONG_NAME_LENGTH_MAX 30
#define SONG_DATA_LENGTH_MAX 500
#define SOUND_SPACE 0.8
/*����*/
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
    /*��ӦC��#C��D��#D��E��F��#F��G��A��#A��B��*/
} Tone;
/*������Ϣ*/
struct beep_song
{
    const uint8_t volume;                     // ����
    const uint16_t Basicspeed;                // ����Ļ�����������ȫ����Ϊ��λ������40��ʾһ����40��ȫ����
    const Tone tone;                        // ��������
    const uint8_t name[SONG_NAME_LENGTH_MAX]; //������
    const uint8_t data[SONG_DATA_LENGTH_MAX]; //��������
};
/*ÿһ����������Ϣ*/
struct beep_song_data
{
    uint16_t freq;        //����Ƶ��
    uint16_t sound_len;   //������������
    uint16_t nosound_len; //������������
};
/*C������Ƶ�ʱ�*/
static const uint16_t freq_tab[12] = {262, 277, 294, 311, 330, 349, 369, 392, 415, 440, 466, 494}; //Ƶ�ʱ� CDEFGAB
/*1~7��Ƶ�ʱ��е�λ��*/
static const uint8_t sign_tab[7] = {0, 2, 4, 5, 7, 9, 11};
/*�������� 2^0,2^1,2^2,2^3...*/
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
    /*������Ƶ�ʱ�*/
    uint16_t freq_tab_new[12]; //�µ�Ƶ�ʱ�
public:
    Buzzer();
    Buzzer(TIMx_Channelx_enum pwmch);
    ~Buzzer();
    void Set_Buzzer_Param(TIMx_Channelx_enum pwmch);
    void Music(const struct beep_song *song);
};

#endif /*__OJ_BUZZER_H*/
