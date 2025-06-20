/****** Includes ******/ 
#include "stdint.h"
#include "config.h"


/****** Variables ******/ 
// 引脚定义
const uint8_t RED_PIN = 2;          // 红灯引脚
const uint8_t YELLOW_PIN = 17;       // 黄灯引脚 A3
const uint8_t GREEN_PIN = 4;        // 绿灯引脚
const uint8_t SEG_PINS[7] = {
    16,     // A2
    6, 
    7, 
    8, 
    9, 
    10, 
    11
};    // 数码管阴极引脚(A~G)
const uint8_t BEEP_PIN = 12;        // 蜂鸣器引脚(低电平有效)
const uint8_t BTN_PIN = 13;         // 行人过街按钮(低电平有效)
const uint8_t PHOTORES_PIN = 14;    // 光敏电阻模块引脚(低电平有效) A0
const uint8_t MIC_PIN = 15;         // 麦克风模块引脚 A1
const uint8_t SERVO_PIN = 3;


// 全局变量
uint16_t RedTime = RED_DAY_TIME;
uint16_t GreenTime = GREEN_DAY_TIME;
State_t LightState = RED;
uint16_t LightTime = RED_DAY_TIME;
uint16_t BlinkTime = 0;
uint16_t BeepTime = 0;
uint32_t Tick = 0;
time_t time;
const char* StateNames[] = {
    "Red", 
    "Green", 
    "Yellow", 
    "Accident"
};

