#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led1(LED1);
DigitalOut led2(PA_4);

void toggle() {
    led2 = !led2;
}

int main() {
    button.rise(&toggle);
    while(1) {
        led1 = !led1;
        ThisThread::sleep_for(500ms);
    }
}