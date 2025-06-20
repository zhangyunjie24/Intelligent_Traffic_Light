#include "../inc/Seg7.h"

// 数码管段码表（共阳极，0-9对应的七段码）
// 段码顺序：g f e d c b a（高位到低位）
// 格式：0b gfedcba （1表示点亮，0表示熄灭）
const uint8_t SEG_NUM_VAL[10] = {
    0x7E,
    0x30, 
    0x6D, 
    0x79, 
    0x33, 
    0x5B, 
    0x5F, 
    0x70, 
    0x7F, 
    0x7B
};

uint8_t* Seg7Pins = NULL;   // 存储数码管引脚配置的指针

/**
 * @brief 数码管初始化
 * @param pins 7段数码管的引脚数组（a~g顺序）
 * 
 * 配置7个IO口为输出模式，默认设为高电平（共阳数码管初始全灭）
 */
void Seg7_init(const uint8_t* pins) {
    Seg7Pins = (uint8_t*) pins; // 保存引脚配置

    // 初始化所有段引脚为输出模式
    uint8_t i;
    for (i = 0; i < 7; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
}

/**
 * @brief 显示指定数字
 * @param num 要显示的数字（0-9）
 * 
 * 根据预定义的段码表，控制各段LED的亮灭
 */
void Seg7_show(uint8_t num) {
    uint8_t bit = 0x40;
    uint8_t i;

    // 遍历7个段（从最高位g段开始）
    for (i = 0; i < 7; i++) {
        if (SEG_NUM_VAL[num] & bit) {
            digitalWrite(Seg7Pins[i], LOW); // 共阳极：低电平点亮
        }
        else {
            digitalWrite(Seg7Pins[i], HIGH);
        }
        bit >>= 1;
    }
}

/**
 * @brief 数码管显示任务
 * 
 * 每秒检测一次剩余时间，并更新数码管显示：
 * - 将毫秒时间转换为秒
 * - 限制最大显示9秒（单数码管限制）
 * - 仅在时间变化时更新显示
 */
void TaskSeg(void) {
    static uint8_t lastTime = 0;
    
    uint8_t time = (uint8_t)(LightTime / 1000);
    if (time > 9)   time = 9;
    
    // 仅在时间变化时更新显示（降低刷新频率）
    if (lastTime != time) {
        lastTime = time;
        Seg7_show(time);
    }

    if (LightState == ACCIDENT)
        Seg7_show(0);
}
