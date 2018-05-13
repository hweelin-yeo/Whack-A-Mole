// #include <stdint.h>
// #include <stdbool.h>
// #include "delay.h"
#include "utils.h"
#include "controller.h"
#include <string.h>
#include "MK64F12.h"
// #include <stdlib.h>
#include "realtime.h"

#define GAME_INIT 0
#define GAME_START 1
#define GAME_PAUSE 2
#define GAME_END 3

#define LAG (FALL_SPD*10)
#define END_DELAY (1200)

extern uint16_t dispbuf[8];
extern uint8_t controller_input;

void game_init(void);
void game_run(void);

void game_update(void);
void game_update_beta(void);
void display_update(uint16_t buf[8]);

void clear_disp(void);