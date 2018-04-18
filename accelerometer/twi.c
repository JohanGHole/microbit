#include "twi.h"
#include "gpio.h"

void twi_init() {
	GPIO->PIN_CNF[0] = 0x0000060C;
	GPIO->PIN_CNF[30] = 0x0000060C;
	TWI0->PSELSCL = 0;
	TWI0->PSELSDA = 30;
	TWI0->FREQUENCY = 0x01980000;
	TWI0->ENABLE = 5;
}

void twi_multi_read(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_read,
	uint8_t * data_buffer
){
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	while(!TWI0->TXDSENT);
	TWI0->RXDREADY = 0;
	TWI0->STARTRX = 1;
	for (int reg = 0; reg < registers_to_read - 1; reg++){
		while(!TWI0->RXDREADY);
		uint8_t read = TWI0->RXD;
		data_buffer[reg] = read;
		TWI0->RXDREADY = 0;
	}
	TWI0->STOP = 1;
	while(!TWI0->RXDREADY);
	uint8_t read = TWI0->RXD;
	data_buffer[registers_to_read-1] = read;

}

void twi_multi_write(
	uint8_t slave_address,
	uint8_t start_register,
	int registers_to_write,
	uint8_t * data_buffer
){
	TWI0->ADDRESS = slave_address;
	TWI0->STARTTX = 1;
	TWI0->TXDSENT = 0;
	TWI0->TXD = start_register;
	while(!TWI0->TXDSENT);
	for (int reg = 0; reg < registers_to_write; reg++) {
		TWI0->TXDSENT = 0;
		TWI0->TXD = data_buffer[reg];
		while(!TWI0->TXDSENT);
	}
	TWI0->STOP = 1;
}