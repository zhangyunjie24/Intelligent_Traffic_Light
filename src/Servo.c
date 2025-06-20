#include "../inc/Servo.h"

/**
 * @brief 舵机初始化函数
 * 
 * 配置舵机控制引脚为输出模式
 * 注意：实际舵机控制需要使用PWM引脚
 */
void Servo_init(void) {
    pinMode(SERVO_PIN,OUTPUT);
}

/**
 * @brief 舵机控制任务
 * 
 * 根据交通灯状态控制舵机角度：
 * - 红灯状态：最小角度（约0°）
 * - 绿灯状态：中间角度（约90°）
 * - 事故状态：大角度（约135°）
 * - 其他状态：不改变当前角度
 * 
 * 注意：实际PWM控制需根据舵机型号调整参数
 */
void TaskServo(void) {
    switch (LightState) {
        case RED:
            analogWrite(SERVO_PIN, 1);
        break;

        case GREEN:
            analogWrite(SERVO_PIN, 128);
        break;

        case ACCIDENT:
            analogWrite(SERVO_PIN,64);
        break;

        default:    break;
    }

}

