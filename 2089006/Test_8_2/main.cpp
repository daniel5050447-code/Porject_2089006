#include "mbed.h"

DigitalOut trigger(PC_7);
DigitalIn  echo(PB_6);
PwmOut     buzzer(PB_0);
Timer      timer;

int main()
{
    while(1) {
        // 거리 측정
        trigger = 1;
        timer.reset();
        wait_us(10);
        trigger = 0;

        while(echo == 0) {};
        timer.start();
        while(echo == 1) {};
        timer.stop();

        float distance = timer.elapsed_time().count() * 0.0173f;
        printf("Distance = %f cm\n\r", distance);

        if(distance < 20.0f) {
            // 20cm 이하 접근 시 사이렌 5초
            Timer t;
            t.start();
            while(t.elapsed_time() < 5s) {
                buzzer.period_us(500);   // 2000Hz 높은 소리
                buzzer.write(0.5f);
                ThisThread::sleep_for(500ms);

                buzzer.period_us(1000);  // 1000Hz 낮은 소리
                buzzer.write(0.5f);
                ThisThread::sleep_for(500ms);
            }
            buzzer.write(0.0f);  // 사이렌 종료
        } else {
            buzzer.write(0.0f);  // 소리 끔
        }

        ThisThread::sleep_for(100ms);
    }
}