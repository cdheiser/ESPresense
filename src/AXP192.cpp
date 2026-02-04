#include <Arduino.h>
#include "AXP192.h"

#if defined(M5STICK)

#include <Wire.h>

namespace AXP192 {
uint8_t Read8bit(uint8_t Addr) {
    uint8_t data;
    Wire1.beginTransmission(0x34);
    Wire1.write(Addr);
    Wire1.endTransmission();
    Wire1.requestFrom(0x34, 1);
    data = Wire1.read();
    return data;
}

void Write1Byte(uint8_t Addr, uint8_t Data) {
    Wire1.beginTransmission(0x34);
    Wire1.write(Addr);
    Wire1.write(Data);
    Wire1.endTransmission();
}

void SetLDO2(bool State) {
    uint8_t data = Read8bit(0x12);
    if (State) {
        data |= 0x02;
    } else {
        data &= 0xFD;
    }
    Write1Byte(0x12, data);
}

void Setup() {
    Wire1.begin(21, 22);
    Write1Byte(0x10, 0xFF);  // OLED VPP Enable
    Write1Byte(0x28, 0xff);  // OLED VPP Enable
    Write1Byte(0x82, 0xff);  // OLED VPP Enable
    SetLDO2(true);
}

void Loop() {
}
}  // namespace AXP192

#endif