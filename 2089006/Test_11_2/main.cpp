#include "mbed.h"

DigitalOut trig(D7);
DigitalIn  echo(D8);

PwmOut buzzer(D3);
DigitalOut led(A2);
AnalogIn cds(A0);

float getDistance() {
    trig = 1;
    wait_us(10);
    trig = 0;

    while (echo == 0);
    Timer t;
    t.start();
    while (echo == 1);
    t.stop();

    return t.elapsed_time().count() / 58.0f;
}

int main() {
    buzzer.write(0.0f);

    while (1) {
        // 초음파 체크
        float dist = getDistance();
        printf("거리: %f cm\r\n", dist);

        if (dist < 10.0f) {
            // 사이렌 효과로 크게!
            for (int i = 0; i < 10; i++) {
                buzzer.period_us(700);   // 4000Hz 고음
                buzzer.write(0.5f);
                ThisThread::sleep_for(250ms);
                buzzer.period_us(500);   // 2000Hz 저음
                buzzer.write(0.5f);
                ThisThread::sleep_for(250ms);
            }
            buzzer.write(0.0f);
        }

        // 조도 체크
        float light = cds.read();
        printf("조도: %f\r\n", light);

        if (light > 0.15f) {
            led = 0;
        } else {
            led = 1;
        }

        ThisThread::sleep_for(200ms);
    }
}