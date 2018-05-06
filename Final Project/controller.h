#include <stdint.h>

uint8_t controller_read(void);
void controller_init(void);
void poll_key(uint8_t key);
void poll_key_release(uint8_t key);

#define CTRL_CLK_GPIO GPIOC
#define CTRL_CLK_PIN 3
#define CTRL_CLK_PORT PORTC

#define CTRL_LAT_GPIO GPIOC
#define CTRL_LAT_PIN 2
#define CTRL_LAT_PORT GPIOC

#define CTRL_DAT_GPIO GPIOA
#define CTRL_DAT_PIN 2
#define CTRL_DAT_PORT GPIOA



