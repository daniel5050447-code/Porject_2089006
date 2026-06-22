#include "mbed.h"

PwmOut   led(PA_0);
AnalogIn cds(PA_1);

int main()
{
    led.period_ms(10);  // 100Hz

    while(1) {
        float light = cds.read();  // 실제 범위: 0.05 ~ 0.24

        // 실제 범위를 0.0 ~ 1.0으로 변환
        float min_val = 0.05f;
        float max_val = 0.24f;

        float brightness = (light - min_val) / (max_val - min_val);

        // 0.0~1.0 범위 초과 방지
        if(brightness < 0.0f) brightness = 0.0f;
        if(brightness > 1.0f) brightness = 1.0f;

        // 반전: 어두울수록 LED 밝게
        brightness = 1.0f - brightness;

        led.write(brightness);
        printf("light=%f  brightness=%f\n", light, brightness);
        ThisThread::sleep_for(100ms);
    }
}