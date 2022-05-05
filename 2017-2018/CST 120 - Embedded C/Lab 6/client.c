/****************************************************************************************************
* Author: Zak Rowland
* Filename: client.c
* Date Created: 5/10/2018
* Modifications:
*****************************************************************************************************
* Assignment: Lab 6
*
* Overview: Interboard communication: Control LED on client board with data from server board
*
* Input: Data from server
*
* Output: LED control
*
*****************************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>
#include "uartDriver.h"

#define FALSE 0
#define TRUE !FALSE
#define COMM_MASK (1 << DDB5)
#define BLUE_RGB (1 << DDB0)
#define GREEN_RGB (1 << DDB1)
#define RED_RGB (1 << DDB2)

void receiveData(void);

static volatile uint8_t data = 0;
static volatile uint8_t complete = 0;

/*****************************************************************************************************
* Function: main
* Purpose: Controls data reception from server board and changes LED
* Preconditon: No data
* Postcondition: Received data controls LED
*****************************************************************************************************/
int main(void)
{
    uint8_t processing = 0; //Receive ACTIVE
	FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
	FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
	uart_init();
	stdout = &uart_output;
	stdin = &uart_input;
	DDRB = 0; //All pins INPUT
	DDRB |= BLUE_RGB | GREEN_RGB | RED_RGB;
	PORTB &= ~(RED_RGB | BLUE_RGB | GREEN_RGB);

	while(TRUE)
	{
		if((PINB & COMM_MASK) && (processing == 0))
		{
			processing = 1;
			data = 0;
			TCCR0B |= ((1 << CS02) | (1 << CS00));
			TIMSK0 |= (1 << TOIE0);
			TCNT0 = 0;
			_delay_ms(10);
			sei();
		}
		if(complete == 1)
		{
			complete = 0;
			processing = 0;
			printf("%u\n", data);
			//Change LED
			switch(data)
			{
				case 0: //all off
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					break;
				}
				case 1: //BLUE
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~BLUE_RGB;
					break;
				}
				case 2: //GREEN
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~GREEN_RGB;
					break;
				}
				case 3: //BLUE GREEN
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~(BLUE_RGB | GREEN_RGB);
					break;
				}
				case 4: //RED
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~(RED_RGB);
					break;
				}
				case 5: //RED BLUE
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~(RED_RGB | BLUE_RGB);
					break;
				}
				case 6: //RED GREEN
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~(RED_RGB | GREEN_RGB);
					break;
				}
				case 7: //RED BLUE GREEN
				{
					PORTB |= BLUE_RGB | RED_RGB | GREEN_RGB;
					PORTB &= ~(RED_RGB | BLUE_RGB | GREEN_RGB);
					break;
				}
			}
				data = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	static uint8_t numOverflows = 0;
	numOverflows++;

	if(numOverflows > 10)
	{
		receiveData();
		numOverflows = 0;
	}
}

/*****************************************************************************************************
* Function: receiveData(void)
* Purpose: Receives data from server
* Preconditon: No data
* Postcondition: Data from server
*****************************************************************************************************/
void receiveData(void)
{
	static uint8_t BitCount = 0;
	if(BitCount > 7)
	{
		//Disable Timer 0
		TCCR0B = 0;
		TIMSK0 = 0;
		TCNT0 = 0;
		BitCount = 0;
		complete = 1;
		cli();
	}
	else
	{
		data <<= 1;

		if(PINB & COMM_MASK)
		{
			data |= 0x01;
		}
		BitCount++;
	}
}

