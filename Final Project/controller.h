#include <stdint.h>

uint8_t controller_read(void);
void controller_init(void);
void controller_init_beta(void);
int DATA_READ();
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

#define KEY_A 0x80
#define KEY_B 0x40
#define KEY_START 0x10
#define KEY_SELECT 0x20
#define KEY_UP 0x8
#define KEY_DOWN 0x4
#define KEY_LEFT 0x1 //0x2
#define KEY_RIGHT 0x2 // 0x1



