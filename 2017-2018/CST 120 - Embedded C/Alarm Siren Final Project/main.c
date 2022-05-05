/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.c
* Date Created: 6/1/2018
* Modifications:
*****************************************************************************************************
* Assignment: Final Project - Police Light and Siren controller
*
* Overview: A police light and siren controller that uses LEDs and a buzzer to mimic a police a car.
*			A button will be used to switch modes (pattern 1, pattern 2, alarm mode, pressure mode, off.)
*			A potentiometer controls siren loudness.
*			A pressure sensitive resister controls alarm mode and pressure mode.
*			Timers, interrupts, and ADC will be used.
*
* Input:	User can use button to change modes, potentiometer to change volume, and pressure sensitive
*			resistor to activate/deactivate alarm.
*
* Output:   Light patterns and alarm sound.
*
*****************************************************************************************************
--- PORT D ---
PORTD0 : Red LED 1
PORTD1 : Red LED 2
PORTD2 : RGB Blue
PORTD3 : RGB Green
PORTD4 : RGB Red
PORTD5 : Red LED 3
PORTD6 : Red LED 4
PORTD7 : Buzzer

--- PORT B ---
PORTB0 : Button

--- ANALOG ---
A1 : Pressure sensitive resistor
*/
#define F_CPU 16000000
#define RED1_MASK (1 << DDD0)
#define RED2_MASK (1 << DDD1)
#define RED3_MASK (1 << DDD5)
#define RED4_MASK (1 << DDD6)
#define RGB_BLUE (1 << DDD2)
#define RGB_GREEN (1 << DDD3)
#define RGB_RED (1 << DDD4)
#define BUTTON_MASK1 0x01
#define BUZZER_MASK 0x02
#define PRESSURE_MASK 0x01

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static volatile uint8_t button1_down; //Button status
static volatile uint8_t mode; //Mode status
const uint8_t PRESSURE_MIN = 0; //Pressure sensor minimum value
const uint8_t PRESSURE_MAX = 255; //Pressure sensor maximum value

uint16_t pattern_one[8] = {15000, 27000, 29000, 35000, 35000, 29000, 27000, 15000};
uint16_t pattern_two[2] = {29000, 17000};

void ModeOne(void);
void ModeTwo(void);
void ModeThree(void);
void ModeFour(void);
void ModeOff(void);
void ClearLED(void);
void PlayTone(uint16_t note, uint8_t beats);
void InitADC();
uint16_t ReadADC(uint8_t ADCchannel);
uint8_t scale(uint8_t reading , uint8_t min_in , uint8_t max_in ,uint8_t min_out , uint8_t max_out );
static inline void debounce(void);

ISR(TIMER1_COMPA_vect) //Toggles buzzer
{
	PORTB ^= BUZZER_MASK;
	TCNT2 = 0;
}

/*****************************************************************************************************
* Function: main(void)
* Purpose: Controls which pattern is played by using a mode variable
* Precondition: System is off
* Postcondition: Different patterns played depending on user input
*****************************************************************************************************/
int main(void)
{
	uint8_t adc_result = 0;

	DDRD |= (RED1_MASK | RED2_MASK | RED3_MASK | RED4_MASK | RGB_GREEN | RGB_BLUE | RGB_RED);
	PORTD |= (RGB_RED | RGB_BLUE | RGB_GREEN);
	DDRB |= BUZZER_MASK;
	PORTB |= BUTTON_MASK1; //Activate pull-up resistor
	
	TCNT1 = 0; //Timer count
	TCCR1B |= (1 << CS10); //1 pre-scaler for timer 1
	OCR1A = 0; //Timer 1 comparator A value
	TIMSK1 |= (1 << OCIE1A); //Enable compare interrupts

	InitADC(); //Setup ADC
	ClearLED();

	mode = 0;
	while (1)
	{
		debounce();
		if (button1_down == 1) //If button is pressed
		{
			ClearLED();
			button1_down = 0;
			if(mode == 4)
			{
				mode = 0;
			}
			else
			{
				++mode; //Change mode
			}
		}

		if(mode == 0) //System off
		{
			debounce();
			ModeOff();
			debounce();
		}
		else if(mode == 1) //System in mode one
		{
			debounce();
			ModeOne();
			debounce();
		}
		else if (mode == 2) //System in mode two
		{
			debounce();
			ModeTwo();
			debounce();
		}
		else if (mode == 3) //System in alarm mode
		{
			debounce();
			ReadADC(PRESSURE_MASK);
			adc_result = scale(ADCH, PRESSURE_MIN, PRESSURE_MAX, 0, 100);
			if(adc_result < 5)
			{
				ModeThree();
			}
			adc_result = 0;
			debounce();
		}
		else if (mode == 4) //System in pressure mode
		{
			debounce();
			ReadADC(PRESSURE_MASK);
			adc_result = scale(ADCH, PRESSURE_MIN, PRESSURE_MAX, 0, 100);
			if(adc_result > 5)
			{
				ModeFour();
			}
			adc_result = 0;
			debounce();
		}
		else //System off
		{
			debounce();
			ModeOff();
			debounce();
		}
		debounce();
	}
}

