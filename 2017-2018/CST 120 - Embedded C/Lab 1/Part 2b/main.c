/*
 * Lab1p2b.c
 *
 * Created: 4/5/2018 11:50:33 AM
 * Author : zachery.rowland
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = (0b11 << DDB4);

	while (1)
	{
		PORTB = (0b11 << DDB4);
		_delay_ms(500);
		PORTB = (0b10 << DDB4);
		_delay_ms(500);
		PORTB = (0b01 << DDB4);
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
	}
}

