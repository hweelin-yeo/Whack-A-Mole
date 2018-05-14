#include "MK64F12.h"
#include "i2c.h"

static uint8_t slave_addr = (0x70<<1); //TODO: Why is he shifting

/* SCL Helper Functions */
void scl_setdir(int dir){
  if (dir){
    PTE->PDDR &= ~(1<<24); //Pin 24 is set as input
  } else {
    PTE->PDDR |= (1<<24) //Pin 24 is set as output
  }
}
int scl_getdir(void){
  return ((PTE->PDDR)>>24) &1; //Returns whether Pin 24 is input or output
}
void scl_setval(int val){
  if (val){
    PTE->PSOR |=(1<<24); //Pin 24 is set as logic 1
  } else {
    PTE->PCOR |=(1<<24); //Pin 24 is set as logic 0
  }
}
uint8_t scl_getval(void){
  if (scl_getdir() == 0){
    return ((PTE->PDIR)>>24) &1; //Return logic level of Pin 24
  } else {
    return ((PTE->PDOR)>>24) &1; //Return logic level of driven on Pin 24
  }
}

/* SDA Helper Functions */
void sda_setdir(int dir){
  if (dir){
    PTE->PDDR &= ~(1<<25); //Pin 25 is set as input
  } else {
    PTE->PDDR |= (1<<25) //Pin 25 is set as output
  }
}
int sda_getdir(void){
  return ((PTE->PDDR)>>25) &1; //Returns whether Pin 25 is input or output
}
void sda_setval(int val){
  if (val){
    PTE->PSOR |=(1<<25); //Pin 25 is set as logic 1
  } else {
    PTE->PCOR |=(1<<25); //Pin 25 is set as logic 0
  }

}
uint8_t sda_getval(void){
  if (sda_getdir() == 0){
    return ((PTE->PDIR)>>25) &1; //Return logic level of Pin 25
  } else {
    return ((PTE->PDOR)>>25) &1; //Return logic level of driven on Pin 25
  }
}

/* I2C Functions */

void i2c_delay(void){}

void i2c_init(void){
  SIM->SCGC5 |= (1<<13); //TODO: Why this number?
  //Set SCL and SDA as input
  scl_setdir(1);
  sda_setdir(1);
  PORTE->PCR[24] = PORT_PCR_MUX(001); //Set up PTE24 as GPIO
  PORTE->PCR[25] = PORT_PCR_MUX(001); //Set up PTE25 as GPIO
}

void i2c_start(void){
  //Set SCL and SDA as logic level 1
  scl_setval(1);
  sda_setval(1);
  sda_setval(0);
  i2c_delay();
  i2c_delay();
  i2c_delay();
  i2c_delay();
  i2c_delay();
  scl_setval(0);
}

void i2c_stop(void){
  sda_setval(0);
  scl_setval(1);
  i2c_delay();
  i2c_delay();
  i2c_delay();
  i2c_delay();
  i2c_delay();
  sda_setval(1);
}

int i2c_clock(void){
  int level;
  scl_setval(1);
  i2c_delay();
  while(!scl_getval()){};
  i2c_delay();
  i2c_delay();
  i2c_delay();
  level = sda_getval();
  i2c_delay();
  i2c_delay();
  scl_setval(0);
  return level;
}

int i2c_write(uint8_t data){
  uint8_t mask = 0x80;
  while (mask){
    if (data & mask){
      sda_setval(1);
    } else {
      sda_setval(0);
    }
    i2c_clock();
    mask >>= 1;
  }
  sda_setval(1);
  return i2c_clock();
}
