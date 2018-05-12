/** Controller test:
	Test to see if controller 
	keys get registered through I/O ports*/

#include "utils.h"
#include "controller.h"
#include "delay.h"

uint8_t controller_input = 0;
uint16_t keybuf[8] = {0,0,0,0,0,0,0,0};

void game_update(void){
	uint16_t db[8] = {0,0,0,0,0,0,0,0};
	static uint8_t controller_prev = 0;
	static bool hit_a = false;
	static bool hit_b = false;
	controller_input = controller_read();
	
	
	// basically, at each update cycle, do garbage collection and display
	// the movement of block is implement in the timer interrupt
	if ((controller_input != controller_prev)){
	//clear_buf(keybuf);
		switch(controller_input){
		case KEY_A:
			// write_to_buf(buf_a, keybuf); //MATRIX
			hit_a = true;
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
		case KEY_B:
			// write_to_buf(buf_b, keybuf); //MATRIX
			hit_b = true;
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
		case KEY_SELECT:
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
			
		case KEY_START:
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
			
		case KEY_UP:
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
			
		case KEY_DOWN:
			for (int i = 0; i < 20; i++) {
					LEDBlue_Toggle();
			}
			LEDBlue_Toggle();
			break;
			
		case KEY_LEFT:
			for (int i = 0; i < 8; i++) {
					LEDBlue_Toggle();
			}
			LEDBlue_Toggle();
			break;
			
		case KEY_RIGHT:
			for (int i = 0; i < 20; i++) {
					LEDBlue_On();
			}
			LEDBlue_Toggle();
			break;
			
		default:
			// erase_to_buf(buf_a, keybuf);
			// erase_to_buf(buf_b, keybuf);
			hit_a = false;
			hit_b = false;
			for (int i = 0; i < 20; i++) {
					LEDGreen_On();
				}
			LEDGreen_Toggle();
			break;
		}
	}
}

int main(void) {
	LED_Initialize();
	controller_init_beta();
	// init_delay();
	uint8_t i = 0;
	
	while (1) {
		// game_update();
	}
	LEDRed_On();
}