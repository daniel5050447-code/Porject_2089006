#include "mbed.h"

PwmOut buzzer(D3);          // PB_0 = D3
InterruptIn button(BUTTON1);
volatile bool buzzerOn = false;

void toggleBuzzer() {
    buzzerOn = !buzzerOn;
}

int main() {
    button.rise(&toggleBuzzer);
    buzzer.write(0.0f);     // 처음엔 소리 끔

    while (1) {
        if (buzzerOn) {
            // 1000Hz 음
            buzzer.period_us(1000);
            buzzer.write(0.5f);
            ThisThread::sleep_for(500ms);

            // 500Hz 음
            buzzer.period_us(2000);
            buzzer.write(0.5f);
            ThisThread::sleep_for(500ms);
        } else {
            buzzer.write(0.0f);  // 소리 끔
            ThisThread::sleep_for(100ms);
        }
    }
}