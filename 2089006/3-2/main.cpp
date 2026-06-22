/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

// 입력 설정: PC_0, PC_1 핀을 풀다운(PullDown) 모드로 설정
DigitalIn var1(PC_0, PullDown);
DigitalIn var2(PC_1, PullDown);

// 출력 설정: PA_4 ~ PA_7 핀을 LED 출력으로 설정
DigitalOut bool_not(PA_4);
DigitalOut bool_and(PA_5);
DigitalOut bool_or(PA_6);
DigitalOut bool_xor(PA_7);

int main() {
    unsigned int A, B;

    while (1) {
        // 입력 핀의 상태를 변수 A, B에 저장
        A = var1;
        B = var2;

        // 논리 연산 결과 출력
        bool_not = !A;      // NOT 연산: A가 0이면 1, 1이면 0
        bool_and = A && B;  // AND 연산: A와 B 모두 1일 때만 1
        bool_or  = A || B;  // OR 연산: A 또는 B 중 하나라도 1이면 1
        bool_xor = A ^ B;   // XOR 연산: A와 B가 서로 다를 때만 1

        // 100ms 대기
        ThisThread::sleep_for(100ms);
    }
}