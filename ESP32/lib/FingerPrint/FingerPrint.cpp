#include <FINGERPrint.h>
/**
 * @author  @Varocol
 * @brief   指纹模块初始化
 * @param   None
 * @return  None
 */
void FingerPrint_Init()
{
    PLATFORM_SERIAL.println("<-------------指纹模块初始化------------->");
    //设置引脚
    mySerial.begin(fingerprint_param.SoftwareBaudrate, SERIAL_8N1, fingerprint_param.Rx, fingerprint_param.Tx);
    //验证密码
    if (PLATFORM_FINGER.verifyPassword())
    {
        PLATFORM_SERIAL.println("找到指纹识别模块");
        uint8_t status;
        uint8_t time_limit;
        // 设置包大小
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setPacketSize(fingerprint_param.PacketSize)) != FINGERPRINT_OK && time_limit != 0)
        {
            //状态解析
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //延时100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("指纹数据包大小设置失败");
        }
        else
        {
            PLATFORM_SERIAL.println("指纹数据包大小设置成功");
        }
        //设置通讯速率
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setBaudRate(fingerprint_param.Baudrate)) != FINGERPRINT_OK && time_limit != 0)
        {
            //状态解析
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //延时100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("通讯速率设置失败");
        }
        else
        {
            PLATFORM_SERIAL.println("通讯速率设置成功");
        }
        //延时缓冲
        delay(100);
#if FINGER_SETPASSWORD
        //设置密码
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setPassword(fingerprint_param.Password)) != FINGERPRINT_OK && time_limit != 0)
        {
            //状态解析
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
            //延时100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("密码设置失败");
        }
        else
        {
            PLATFORM_SERIAL.println("密码设置成功");
        }
