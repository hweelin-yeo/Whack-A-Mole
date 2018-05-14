#include "controller.h"
#include "MK64F12.h"
#include "delay.h"
#include "utils.h"
int i = 0;

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
	PIT -> MCR &= ~0x03;
	PIT -> CHANNEL[1].TFLG |= 0x01;
	PIT -> CHANNEL[1].LDVAL = 0xC350;
	PIT -> CHANNEL[1].TCTRL = 0x3;
	// NVIC_EnableIRQ(PIT1_IRQn); // Enable interrupt handler
	// NVIC_SetPriority(PIT1_IRQn, 3);
	
}

//void PIT1_IRQHandler(void) {
//	// int dat = DATA_READ();
//	NVIC_DisableIRQ(PIT1_IRQn);
//	PIT -> CHANNEL[1].TFLG |= 0x1;
//	NVIC_EnableIRQ(PIT1_IRQn);
//	
//}

void controller_init_beta(void) {
	//PTC6, PTA4 as SW2 and SW3
	
	SIM->SCGC5 |= (1<<11); // Enable clock to Port C
	SIM->SCGC5 |= (1<<9); // Enable clock to Port A
	  
	PORTA->PCR[4] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IRQC(0x0A);//PTA1 as GPIO, Pull Up, interrupt on falling edge  
  PORTC->PCR[6] |= PORT_PCR_MUX(1) | PORT_PCR_PE(1) | PORT_PCR_PS(1) | PORT_PCR_IRQC(0x0A);//PTD4 as GPIO, Pull up, interrupt on falling edge  
	
	PTA->PDDR &= ~(1<<4);
	PTC->PDDR &= ~(1<<6);
	
	NVIC_EnableIRQ(PORTC_IRQn); /*Enable the PORTC interrupt*/
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_SetPriority(PORTC_IRQn, 1);
	NVIC_SetPriority(PORTA_IRQn, 1);
		
	// Alternative: SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK;    //Set up peripheral clock for GPIO A,B,D  

	
	// Alternative: PORTA->PCR[4] |= PORT_PCR_MUX(001); //Set up PTA4 as GPIO
//	PORTC->PCR[6] |= PORT_PCR_MUX(001); //Set up PTC6 as GPIO
//	
//	PORTA -> PCR[4] |= 0x00003; // enable pullup
//	PORTC -> PCR[6] |= 0x00003; // enable pullup
	
//	PORTA -> PCR[4] &= ~0xF0000; // clear interrupt selection
//	PORTA -> PCR[4] |= 0xA0000; // enable falling edge interrupt
//	
//	PORTC -> PCR[6] &= ~0xF0000; // clear interrupt selection
//	PORTC -> PCR[6] |= 0xA0000; //  0xB0000 // enable falling edge interrupt
	 
	// NVIC->ISER[0] |= 0x40000000;    /* enable INT30 (bit 30 of ISER[0]) */
	// 
	
	// PORTC -> ISFR  = PORT_ISFR_ISF(0x40); /* Clear interrupt status flag */
	// PORTA -> ISFR = PORT_ISFR_ISF(0x10);
	/* Init input switch GPIO. */
	
	
//    PORT_SetPinInterruptConfig(BOARD_SW_PORT, BOARD_SW_GPIO_PIN, kPORT_InterruptFallingEdge);
//    EnableIRQ(BOARD_SW_IRQ);
//    GPIO_PinInit(BOARD_SW_GPIO, BOARD_SW_GPIO_PIN, &sw_config);
	
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

//int main() {
//	LED_Initialize();
//	controller_init_beta();
//}
