/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define LED_MASK 0x000000f0
// LED0=PA_4, LED1=PA_5, LED2=PA_6, LED3=PA_7
#define POT_DELAY 200ms

AnalogIn mypot(PA_0, 3.3);
PortOut leds(PortA, LED_MASK);

int main() {
    int led_on, pos=0;
    
    while(1){
        pos = mypot/0.2;            // 5구간으로 분할
        //printf("val= %d\n", pos);
        led_on = 0x00;              // led들의 비트 패턴
        
        for(int i=0; i<=pos; i++){
            // pos의 값에 따라 LED 비트설정
            led_on |= 0x08 << i;
        }
        
        leds = led_on ;             // 비트패턴에 따라 LED 켬
        ThisThread::sleep_for(POT_DELAY);
    }
}
