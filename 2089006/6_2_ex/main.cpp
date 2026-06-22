#include "mbed.h"

#define DS3231_ADDR (0x68)
#define REG_SEC     (0x00)
#define REG_MIN     (0x01)
#define REG_HOUR    (0x02)
#define REG_WEEK    (0x03)
#define REG_DAY     (0x04)
#define REG_MONTH   (0x05)
#define REG_YEAR    (0x06)

void write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);
uint8_t bcd_to_decimal(uint8_t bcd);
uint8_t decimal_to_bcd(uint8_t decimal);

I2C i2c(I2C_SDA, I2C_SCL);

int main(){
    char week[8][4] = {"nul", "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    unsigned char times[7];
    uint8_t addr = DS3231_ADDR << 1;

    write_data(addr, REG_SEC,   decimal_to_bcd(30));
    write_data(addr, REG_MIN,   decimal_to_bcd(59));
    write_data(addr, REG_HOUR,  decimal_to_bcd(15));
    write_data(addr, REG_WEEK,  decimal_to_bcd(3));
    write_data(addr, REG_DAY,   decimal_to_bcd(18));
    write_data(addr, REG_MONTH, decimal_to_bcd(5));
    write_data(addr, REG_YEAR,  decimal_to_bcd(26));

    while(1){
        ThisThread::sleep_for(1000ms);
        times[0] = bcd_to_decimal(read_data(addr, REG_SEC));
        times[1] = bcd_to_decimal(read_data(addr, REG_MIN));
        times[2] = bcd_to_decimal(read_data(addr, REG_HOUR));
        times[3] = bcd_to_decimal(read_data(addr, REG_WEEK));
        printf("%02d:%02d:%02d %s\n", times[2], times[1], times[0], week[times[3]]);
    }
}

void write_data(uint8_t addr, uint8_t reg, uint8_t data){
    char byte[2];
    byte[0] = reg;
    byte[1] = data;
    i2c.write(addr, byte, 2, 0);
}

uint8_t read_data(uint8_t addr, uint8_t reg){
    char data[1];
    char byte[1];
    byte[0] = reg;
    i2c.write(addr, byte, 1, 1);
    i2c.read(addr, data, 1, 0);
    return data[0];
}

uint8_t bcd_to_decimal(uint8_t bcd){
    return (bcd >> 4) * 10 + (bcd & 0x0F);
}

uint8_t decimal_to_bcd(uint8_t decimal){
    return ( ((decimal / 10) << 4) | (decimal % 10) );
}