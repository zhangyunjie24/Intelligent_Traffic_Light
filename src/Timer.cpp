#include "../inc/Timer.hpp"
#include <TimerOne.h>

/**
 * @brief 定时器1初始化函数
 * 
 * 配置定时器1为1秒周期，并设置中断回调函数
 * 初始化后立即显示"00:00:00"作为时间起始点
 */
void Timer1_init(void) {
    /* timer init */
    Timer1.initialize(1000000);                 //配置定时器时长(1/s)
    Timer1.attachInterrupt(Timer1_Callback);    //定义回调函数
    Serial.println(F("00:00:00"));                 //显示当前时间
}

/**
 * @brief 定时器1中断回调函数
 * 
 * 每秒自动执行一次，实现以下功能：
 * - 秒计数器递增
 * - 60秒进位到分钟
 * - 60分钟进位到小时
 * - 24小时归零
 * 
 * 注意：此函数在中断上下文中执行，应保持简短
 */
void Timer1_Callback(void) {
    time.sec++;
    if (time.sec >= 60) {
        time.sec = 0;
        time.min++;
    }
    if (time.min >= 60) {
        time.min = 0;
        time.hour++;
    }
    if (time.hour >= 24) {
        time.hour = 0;
    }
}