/*
 * Lab 2.c
 *
 * Created: 4/12/2018 11:25:22 AM
 * Author : zachery.rowland
 */ 
#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>

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
	unsigned char pattern[] = {0x21, 0x12, 0x0c, 0x12, 0x21};
	int index = 0;

	DDRD = (0b111111 << DDB2);

	while (1)
	{
		//leds.portd = (0b111111 << DDB2);
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led0 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led1 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led2 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led3 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led4 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);
		//leds.bits.led5 = 0;
		//PORTD = leds.portd;
		//_delay_ms(500);

		configure_leds(&leds, pattern[index]);
		set_leds(&leds);
		_delay_ms(500);

		index++;
		if (index >= sizeof(pattern)/sizeof(pattern[0]))
		{
			index = 0;
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
