#include "mbed.h"

// LED 4개를 PortOut으로 한꺼번에 제어 (PA_4, 5, 6, 7 사용 가정)
PortOut leds(PortA, 0x000000F0); 
AnalogIn cds(PA_0); // 조도 센서 입력

int main() {
    while(1) {
        // 어두우면(값이 0.5 미만이면) LED 4개 모두 ON (0xF0)
        // 밝으면 LED 모두 OFF (0x00)
        if (cds.read() < 0.5f) {
            leds = 0xF0; 
        } else {
            leds = 0x00;
        }
        ThisThread::sleep_for(100ms);
    }
}