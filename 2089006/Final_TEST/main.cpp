#include "mbed.h"

/* ========== 센서 ========== */
DigitalOut trig(D7);
DigitalIn  echo(D8);
DigitalIn  pir(D4);
AnalogIn   cds(A0);

/* ========== 출력 ========== */
PwmOut     buzzer(D3);
DigitalOut yellowLed(D9);
DigitalOut redLed(A2);
DigitalOut blueLed(D5);

/* ========== 버튼 ========== */
InterruptIn button(BUTTON1);

/* ========== 공유 변수 ========== */
volatile bool blueState   = false;
volatile bool buzzerOn    = false;
volatile bool pirDetected = false;

/* ========== 쓰레드 선언 ========== */
Thread ultrasonicThread;
Thread buzzerThread;
Thread pirThread;
Thread cdsThread;
Thread blueThread;

/* ========== 버튼 ISR ========== */
void toggleBlue() {
    blueState = !blueState;
}

/* ========== 거리 측정 ========== */
float getDistance() {
    trig = 1;
    wait_us(10);
    trig = 0;

    Timer timeout;
    timeout.start();
    while (echo == 0) {
        if (timeout.elapsed_time() > 30ms) return -1.0f;
    }

    Timer t;
    t.start();
    timeout.reset();
    while (echo == 1) {
        if (timeout.elapsed_time() > 30ms) break;
    }
    t.stop();

    return t.elapsed_time().count() / 58.0f;
}

/* ========== 쓰레드 1: 초음파 ========== */
void ultrasonicTask() {
    while (1) {
        float dist = getDistance();
        if (dist > 0 && dist < 10.0f && !buzzerOn) {
            buzzerOn = true;
        }
        ThisThread::sleep_for(200ms);
    }
}

/* ========== 쓰레드 2: 버저 ========== */
void buzzerTask() {
    while (1) {
        if (buzzerOn) {
            for (int i = 0; i < 10; i++) {
                buzzer.period_us(250);
                buzzer.write(0.5f);
                ThisThread::sleep_for(250ms);
                buzzer.period_us(500);
                buzzer.write(0.5f);
                ThisThread::sleep_for(250ms);
            }
            buzzer.write(0.0f);
            buzzerOn = false;
        }
        ThisThread::sleep_for(50ms);
    }
}

/* ========== 쓰레드 3: PIR ========== */
void pirTask() {
    while (1) {
        if (pir == 1 && !pirDetected) {
            pirDetected = true;
            for (int i = 0; i < 6; i++) {
                redLed = 1;
                ThisThread::sleep_for(200ms);
                redLed = 0;
                ThisThread::sleep_for(200ms);
            }
            pirDetected = false;
        }
        ThisThread::sleep_for(100ms);
    }
}

/* ========== 쓰레드 4: 조도센서 ========== */
void cdsTask() {
    while (1) {
        float light = cds.read();
        if (light > 0.15f) {
            yellowLed = 0;
        } else {
            yellowLed = 1;
        }
        ThisThread::sleep_for(200ms);
    }
}

/* ========== 쓰레드 5: 파랑 LED ========== */
void blueTask() {
    while (1) {
        blueLed = blueState;
        ThisThread::sleep_for(100ms);
    }
}

int main() {
    buzzer.write(0.0f);
    button.rise(&toggleBlue);

    // 쓰레드 시작
    ultrasonicThread.start(ultrasonicTask);
    buzzerThread.start(buzzerTask);
    pirThread.start(pirTask);
    cdsThread.start(cdsTask);
    blueThread.start(blueTask);

    while (1) {
        ThisThread::sleep_for(1000ms);
    }
}