#endif
        //设置安全等级
        time_limit = FINGER_TIMELIMIT;
        while ((status = PLATFORM_FINGER.setSecurityLevel(fingerprint_param.SecurityLevel)) != FINGERPRINT_OK && time_limit != 0)
        {
            //状态解析
            PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            //延时100ms
            delay(100);
            time_limit--;
        }
        if (time_limit == 0)
        {
            PLATFORM_SERIAL.println("安全等级设置失败");
        }
        else
        {
            PLATFORM_SERIAL.println("安全等级设置成功");
        }
        //显示设置后的参数
        FingerPrint_ShowParameters();
        //从模块中获取存在的指纹索引表
        FingerPrint_GetIndexTable();
        //从文件系统加载指纹索引表中映射的信息(学号、查询信息)
        FingerPrint_LoadList();
        PLATFORM_SERIAL.println("指纹识别模块初始化成功");
    }
    else
    {
        PLATFORM_SERIAL.println("未能找到指纹识别模块");
        PLATFORM_SERIAL.println("指纹识别模块初始化失败");
    }
    PLATFORM_SERIAL.println("<---------------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   获取模块参数并通过串口显示
 * @param   None
 * @return  None
 */
void FingerPrint_ShowParameters()
{
    PLATFORM_SERIAL.println("获取模块参数");
    //获取指纹模块参数
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (PLATFORM_FINGER.getParameters() != FINGERPRINT_OK && time_limit != 0)
    {
        time_limit--;
        //延时100ms
        delay(100);
    }
    if (time_limit != 0)
    {
        PLATFORM_SERIAL.println("密码测试通过");
        PLATFORM_SERIAL.printf(
            "-----------指纹模块参数----------\n"
            "状态:%s\n"
            "ID:%d\n"
            "容量:%d\n"
            "识别等级(1~5):%d\n"
            "设备地址:%#x\n"
            "数据包大小:%d\n"
            "波特率:%d\n"
            "--------------------------------\n",
            FingerPrint_AnalyzeStatus(PLATFORM_FINGER.status_reg),
            PLATFORM_FINGER.system_id,
            PLATFORM_FINGER.capacity,
            PLATFORM_FINGER.security_level,
            PLATFORM_FINGER.device_addr,
            PLATFORM_FINGER.packet_len,
            PLATFORM_FINGER.baud_rate);
    }
    else
    {
        PLATFORM_SERIAL.println("密码测试失败");
    }
}

/**
 * @author  @Varocol
 * @brief   状态解析
 * @param   uint8_t     status_code
 * @return  状态对应的信息
 */
const char *FingerPrint_AnalyzeStatus(uint16_t status_code)
{
    switch (status_code)
    {
    case FINGERPRINT_OK:
        return "指纹模块已就绪";
    case FINGERPRINT_PACKETRECIEVEERR:
        return "指纹数据包错误";
    case FINGERPRINT_NOFINGER:
        return "没有可识别的手指";
    case FINGERPRINT_IMAGEFAIL:
        return "指纹图像混乱";
    case FINGERPRINT_FEATUREFAIL:
        return "指纹特征点缺失";
    case FINGERPRINT_NOMATCH:
        return "指纹不匹配";
    case FINGERPRINT_NOTFOUND:
        return "找不到该指纹";
    case FINGERPRINT_ENROLLMISMATCH:
        return "两次录入指纹不匹配";
    case FINGERPRINT_BADLOCATION:
        return "指纹无法存储在该位置";
    case FINGERPRINT_DBRANGEFAIL:
        return "指纹模板读取失败";
    case FINGERPRINT_UPLOADFEATUREFAIL:
        return "指纹模板上传失败";
    case FINGERPRINT_PACKETRESPONSEFAIL:
        return "指纹数据包响应失败";
    case FINGERPRINT_UPLOADFAIL:
        return "指纹图像上传失败";
    case FINGERPRINT_DELETEFAIL:
        return "指纹模板删除失败";
    case FINGERPRINT_DBCLEARFAIL:
        return "清空指纹库失败";
    case FINGERPRINT_PASSFAIL:
        return "指纹模块密码错误";
    case FINGERPRINT_INVALIDIMAGE:
        return "图像错误";
    case FINGERPRINT_FLASHERR:
        return "闪存写入错误";
    case FINGERPRINT_INVALIDREG:
        return "错误的寄存器地址";
    case FINGERPRINT_TIMEOUT:
        return "通讯超时";
    case FINGERPRINT_BADPACKET:
        return "数据包已损坏";
    case FINGERPRINT_UNKOWNERR:
        return "未知的错误";
    case FINGERPRINT_REGCONTENTERR:
        return "寄存器设定内容错误";
    case FINGERPRINT_PAGERANGEERR:
        return "记事本页码指定错误";
    case FINGERPRINT_COMOPERATEERR:
        return "端口操作失败";
    case FINGERPRINT_AUTOENROLLERR:
        return "自动注册(enroll)失败";
    case FINGERPRINT_DBFULL:
        return "指纹库满";
    default:
        return "未知的状态";
    }
}

/**
 * @author  @Varocol
 * @brief   指纹录入(如果已有指纹则不录入)
 * @param   None
 * @return  指纹模块状态码
 */
uint16_t FingerPrint_Enroll()
{
    uint8_t status;
    PLATFORM_SERIAL.println("<-------------指纹录入------------->");
    PLATFORM_SERIAL.println("等待录入的指纹...");
    PLATFORM_SERIAL.println("等待手指放置...");
    //等待手指放下
    while (PLATFORM_FINGER.getImage() == FINGERPRINT_NOFINGER)
    {
        delay(1);
    }

    //检查指纹是否已存在指纹库
    if (PLATFORM_FINGER.autoIdentify() == FINGERPRINT_OK)
    {
        String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
        uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
        PLATFORM_SERIAL.printf(
            "指纹库已有该指纹\n"
            "[指纹ID:%d|匹配度:%d|学号:%s|搜索次数:%d]\n",
            PLATFORM_FINGER.fingerID,
            PLATFORM_FINGER.confidence,
            school_id.c_str(),
            operations_cnt);
        PLATFORM_SERIAL.println("<---------------------------------->");
        return status;
    }
#if FINGER_AUTOENROLL
    while ((status = PLATFORM_FINGER.autoEnroll()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
    }
    uint16_t pos = PLATFORM_FINGER.autoEnrollindex;
#else
    for (int i = 1; i <= 2; i++)
    {
        PLATFORM_SERIAL.printf("采集特征点模板%d\n", i);
        PLATFORM_SERIAL.println("图像采集中");

        //采集特征点模板1的图像
        while ((status = PLATFORM_FINGER.getImage()) != FINGERPRINT_OK)
        {
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        }
        PLATFORM_SERIAL.println("图像采集完成");
        //将图像转换成模板
        if ((status = PLATFORM_FINGER.image2Tz(i)) != FINGERPRINT_OK)
        {
            PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
            PLATFORM_SERIAL.println("<---------------------------------->");
            return status;
        }
        PLATFORM_SERIAL.printf("特征点模板%d转换成功\n", i);
        if (i == 1)
        {
            //查找模板1是否已存在指纹库
            if ((status = PLATFORM_FINGER.fingerFastSearch()) == FINGERPRINT_OK)
            {
                String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
                uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
                PLATFORM_SERIAL.printf(
                    "指纹库已有该指纹\n"
                    "[指纹ID:%d|匹配度:%d|学号:%s|搜索次数:%d]\n",
                    PLATFORM_FINGER.fingerID,
                    PLATFORM_FINGER.confidence,
                    school_id.c_str(),
                    operations_cnt);
                PLATFORM_SERIAL.println("<---------------------------------->");
                return status;
            }
            PLATFORM_SERIAL.printf("特征点模板%d采样完成,请拿开手指\n", i);
            delay(1000);

            //等待手指拿开
            while (PLATFORM_FINGER.getImage() != FINGERPRINT_NOFINGER)
            {
                delay(1);
            }

            PLATFORM_SERIAL.println("重新放下同一根手指");
        }
    }
    //两个特征点模板转换完成后整合并形成可用的模板
    PLATFORM_SERIAL.printf("为指纹创建模板中...\n");
    if ((status = PLATFORM_FINGER.createModel()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        PLATFORM_SERIAL.println("<---------------------------------->");
        return status;
    }
    PLATFORM_SERIAL.println("两次指纹匹配成功");
    //存入指纹库
    PLATFORM_SERIAL.println("存入指纹库");
    //查找可以存储的槽位
    uint16_t pos;
    for (pos = 0; pos < PLATFORM_FINGER.IndexTable.size() && pos == PLATFORM_FINGER.IndexTable[pos]; pos++)
        ;
    if ((status = PLATFORM_FINGER.storeModel(pos)) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        PLATFORM_SERIAL.println("<---------------------------------->");
        return status;
    }
#endif
    PLATFORM_SERIAL.printf("指纹录入ID为%d\n", pos);
    PLATFORM_SERIAL.println("指纹录入成功");
    //输入所属人信息(学号)
    PLATFORM_SERIAL.println("请输入学号:");
    String num = ReadOption();
    //添加属性值(学号,次数)
    JsonObject property = finger_data.createNestedObject(String(pos));
    property[finger_keys.school_id] = num;
    property[finger_keys.operations_cnt] = 0;
    //更新指纹索引表
    FingerPrint_GetIndexTable();
    //更新存储文件的索引表
    FingerPrint_WriteList();
    PLATFORM_SERIAL.println("<---------------------------------->");
    return status;
}

/**
 * @author  @Varocol
 * @brief   指纹删除
 * @param   None
 * @return  指纹模块状态码
 */
uint16_t FingerPrint_Delete()
{
    //将ID初始化为容量值(越界值)
    uint8_t status;
    vector<String> data;
    int8_t mode;
    PLATFORM_SERIAL.println("<-------------指纹删除------------->");
    PLATFORM_SERIAL.printf(
        "请输入删除模式:\n"
        "%d.搜索指纹库自动删除\n"
        "%d.通过学号删除\n"
        "注:删除会连同指纹附属信息一同删除\n",
        Finger_Delete_FingerPrint,
        Finger_Delete_ID);
    //输入删除模式
    mode = ReadOption().toInt();
    //查找指纹
    if (mode == Finger_Delete_FingerPrint)
    {
        if ((status = FingerPrint_Search()) == FINGERPRINT_OK)
        {
            data.push_back(String(PLATFORM_FINGER.fingerID));
        }
        else
        {
            return status;
        }
    }
    else if (mode == Finger_Delete_ID)
    {
        FingerPrint_NumSearch(data);
    }
    else
    {
        PLATFORM_SERIAL.println("没有该模式");
        return FINGERPRINT_BADLOCATION;
    }
    if (data.size() != 0)
    {
        for (String el : data)
        {
            if ((status = PLATFORM_FINGER.deleteModel(el.toInt())) != FINGERPRINT_OK)
            {
                PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
            }
            else
            {
                //删除数据
                finger_data.remove(el);
                PLATFORM_SERIAL.println("删除ID" + el + "成功");
            }
        }
        //更新指纹索引表
        FingerPrint_GetIndexTable();
        //更新存储文件的索引表
        FingerPrint_WriteList();
    }
    else
    {
        PLATFORM_SERIAL.println("没有可以删除的指纹");
    }
    return status;
    PLATFORM_SERIAL.println("<---------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   指纹ID查找
 * @param   None
 * @return  指纹模块状态码
 */
uint16_t FingerPrint_IDSearch()
{
    uint8_t status;
    int8_t mode;
    PLATFORM_SERIAL.println("<-------------指纹查找------------->");
    PLATFORM_SERIAL.printf(
        "请输入查找模式:\n"
        "%d.指纹查找ID\n"
        "%d.学号查找ID\n",
        Finger_Search_FingerPrint,
        Finger_Search_Name);
    mode = ReadOption().toInt();
    if (mode == Finger_Search_FingerPrint)
    {
        FingerPrint_Search();
    }
    else if (mode == Finger_Search_Name)
    {
        vector<String> data;
        FingerPrint_NumSearch(data);
        PLATFORM_SERIAL.printf("查找到%d个数据\n", data.size());
        for (String el : data)
        {
            PLATFORM_SERIAL.println(el);
        }
    }
    PLATFORM_SERIAL.println("<---------------------------------->");
    return status;
}

/**
 * @author  @Varocol
 * @brief   指纹查找(通过指纹搜索)
 * @param   None
 * @return  指纹模块状态码
 */
uint16_t FingerPrint_Search()
{
    uint8_t status;
    PLATFORM_SERIAL.println("开始查找指纹");
    PLATFORM_SERIAL.println("等待手指放置...");
    //等待手指放下
    while (PLATFORM_FINGER.getImage() == FINGERPRINT_NOFINGER)
    {
        delay(1);
    }
#if FINGER_AUTOIDENTIFY
    // 直接搜索
    status = PLATFORM_FINGER.autoIdentify();
#else
    //采集特征点模板1的图像
    while ((status = PLATFORM_FINGER.getImage()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
    }
    PLATFORM_SERIAL.println("图像采集完成");
    //将图像转换成模板
    if ((status = PLATFORM_FINGER.image2Tz()) != FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println(FingerPrint_analyzeStatus(status));
        return status;
    }
    PLATFORM_SERIAL.println("模板转换成功");
    //快速查找指纹库
    status = PLATFORM_FINGER.fingerFastSearch();
#endif
    //找到指纹
    if (status == FINGERPRINT_OK)
    {
        String school_id = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id].as<String>();
        uint32_t operations_cnt = finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt].as<uint32_t>();
        PLATFORM_SERIAL.printf(
            "找到指纹\n"
            "[指纹ID:%d|匹配度:%d|学号:%s|搜索次数:%d]\n",
            PLATFORM_FINGER.fingerID,
            PLATFORM_FINGER.confidence,
            school_id.c_str(),
            operations_cnt);
        finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.operations_cnt] = operations_cnt + 1;
        FingerPrint_WriteList();
    }
    //没有该指纹
    else if (status == FINGERPRINT_NOTFOUND)
    {
        PLATFORM_SERIAL.println("指纹库中没有该指纹");
    }
    //查找出错
    else
    {
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
    }
    return status;
}

/**
 * @author  @Varocol
 * @brief   指纹查找(通过学号搜索)
 * @param   data            用于存入查找结果的容器
 * @return  指纹模块状态码
 */
void FingerPrint_NumSearch(vector<String> &data)
{
    //获取输入的ID
    PLATFORM_SERIAL.println("请输入学号:");
    String num = ReadOption();
    //查找有无该学号的指纹
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        if (finger_data[String(el)][finger_keys.school_id].as<String>() == num)
        {
            data.push_back(String(el));
        }
    }
}

/**
 * @author  @Varocol
 * @brief   从文件系统中加载数据
 * @param   None
 * @return  None
 */
void FingerPrint_LoadList()
{
    PLATFORM_SERIAL.print("打开SPIFFS文件系统");
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (!SPIFFS.begin() && time_limit)
    {
        PLATFORM_SERIAL.print("...");
        time_limit--;
    }
    PLATFORM_SERIAL.println();
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("SPIFFS文件系统无法打开");
        return;
    }
    else
    {
        PLATFORM_SERIAL.println("SPIFFS文件系统打开成功");
    }
    PLATFORM_SERIAL.println("从文件系统加载数据");
    //加载文件
    finger_file = SPIFFS.open(FINGER_DATA_PATH, "r", true);
    DynamicJsonDocument tmp(2048);
    DeserializationError error = deserializeJson(tmp, finger_file.readString());
    // JSON反序列化获取数据
    if (error)
    {
        PLATFORM_SERIAL.println(error.c_str());
        PLATFORM_SERIAL.println("数据反序列化失败,请格式化数据");
    }
    else
    {
        PLATFORM_SERIAL.println("数据加载成功");
    }
    //与索引表合并(先要获取索引表)
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        String school_id = tmp[String(el)][finger_keys.school_id].as<String>();
        if (school_id == "null")
        {
            school_id = FINGER_KEYDEFAULTVALUE;
        }
        finger_data[String(el)][finger_keys.school_id] = school_id;
        finger_data[String(el)][finger_keys.operations_cnt] = tmp[String(el)][finger_keys.operations_cnt].as<uint32_t>();
    }
    //关闭文件
    finger_file.close();
    //关闭文件系统
    SPIFFS.end();
}

