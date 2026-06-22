#include "mbed.h"

#define LED_MASK 0x000000f0  // PA_4, PA_5, PA_6, PA_7
#define LOW 0
#define HIGH 1

PortOut leds(PortA, LED_MASK);
// 버튼을 GND에 연결하므로 내부 PullUp 저항 사용
DigitalIn btn1(PC_0, PullUp); 
DigitalIn btn2(PC_1, PullUp);

int main() {
    int before1 = HIGH; 
    int before2 = HIGH;
    int now1, now2;
    int count = 0;

    leds = 0;

    while (1) {
        now1 = btn1;
        now2 = btn2;

        
        if ((before1 == HIGH) && (now1 == LOW)) {
            count = (count + 1) % 16;
            leds = count << 4;
        }
        before1 = now1;

        if ((before2 == HIGH) && (now2 == LOW)) {
            count = (count - 1 + 16) % 16;
            leds = count << 4;
        }
        before2 = now2;

    
        
        ThisThread::sleep_for(20ms);
    }
}