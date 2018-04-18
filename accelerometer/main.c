#include "twi.h"
#include "uart.h"
#include "gpio.h"
#include "accel.h"
#include "utility.h"
#include "ubit_led_matrix.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	uart_init();
	twi_init();
	accel_init();
	ubit_led_matrix_init();
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	int * data_buffer = (int *)malloc(3 * sizeof(int));
    int x_acc, y_acc;
	int sleep;
	while(1){
		accel_read_x_y_z(data_buffer);
		x_acc = data_buffer[0];
		y_acc = data_buffer[1];
		int x_dot = x_acc / 50;
		int y_dot = -y_acc / 50;
		ubit_led_matrix_light_only_at(x_dot,y_dot);
		sleep = 0;
		while(sleep < 20000){
			sleep++;
		}

	}
	//twi_multi_read(0x1D, 0x0D, 8, data_buffer);

	/*if (data_buffer[0] == 0x5A){
		uart_send('A');
		for(int i = 13; i <= 15; i++){
				GPIO->OUTSET = (1 << i);
			}
	}
	*/
	free(data_buffer);
}