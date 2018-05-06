/** Controller test:
	Test to see if controller 
	keys get registered through I/O ports*/

#include "utils.h"
#include "controller.h"

int main(void) {
	LED_Initialize();
	controller_init();
	
	uint8_t controller_input = controller_read();
	
	switch (controller_input) {
		case KEY_A:
			for (int i = 0; i < 8; i++) {
				LEDBlue_Toggle();
			}

		case KEY_B:
			for (int i = 0; i < 8; i++) {
				LEDRed_Toggle();
			}
		
		default:
				for (int i = 0; i < 8; i++) {
					LEDGreen_Toggle();
			}
		
		}
		
		LEDGreen_On();
}