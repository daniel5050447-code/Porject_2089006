#include "mbed.h"

PortOut leds(PortA, 0x000000F0);
AnalogIn cds(PA_0);

int main() {
    while(1) {
        float val = cds.read(); // 0.0 ~ 1.0

        if (val < 0.2) {
            leds = 0xF0; // 아주 어두움: 4개 다 켬
        } else if (val < 0.4) {
            leds = 0x70; // 조금 어두움: 3개 켬
        } else if (val < 0.6) {
            leds = 0x30; // 보통: 2개 켬
        } else if (val < 0.8) {
            leds = 0x10; // 조금 밝음: 1개 켬
        } else {
            leds = 0x00; // 아주 밝음: 다 끔
        }
        
        ThisThread::sleep_for(100ms);
    }
}

