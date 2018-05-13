#include "game.h"

int game_state = 0; 
int game_end = 0;
int score = 0;
int answer_key = 0;
int key_pressed = 0;
uint8_t controller_input = 0;

void game_init(void){
	LED_Initialize();
//	init_delay();
	controller_init_beta();
	
	game_state = GAME_INIT;
	game_run();
}

void game_run(void){
	game_end = 0;
	// main game implemented here
	while(!game_end){
		switch(game_state){
			case GAME_INIT:
				// task = HTCreate();
				// loadbuffer(data, reload_sw);
				// poll_key(KEY_START);
				game_state = GAME_START;
				timer_init();
				break;
			case GAME_START:
				game_update_beta();
				break;
			case GAME_END:
				LEDGreen_On();
				//clear_buf(blocktmpbuf);
				//HTDestroy(task);
				// task = 0;
				// reload_sw = true;
				// clear_timer(&current_time);
				// poll_key(KEY_START);
				LEDGreen_On();
				game_end = 1;
				break;
			default:
				break;
		}
	}
}

int draw_moles (void) {
	int pos = current_time.msec % 2;
	int key = (pos == 0) ? KEY_LEFT : KEY_RIGHT;
	return key;
}
void game_update_beta(void) {
	// draw moles
	key_pressed = 0;
	answer_key = draw_moles(); // draw moles function updates display, and also returns key
	
	// poll for x seconds for the right key
	int time = 0;
	
	while (key_pressed == 0 && time < 999) {
		time++; // wait
	}
	
	int delay = 0;
	while (delay < 1000) {
		delay++; 
	}
	
	
}
void game_update(void){
	// draw moles?
	uint16_t db[8] = {0,0,0,0,0,0,0,0};
	static uint8_t controller_prev = 0;
	static int hit_a = 0;
	static int hit_b = 0;
	// controller_input = controller_read();
	// 
	
	// basically, at each update cycle, do garbage collection and display
	// the movement of block is implement in the timer interrupt
	if ((controller_input != controller_prev)){
	// clear_buf(keybuf);
		switch(controller_input){
		case KEY_A:
			// write_to_buf(buf_a, keybuf);
			hit_a = 1;
			break;
		case KEY_B:
			// write_to_buf(buf_b, keybuf);
			hit_b = 1;
			break;
		case KEY_A+KEY_B:
			// write_to_buf(buf_b, keybuf);
			// write_to_buf(buf_a, keybuf);
			hit_a = 1;
			hit_b = 1;
			break;
		case KEY_SELECT:
			game_state = GAME_PAUSE;
		default:
			// erase_to_buf(buf_a, keybuf);
			//erase_to_buf(buf_b, keybuf);
			hit_a = 1;
			hit_b = 1;
			break;
		}
	}
	if (hit_a){
		// if ((blocktmpbuf[2] >> 14) & 3) health += 2; else if ((blocktmpbuf[2] >> 12) & 3) health += 1;
	} 
	if (hit_b){
		//if ((blocktmpbuf[5] >> 14) & 3) health += 2; else if ((blocktmpbuf[5] >> 12) & 3) health += 1;
	}
	
//	if (health > 16) health = 16;
//	write_to_buf(keybuf, db);
//	write_to_buf(blocktmpbuf, db);
//	display_health(health, scorebuf);
//	write_to_buf(scorebuf,db);
//	display_update(db);
//	controller_prev = controller_input;
}



void display_update(uint16_t buf[8]){
//	if (!buf_eq(buf, dispbuf)){
//		clear_buf(dispbuf);
//		write_to_buf(buf, dispbuf);
//		i2c_display(dispbuf);
//	}
}


void evaluateAnswer() {
	if (key_pressed != answer_key) {
		LEDRed_On();
		score--;
		
		int delay = 0;
		while (delay < 1000) {
			delay++; 
		}
		LED_Off();
			
	} else {
		LEDGreen_On();
		score++;
		
		int delay = 0;
		while (delay < 1000) {
			delay++; 
		}
		LED_Off();
	}
}
void PORTA_IRQHandler(void)
{ 
	__disable_irq();
	PORTA ->ISFR  = (1 << 4);
	key_pressed = KEY_RIGHT;
	evaluateAnswer();
	// LEDGreen_On();
	__enable_irq();
	
}

void PORTC_IRQHandler(void)
{ 
	__disable_irq();
	NVIC_DisableIRQ(PIT1_IRQn);
	PORTC ->ISFR  = (1 << 6);
	key_pressed = KEY_LEFT;
	evaluateAnswer();
	
	//	LEDRed_On();
	__enable_irq();
	NVIC_EnableIRQ(PIT1_IRQn);
}

int main() {
	game_init();
}