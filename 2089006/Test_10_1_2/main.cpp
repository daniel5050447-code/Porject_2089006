#include "mbed.h"

InterruptIn button(BUTTON1);
volatile bool running = true;
volatile int counter = 10;   // count → counter 로 변경

void toggleRun() {
    running = !running;
}

int main() {
    button.rise(&toggleRun);

    printf("Start!\r\n");

    while (1) {
        if (running) {
            printf("%d\r\n", counter);

            if (counter == 0) {
                printf("Boom!\r\n");
                running = false;
            } else {
                counter--;
            }
        }
        ThisThread::sleep_for(1000ms);
    }
}