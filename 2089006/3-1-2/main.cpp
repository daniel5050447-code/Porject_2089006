/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define LED_MASK 0x000000f0
PortOut leds(PortA, LED_MASK);
DigitalIn btn1(PC_0, PullUp); // 오른쪽 이동 버튼 (GND 연결)
DigitalIn btn2(PC_1, PullUp); // 왼쪽 이동 버튼 (GND 연결)

int main() {
    // 초기 상태: 4비트 중 가장 오른쪽(PA_4)만 켬
    int pos = 1; 
    leds = pos << 4;

    while (1) {
        // 버튼 1을 누르는 동안 (Active-Low)
        if (btn1 == 0) {
            pos = pos << 1;        // 비트를 왼쪽으로 밀기 (오른쪽 LED 방향으로 이동)
            if (pos > 8) pos = 1;  // 마지막 LED를 넘어가면 처음으로
            leds = pos << 4;
            ThisThread::sleep_for(200ms); // 이동 속도 조절
        } 
        // 버튼 2를 누르는 동안
        else if (btn2 == 0) {
            pos = pos >> 1;        // 비트를 오른쪽으로 밀기 (왼쪽 LED 방향으로 이동)
            if (pos < 1) pos = 8;  // 처음 LED보다 작아지면 마지막으로
            leds = pos << 4;
            ThisThread::sleep_for(200ms); // 이동 속도 조절
        }
        // 둘 다 누르지 않으면 아무 작업도 하지 않고 멈춰 있음
    }
}