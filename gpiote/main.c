#include <stdint.h>
#include <stdio.h>
#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"

int main (){
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	GPIOTE->CONFIG[0]= (1 | (17 << 8) | (2 << 16));
	GPIOTE->CONFIG[1]= (3 | (13 << 8) | (3 << 16) );
	GPIOTE->CONFIG[2]= (3 | (14 << 8) | (3 << 16) );
	GPIOTE->CONFIG[3]= (3 | (15 << 8) | (3 << 16) );
	
	
	//setter PPI-kanaler
	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);
	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);
	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);
	PPI->CHEN = (1 | 1<<1 | 1 << 2);
	while(1);
}