/*****************************************************************************************************
* Function: ModeOff(void)
* Purpose: Turns the system off
* Precondition: System is either running or off
* Postcondition: System is off
*****************************************************************************************************/
void ModeOff(void)
{
	debounce();
	ClearLED();
	debounce();
}

/*****************************************************************************************************
* Function: ModeOne(void)
* Purpose: Plays the first light and buzzer pattern
* Precondition: System is either running or off
* Postcondition: System runs in first mode
*****************************************************************************************************/
void ModeOne(void)
{
	debounce();
	PORTD |= RED1_MASK;
	PlayTone(pattern_one[0],1);
	_delay_ms(30);
	
	PORTD &= ~RED1_MASK;
	_delay_ms(10);
	
	PORTD |= RED2_MASK;
	PlayTone(pattern_one[1],1);
	_delay_ms(30);
	
	PORTD &= ~RED2_MASK;
	_delay_ms(10);
	
	PORTD &= ~RGB_BLUE;
	PORTD &= ~RGB_GREEN;
	PORTD &= ~RGB_RED;
	PlayTone(pattern_one[2],1);
	_delay_ms(30);
	
	PORTD |= RGB_BLUE;
	PORTD |= RGB_GREEN;
	PORTD |= RGB_RED;
	_delay_ms(10);
	
	PORTD |= RED3_MASK;
	PlayTone(pattern_one[3],1);
	_delay_ms(30);
	
	PORTD &= ~RED3_MASK;
	_delay_ms(10);
	
	PORTD |= RED4_MASK;
	PlayTone(pattern_one[4],1);
	_delay_ms(30);
	
	PORTD &= ~RED4_MASK;
	_delay_ms(10);
	
	PORTD |= RED3_MASK;
	PlayTone(pattern_one[5],1);
	_delay_ms(30);
	
	PORTD &= ~RED3_MASK;
	_delay_ms(10);
	
	PORTD &= ~RGB_BLUE;
	PlayTone(pattern_one[6],1);
	_delay_ms(30);
	
	PORTD |= RGB_BLUE;
	_delay_ms(10);
	
	PORTD |= RED2_MASK;
	PlayTone(pattern_one[7],1);
	_delay_ms(30);
	
	PORTD &= ~RED2_MASK;
	_delay_ms(10);
	debounce();
}

/*****************************************************************************************************
* Function: ModeTwo(void)
* Purpose: Plays the second light and buzzer pattern
* Precondition: System is either running or off
* Postcondition: System runs in second mode
*****************************************************************************************************/
void ModeTwo(void)
{
	debounce();
	PORTD |= RED1_MASK | RED3_MASK;
	PORTD &= ~RGB_BLUE;
	PORTD &= ~RGB_GREEN;
	PORTD &= ~RGB_RED;
	PlayTone(pattern_two[0],8);
	debounce();
	
	PORTD &= RED1_MASK & RED3_MASK;
	PORTD |= RGB_BLUE;
	PORTD |= RGB_GREEN;
	PORTD |= RGB_RED;
	_delay_ms(10);
	
	PORTD |= RED2_MASK | RED4_MASK;
	PORTD &= ~RGB_BLUE;
	PlayTone(pattern_two[0],8);
	debounce();
	
	PORTD &= RED2_MASK & RED4_MASK;
	PORTD |= RGB_BLUE;
	_delay_ms(10);
	
	PORTD |= RED1_MASK | RED3_MASK;
	PORTD &= ~RGB_BLUE;
	PORTD &= ~RGB_GREEN;
	PORTD &= ~RGB_RED;
	PlayTone(pattern_two[1],8);
	debounce();
	
	PORTD &= RED1_MASK & RED3_MASK;
	PORTD |= RGB_BLUE;
	PORTD |= RGB_GREEN;
	PORTD |= RGB_RED;
	_delay_ms(10);
	
	PORTD |= RED2_MASK | RED4_MASK;
	PORTD &= ~RGB_BLUE;
	PlayTone(pattern_two[1],8);
	debounce();
	
	PORTD &= RED2_MASK & RED4_MASK;
	PORTD |= RGB_BLUE;
	_delay_ms(10);
	debounce();
}

/*****************************************************************************************************
* Function: ModeThree(void)
* Purpose: Plays the third light and buzzer pattern (caused by pressure removal)
* Precondition: System is either running or off
* Postcondition: System runs in alarm mode
*****************************************************************************************************/
void ModeThree(void)
{
	debounce();
	PORTD &= ~RGB_GREEN;
	PORTD &= ~RGB_RED;
	PlayTone(pattern_one[0],4);
	
	PORTD |= RGB_GREEN;
	PORTD |= RGB_RED;
	_delay_ms(10);
	
	PORTD |= RED2_MASK;
	PORTD |= RED3_MASK;
	PlayTone(pattern_one[1],4);
	
	PORTD &= ~RED2_MASK;
	PORTD &= ~RED3_MASK;
	_delay_ms(10);
	
	PORTD |= RED1_MASK;
	PORTD |= RED4_MASK;
	PlayTone(pattern_one[2],4);
	
	PORTD &= ~RED1_MASK;
	PORTD &= ~RED4_MASK;
	_delay_ms(10);
	debounce();
}