/**
 * @author  @Varocol
 * @brief   写入文件系统
 * @param   None
 * @return  None
 */
void FingerPrint_WriteList()
{
    PLATFORM_SERIAL.print("打开SPIFFS文件系统");
    uint8_t time_limit = FINGER_TIMELIMIT;
    while (!SPIFFS.begin() && time_limit)
    {
        PLATFORM_SERIAL.print("...");
        time_limit--;
    }
    PLATFORM_SERIAL.println();
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("SPIFFS文件系统无法打开");
        return;
    }
    else
    {
        PLATFORM_SERIAL.println("SPIFFS文件系统打开成功");
    }
    //写入文件
    finger_file = SPIFFS.open(FINGER_DATA_PATH, "w", true);
    // JSON序列化存储数据
    String output;
    serializeJson(finger_data, output);
    finger_file.print(output);
    //关闭文件
    finger_file.close();
    PLATFORM_SERIAL.println("数据写入成功");
    //关闭文件系统
    SPIFFS.end();
}

/**
 * @author  @Varocol
 * @brief   获取指纹索引表
 * @param   None
 * @return  None
 */
void FingerPrint_GetIndexTable()
{
    PLATFORM_SERIAL.println("获取指纹索引表");
    uint8_t status;
    //获取指纹库索引表
    uint8_t time_limit = FINGER_TIMELIMIT;
    while ((status = PLATFORM_FINGER.readIndexTable()) != FINGERPRINT_OK && time_limit != 0)
    {
        //状态解析
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
        //延时100ms
        delay(100);
        time_limit--;
    }
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("指纹库索引表更新失败");
        return;
    }
    PLATFORM_SERIAL.println("指纹库索引表更新成功");
}
/**
 * @author  @Varocol
 * @brief   修改指纹信息
 * @param   None
 * @return  None
 */
