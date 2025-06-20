#include "../inc/Beep.h"

/**
 * @brief 蜂鸣器初始化函数
 * 
 * 设置蜂鸣器引脚为输出模式，并初始化为低电平（关闭状态）
 */
void Beep_init(void) {
    pinMode(BEEP_PIN, OUTPUT);
    
    digitalWrite(BEEP_PIN, LOW);
}

/**
 * @brief 蜂鸣器控制任务
 * 
 * 根据当前交通灯状态控制蜂鸣器的不同鸣叫模式
 * 使用BeepTime计时器为每种状态创建不同的鸣叫节奏
 */
void TaskBeep(void) {
    static uint32_t lastTick = 0;

    // 仅当全局tick计数器发生变化时执行
    if (lastTick != Tick) {
        lastTick = Tick;
        BeepTime++;

        // 根据当前交通灯状态切换不同的蜂鸣模式
        switch (LightState) {
            case RED:
                // 红灯状态蜂鸣模式：
                // - 鸣叫NORMAL_BEEP_TIME时长
                // - 静音直到RED_BEEP_CYCLE时长
                // - 然后重置计时器
                if (BeepTime < NORMAL_BEEP_TIME) {
                    digitalWrite(BEEP_PIN, LOW);
                }
                else if (BeepTime < RED_BEEP_CYCLE) {
                    digitalWrite(BEEP_PIN, HIGH);
                }
                else {
                    BeepTime = 0;
                }
            break;

            case GREEN:
                // 绿灯状态蜂鸣模式：
                // - 鸣叫NORMAL_BEEP_TIME时长
                // - 静音直到GREEN_BEEP_CYCLE时长
                // - 然后重置计时器
                if (BeepTime < NORMAL_BEEP_TIME) {
                    digitalWrite(BEEP_PIN, LOW);
                }
                else if (BeepTime < GREEN_BEEP_CYCLE) {
                    digitalWrite(BEEP_PIN, HIGH);
                }
                else {
                    BeepTime = 0;
                }
            break;
            
            case YELLOW:
                // 黄灯状态蜂鸣模式：
                // - 持续静音
                // - 重置计时器（虽然不使用）
                digitalWrite(BEEP_PIN, HIGH);
                BeepTime = 0;
            break;
            
            case ACCIDENT:
                // 事故状态蜂鸣模式：
                // - 鸣叫ACCIDENT_BEEP_TIME时长
                // - 静音直到ACCIDENT_BEEP_CYCLE时长
                // - 然后重置计时器
                if (BeepTime < ACCIDENT_BEEP_TIME) {
                    digitalWrite(BEEP_PIN, LOW);
                }
                else if (BeepTime < ACCIDENT_BEEP_CYCLE) {
                    digitalWrite(BEEP_PIN, HIGH);
                }
                else {
                    BeepTime = 0;
                }
        }
    }
}