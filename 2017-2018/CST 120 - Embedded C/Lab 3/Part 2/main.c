/*
 * Lab3p2.c
 *
 * Created: 4/19/2018 12:29:15 PM
 * Author : zachery.rowland
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_MASK 0x20
#define BUTTON_MASK1 0x10
#define BUTTON_MASK2 0x08

static volatile uint16_t NumOverflows = 0;

ISR(TIMER0_OVF_vect)
{
	NumOverflows++;
}

union leds_t
{
	struct
	{
		uint8_t unused	:2;
		uint8_t led0	:1;
		uint8_t led1	:1;
		uint8_t led2	:1;
		uint8_t led3	:1;
		uint8_t led4	:1;
		uint8_t led5	:1;
	}bits;
	
	uint8_t portd;
};

void configure_leds(union leds_t * setting, uint8_t value);
void set_leds(union leds_t *  setting);

int main(void)
{
	union leds_t leds;
	unsigned char pattern[] = {0x01, 0x02, 0x04, 0x8, 0x10, 0x20};
	int index = 0;

	TCCR0B |= (1 << CS00);
	TCNT0 = 0;
	TIMSK0 |= (1 << TOIE0);
	sei();
	DDRD = (0b111111 << DDB2);
	PORTB |= BUTTON_MASK1 | BUTTON_MASK2;

	while (1)
	{
		if((PINB & BUTTON_MASK2) == 0 || (PINB & BUTTON_MASK1) == 0)
		{
			if(NumOverflows >= 12500)
			{
				TCNT0 = 0;
				NumOverflows = 0;
				configure_leds(&leds, pattern[index]);
				set_leds(&leds);
				index++;
				if (index >= sizeof(pattern)/sizeof(pattern[0]))
				{
					index = 0;
				}
			}
		}
		else
		{
			configure_leds(&leds, 0x00);
			set_leds(&leds);
			index = 0;
		}
	}
	return 0;
}

void configure_leds(union leds_t * setting, uint8_t value)
{
	setting->portd = (value << DDB2);
}

void set_leds(union leds_t *  setting)
{
	PORTD = setting->portd;
}

