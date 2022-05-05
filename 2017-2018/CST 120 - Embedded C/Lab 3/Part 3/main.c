/*
 * Lab3p3.c
 *
 * Created: 4/19/2018 1:37:38 PM
 * Author : zachery.rowland
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define BUTTON_MASK1 0x10
#define BUTTON_MASK2 0x08

static volatile uint16_t NumOverflows = 0;

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

static volatile uint8_t button1_down;
static volatile uint8_t button2_down;

static inline void debounce(void);

ISR(TIMER0_OVF_vect) //LED timer
{
	NumOverflows++;
}

ISR(TIMER1_COMPA_vect) //debounce timer
{
	debounce();
	TCNT1 = 0;
}

int main(void)
{
	union leds_t leds;
	unsigned char pattern[] = {0x01, 0x02, 0x4, 0x8, 0x10, 0x20};
	//uint8_t index = 6;
	uint8_t current1 = 0;
	int current2 = 5;
	int current3 = 0;
	int direction = 0;


	TCCR0B |= (1 << CS00); //timer 0 prescaler
	TCNT0 = 0; //timer 0 counter
	TIMSK0 |= (1 << TOIE0); //enable timer 0 overflow interrupt
	DDRD = (0b111111 << DDB2); //set ports to output

	TCNT1 = 0;
	PORTB |= BUTTON_MASK1 | BUTTON_MASK2; //activate pull-up resistors
	TCCR1B |= (1 << CS11) | (1 << CS10); //64 prescaler timer 1 
	OCR1A = 250; //output compare register A
	TIMSK1 |= (1 << OCIE1A); //interrupt for compare output

	sei(); //enable global interrupts
	while (1)
	{
		if(button1_down == 1 && button2_down == 0)
		{
			while((PINB & BUTTON_MASK1) == 0 && (PINB & BUTTON_MASK2) != 0)
			{
				if(NumOverflows >= 12500) //LEDS on
				{
					TCNT0 = 0;
					NumOverflows = 0;
					configure_leds(&leds, pattern[current1]);
					set_leds(&leds);
					current1++;
					if(current1 > 5)
					{
						current1 = 0;
					}
				}
			}
		}
		else if(button2_down == 1 && button1_down == 0)
		{
			while((PINB & BUTTON_MASK2) == 0 && (PINB & BUTTON_MASK1) != 0)
			{
				if(NumOverflows >= 12500) //LEDS on
				{
					TCNT0 = 0;
					NumOverflows = 0;
					configure_leds(&leds, pattern[current2]);
					set_leds(&leds);
					current2--;
					if(current2 < 0)
					{
						current2 = 5;
					}
				}
			}
		}
		else if((button2_down == 1) && (button1_down == 1))
		{

			while(((PINB & BUTTON_MASK1) == 0) && ((PINB & BUTTON_MASK2) == 0))
			{
				if(NumOverflows >= 12500) //LEDS on
				{
					TCNT0 = 0;
					NumOverflows = 0;

					if(direction == 0)
					{
						configure_leds(&leds, pattern[current3]);
						set_leds(&leds);
						current3++;
						if(current3 == 5)
						{
							direction = 1;
						}
					}
					else
					{
						configure_leds(&leds, pattern[current3]);
						set_leds(&leds);
						current3--;
						if(current3 == 0)
						{
							direction = 0;
						}
					}
				}
			}
		}
		else //LEDS off
		{
			configure_leds(&leds, 0x00);
			set_leds(&leds);
			current1 = 0;
			current2 = 5;
			current3 = 0;
			direction = 0;
		}
	}
}

void configure_leds(union leds_t * setting, uint8_t value)
{
	setting->portd = (value << DDB2);
}

void set_leds(union leds_t *  setting)
{
	PORTD = setting->portd;
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
			else
			{
				button1_down = 0;
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
			else
			{
				button2_down = 0;
			}
		}
	}
	else
	{
		count1 = 0;
		count2 = 0;
	}
}
