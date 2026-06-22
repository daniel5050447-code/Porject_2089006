#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(A2);
DigitalOut led3(D9);

InterruptIn button(BUTTON1);
Ticker ticker2;
Ticker ticker3;
Timer timer;

void blink2() {
    led2 = !led2;
}

void blink3() {
    if (timer.elapsed_time() < 10s) {
        led3 = !led3;
    } else {
        led3 = 0;
        ticker3.detach();   // 10초 후 Ticker 정지
    }
}

void toggle() {
    led1 = !led1;
}

int main() {
    button.rise(&toggle);

    timer.start();
    ticker2.attach(&blink2, 200ms);   // 200ms마다 blink2 호출
    ticker3.attach(&blink3, 500ms);   // 500ms마다 blink3 호출

    while (1) {
        ThisThread::sleep_for(1000ms);
    }
}