#include "../inc/BTN.h"

/**
 * @brief 按钮初始化函数
 * 
 * 设置按钮引脚为输入模式，并启用内部上拉电阻
 * （当按钮未按下时，引脚电平被拉高；按下时接地变为低电平）
 */
void BTN_init(void) {
    pinMode(BTN_PIN, INPUT_PULLUP);
}

/**
 * @brief 按钮检测任务
 * 
 * 检测按钮按下事件，并根据当前交通灯状态执行不同的功能：
 * - 红灯状态下：如果亮灯时间≥5秒，则缩短为3秒
 * - 绿灯状态下：如果亮灯时间≤3秒，则延长为5秒
 * - 事故状态下：立即恢复为红灯状态
 */
void TaskBTN(void) {
    if (digitalRead(BTN_PIN) == LOW) {
        if (LightState == RED && LightTime >= 5000) 
            LightTime = 3000;
        else if (LightState == GREEN && LightTime <= 3000) 
            LightTime = 5000;
        else if (LightState == ACCIDENT) {
            LightState = RED;
            LightTime = RedTime;
        }
    }
}