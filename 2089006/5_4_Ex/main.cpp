#include "mbed.h"
DigitalOut led1(LED1);
DigitalIn alarm(D7);

int main() {
    ThisThread::sleep_for(2000ms);
    while(1) {
        if(alarm){
            led1=1;
            ThisThread::sleep_for(5000ms);
        }
        else
            led1=0;
    }
}
