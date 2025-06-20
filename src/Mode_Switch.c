#include "../inc/Mode_Switch.h"

/**
 * @brief 模式切换模块初始化
 * 
 * 初始化光敏电阻和声音传感器的引脚为输入模式
 */
void Mode_Switch_init(void) {
    pinMode(PHOTORES_PIN, INPUT);
    pinMode(MIC_PIN, INPUT);
}

/**
 * @brief 昼夜模式检测任务
 * 
 * 根据光敏电阻检测环境亮度，自动切换红绿灯的持续时间：
 * - 白天模式：使用较长的红绿灯时间
 * - 夜晚模式：使用较短的红绿灯时间
 */
void TaskDayNight(void) {
    // 检测光敏电阻（LOW表示光照充足/白天）
    if (digitalRead(PHOTORES_PIN) == LOW) {
        RedTime = RED_DAY_TIME;
        GreenTime = GREEN_DAY_TIME;
    }
    else {
        RedTime = RED_NIGHT_TIME;
        GreenTime = GREEN_NIGHT_TIME;
    }
}

/**
 * @brief 事故检测任务
 * 
 * 通过声音传感器检测异常声响（如车辆碰撞声），
 * 当检测到超过阈值的声音时，立即切换到事故模式：
 * - 交通灯进入事故状态（红灯常亮+黄灯闪烁）
 * - 激活报警器（通过PWM控制蜂鸣器）
 */
void TaskAccidentCheck(void) {
    uint32_t num = analogRead(MIC_PIN);
    // 调试用（可取消注释查看实时数值，但是会影响系统的实时性）
    // Serial.println(num,DEC);
    if (num>400) {
        LightState = ACCIDENT;
        LightTime = 0;
    }
}