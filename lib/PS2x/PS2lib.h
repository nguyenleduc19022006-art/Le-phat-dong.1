#ifndef PS2X_H
#define PS2X_H

#include<Arduino.h>
#include<PS2X_lib.h>

const uint16_t BTN_TOGGLE_GRAB     = PSB_R1;     // Bấm 1 phát: Gắp. Bấm phát nữa: Thả
const uint16_t BTN_TOGGLE_LIFT     = PSB_R2;     // Bấm 1 phát: Nâng. Bấm phát nữa: Hạ
const uint16_t BTN_SPIN_180        = PSB_L1;     // Xoay nhanh 180 độ quay đầu
const uint16_t BTN_AUTO_START      = PSB_START;  // Kích hoạt dò line tự động
const uint16_t BTN_EMERGENCY_STOP  = PSB_SELECT;   // Dừng khẩn cấp / Hủy Auto về Manual
const uint16_t BTN_CALIBRATE_LINE  = PSB_TRIANGLE; // Kích hoạt chế độ Cân chỉnh quang trở

// Ngưỡng bỏ qua nhiễu rần của lò xo Joystick
const int DEADZONE = 15; 

class PS2Input{
private: 
    PS2X _ps2x;
    int _clk, _cmd, _att, _dat;
    bool _connected;

public: 
    PS2Input(int clk, int cmd, int att, int dat);
    bool init();
    bool read();

    // Lấy giá trị Cần Trái - Trục Dọc (Throttle - Ga)
    int getThrottle(); 

    // Lấy giá trị Cần Phải - Trục Ngang (Turn - Lái)
    int getTurn();

    bool isButtonPressed(uint16_t button); 
    bool isButtonNewPressed(uint16_t button); 
    bool isConnected();
};
#endif