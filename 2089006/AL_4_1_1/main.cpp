#include "mbed.h"

// 4개의 LED를 PortOut으로 묶어서 선언 (PA_4 ~ PA_7 사용 가정)
// LED_MASK 0xF0은 이진수로 11110000이며, 4,5,6,7번 비트를 제어합니다.
#define LED_MASK 0x000000f0

AnalogIn mypot(PA_0);           
PortOut leds(PortA, LED_MASK);  

int main() {
    int value;
    int binary;

    while(1) {
      
        value = mypot.read_u16();
        binary = value / 4096; 
        leds = (binary<< 4);

        ThisThread::sleep_for(100ms);
    }
}