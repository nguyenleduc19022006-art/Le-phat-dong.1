#include "PS2lib.h"
PS2Input::PS2Input(int clk, int cmd, int att, int dat):
    _clk(clk), _cmd(cmd), _att(att), _dat(dat)
{}

bool PS2Input::init() {
    // Tắt Pressure và Rumble
    int error = _ps2x.config_gamepad(_clk, _cmd, _att, _dat, false, false);
    if (error == 0) {
        _connected = true;
        return true;
    }
    _connected = false;
    return false;
}

bool PS2Input::read() {
    // Tự động kết nối lại nếu rớt sóng
    if (!_connected) {
        init(); 
        if (!_connected) return false;
    }
    _ps2x.read_gamepad(false, 0); 
    return true;
}

int PS2Input::getThrottle(){
    int rawVal=_ps2x.Analog(PSS_LY);
    int centeredValue = 128 - rawVal; // Lên = Dương, Xuống = Âm

    //loc nhieu
    if (abs(centeredValue) <= DEADZONE) {
        return 0;
    }

        float normalized = (abs(centeredValue) - DEADZONE) / (float)(128 - DEADZONE);
    
    if (centeredValue < 0) {
        normalized = -normalized;
    }

    // 3. LÀM MƯỢT BẰNG HÀM BẬC 3 (CUBIC CURVE)
    float smoothed = normalized * normalized * normalized;
        int finalPWM = round(smoothed * 255.0f);
    
    return constrain(finalPWM, -255, 255);
}

int PS2Input::getTurn(){
    int rawVal=_ps2x.Analog(PSS_LX);
    int centeredValue = rawVal - 128; // Phải = Dương, Trái = Âm

        if (abs(centeredValue) <= DEADZONE) {
        return 0;
    }

    float normalized = (abs(centeredValue) - DEADZONE) / (float)(128 - DEADZONE);
    if (centeredValue < 0) {
        normalized = -normalized;
    }
    float smoothed = normalized * normalized * normalized;
    int finalPWM = round(smoothed * 255.0f);
    
    return constrain(finalPWM, -255, 255);
}

bool PS2Input::isButtonPressed(uint16_t button){
    return _ps2x.Button(button);
}
bool PS2Input::isButtonNewPressed(uint16_t btn){
    return _ps2x.Button(btn);
}
bool PS2Input::isConnected(){
    return _connected;
}
