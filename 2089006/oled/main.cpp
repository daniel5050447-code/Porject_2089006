/*#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(PB_9, PB_8);  // SDA=PB9, SCL=PB8 직접 지정
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

void oled_write_string(char *str);

int main() {
    i2c.frequency(400000);
    oled.begin();          // ← 이것도 추가!
    oled.clearDisplay();
    oled.setTextSize(1);
    oled.setTextCursor(10, 10);
    oled_write_string("Hello, World!");
    oled.setTextSize(2);
    oled.setTextCursor(10, 25);
    oled_write_string("SSD1306");
    oled.display();
    ThisThread::sleep_for(5000ms);
    oled.clearDisplay();
    oled.display();
    ThisThread::sleep_for(2000ms);
    oled.setTextSize(2);
    oled.setTextCursor(10, 25);
    oled_write_string("10:25 AM");
    oled.display();
    while(1) {}
}

void oled_write_string(char *str) {
    for(int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}*/
/*#include "mbed.h"
#include "Adafruit_SSD1306.h"

I2C i2c(PB_9, PB_8);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

void oled_write_string(char *str);

int main() {
    i2c.frequency(400000);
    oled.begin();
    oled.clearDisplay();

    char buff[20];

    // I2C 주소 저장 (0x3C = 실제 주소, 0x78 = 쓰기용 주소)
    int addr = 0x3C;

    // OLED에 출력
    oled.setTextSize(1);
    oled.setTextCursor(0, 0);
    oled_write_string("SSD1306 I2C Addr");

    oled.setTextSize(2);
    oled.setTextCursor(0, 20);
    sprintf(buff, "0x%X", addr);   // 0x3C 문자열로 변환
    oled_write_string(buff);

    oled.display();

    while(1) {}
}

void oled_write_string(char *str) {
    for(int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}*/

#include "mbed.h"
#include "Adafruit_SSD1306.h"

/* ========== 핀 설정 ========== */
I2C i2c(PB_9, PB_8);
Adafruit_SSD1306_I2c oled(i2c, NC, 0x78, 64, 128);

/* ========== DS3231 주소 ========== */
#define DS3231_ADDR  (0x68)
#define REG_SEC      (0x00)
#define REG_MIN      (0x01)
#define REG_HOUR     (0x02)
#define REG_WEEK     (0x03)
#define REG_DAY      (0x04)
#define REG_MONTH    (0x05)
#define REG_YEAR     (0x06)
#define REG_TEMP_MSB (0x11)
#define REG_TEMP_LSB (0x12)

/* ========== 함수 선언 ========== */
void    write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);
void    oled_write_string(char *str);

int main() {
    i2c.frequency(400000);
    oled.begin();
    oled.clearDisplay();

    uint8_t addr = DS3231_ADDR << 1;


    const char* week[]  = {"nul","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    const char* month[] = {"","Jan","Feb","Mar","Apr","May","Jun",
                           "Jul","Aug","Sep","Oct","Nov","Dec"};
    char buff[30];

    while (1) {
        ThisThread::sleep_for(1000ms);

        // 시간 읽기
        uint8_t sec  = bcd_to_decimal(read_data(addr, REG_SEC));
        uint8_t min  = bcd_to_decimal(read_data(addr, REG_MIN));
        uint8_t hour = bcd_to_decimal(read_data(addr, REG_HOUR));
        uint8_t wk   = bcd_to_decimal(read_data(addr, REG_WEEK));
        uint8_t day  = bcd_to_decimal(read_data(addr, REG_DAY));
        uint8_t mon  = bcd_to_decimal(read_data(addr, REG_MONTH));
        uint8_t year = bcd_to_decimal(read_data(addr, REG_YEAR));

        // 온도 읽기
        int8_t  temp_msb  = (int8_t)read_data(addr, REG_TEMP_MSB);
        uint8_t temp_lsb  = read_data(addr, REG_TEMP_LSB);
        float   temp_frac = ((temp_lsb >> 7) & 1) * 0.5f
                          + ((temp_lsb >> 6) & 1) * 0.25f;
        int temperature   = (int)(temp_msb + temp_frac);  // 정수로 표시

        // AM/PM 변환
        const char* ampm = (hour >= 12) ? "PM" : "AM";
        uint8_t hour12 = (hour > 12) ? (hour - 12) : (hour == 0 ? 12 : hour);

        oled.clearDisplay();

        // 1줄: 요일, 날짜 (작게)
        // 예: Mon, 20 May 2021
        oled.setTextSize(1);
        oled.setTextCursor(0, 0);
        sprintf(buff, "%s, %d %s 20%02d", week[wk], day, month[mon], year);
        oled_write_string(buff);

        // 2줄: 시간 (크게)
        // 예: 10:20 AM
        oled.setTextSize(2);
        oled.setTextCursor(0, 16);
        sprintf(buff, "%02d:%02d %s", hour12, min, ampm);
        oled_write_string(buff);

        // 3줄: 온도 (작게)
        // 예: Temp: 25C
        oled.setTextSize(1);
        oled.setTextCursor(0, 48);
        sprintf(buff, "Temp: %dC", temperature);
        oled_write_string(buff);

        oled.display();
    }
}

/* ========== 함수 구현 ========== */
void write_data(uint8_t addr, uint8_t reg, uint8_t data) {
    char byte[2];
    byte[0] = reg;
    byte[1] = data;
    i2c.write(addr, byte, 2, 0);
}

uint8_t read_data(uint8_t addr, uint8_t reg) {
    char data[1];
    char byte[1];
    byte[0] = reg;
    i2c.write(addr, byte, 1, 1);
    i2c.read(addr, data, 1, 0);
    return data[0];
}

uint8_t bcd_to_decimal(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t decimal_to_bcd(uint8_t decimal) {
    return ((decimal / 10) << 4) | (decimal % 10);
}

void oled_write_string(char *str) {
    for (int i = 0; str[i]; i++) {
        oled.writeChar(str[i]);
    }
}