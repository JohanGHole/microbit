#include "twi.h"
#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	uint8_t * data_buffer;
	data_buffer = (uint8_t *)malloc(8 * sizeof(uint8_t));
	twi_init();
	twi_multi_read(0x1D, 0x0D, 1, data_buffer);

	if (data_buffer[0] == 0x5A){
		for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
	}
	free(data_buffer);
}