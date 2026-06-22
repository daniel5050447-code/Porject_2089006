#include "mbed.h"
PwmOut buzzer(PB_0);
int main(void){
for(int i = 1; i <= 5; i++) {
buzzer.period_us(1000); // 1ms period, 1000Hz
buzzer.write(0.5f); // 50% duty cycle
ThisThread::sleep_for(1000ms);
buzzer.period_us(2000); // 2ms period, 500Hz
buzzer.write(0.5f); // 50% duty cycle
ThisThread::sleep_for(1000ms);
}
return 0;
}