#include "mbed.h"
PwmOut led(PA_0);
int main()
{
led.period(2.0f); // 2 second period
led.write(0.25f); // 25% duty cycle
//led.pulsewidth(1);
//led = 0.5f;
while (1);
}