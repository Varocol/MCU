#ifndef __OJ_BUZZER_H
#define __OJ_BUZZER_H
#include "headfile.h"
#include "PWM.h"
/*
   ����ģ�����:
  https://www.rt-thread.org/document/site/#/rt-thread-version/rt-thread-standard/tutorial/beep-player
*/

/*���������ֲ���*/
#define SONG_NAME_LENGTH_MAX  30
#define SONG_DATA_LENGTH_MAX  500
#define SOUND_SPACE 0.8
/*����*/
typedef enum
{
    C, uC, D, uD, E, F, uF, G, uG, A, uA, B
/*��ӦC��#C��D��#D��E��F��#F��G��A��#A��B��*/
}Tone;
/*������Ϣ*/
struct beep_song
{
        const uint8 volume;      // ����
        const uint16 Basicspeed; // ����Ļ�����������ȫ����Ϊ��λ������40��ʾһ����40��ȫ����
        const Tone tone;         // ��������
        const uint8 name[SONG_NAME_LENGTH_MAX]; //������
        const uint8 data[SONG_DATA_LENGTH_MAX]; //��������
};
/*ÿһ����������Ϣ*/
struct beep_song_data
{
        uint16 freq;            //����Ƶ��
        uint16 sound_len;       //������������
        uint16 nosound_len;     //������������
};
/*C������Ƶ�ʱ�*/
static const uint16 freq_tab[12] = {262, 277, 294, 311, 330, 349, 369, 392, 415, 440, 466, 494}; //Ƶ�ʱ� CDEFGAB
/*1~7��Ƶ�ʱ��е�λ��*/
static const uint8 sign_tab[7] = {0, 2, 4, 5, 7, 9, 11};
/*�������� 2^0,2^1,2^2,2^3...*/
static const uint8 length_tab[7] = {1, 2, 4, 8, 16, 32, 64};

class Buzzer : public PWM
{
    private:
        void Beep_On ();
        void Beep_Off ();
        void Beep_Set (uint16 freq, uint8 volume);
        void Beep_Song_Decode (uint16 tone, uint16 length, uint16 Basicspeed, struct beep_song_data *data);
        void Beep_Song_Decode_new_freq (uint8 signature, int8 octachord);
        void Beep_Song_Get_Data (const struct beep_song *song, uint16 index, struct beep_song_data *data);
        static uint16 Beep_Song_Get_Len (const struct beep_song *song);
        static void Beep_Song_Get_Name (const struct beep_song *song, char *name);
        /*������Ƶ�ʱ�*/
        uint16 freq_tab_new[12];     //�µ�Ƶ�ʱ�
    public:
        Buzzer ();
        Buzzer (ATOM_PIN_enum pwmch);
        ~Buzzer ();
        void Init ();
        void Music (const struct beep_song *song);
};

#endif  /*__OJ_BUZZER_H*/
