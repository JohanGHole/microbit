#include <stdint.h>
#include "uart.h"
#include "gpio.h"


int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;

	//masker
	int a_button = 131072;
	int b_button = 67108864;
	int sleep = 0;
	while(1){
		if ((GPIO->IN & b_button) != b_button) {
			for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
		}
		if ((GPIO->IN & a_button) != a_button) {
			for(int i = 13; i <= 15; i++){
				GPIO->OUTCLR = (1 << i);
			}
		}

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
