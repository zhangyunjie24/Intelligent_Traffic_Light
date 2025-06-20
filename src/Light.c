#include "../inc/Light.h"

/**
 * @brief 交通灯硬件初始化
 * 
 * 设置红黄绿灯引脚为输出模式，并初始化为红灯亮、其他灯灭的状态
 */
void Light_init(void) {
    pinMode(RED_PIN, OUTPUT);
    pinMode(YELLOW_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);

    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
}

/**
 * @brief 交通灯控制任务
 * 
 * 根据当前状态自动切换灯光，实现：
 * - 红灯→绿灯→黄灯→红灯的循环
 * - 绿灯末期闪烁提醒
 * - 事故状态红黄灯交替闪烁
 */
void TaskLight(void) {
    static uint32_t lastTick = 0;
    if (lastTick != Tick) {
        lastTick = Tick;
        LightTime--;

        // 计时变灯
        // 计时结束，换状态
        if (LightTime <= 0) {
            switch (LightState) {
                case RED:    
                    LightState = GREEN; 
                    LightTime = GreenTime; 
                    break;
                case GREEN:  
                    LightState = YELLOW; 
                    LightTime = YELLOW_TIME; 
                    break;
                case YELLOW: 
                    LightState = RED; 
                    LightTime = RedTime; 
                    break;
                case ACCIDENT: 
                    LightTime = 0; 
                    break;
            }
        }

        // 按状态切换灯光
        switch (LightState) {
            case RED:   // 红灯状态
                digitalWrite(RED_PIN, HIGH);
                digitalWrite(YELLOW_PIN, LOW);
                digitalWrite(GREEN_PIN, LOW);
            break;

            case GREEN: // 绿灯状态
                // 绿灯末期闪烁处理（最后GREEN_BLINK_TIME毫秒）
                if (LightTime <= GREEN_BLINK_TIME) {
                    BlinkTime++;
                    if (BlinkTime <= GREEN_BLINK_INT) {
                        digitalWrite(GREEN_PIN, LOW);
                    }
                    else if (BlinkTime < 2 * GREEN_BLINK_INT) {
                        digitalWrite(GREEN_PIN, HIGH);
                    }
                    else {
                        BlinkTime = 0;
                    }
                } 
                // 绿灯常亮阶段
                else {
                    BlinkTime = 0;
                    digitalWrite(RED_PIN, LOW);
                    digitalWrite(YELLOW_PIN, LOW);
                    digitalWrite(GREEN_PIN, HIGH);
                }
            break;

            case YELLOW:    // 黄灯状态（常亮）
                digitalWrite(RED_PIN, LOW);
                digitalWrite(GREEN_PIN, LOW);
                digitalWrite(YELLOW_PIN, HIGH);
            break;

            case ACCIDENT:  // 事故状态（红灯常亮+黄灯闪烁）
                digitalWrite(GREEN_PIN, LOW);   // 绿灯常灭
                digitalWrite(RED_PIN, HIGH);    // 红灯常亮
                BlinkTime++;

                // 黄灯闪烁控制
                if (BlinkTime < ACCIDENT_BLINK_INT) {
                    digitalWrite(YELLOW_PIN, LOW);
                }
                else if (BlinkTime < 2 * ACCIDENT_BLINK_INT) {
                    digitalWrite(YELLOW_PIN, HIGH);
                }
                else {
                    BlinkTime = 0;
                }
            break;
        }
    }
}