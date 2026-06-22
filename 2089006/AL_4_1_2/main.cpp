/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#define LED_MASK 0x000000f0


AnalogIn mypot(PA_0);           
PortOut leds(PortA, LED_MASK);  


int main()
{
    while(1) {
        
        float read= mypot.read();
        float cal = read * 3.3f; 

        
        float dir = mypot.read_voltage();

        
        printf("(1) cal: %8.2f, (2) dir: %8.2f\n", cal, dir);

        ThisThread::sleep_for(500ms); // 0.5초마다 갱신
    }
}
