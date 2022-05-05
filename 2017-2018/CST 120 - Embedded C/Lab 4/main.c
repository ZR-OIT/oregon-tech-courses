/*
 * Lab 4.c
 *
 * Created: 4/26/2018 11:00:42 AM
 * Author : zachery.rowland
 */ 
#define BUTTON_MASK1 0x10
#define BUTTON_MASK2 0x08

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint8_t button1_down;
static volatile uint8_t button2_down;

static inline void debounce(void);

ISR(TIMER2_COMPA_vect)
{
	//set the control line and clear timer 0 & 2 count
	PORTB |= (1 << DDB5);
	TCNT2 = 0;
	TCNT0 = 0;
}
ISR(TIMER0_COMPA_vect)
{
	//clear control line
	PORTB &= ~(1 << DDB5);
	TCNT0 = 0;
}
ISR(TIMER1_COMPA_vect)
{
	//call debounce() and clear timer count
	debounce();
	TCNT1 = 0;
}

int main(void)
{
    DDRB |= (1 << DDB5);
	PORTB |= BUTTON_MASK1 | BUTTON_MASK2; //activate pull-up resistors

	TCNT0 = 0; //counts
	TCNT1 = 0;
	TCNT2 = 0;
	
	TCCR0B |= (1 << CS02); //256 prescaler timer 0
	TCCR1B |= (1 << CS11) | (1 << CS10); //64 prescaler timer 1 
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); //1024 prescaler timer 2

	TCCR0A = 0; //Timer 0 register counter normal mode

	OCR0A = 95; //Timer 0 comparator A value between 32 and 156
	OCR1A = 250;
	OCR2A = 250; //Timer 2 comparator A value

	TIMSK0 |= (1 << OCIE0A); //enable COMPARE interrupts
	TIMSK1 |= (1 << OCIE1A);
	TIMSK2 |= (1 << OCIE2A);

	sei();

    while (1) 
    {
		if (button2_down == 1)
		{
			button2_down = 0;
			if(OCR0A - 20 < 32)
			{
				OCR0A = 32;
			}
			else
			{
				OCR0A = OCR0A - 20;
			}
		}
		else if (button1_down == 1)
		{
			button1_down = 0;
			if(OCR0A + 10 > 152)
			{
				OCR0A = 152;
			}
			else
			{
				OCR0A = OCR0A + 10;
			}
		}
	}
}

static inline void debounce(void)
{
	static uint8_t count1 = 0;
	static uint8_t count2 = 0;
	static uint8_t button1_state = 0;
	static uint8_t button2_state = 0;
	uint8_t current_state1 = (~PINB & BUTTON_MASK1)!=0;
	uint8_t current_state2 = (~PINB & BUTTON_MASK2)!=0;

	if(current_state1 != button1_state)
	{
		count1++;
		if (count1 >= 4)
		{
			button1_state = current_state1;
			if (current_state1 != 0)
			{
				button1_down = 1;
			}
		}
	}
	else if(current_state2 !=  button2_state)
	{
		count2++;
		if (count2 >= 4)
		{
			button2_state = current_state2;
			if (current_state2 != 0)
			{
				button2_down = 1;
			}
		}
	}
	else
	{
		count1 = 0;
		count2 = 0;
	}
}