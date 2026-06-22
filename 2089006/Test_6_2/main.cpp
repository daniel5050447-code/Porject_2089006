#include "mbed.h"

#define DS3231_ADDR  (0x68)
#define REG_TEMP_MSB (0x11)
#define REG_TEMP_LSB (0x12)

I2C i2c(I2C_SDA, I2C_SCL);

void    write_data(uint8_t addr, uint8_t reg, uint8_t data);
uint8_t read_data(uint8_t addr, uint8_t reg);

int main() {
    uint8_t addr = DS3231_ADDR << 1;

    while (1) {
        ThisThread::sleep_for(1000ms);

        int8_t  temp_msb  = (int8_t)read_data(addr, REG_TEMP_MSB);
        uint8_t temp_lsb  = read_data(addr, REG_TEMP_LSB);
        float   temp_frac = ((temp_lsb >> 7) & 1) * 0.5f
                          + ((temp_lsb >> 6) & 1) * 0.25f;
        float temperature = temp_msb + temp_frac;

        printf("온도: %.2f C\r\n", temperature);
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