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
        pos = mypot/0.2;           
      
        led_on = 0x00;             
        
        for(int i=0; i<=pos; i++){
           
            led_on |= 0x08 << i;
        }
        
        leds = led_on ;            
        ThisThread::sleep_for(POT_DELAY);
    }
}