#include "mbed.h"
#define SAMPLING_DELAY 1000ms

// temperature sensor -> TMP36GT
AnalogIn TMP36(PA_0);

int main() {
    float temp = 0.0;
    while(1) {
        temp = (TMP36.read() * 3.3 - 0.5) * 100;
        printf("Temperature= %f\n", temp);
        ThisThread::sleep_for(SAMPLING_DELAY);
    }
}