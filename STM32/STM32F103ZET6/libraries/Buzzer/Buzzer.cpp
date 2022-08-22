#include "Buzzer.h"
#include "System.h"
/**
 * @brief       �������չ��췽��
 * @param       None
 * @retval      None
 */
Buzzer::Buzzer()
{
}

/**
 * @brief       ���������ι��췽��
 * @param       pin         ����������������
 * @retval      None
 */
Buzzer::Buzzer(TIMx_Channelx_enum pwmch)
{
    Set_TIMx_Channelx_enum(pwmch);
}

/**
 * @brief       ���������ι��췽��
 * @param       pin         ����������������
 * @retval      None
 */
Buzzer::~Buzzer()
{
}

/**
 * @brief       ����������PWM
 * @param       Null
 * @retval      None
 */
void Buzzer::Beep_On()
{
    Start();
}

/**
 * @brief       ������ֹͣPWM
 * @param       Null
 * @retval      None
 */
void Buzzer::Beep_Off()
{
    ShutUp();
}

/**
 * @brief       ����������PWM����
 * @param       freq        ������Ƶ��
 * @param       volume      ����������
 * @retval      None
 */
void Buzzer::Beep_Set(uint16_t freq, uint8_t volume)
{
    Set_Frequency(freq);
    Set_DutyRatio(volume);
    PWM::Init();
}

/**
 * @brief       ��������ȡ��������
 * @param       song        ���ֽṹ��
 * @retval      None
 */
uint16_t Buzzer::Beep_Song_Get_Len(const struct beep_song *song)
{
    uint16_t cnt = 0;
    /* ������0x00 0x00��β ��������־*/
    while (song->data[cnt])
    {
        cnt += 2;
    }
    return cnt / 2;
}

/**
 * @brief       ��������ȡ��������
 * @param       song        ���ֽṹ��
 * @param       name        ���ڶ�ȡ���������ַ�����
 * @retval      None
 */
void Buzzer::Beep_Song_Get_Name(const struct beep_song *song, char *name)
{
    int i = 0;
    while (song->name[i])
    {
        name[i] = song->name[i];
        i++;
    }
    name[i] = '\0';
}

/**
 * @brief       ������������������
 * @param       signature|����(0-11)       :  ��ָ���������ٸ���������;
 * @param       octachord|�����˶�(-2��+2) :  < 0 �������˶�; > 0 �������˶�
 * @retval      None
 */
void Buzzer::Beep_Song_Decode_new_freq(uint8_t signature, int8_t octachord)
{
    uint8_t i, j;
    for (i = 0; i < 12; i++) // ���ݵ��ż������˶��������µ�Ƶ�ʱ�
    {
        j = i + signature;

        if (j > 11) //����֮�󳬳����������������������һ������
        {
            j = j - 12;
            freq_tab_new[i] = freq_tab[j] * 2;
        }
        else
        {
            freq_tab_new[i] = freq_tab[j];
        }

        /* �����˶� */
        if (octachord < 0)
        {
            freq_tab_new[i] >>= (-octachord);
        }
        else if (octachord > 0)
        {
            freq_tab_new[i] <<= octachord; //ÿ��һ���˶� Ƶ�ʾͷ�һ��
        }
    }
}

/**
 * @brief       ���������ֽ���
 * @param       tone            ����
 * @param       length          ��������
 * @param       Basicspeed      �����ٶ�
 * @param       data            ������Ϣ����(���ڴ�Ž�������Ϣ)
 * @retval      None
 */
void Buzzer::Beep_Song_Decode(uint16_t tone, uint16_t length, uint16_t Basicspeed, struct beep_song_data *data)
{
    static const uint16_t div0_len = 60.0 / Basicspeed * 1000; // ȫ�����ĳ���(ms)
    uint16_t note_len, note_sound_len, current_freq;
    uint8_t note, sharp, range, note_div, effect, dotted;

    note = tone % 10;                                        //���������
    range = tone / 10 % 10;                                  //������ߵ���
    sharp = tone / 100;                                      //������Ƿ�����
    current_freq = freq_tab_new[sign_tab[note - 1] + sharp]; //�����Ӧ������Ƶ��

    if (note != 0)
    {
        if (range == 1)
            current_freq >>= 1; //���� ���˶�
        if (range == 3)
            current_freq <<= 1; //���� ���˶�
        data->freq = current_freq;
    }
    else
    {
        data->freq = 0;
    }
    note_div = length_tab[length % 10]; //����Ǽ�������
    effect = length / 10 % 10;          //�����������(0��ͨ1����2����)
    dotted = length / 100;              //����Ƿ񸽵�
    note_len = div0_len / note_div;     //���������ʱ��

    if (dotted == 1)
        note_len = note_len + note_len / 2;

    if (effect != 1)
    {
        if (effect == 0) //�����ͨ���������೤��
        {
            note_sound_len = note_len * SOUND_SPACE;
        }
        else //������������೤��
        {
            note_sound_len = note_len / 2;
        }
    }
    else //������������೤��
    {
        note_sound_len = note_len;
    }
    if (note == 0)
    {
        note_sound_len = 0;
    }
    data->sound_len = note_sound_len;
    data->nosound_len = note_len - note_sound_len; //����������ĳ���
}

/**
 * @brief       ��������ȡ���ֽ�����Ϣ
 * @param       song            ������Ϣ
 * @param       index           ������ǰ����λ��
 * @param       data            ������Ϣ����(���ڴ�Ž�������Ϣ)
 * @retval      None
 */
void Buzzer::Beep_Song_Get_Data(const struct beep_song *song, uint16_t index, struct beep_song_data *data)
{
    Beep_Song_Decode(song->data[index * 2], song->data[index * 2 + 1], song->Basicspeed, data);
}

/**
 * @brief       �������ͨ��
 * @param       pwmch   ���ͨ��ѡ��
 * @retval      None
 */
void Buzzer::Set_Buzzer_Param(TIMx_Channelx_enum pwmch)
{
    Set_TIMx_Channelx_enum(pwmch);
}

/**
 * @brief       ���ַ���
 * @param       HZ:������Ƶ����
 * @param       time:��Ӧ��ʱ��(һ��Ϊ1,����Ϊ0.5,�Դ�����)
 * @param       Basespeed:������������(��ʾÿ���Ӽ���1���ȵ�����)
 * @retval      None
 */
void Buzzer::Music(const struct beep_song *song)
{
    /* user app entry */
    struct beep_song_data data;
    int len, i = 0;
    char name[SONG_NAME_LENGTH_MAX + 1];
    /*������������,song->tone = 0, Ĭ��ΪC��*/
    Beep_Song_Decode_new_freq(song->tone, 0);
    /*��ȡ������*/
    Beep_Song_Get_Name(song, name);
    //�÷����ӵײ����uart���������ȫ
    printf("���ڲ��ţ�%s\n", name);
    /*��ȡ��������*/
    len = Beep_Song_Get_Len(song);
    /*��ʼ��������*/
    while (i < len)
    {
        /* ������������ */
        Beep_Song_Get_Data(song, i, &data);
        Beep_Set(data.freq, song->volume);
        Beep_On();
        system_delay_ms(data.sound_len);
        Beep_Off();
        system_delay_ms(data.nosound_len);
        i++;
    }
}
