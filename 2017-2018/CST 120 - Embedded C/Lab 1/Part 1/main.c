/*
 * Lab1p1.c
 *
 * Created: 4/5/2018 11:14:09 AM
 * Author : zachery.rowland
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRB = (1 << DDB5);

    while (1) 
    {
		PORTB = (1 << DDB5);
		_delay_ms(500);
		PORTB = 0;
		_delay_ms(500);
    }
}

