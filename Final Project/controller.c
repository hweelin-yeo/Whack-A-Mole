#include "controller.h"
#include "MK64F12.h"

void CTRL_CLK_HIGH(void){
	PTC->PSOR |= (1<<CTRL_CLK_PIN);
}

void CTRL_CLK_LOW(void){
	PTC->PCOR |= (1<<CTRL_CLK_PIN);
}

void CTRL_LAT_HIGH(void) {
	PTC->PSOR |= (1<<CTRL_LAT_PIN);
}

void CTRL_LAT_LOW(void){
	PTC->PCOR |= (1<<CTRL_LAT_PIN);
}

void controller_init(void){
	SIM->SCGC5 |= (1<<11); // Enable clock to Port C
	SIM->SCGC5 |= (1<<9); // Enable clock to Port A
	
	PORTC->PCR[CTRL_CLK_PIN] = PORT_PCR_MUX(001); // set pins as GPIO
	PORTC->PCR[CTRL_LAT_PIN] = PORT_PCR_MUX(001);
	PORTA->PCR[CTRL_DAT_PIN] = PORT_PCR_MUX(001);

	PTC->PDDR |= (1<<CTRL_CLK_PIN) | (1<<CTRL_LAT_PIN); 
	PTA->PDDR &= ~(1<<CTRL_DAT_PIN);
	
	CTRL_CLK_HIGH();
	CTRL_LAT_HIGH();
}

int DATA_READ(void){
	return ((PTA->PDIR >> CTRL_DAT_PIN) & 1);
}


uint8_t controller_read(void){
	uint8_t res = 0;
	int i = 0;
	
	CTRL_LAT_LOW();
	CTRL_CLK_LOW();
	
	CTRL_LAT_HIGH();
	for (i = 1; i <= 7; i++) {
		// delay
	}
	CTRL_LAT_LOW();
	
	res = DATA_READ();
	
	for(i = 1;i <= 7; i++)
  {
		CTRL_CLK_HIGH();
		for (i = 1; i <= 7; i++) {
		// delay
	}
		res = res << 1;
		res += DATA_READ();
		for (i = 1; i <= 7; i++) {
		// delay
	}
		CTRL_CLK_LOW();
  }
	
	return ~res;

}

void poll_key(uint8_t key){
	uint8_t d = 0;
	while (d != key) {d = controller_read();}
}

void poll_key_release(uint8_t key){
	uint8_t d = 0;
	uint8_t d_prev = 0;
	while (1) {
		d = controller_read();
		if ((d_prev == key) && (d != d_prev)) {break;}
		d_prev = d;
	}
}