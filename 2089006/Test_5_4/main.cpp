#include "mbed.h"

DigitalIn  alarm(D7);       // PIR OUT → PA8 (D7)
DigitalOut greenLed(D5);    // 녹색 LED
DigitalOut redLed(D4);      // 적색 LED

int main() {
    ThisThread::sleep_for(2000ms);  // 코드 5-4와 동일: PIR 초기화 대기

    while(1) {
        if(alarm) {
            // 움직임 감지됨
            greenLed = 0;           // 녹색 LED 끔

            for(int i = 0; i < 5; i++) {   // 적색 LED 5번 깜빡임
                redLed = 1;
                ThisThread::sleep_for(300ms);
                redLed = 0;
                ThisThread::sleep_for(300ms);
            }

            // 평상시로 복귀
            greenLed = 1;
        }
        else {
            // 평상시
            greenLed = 1;
            redLed   = 0;
        }
    }
}