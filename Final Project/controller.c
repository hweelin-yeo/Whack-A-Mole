#include "controller.h"
#include "MK64F12.h"
#include "delay.h"
#include "utils.h"

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

void PIT_init() {
	SIM-> SCGC6 = SIM_SCGC6_PIT_MASK;
	PIT -> MCR &= ~0X03;
	PIT -> CHANNEL[1].TFLG |= 0X01;
	PIT -> CHANNEL[1].LDVAL = 0XD9FB92;
	PIT -> CHANNEL[1].TCTRL = 0X3;
	NVIC_EnableIRQ(PIT1_IRQn); // Enable interrupt handler
	
}

void controller_init_beta(void) {
	//PTC6, PTA4
	PIT_init();
	
	SIM->SCGC5 |= (1<<11); // Enable clock to Port C
	SIM->SCGC5 |= (1<<9); // Enable clock to Port A
	
	PORTA->PCR[4] |= 0X00100; // PORT_PCR_MUX(001); //Set up PTA4 as GPIO
	PORTC->PCR[6] |= 0X00100; // PORT_PCR_MUX(001); //Set up PTC6 as GPIO
	
	PORTA -> PCR[4] |= 0X00003; // enable pullup
	PORTC -> PCR[6] |= 0X00003; // enable pullup
	
	PTA->PDDR &= ~(1<<4);
	PTC->PDDR &= ~(1<<6);
	
	PORTA -> PCR[4] &= ~0XF0000; // clear interrupt selection
	PORTA -> PCR[4] |= 0XA0000; // enable falling edge interrupt
	
	PORTC -> PCR[6] &= ~0XF0000; // clear interrupt selection
	PORTC -> PCR[6] |= 0XA0000; // enable falling edge interrupt
	 
	NVIC->ISER[0] |= 0x40000000;    /* enable INT30 (bit 30 of ISER[0]) */
	// 
	
	// PORTC -> ISFR  = PORT_ISFR_ISF(0x40); /* Clear interrupt status flag */
	// PORTA -> ISFR = PORT_ISFR_ISF(0x10);
	/* Init input switch GPIO. */
	
	
//    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
//    EnableIRQ(BOARD_SW_IRQ);
//    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
	
	NVIC_EnableIRQ(PORTC_IRQn); /*Enable the PORTC interrupt*/
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTC_IRQn, 1);
	NVIC_SetPriority(PORTC_IRQn, 1);
}

void PORTA_IRQHandler(void)
{ PORTA ->ISFR  = 0x04;
	LEDGreen_On();
	
}

void PORTC_IRQHandler(void)
{ 
	PORTC ->ISFR  = 0x06;
	LEDBlue_On();
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
	int dat = (PTA->PDIR >> CTRL_DAT_PIN) & 1;
	return dat;
}


uint8_t controller_read(void){
	uint8_t res = 0;
	int i = 0;
	
	CTRL_LAT_LOW();
	CTRL_CLK_LOW();
	
	CTRL_LAT_HIGH();
	delay_us(2);
	CTRL_LAT_LOW();
	
	res = DATA_READ();
	
	for(i = 1;i <= 2; i++)
  {
		CTRL_CLK_HIGH();
		delay_us(2);
		res = res << 1;
		res += DATA_READ();
		delay_us(4);
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

int poll_2k_release(uint8_t key1, uint8_t key2){
	uint8_t d = 0;
	uint8_t d_prev = 0;
	while (1) {
		d = controller_read();
		if ((d_prev == key1) && (d != d_prev)) {return 1;}
		if ((d_prev == key2) && (d != d_prev)) {return 2;}
		d_prev = d;
	}
}