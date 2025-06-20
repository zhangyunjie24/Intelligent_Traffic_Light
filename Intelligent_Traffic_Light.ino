#include "config.h"

/****** initialize ******/ 
void setup() {
    oled_init();            // 屏幕
    Light_init();           // 红绿灯
    Beep_init();            // 蜂鸣器
    BTN_init();             // 按键
    Mode_Switch_init();     // 模式切换
    Seg7_init(SEG_PINS);    // 数码管
    Servo_init();           // 舵机
    Cmd_init();             // 命令行工具
    Timer1_init();          // 定时器


}

/****** loop ******/ 
void loop() {
    Tick = millis();    // 获取当前时刻(ms)
    TaskLight();                            // 红绿灯
    TaskSeg();                              // 数码管
    TaskBeep();                             // 蜂鸣器
    TaskBTN();                              // 按键
    TaskDayNight();                         // 白天/黑夜切换
    TaskAccidentCheck();                    // 事故切换
    TaskServo();                            // 舵机
    TaskCmd();                              // 命令行工具
    oled_showData(LightState, LightTime);   // 屏幕
}
