#include "../inc/cmd_tool.hpp"


// 指令接收缓冲区
char buffer[BUFFER_SIZE]; // 原始输入命令
char command[8];          // 存储命令类型(set/check等)
char item[10];            // 存储具体事项
char data[10];            // 存储可能的数据

// 日志存储区
struct LogEntry logEntries[MAX_LOG_ENTRIES];
uint8_t logIndex = 0;     //日志索引

/**
 * @brief 命令行初始化
 * 
 * 初始化串口通信，打印欢迎信息
 */
void Cmd_init(void) {
    /* command line init */
    Serial.begin(9600);   //波特率设置
    Serial.println(F("Intelligent Traffic Light System"));  // 使用F()节省RAM
    Serial.println(F("Command Line Interface Ready"));
    Serial.println(F("Usage: <set/check> <item> [data/option]"));
}

/**
 * @brief 命令行处理任务
 * 
 * 监听串口输入，解析并执行命令
 */
void TaskCmd(void) {
  if (Serial.available() > 0) {
    Serial.println(F("------------------------"));

    // 读取一行输入
    int bytesRead = Serial.readBytesUntil('\n', buffer, BUFFER_SIZE - 1);
    buffer[bytesRead] = '\0';  // 添加字符串终止符

    // 清空可能残留的输入
    while (Serial.available() > 0) Serial.read();

    // 解析命令
    if (parseCommand(buffer, command, item, data)) {
      // 记录命令到日志
      addToLog(buffer);
      // 执行命令
      executeCommand(command, item, data);
    } 
    else {
      // 处理特殊命令（help/log）
      if (!strcmp(buffer, "help")) {
        showHelp();
      } 
      else if (!strcmp(buffer, "log")) {
        showLog();
      } 
      // 无效命令提示
      else {
        
        Serial.println(F("Error: Invalid command format"));
        Serial.println(F("Usage: <set/check> <item> [data]"));
        Serial.println(F("Or type 'help' for available commands"));
      }
    }
  }
}

/**
 * @brief 解析命令字符串
 * @param input 原始输入字符串
 * @param cmd  [out] 提取的命令类型
 * @param itm  [out] 提取的操作对象
 * @param dat  [out] 提取的附加数据
 * @return true-解析成功, false-格式错误
 */
bool parseCommand(char* input, char* cmd, char* itm, char* dat) {
  // 重置所有缓冲区
  memset(cmd, 0, sizeof(cmd));
  memset(itm, 0, sizeof(itm));
  memset(dat, 0, sizeof(dat));
  
  // 使用sscanf解析输入
  int parsed = sscanf(input, "%15s %31s %63[^\n]", cmd, itm, dat);
  
  // 至少需要命令和事项两部分
  return parsed >= 2;
}

/**
 * @brief 执行解析后的命令
 * @param cmd  命令类型（set/check）
 * @param itm  操作对象
 * @param dat  附加数据
 */
void executeCommand(const char* cmd, const char* itm, const char* dat) {
  // 转换为小写以不区分大小写
  
  if (!strcmp(cmd, "set")) {
    handleSetCommand(itm, dat);
  } 
  else if (!strcmp(cmd, "check")) {
    handleCheckCommand(itm, dat);
  }
  else {
    Serial.print(F("Error: Unknown command - "));
    Serial.println(cmd);
    Serial.println(F("type 'help' for available commands"));
  }
}


/**
 * @brief 处理set命令
 * @param item 要设置的对象
 * @param data 要设置的值
 */
void handleSetCommand(const char* item, const char* data) {
  if (strlen(data) == 0) {
    Serial.println(F("Error: Set command requires data"));
    return;
  }
  
  // 设置系统时间
  if (!strcmp(item, "time")) {
    // 设置时间的具体实现
    struct _time_t tmp_time;
    uint8_t prased = sscanf(data,"%u:%hhu:%hhu", &tmp_time.hour, &tmp_time.min, &tmp_time.sec);
    if (prased != 3 || is_illegalTime(tmp_time)) {
      Serial.println(F("Error: Invalid time format. Expected: <HH:MM:SS>"));
      return;
    }
    else {
      memcpy(&time, &tmp_time, sizeof(struct _time_t));
    }
  } 
  // 设置交通灯状态
  else if (!strcmp(item, "light")) {
    if (LightState == ACCIDENT) {
        Serial.println(F("Error: Accident occurred, no traffic light"));
        return;
    }
    else if (!strcmp(data, "red")) {  // 切换红灯
        if (LightState != RED) {      // 先设置为黄灯
            LightState = YELLOW; 
            LightTime = YELLOW_TIME; 
        }
        else {
            Serial.println(F("Error: Already red!"));
            return;
        }
    }
    else if (!strcmp(data, "green")) {  // 切换绿灯
        if (LightState != GREEN) {
            LightState = GREEN;
            LightTime = GreenTime;
        }
        else {
            Serial.println(F("Error: Already green!"));
            return;
        }
    }
    else {
        Serial.print(F("Error: Unknown light color - "));
        Serial.println(data);
        return;
    }
  }
  else {
    Serial.print(F("Error: Unknown item - "));
    Serial.println(item);
    return;
  }

  // 打印设置成功的反馈
  Serial.print(F("Setting "));
  Serial.print(item);
  Serial.print(F(" to: "));
  Serial.println(data);

}

