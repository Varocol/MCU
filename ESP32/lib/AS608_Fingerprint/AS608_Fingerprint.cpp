#include <AS608_Fingerprint.h>

/*!
 * @brief Gets the command packet
 */
#define GET_CMD_PACKET(...)                                                     \
    uint8_t data[] = {__VA_ARGS__};                                             \
    Adafruit_Fingerprint_Packet packet(FINGERPRINT_COMMANDPACKET, sizeof(data), \
                                       data);                                   \
    writeStructuredPacket(packet);                                              \
    if (getStructuredPacket(&packet) != FINGERPRINT_OK)                         \
        return FINGERPRINT_PACKETRECIEVEERR;                                    \
    if (packet.type != FINGERPRINT_ACKPACKET)                                   \
        return FINGERPRINT_PACKETRECIEVEERR;

/*!
 * @brief Sends the command packet
 */
#define SEND_CMD_PACKET(...)     \
    GET_CMD_PACKET(__VA_ARGS__); \
    return packet.data[0];

/**
 * @author  @Varocol
 * @brief   软串口驱动指纹模块构造方法
 * @param   ss              软串口指针
 * @param   password        口令
 * @return  None
 */
#if defined(__AVR__) || defined(ESP32) || defined(ESP8266) || defined(FREEDOM_E300_HIFIVE1)
AS608_Fingerprint::AS608_Fingerprint(SoftwareSerial *ss, uint32_t password) : Adafruit_Fingerprint(ss, password)
{
}
#endif
/**
 * @author  @Varocol
 * @brief   硬串口驱动指纹模块构造方法
 * @param   hs              硬串口指针
 * @param   password        口令
 * @return  None
 */
AS608_Fingerprint::AS608_Fingerprint(HardwareSerial *hs, uint32_t password) : Adafruit_Fingerprint(hs, password)
{
}
/**
 * @author  @Varocol
 * @brief   串口流驱动指纹模块构造方法
 * @param   serial          串口流指针
 * @param   password        口令
 * @return  None
 */
AS608_Fingerprint::AS608_Fingerprint(Stream *serial, uint32_t password) : Adafruit_Fingerprint(serial, password)
{
}
/**
 * @author  @Varocol
 * @brief   自动注册模板,并将ID放入autoEnrollindex
 * @param   None
 * @return  指纹模块状态码
 */
uint8_t AS608_Fingerprint::autoEnroll()
{
    GET_CMD_PACKET(FINGERPRINT_AUTOENROLL);
    autoEnrollindex = 0xFFFF;
    autoEnrollindex = packet.data[1];
    autoEnrollindex << 8;
    autoEnrollindex |= packet.data[2];
    return packet.data[0];
}
/**
 * @author  @Varocol
 * @brief   自动采集指纹,并更新指纹,使得指纹更清晰
 * @param   None
 * @return  指纹模块状态码
 */
uint8_t AS608_Fingerprint::autoIdentify()
{
    GET_CMD_PACKET(FINGERPRINT_AUTOIDENTIFY);
    fingerID = 0xFFFF;
    confidence = 0xFFFF;

    fingerID = packet.data[1];
    fingerID <<= 8;
    fingerID |= packet.data[2];

    confidence = packet.data[3];
    confidence <<= 8;
    confidence |= packet.data[4];

    return packet.data[0];
}
/**
 * @author  @Varocol
 * @brief   获取索引表
 * @param   None
 * @return  指纹模块状态码
 */
uint8_t AS608_Fingerprint::readIndexTable()
{
    uint8_t tmp;
    uint8_t status;
    //清空列表
    IndexTable.clear();
    for (uint8_t i = 0; i * 256 < capacity; i++)
    {
        GET_CMD_PACKET(FINGERPRINT_READINDEXTABLE, i);
        for (uint8_t j = 1; j <= 32; j++)
        {
            tmp = packet.data[j];
            for (uint8_t k = 0; k < 8 && tmp; k++)
            {
                if (tmp & 0x01)
                {
                    IndexTable.push_back(i * 256 + (j - 1) * 8 + k);
                }
                tmp >>= 1;
            }
        }
        status = packet.data[0];
    }
    return status;
}
/**
 * @author  @Varocol
 * @brief   写记事本
 * @param   pagenum         页码
 * @param   pagedataptr     数据指针
 * @return  指纹模块状态码
 */
uint8_t AS608_Fingerprint::writeNotepad(uint8_t pagenum, uint8_t *pagedataptr)
{
    uint8_t data[34] = {FINGERPRINT_WRITENOTEPAD, pagenum};
    for (int i = 1; i <= 32; i++)
    {
        data[i] = pagedataptr[i - 1];
    }
    Adafruit_Fingerprint_Packet packet(FINGERPRINT_COMMANDPACKET, sizeof(data), data);
    writeStructuredPacket(packet);
    if (getStructuredPacket(&packet) != FINGERPRINT_OK)
        return FINGERPRINT_PACKETRECIEVEERR;
    if (packet.type != FINGERPRINT_ACKPACKET)
        return FINGERPRINT_PACKETRECIEVEERR;
    return packet.data[0];
}
/**
 * @author  @Varocol
 * @brief   读记事本
 * @param   pagenum         页码
 * @param   pagedataptr     数据指针
 * @return  指纹模块状态码
 */
uint8_t AS608_Fingerprint::readNotepad(uint8_t pagenum, uint8_t *pagedataptr)
{
    GET_CMD_PACKET(FINGERPRINT_READNOTEPAD, pagenum);
    for (int i = 0; i < 32; i++)
    {
        pagedataptr[i] = packet.data[i + 1];
    }
    return packet.data[0];
}