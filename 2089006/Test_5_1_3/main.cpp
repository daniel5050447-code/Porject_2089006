#include "mbed.h"
#define SAMPLING_DELAY 1000ms
AnalogIn CdS(PA_0, 3.3);
int main() {
float light = 0.0;
while(1){
light = CdS;
printf("Light level = %f\n", light);
ThisThread::sleep_for(SAMPLING_DELAY);
}
}