void FingerPrint_Alert()
{
    PLATFORM_SERIAL.println("<-------------指纹修改------------>");
    PLATFORM_SERIAL.println("根据指纹修改学号");
    if (FingerPrint_Search() == FINGERPRINT_OK)
    {
        PLATFORM_SERIAL.println("请输入学号:");
        String num = ReadOption();
        finger_data[String(PLATFORM_FINGER.fingerID)][finger_keys.school_id] = num;
        PLATFORM_SERIAL.println("学号修改成功");
        FingerPrint_WriteList();
    }
    PLATFORM_SERIAL.println("<--------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   展示指纹索引表
 * @param   None
 * @return  None
 */
void FingerPrint_ShowList()
{
    PLATFORM_SERIAL.println("<-------------指纹索引表------------>");
    for (uint16_t el : PLATFORM_FINGER.IndexTable)
    {
        PLATFORM_SERIAL.printf(
            "[指纹ID:%d|学号:%s|搜索次数:%d]\n",
            el,
            finger_data[String(el)][finger_keys.school_id].as<String>().c_str(),
            finger_data[String(el)][finger_keys.operations_cnt].as<uint32_t>());
    }
    PLATFORM_SERIAL.println("<----------------------------------->");
}

/**
 * @author  @Varocol
 * @brief   清空指纹库
 * @param   None
 * @return  None
 */
void FingerPrint_ClearDB()
{
    PLATFORM_SERIAL.println("清空指纹库");
    uint8_t time_limit = FINGER_TIMELIMIT;
    uint8_t status;
    while ((status = PLATFORM_FINGER.emptyDatabase()) != FINGERPRINT_OK && time_limit)
    {
        PLATFORM_SERIAL.println(FingerPrint_AnalyzeStatus(status));
        time_limit--;
    }
    if (time_limit == 0)
    {
        PLATFORM_SERIAL.println("指纹库删除失败");
        return;
    }
    PLATFORM_SERIAL.println("指纹库删除成功");
    //删除学号等信息
    finger_data.clear();
    FingerPrint_GetIndexTable();
    FingerPrint_WriteList();
}

/**
 * @author  @Varocol
 * @brief   获取数据JSON包
 * @param   None
 * @return  None
 */
String FingerPrint_GetDataJson()
{
    PLATFORM_SERIAL.println("获取数据JSON包");
    FingerPrint_LoadList();
    String result;
    serializeJson(finger_data, result);
    return result;
}