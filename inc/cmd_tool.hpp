#ifndef CMD_TOOL_H
#define CMD_TOOL_H

/* Dependencies */
#include "../config.h"

/* Macro */
#define BUFFER_SIZE 24  // 缓冲区大小
#define MAX_LOG_ENTRIES 1 // 最多可存储的日志数量

/* Type defines */
// 日志结构体
struct LogEntry {
  char timestamp[9]; // 格式: "HH:MM:SS"
  char command[20];
};

/* Function Declarations */
void Cmd_init(void);
void TaskCmd(void);
bool parseCommand(char* input, char* cmd, char* itm, char* dat);  // 解析命令
void executeCommand(const char* cmd, const char* itm, const char* dat); // 执行命令
void handleSetCommand(const char* item, const char* data);  // 处理set命令
void handleCheckCommand(const char* item, const char* data);  // 处理check命令
bool is_illegalTime(struct _time_t time); // 判断时间合法性
void addToLog(const char* command); // 添加日志
void showHelp(void);  // 展示帮助
void showLog(void); //展示日志


#endif  //CMD_TOOL_H