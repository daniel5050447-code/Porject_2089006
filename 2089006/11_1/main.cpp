#include "mbed.h"

// 핀 설정
DigitalOut led1(LED1);
DigitalOut led2(PA_4);
DigitalOut led3(PA_7);
InterruptIn button(BUTTON1);

// 독립적인 쓰레드 객체 생성
Thread thread2;
Thread thread3;

// LED2 깜박임 함수 (200ms)
void blink_led2() {
    while (1) {
        led2 = !led2;
        ThisThread::sleep_for(200ms);
    }
}

// LED3 깜박임 함수 (500ms)
void blink_led3() {
    while (1) {
        led3 = !led3;
        ThisThread::sleep_for(500ms);
    }
}

// LED1 토글 함수 (버튼 인터럽트용)
void toggle_led1() {
    led1 = !led1;
}

int main() {
    // 1. 버튼 인터럽트 연결 (버튼을 누를 때마다 토글)
    button.rise(toggle_led1);

    // 2. LED2와 LED3를 제어하는 쓰레드 시작
    thread2.start(blink_led2);
    thread3.start(blink_led3);

    // 3. 메인 쓰레드는 10초 동안 대기
    ThisThread::sleep_for(10s);

    // 4. 10초 후 LED3를 제어하는 쓰레드를 종료하여 깜박임 중지
    thread3.terminate();
    
    // 안전을 위해 LED3를 꺼진 상태로 명시적 초기화할 수도 있습니다 (선택사항)
    led3 = 0; 

    // 5. 남은 쓰레드(thread2)와 인터럽트가 계속 동작할 수 있도록 메인 루프 유지
    while (1) {
        ThisThread::sleep_for(1s); // 빈 루프보다 CPU 점유율을 낮춤
    }
}
