#include "mbed.h"

#define DS3231_ADDR (0x68)
#define REG_SEC     (0x00)
#define REG_MIN     (0x01)
#define REG_HOUR    (0x02)
#define REG_WEEK    (0x03)
#define REG_DAY     (0x04)
#define REG_MONTH   (0x05)
#define REG_YEAR    (0x06)

I2C i2c(I2C_SDA, I2C_SCL);

void    write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);

int main() {
    uint8_t addr = DS3231_ADDR << 1;

    // 시간 설정 (10:30 PM Tue, May 18, 2021)
    // 시간 설정 (현재 시간으로 수정)
/*write_data(addr, REG_SEC,   decimal_to_bcd(0));   // 초
write_data(addr, REG_MIN,   decimal_to_bcd(0));   // 분 ← 직접 수정
write_data(addr, REG_HOUR,  decimal_to_bcd(0));   // 시 ← 직접 수정
write_data(addr, REG_WEEK,  decimal_to_bcd(3));   // 3=Tue (화요일)
write_data(addr, REG_DAY,   decimal_to_bcd(10));  // 10일
write_data(addr, REG_MONTH, decimal_to_bcd(6));   // 6월
write_data(addr, REG_YEAR,  decimal_to_bcd(26));  // 26 = 2026년*/

    const char* week[]  = {"nul","Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    const char* month[] = {"","Jan","Feb","Mar","Apr","May","Jun",
                           "Jul","Aug","Sep","Oct","Nov","Dec"};

    while (1) {
        ThisThread::sleep_for(1000ms);

        uint8_t sec  = bcd_to_decimal(read_data(addr, REG_SEC));
        uint8_t min  = bcd_to_decimal(read_data(addr, REG_MIN));
        uint8_t hour = bcd_to_decimal(read_data(addr, REG_HOUR));
        uint8_t wk   = bcd_to_decimal(read_data(addr, REG_WEEK));
        uint8_t day  = bcd_to_decimal(read_data(addr, REG_DAY));
        uint8_t mon  = bcd_to_decimal(read_data(addr, REG_MONTH));
        uint8_t year = bcd_to_decimal(read_data(addr, REG_YEAR));

        const char* ampm = (hour >= 12) ? "PM" : "AM";
        uint8_t hour12 = (hour > 12) ? (hour - 12) : (hour == 0 ? 12 : hour);

        printf("현재시간: %02d:%02d %s %s, %s %d, 20%02d\r\n",
               hour12, min, ampm, week[wk], month[mon], day, year);
    }
}

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