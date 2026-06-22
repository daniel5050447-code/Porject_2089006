#include "mbed.h"
#define SAMPLING_DELAY 1000ms

// temperature sensor -> LM35DZ
AnalogIn LM35(PA_0);

int main() {
    float temp = 0.0;
    while(1) {
        temp = LM35.read() * 330;
        printf("Temperature= %f\n", temp);
        ThisThread::sleep_for(SAMPLING_DELAY);
    }
}