/*****************************************************************************************************
* Function: ModeFour(void)
* Purpose: Plays the fourth light and buzzer pattern (caused by applying pressure)
* Precondition: System is either running or off
* Postcondition: System runs in pressure mode
*****************************************************************************************************/
void ModeFour(void)
{
	debounce();
	PORTD &= ~RGB_GREEN;
	PORTD &= ~RGB_RED;
	PORTD &= ~RGB_BLUE;
	PlayTone(pattern_one[0],4);
	
	PORTD |= RGB_GREEN;
	PORTD |= RGB_RED;
	PORTD |= RGB_BLUE;
	_delay_ms(10);
	
	PORTD |= RED2_MASK;
	PORTD |= RED3_MASK;
	PlayTone(pattern_one[1],4);
	
	PORTD &= ~RED2_MASK;
	PORTD &= ~RED3_MASK;
	_delay_ms(10);
	
	PORTD |= RED1_MASK;
	PORTD |= RED4_MASK;
	PlayTone(pattern_one[2],4);
	
	PORTD &= ~RED1_MASK;
	PORTD &= ~RED4_MASK;
	_delay_ms(10);
	debounce();
}
/*****************************************************************************************************
* Function: ClearLED(void)
* Purpose: Turns off all LEDs
* Precondition: System is either running or off
* Postcondition: All LEDs off
*****************************************************************************************************/
void ClearLED(void)
{
	PORTD &= (~RED1_MASK & ~RED2_MASK & ~RED3_MASK & ~RED4_MASK);
	PORTD |= (RGB_BLUE | RGB_GREEN | RGB_RED);
}

/*****************************************************************************************************
* Function: PlayTone(uint16_t note, uint8_t beats)
* Purpose: Plays a passed note for the passed amount of beats
* Precondition: No noise
* Postcondition: Buzzer emits passed note
*****************************************************************************************************/
void PlayTone(uint16_t note, uint8_t beats)
{
	debounce();
	OCR2A = note;
	for(int b = 0; b < beats; b++)
	{
		sei();
		_delay_ms(25);
	}
	cli();
	debounce();
}

/*****************************************************************************************************
* Function: InitADC()
* Purpose: Initializes analog to digital conversion
* Preconditon: ADC disabled
* Postcondition: ADC enabled and configured
*****************************************************************************************************/
void InitADC()
{
	ADMUX |= (1 << REFS0); //Sets ADMUX analog reference to use AVcc
	ADCSRA |= (1 << ADEN); //Enables ADC in ADCSRA register
	ADMUX |= (1 << ADLAR); //Sets ADMUX to left adjust result
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); //Sets ADC prescaler to 128
	ADCSRA |= (1 << ADATE);
	ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));
	ADMUX &= 0xF0;
	ADCSRA |= (1 << ADSC); //Enables ADC start conversion
}

/*****************************************************************************************************
* Function: ReadADC(uint8_t ADCchannel)
* Purpose: Reads the data in the ADC
* Preconditon: No data
* Postcondition: Data read from potentiometer or pressure sensor
*****************************************************************************************************/
uint16_t ReadADC(uint8_t ADCchannel)
{
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F); //Selects channel to read data from (POT or SENSOR)
	
	while((ADCSRA & (1 << ADIF)) == 0);
	{
		ADCSRA |= (1 << ADIF); //Resets conversion interrupt flag
	}
	return ADC;
}

/*****************************************************************************************************
* Function: scale(uint8_t reading , uint8_t min_in , uint8_t max_in ,uint8_t min_out , uint8_t max_out )
* Purpose: Adjusts the read value from the ADC to match the range limits of the servo
* Preconditon: Reading may be too large or too small for the servo
* Postcondition: An adjusted value that scales the reading to the range of the servo
*****************************************************************************************************/
uint8_t scale(uint8_t reading , uint8_t min_in , uint8_t max_in ,uint8_t min_out , uint8_t max_out )
{
	uint16_t product = (reading - min_in) * (max_out - min_out);
	uint16_t scaledValue = 0;
	uint8_t adjustedValue = 0;
	
	scaledValue = ((product / (max_in - min_in)) + min_out);
	if(scaledValue < min_out)
	{
		adjustedValue = min_out;
	}
	else if(scaledValue > max_out)
	{
		adjustedValue = max_out;
	}
	else
	{
		adjustedValue = (uint8_t) scaledValue;
	}
	return adjustedValue;
}

/*****************************************************************************************************
* Function: debounce(void)
* Purpose: Eliminates switch bounce
* Preconditon: Switch bounce causes extra input
* Postcondition: Switch bounce removed
*****************************************************************************************************/
static inline void debounce(void)
{
	static uint8_t count1 = 0;
	static uint8_t button1_state = 0;
	uint8_t current_state1 = (~PINB & BUTTON_MASK1)!=0;

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
	else
	{
		count1 = 0;
	}
}

