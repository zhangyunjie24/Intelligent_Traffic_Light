#ifndef CONFIGS_H
#define CONFIGS_H

/****** C++ Include ******/ 
#include <Arduino.h>
#include "inc/cmd_tool.hpp"
#include "inc/oled.hpp"
#include "inc/Timer.hpp"

#ifdef __cplusplus
extern "C" {
#endif

/****** Dependencies ******/ 
#include "stdint.h"
#include "inc/Beep.h"
#include "inc/BTN.h"
#include "inc/Light.h"
#include "inc/Mode_Switch.h"
#include "inc/Seg7.h"
#include "inc/Servo.h"

/****** Macros ******/ 
#define RED_DAY_TIME       10000    // 红灯白天时长(ms)
#define RED_NIGHT_TIME     5000     // 红灯夜间时长(ms)
#define GREEN_DAY_TIME     10000    // 绿灯白天时长(ms)
#define GREEN_NIGHT_TIME   5000     // 绿灯夜间时长(ms)
#define YELLOW_TIME        2000     // 黄灯时长(ms)
#define GREEN_BLINK_TIME   3000     // 绿灯开始闪烁时间(ms)
#define GREEN_BLINK_INT    500      // 绿灯闪烁间隔(ms)
#define ACCIDENT_BLINK_INT 1000     // 红灯蜂鸣周期(ms)
#define RED_BEEP_CYCLE     1000     // 绿灯蜂鸣周期(ms)
#define GREEN_BEEP_CYCLE   500      // 红灯蜂鸣周期(ms)
#define ACCIDENT_BEEP_CYCLE 5000    // 事故蜂鸣周期(ms)
#define NORMAL_BEEP_TIME   100      // 正常蜂鸣时长(ms)
#define ACCIDENT_BEEP_TIME 1000     // 事故蜂鸣时长(ms)

/****** Type Defines ******/ 
typedef enum {
    RED = 0,
    GREEN,
    YELLOW,
    ACCIDENT 
} State_t;
//时间结构体
typedef struct _time_t {
  uint16_t hour;
  uint8_t min;
  uint8_t sec;
} time_t;

/****** External Declarations ******/ 
// 变量声明
// 引脚定义
extern const uint8_t RED_PIN;          // 红灯引脚
extern const uint8_t YELLOW_PIN;       // 黄灯引脚
extern const uint8_t GREEN_PIN;        // 绿灯引脚
extern const uint8_t SEG_PINS[7];    // 数码管阴极引脚(A~G)
extern const uint8_t BEEP_PIN;        // 蜂鸣器引脚(低电平有效)
extern const uint8_t BTN_PIN;         // 行人过街按钮(低电平有效)
extern const uint8_t PHOTORES_PIN;    // 光敏电阻模块引脚(低电平有效)
extern const uint8_t MIC_PIN;         // 麦克风模块引脚
extern const uint8_t SERVO_PIN;

// 全局变量
extern uint16_t RedTime;
extern uint16_t GreenTime;
extern State_t LightState;
extern uint16_t LightTime;
extern uint16_t BlinkTime;
extern uint16_t BeepTime;
extern uint32_t Tick;
extern time_t time;
extern const char* StateNames[];

#ifdef __cplusplus
}
#endif
#endif  //CONFIGS_H