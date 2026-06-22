#include "mbed.h"

InterruptIn button(BUTTON1);
DigitalOut led1(LED1);
DigitalOut led2(A2);    

Ticker ticker;          

void blink() {
    led1 = !led1;       
}

void toggle() {
    led2 = !led2;       
}

int main() {
    button.rise(&toggle);
    ticker.attach(&blink, 500ms);  

    while (1) {
        
        ThisThread::sleep_for(1000ms);
    }
}