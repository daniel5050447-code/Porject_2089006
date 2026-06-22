/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define BLINK_DELAY 500ms
#define Led_MASK    0x000000f0
DigitalOut led0(PA_4);
DigitalOut led1(PA_5);
DigitalOut led2(PA_6);
DigitalOut led3(PA_7);

/*int main()
{
    while(1)
    {
        led0=1;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);


    }
}*/
//문제 2번
/*int main()
{
    while(1)
    {
        led0=0;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=1;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=0;led2=0;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);

    }
}*/
/*int main()
{
    while(1)
    {
        led0=1;led1=0;led2=1;led3=0;
        ThisThread::sleep_for(BLINK_DELAY);
        led0=0;led1=1;led2=0;led3=1;
        ThisThread::sleep_for(BLINK_DELAY);


    }
}*/
//실습 2-1
/*PortOut leds(PortA, Led_MASK);
int main(){
   // 1. 2진 계수
while(1) {
    for(int i=0; i<=15; i++) {
        leds = (i << 4); 
        ThisThread::sleep_for(BLINK_DELAY);
    }
    leds = 0;
    ThisThread::sleep_for(BLINK_DELAY);
}
}*/
//실습 2-2
/*PortOut leds(PortA, Led_MASK);
int main(){
    while(1){
        leds=0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i=0;i<=3;i++){
            leds=0b00010000<<i;
            ThisThread::sleep_for(BLINK_DELAY);

        }
        for(int j=0;j<=3;j++){
                leds=0b10000000>>j;
                ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}*/
/*PortOut leds(PortA, Led_MASK);
int main(){
    while(1){
        leds=0;
        ThisThread::sleep_for(BLINK_DELAY);
        for(int i=0;i<=3;i++){
            leds=0b00010000<<i;
            ThisThread::sleep_for(BLINK_DELAY);

        }
        for(int j=0;j<=3;j++){
                leds=0b10000000>>j;
                ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}*/

PortOut leds(PortA, Led_MASK);

int main() {
    while(1) {
        leds = 0; // 모든 LED 끄기
        ThisThread::sleep_for(BLINK_DELAY);
        
        // 1. 하나씩 켜기 (Accumulate)
        // 0x80(1000 0000)부터 오른쪽으로 밀면서 4번 반복
        for(int i=0; i<4; i++) {
            leds | = (0x80 >> i);  
            ThisThread::sleep_for(BLINK_DELAY);
        }

        // 2. 하나씩 끄기 (Diminish)
        // 0x80(1000 0000) 비트를 반전(~)시켜서 하나씩 끄기
        for(int i=0; i<4; i++) {
            leds & = ~(0x80 >> i); 
            ThisThread::sleep_for(BLINK_DELAY);
        }
    }
}
/*
PortOut leds(PortA, Led_MASK);
int main(){
    while(1) {
    leds = 0;
    ThisThread::sleep_for(BLINK_DELAY);

    uint32_t val = 0;
    
    for(int i=0; i<4; i++) {
        val |= (0x80 >> i); 
        leds = val;
        ThisThread::sleep_for(BLINK_DELAY);
    }
    
    for(int i=0; i<4; i++) {
        val &= ~(0x10 << i); 
        leds = val;
        ThisThread::sleep_for(BLINK_DELAY);
    }
}
}*/