/**
 * @brief 处理check命令
 * @param item 要查询的对象
 * @param data 查询选项（可选）
 */
void handleCheckCommand(const char* item, const char* data) {
  Serial.print(F("Checking "));
  Serial.print(item);
  Serial.print(F(" "));
  Serial.println(data);
  
  char temp[30] = {0};

  // 查询交通灯状态
  if (strcmp(item, "light") == 0) {
    if (LightState == ACCIDENT) {
      Serial.println(F("Error: Accident occurred, no traffic light"));
      return;
    }
    // -c 选项：仅查询颜色（默认）
    if (!strcmp(data, "-c") || !strcmp(data, "")) {
      Serial.print(F("Color = "));
      Serial.println(StateNames[LightState]);
    }
    // -a 选项：查询颜色和剩余时间
    else if (!strcmp(data, "-a")) {
      Serial.print(F("Color = "));
      Serial.print(StateNames[LightState]);

      Serial.print(F(" | Time = "));
      Serial.print((uint8_t)(LightTime / 1000));
      Serial.println(F("s"));
    }
    else {
      Serial.print(F("Error: Unknown option "));
      Serial.println(data);
      return;
    }
  } 
  // 查询系统时间
  else if (strcmp(item, "time") == 0) {
    sprintf(temp, "%02hhu:%02hhu:%02hhu", time.hour, time.min, time.sec);
    Serial.println(temp);
  }
  // 查询系统模式
  else if (strcmp(item, "mode") == 0) {
    if (LightState == ACCIDENT) {
      Serial.println(F("Mode: accident"));
    }
    else {
      Serial.println(F("Mode: normal"));
    }
  }
  else {
    Serial.print(F("Error: Unknown item - "));
    Serial.println(item);
    return;
  }
}

/**
 * @brief 检查时间合法性
 * @param time 时间结构体
 * @return true-非法时间, false-合法时间
 */
bool is_illegalTime(struct _time_t time) {
  if (time.hour >= 24 || time.min >= 60 || time.min < 0 || 
      time.sec >= 60 || time.sec < 0)
    return true;
  else 
    return false;
}

/**
 * @brief 添加命令到日志（环形缓冲区）
 * @param command 要记录的完整命令
 */
void addToLog(const char* command) {
  // 获取当前时间作为时间戳
  char timestamp[20];
  sprintf(timestamp, "%02hhu:%02hhu:%02hhu", time.hour, time.min, time.sec);
  
  // 存储日志条目
  strncpy(logEntries[logIndex].timestamp, timestamp, sizeof(logEntries[logIndex].timestamp));
  strncpy(logEntries[logIndex].command, command, sizeof(logEntries[logIndex].command));
  
  // 循环缓冲区
  logIndex = (logIndex + 1) % MAX_LOG_ENTRIES;
}

/**
 * @brief 显示帮助信息
 */
void showHelp(void) {
  Serial.println(F("Available Commands:"));
  Serial.println();
  Serial.println(F("help - Show this help message"));
  Serial.println(F("log - Show command history"));
  Serial.println();
  Serial.println(F("set <item> <data> - Set a value"));
  Serial.println(F("  Available items:"));
  Serial.println(F("  time <HH:MM:SS> - Set current time"));
  Serial.println(F("  light <green/red> - Set light to green/red"));
  Serial.println();
  Serial.println(F("check <item> [option] - Check a value"));
  Serial.println(F("  Available items:"));
  Serial.println(F("  light [-c|-a] - Check light [color(default) / color & time]"));
  Serial.println(F("  time - Check current time"));
  Serial.println(F("  mode - Check current working mode [normal / accident]"));
  Serial.println();
}

/**
 * @brief 显示命令历史日志
 */
void showLog(void) {
  Serial.println(F("Command History:"));
  Serial.println();
  
  if (logIndex == 0 && strcmp(logEntries[0].command, "") == 0) {
    Serial.println(F("No commands logged yet"));
    return;
  }
  
  // 从最早的记录开始显示（循环缓冲区）
  for (int i = 0; i < MAX_LOG_ENTRIES; i++) {
    int idx = (logIndex + i) % MAX_LOG_ENTRIES;
    if (strcmp(logEntries[idx].command, "") != 0) {
      Serial.print(F("["));
      Serial.print(logEntries[idx].timestamp);
      Serial.print(F("] "));
      Serial.println(logEntries[idx].command);
    }
  }
}

