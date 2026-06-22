#include "mbed.h"

// --- 핀 설정 ---
// 1. LED 및 버저
DigitalOut led(PA_4);     // 조도 연동 LED
PwmOut buzzer(PB_0);      // 버저 핀 (요청하신 PB_0)

// 2. 센서
AnalogIn ldr(PA_0);       // 조도 센서 (요청하신 PA_0)
DigitalOut trig(PC_7);    // 초음파 센서 Trigger (요청하신 PC_7)
DigitalIn echo(PB_6);     // 초음파 센서 Echo (요청하신 PB_6)
Timer echo_timer;         // 초음파 센서 시간 측정을 위한 타이머

// --- 쓰레드 객체 생성 ---
Thread distance_thread;
Thread light_thread;

// --- 초음파 센서 거리 측정 함수 ---
float get_distance_cm() {
    trig = 1;
    wait_us(10); // 10us 펄스 전송
    trig = 0;
    
    echo_timer.reset();
    
    // Echo 핀이 High가 될 때까지 대기
    while (echo == 0); 
    echo_timer.start();
    
    // Echo 핀이 Low가 될 때까지 시간 측정
    while (echo == 1); 
    echo_timer.stop();
    
    // 왕복 시간(us)을 거리(cm)로 변환 (음속 340m/s 기준)
    long duration = echo_timer.elapsed_time().count();
    return duration * 0.017f; 
}

// --- Task 1: 거리 감지 및 버저 제어 쓰레드 ---
void distance_task() {
    while (1) {
        float distance = get_distance_cm();
        
        // 물체가 10cm 이내로 접근한 경우
        if (distance > 0.0f && distance <= 10.0f) {
            buzzer.period(1.0f / 1000.0f); // 1kHz 경고음 주파수 설정
            buzzer.write(0.5f);            // 50% 듀티 사이클로 버저 켜기