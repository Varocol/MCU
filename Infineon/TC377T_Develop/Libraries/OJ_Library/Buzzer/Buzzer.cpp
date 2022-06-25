#include "Buzzer.h"
/**
 * @brief       蜂鸣器空构造函数
 * @param       None
 * @retval      None
 */
Buzzer::Buzzer ()
{

}

/**
 * @brief       蜂鸣器带参构造函数
 * @param       pin         驱动蜂鸣器的引脚
 * @retval      None
 */
Buzzer::Buzzer (ATOM_PIN_enum pwmch)
{
    Set_Pin(pwmch);
}

/**
 * @brief       蜂鸣器带参构造函数
 * @param       pin         驱动蜂鸣器的引脚
 * @retval      None
 */
Buzzer::~Buzzer ()
{
}

/**
 * @brief       蜂鸣器启动PWM
 * @param       Null
 * @retval      None
 */
void Buzzer::Beep_On ()
{
    Start();
}

/**
 * @brief       蜂鸣器停止PWM
 * @param       Null
 * @retval      None
 */
void Buzzer::Beep_Off ()
{
    Stop();
}

/**
 * @brief       蜂鸣器设置PWM参数
 * @param       freq        蜂鸣器频率
 * @param       volume      蜂鸣器音量
 * @retval      None
 */
void Buzzer::Beep_Set (uint16 freq, uint8 volume)
{
    Set_Freq(freq);
    Set_Percent(volume);
    PWM::Init();
}

/**
 * @brief       蜂鸣器获取歌曲长度
 * @param       song        音乐结构体
 * @retval      None
 */
uint16 Buzzer::Beep_Song_Get_Len (const struct beep_song *song)
{
    uint16 cnt = 0;
    /* 歌曲以0x00 0x00结尾 检测结束标志*/
    while (song->data[cnt])
    {
        cnt += 2;
    }
    return cnt / 2;
}

/**
 * @brief       蜂鸣器获取歌曲名字
 * @param       song        音乐结构体
 * @param       name        用于读取音乐名的字符数组
 * @retval      None
 */
void Buzzer::Beep_Song_Get_Name (const struct beep_song *song, char *name)
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
 * @brief       蜂鸣器调整音乐曲调
 * @param       signature|调号(0-11)       :  是指乐曲升多少个半音演奏;
 * @param       octachord|升降八度(-2到+2) :  < 0 降几个八度; > 0 升几个八度
 * @retval      None
 */
void Buzzer::Beep_Song_Decode_new_freq (uint8 signature, int8 octachord)
{
    uint8 i, j;
    for (i = 0; i < 12; i++)        // 根据调号及升降八度来生成新的频率表
    {
        j = i + signature;

        if (j > 11) //升完之后超出本组基本音级，就跳到下一组音级
        {
            j = j - 12;
            freq_tab_new[i] = freq_tab[j] * 2;
        }
        else
        {
            freq_tab_new[i] = freq_tab[j];
        }

        /* 升降八度 */
        if (octachord < 0)
        {
            freq_tab_new[i] >>= (-octachord);
        }
        else if (octachord > 0)
        {
            freq_tab_new[i] <<= octachord; //每升一个八度 频率就翻一倍
        }
    }
}

void Buzzer::Beep_Song_Decode (uint16 tone, uint16 length, uint16 Basicspeed, struct beep_song_data *data)
{
    static const uint16 div0_len = 60.0 / Basicspeed * 1000;        // 全音符的长度(ms)
    uint16 note_len, note_sound_len, current_freq;
    uint8 note, sharp, range, note_div, effect, dotted;

    note = tone % 10;                             //计算出音符
    range = tone / 10 % 10;                       //计算出高低音
    sharp = tone / 100;                           //计算出是否升半
    current_freq = freq_tab_new[sign_tab[note - 1] + sharp]; //查出对应音符的频率

    if (note != 0)
    {
        if (range == 1)
            current_freq >>= 1;       //低音 降八度
        if (range == 3)
            current_freq <<= 1;       //高音 升八度
        data->freq = current_freq;
    }
    else
    {
        data->freq = 0;
    }
    note_div = length_tab[length % 10];           //算出是几分音符
    effect = length / 10 % 10;                    //算出音符类型(0普通1连音2顿音)
    dotted = length / 100;                        //算出是否附点
    note_len = div0_len / note_div;                //算出音符的时长

    if (dotted == 1)
        note_len = note_len + note_len / 2;

    if (effect != 1)
    {
        if (effect == 0)                          //算出普通音符的演奏长度
        {
            note_sound_len = note_len * SOUND_SPACE;
        }
        else                                      //算出顿音的演奏长度
        {
            note_sound_len = note_len / 2;
        }
    }
    else                                          //算出连音的演奏长度
    {
        note_sound_len = note_len;
    }
    if (note == 0)
    {
        note_sound_len = 0;
    }
    data->sound_len = note_sound_len;
    data->nosound_len = note_len - note_sound_len;     //算出不发音的长度
}

void Buzzer::Beep_Song_Get_Data (const struct beep_song *song, uint16 index, struct beep_song_data *data)
{
    Beep_Song_Decode(song->data[index * 2], song->data[index * 2 + 1], song->Basicspeed, data);
}

/*
 * @brief       蜂鸣器初始化
 * @param       null
 * @return      void
 */
void Buzzer::Init ()
{

}

/**
 * @brief       音乐函数
 * @param       HZ:音调的频率数
 * @param       time:响应的时间(一拍为1,半拍为0.5,以此类推)
 * @param       Basespeed:乐曲基本拍数(表示每分钟几个1长度的音符)
 * @retval      None
 */
void Buzzer::Music (const struct beep_song *song)
{
    /* user app entry */
    struct beep_song_data data;
    int len, i = 0;
    char name[SONG_NAME_LENGTH_MAX + 1];

    /*配置乐曲曲调,song->tone = 0, 默认为C调*/
    Beep_Song_Decode_new_freq(song->tone, 0);
    /*提取乐曲名*/
    Beep_Song_Get_Name(song, name);
    //该方法从底层调用uart，输出更安全
    platform_printf("正在播放：%s\n", name);
    /*获取乐曲长度*/
    len = Beep_Song_Get_Len(song);
    /*开始播放乐曲*/
    while (i < len)
    {
        /* 解码音乐数据 */
        Beep_Song_Get_Data(song, i, &data);
        Beep_Set(data.freq, song->volume);
        Beep_On();
        //该函数有自动获取核ID并根据需要切换定时器的功能
        platform_delay_ms(data.sound_len);
        Beep_Off();
        platform_delay_ms(data.nosound_len);
        i++;
    }
}
