#ifndef _AXP192_H_
#define _AXP192_H_

#if defined(M5STICK)

#include <Arduino.h>

namespace AXP192 {
uint8_t Read8bit(uint8_t Addr);
void Write1Byte(uint8_t Addr, uint8_t Data);
void SetLDO2(bool State);
void Setup();
void Loop();
}  // namespace AXP192

#endif

#endif