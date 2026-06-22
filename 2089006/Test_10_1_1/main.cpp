#include "mbed.h"

InterruptIn button(PC_13); // 외부 버튼 사용 시 D2 등으로 핀 번호 변경 권장
DigitalOut led1(LED1);
Ticker led_ticker;

volatile int btn_flag = 0;

void toggle_led() {
    led1 = !led1.read();
}

void btn_isr() {
    btn_flag = 1;
}

int main() {
    int cnt = 0;
    
    // 1. 내부 풀다운 저항 활성화 (평상시 Low 유지)
    button.mode(PullDown);
    
    // 2. 누르는 순간(Low -> High)을 감지하도록 rise() 사용
    button.rise(&btn_isr); 
    
    led_ticker.attach(&toggle_led, 500ms); 

    while (true) {
        if (btn_flag) {
            cnt++;
            printf("Button press %d times\n", cnt);
            btn_flag = 0;
        }
        ThisThread::sleep_for(50ms);
    }
}