#include "mbed.h"
InterruptIn button(BUTTON1);
DigitalOut led1(LED1);

void toggle() {
    led1 = !led1;
}

int main() {
    button.rise(&toggle);
    while (1) {
        ThisThread::sleep_for(10s);
    }
}