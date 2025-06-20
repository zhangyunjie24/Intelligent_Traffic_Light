#include "../inc/oled.hpp"
// #include <U8g2lib.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// 旧版U8g2库构造方式（已注释）
// U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,SCL,SDA); //配置构造函数      

#define OLED_RESET     4
// 创建SSD1306显示对象（128x64分辨率，I2C接口，指定复位引脚）
Adafruit_SSD1306 display(128, 64, &Wire,OLED_RESET);

/**
 * @brief OLED屏幕初始化
 * 
 * 初始化SSD1306显示屏，设置I2C地址和电压模式
 */
void oled_init(void) {
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.setTextColor(WHITE);//开像素点发光
}

/**
 * @brief 显示交通灯状态信息
 * @param Light_State 当前交通灯状态（RED/GREEN/YELLOW/ACCIDENT）
 * @param LightTime 当前状态剩余时间（毫秒）
 * 
 * 每秒更新一次显示内容，包含：
 * - 标题栏
 * - 大字号显示当前状态：颜色及时间
 * - 状态剩余时间（事故状态不显示）
 * - 底部实时时间、签名
 */
void oled_showData(int Light_State, int LightTime) {
  static uint8_t last_time;

  // 每秒更新一次显示（避免频繁刷新）
  if (time.sec != last_time) {
    last_time = time.sec;

    display.clearDisplay(); // 清屏
  
    // 显示标题（第一行）
    display.setTextSize(1); // 设置字体大小
    display.setCursor(20, 5); // 设置显示位置
    display.println(F("-Traffic Light-"));

    // 显示主状态信息（中间大字体）
    display.setTextSize(2);// 设置字体大小  
    display.setCursor(0, 30);// 设置显示位置
    display.print(StateNames[Light_State]);
    display.print("   ");
    // 非事故状态显示剩余时间（秒）
    if (Light_State != ACCIDENT) {
      display.println(LightTime/1000);
    }

    
    display.setTextSize(1); // 设置字体大小  

    // 显示时间
    display.setCursor(10,55);
    if (time.hour < 10)
      display.print(F("0"));
    display.print(time.hour);
    display.print(F(":"));
    if (time.min < 10)
      display.print(F("0"));
    display.print(time.min);
    display.print(F(":"));
    if (time.sec < 10)
      display.print(F("0"));
    display.print(time.sec);

    // 显示签名（右下角）
    display.setCursor(105, 55);// 设置显示位置
    display.println(F("ZYJ"));

    // 将缓冲区内容输出到实际显示屏
    display.display();
  }
}

