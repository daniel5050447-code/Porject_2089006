#include "mbed.h"

#define LED_MASK 0x000000f0
PortOut leds(PortA, LED_MASK);

// 버튼 설정: PullUp (누르면 0)
DigitalIn btn_up(PC_0, PullUp);   // 숫자를 키우는 버튼
DigitalIn btn_down(PC_1, PullUp); // 숫자를 줄이는 버튼

int main() {
    int count = 0; // 0부터 15까지 저장할 변수
    leds = (count << 4);

    while (1) {
        // [UP 버튼] 숫자를 1씩 더함
        if (btn_up == 0) {
            count++;               // 숫자 1 증가
            if (count > 15) count = 0; // 15를 넘어가면 다시 0으로
            leds = (count << 4);   // 2진수 모양으로 출력
            ThisThread::sleep_for(200ms); // 디바운싱(중복 입력 방지)
        } 
        
        // [DOWN 버튼] 숫자를 1씩 뺌
        else if (btn_down == 0) {
            count--;               // 숫자 1 감소
            if (count < 0) count = 15; // 0보다 작아지면 다시 15로
            leds = (count << 4);
            ThisThread::sleep_for(200ms);
        }
    }
}