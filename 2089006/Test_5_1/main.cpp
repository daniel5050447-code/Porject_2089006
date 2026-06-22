#include "mbed.h"


AnalogIn tempSensor(PA_0);      
PortOut leds(PortA, 0x000000F0); 

#define THRESHOLD_TEMP 27

int main() {
    float voltage, temp;

    while(1) {
       
        temp = (tempSensor.read() * 3.3f - 0.5f) * 100.0f;
        
        printf("Current Temp: %.2f C\n", temp);

        // --- 실습 1번: 25도 이상이면 모두 켜기 ---
        /*
        if (temp >= THRESHOLD_TEMP) leds = 0xF0; 
        else leds = 0x00;                        
        */

        // --- 실습 2번: 25도 이상이면 모두 깜빡이기 ---
        /*
        if (temp >= THRESHOLD_TEMP) {
            leds = 0xF0;
            ThisThread::sleep_for(200ms);
            leds = 0x00;
            ThisThread::sleep_for(200ms);
        } 
        else {
            leds = 0x00; // 25도 미만이면 끄기
        }
        */
        // --- 실습 3번: 온도에 따라 켜지는 LED 수 조절 (응용) ---
        // 예: 20도(1개), 25도(2개), 30도(3개), 35도(4개)
        
        if (temp >= 27) leds = 0xF0;
        else if (temp >= 25) leds = 0x70;
        else if (temp >= 23) leds = 0x30;
        else if (temp >= 20) leds = 0x10;
        else leds = 0x00;
        

        ThisThread::sleep_for(500ms);
    }
}