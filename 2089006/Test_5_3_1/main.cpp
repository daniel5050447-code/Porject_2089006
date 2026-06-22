#include "mbed.h"

// 핀 설정 (강의자료 기준)
DigitalOut trigger(PC_7);
DigitalIn  echo(PB_6);
PortOut    leds(PortA, 0x000000F0); // PA_4, PA_5, PA_6, PA_7 사용 (LED_MASK)
Timer      timer;
Timer      polling_timer; // 실습 3번: 폴링 시간 측정용

int main()
{
    float distance = 0.0;
    
    printf("--- Ultrasonic Distance Control System Start ---\n\r");

    while(1) {
        // 1. 초음파 트리거 신호 전송
        trigger = 1;
        wait_us(10); 
        trigger = 0;

        // 2. 에코 신호 대기 및 시간 측정 (실습 3번: 폴링 시간 측정 포함)
        polling_timer.reset();
        polling_timer.start();
        
        while(echo == 0) {}; // Echo가 High가 될 때까지 대기 (폴링)
        
        polling_timer.stop();
        // printf("Polling Time: %llu us\n\r", polling_timer.elapsed_time().count());

        timer.reset();
        timer.start();
        while(echo == 1) {}; // Echo가 Low가 될 때까지 시간 측정
        timer.stop();

        // 3. 거리 계산 (왕복 시간이므로 0.0173 곱함)
        auto duration = timer.elapsed_time().count();
        distance = duration * 0.0173f;
        printf("Distance: %.2f cm\n\r", distance);

        // 4. 거리별 LED 제어 (실습 1, 2번 통합 로직)
        if (distance <= 5.0f) {
            // [실습 1번] 5cm 이내: 모든 LED 깜빡이기 (Emergency)
            leds = 0xF0; // 모두 켜기 (PA4~7)
            ThisThread::sleep_for(100ms);
            leds = 0x00; // 모두 끄기
            ThisThread::sleep_for(100ms);
        } 
        else if (distance <= 10.0f) {
            // [실습 2번] 10cm 이내: LED 3개 ON
            leds = 0x70; // 0b0111 0000
        } 
        else if (distance <= 15.0f) {
            // 15cm 이내: LED 2개 ON
            leds = 0x30; // 0b0011 0000
        } 
        else if (distance <= 20.0f) {
            // 20cm 이내: LED 1개 ON
            leds = 0x10; // 0b0001 0000
        } 
        else {
            // 20cm 이상: 모두 OFF
            leds = 0x00;
        }
        auto us = timer.elapsed_time().count(); // 마이크로초(long long 타입)

        // 실수로 출력하고 싶을 때 (가장 많이 씀)
        float seconds = us / 1000000.0f; 
        printf("Time: %.3f seconds\n\r", seconds); // 소수점 3자리까지 출력

        // 측정 주기 조절 (에코 간섭 방지)
        ThisThread::sleep_for(200ms);
    }
}