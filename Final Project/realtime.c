#include "realtime.h"

realtime_t current_time = {0, 0};

void timer_init (void) {
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT->MCR = 0;
	PIT->CHANNEL[1].LDVAL = 0x24613; // 0xc350// not accurate // TODO: Revise this value
	PIT -> CHANNEL[1].TCTRL |= 0x3; // Enable interrupts and timer
	NVIC_EnableIRQ(PIT1_IRQn);
	NVIC_SetPriority(PIT1_IRQn, 3);
	// Don't enable the timer yet . 
}

void PIT1_IRQHandler(void) {
	if (current_time.msec == 999) {
		current_time.sec = (current_time.sec) + 1;
		current_time.msec = 0;
	} else {
		current_time.msec++;
	}
	NVIC_DisableIRQ(PIT1_IRQn);
	PIT -> CHANNEL[1].TFLG |= 0x1;
	NVIC_EnableIRQ(PIT1_IRQn);

}