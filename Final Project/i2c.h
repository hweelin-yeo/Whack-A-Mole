#include <stdint.h>

void i2c_init(void);
void i2c_sendbyte(uint8_t data);
void i2c_test(void);
void i2c_setaddr(uint8_t addr);
void i2c_display(uint8_t buf[8]);
