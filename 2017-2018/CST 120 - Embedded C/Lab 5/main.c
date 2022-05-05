/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.c
* Date Created: 5/3/2018
* Modifications:
*****************************************************************************************************
* Assignment: Lab 5
*
* Overview: In this lab, you will use an analog input channel to control a servo. You will re-use
*			 some of the timer, button, and servo code from previous weeks.
*
* Input: Data from potentiometer or pressure sensor
*
* Output: Data to (4) LEDs and a servo motor
*
*****************************************************************************************************/
// This is the layout of the port connections
// LED 0 = PB0
// LED 1 = PB1
// LED 2 = PB2
// LED 3 = PB3
// SERVO = PB4
// BUTTON = PB5
// POTENTIOMETER = A0 -> PC0
// PRESSURE = A1 -> PC1

#define F_CPU 16000000
#define BUTTON_MASK 0x20

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

const uint8_t POT_MIN = 0; //Potentiometer minimum value
const uint8_t POT_MAX = 255; //Potentiometer maximum value
const uint8_t SRV_MIN = 32; //Servo minimum value
const uint8_t SRV_MAX = 152; //Servo maximum value
const uint8_t POT_CHANNEL = 0xF0; //Mask for ADMUX to read potentiometer data
const uint8_t SNSR_CHANNEL = 0x01; //Mask for ADMUX to read pressure sensor data
static volatile uint8_t button_down; //Button status

void InitTimers();
void InitADC();
uint16_t ReadADC(uint8_t ADCchannel);
uint8_t scale(uint8_t reading , uint8_t min_in , uint8_t max_in ,uint8_t min_out , uint8_t max_out );
uint8_t filter(uint16_t reading, uint8_t *last_value);
static inline void debounce(void);

/*****************************************************************************************************
* Function: main()
* Purpose: Initializes timers and ADC, then controls a servo and LEDs based on analog input data
* Preconditon: No data
* Postcondition: Servo and LEDs adjusted
*****************************************************************************************************/
int main(void)
{
	static volatile int channel_state = 0; //Keeps track of current ADC channel -> 0 = POT, 1 = SENSOR
	uint8_t filtered_value = 0;

	DDRB = (0b00011111); //Sets button as input, and the servo and LEDs as output
	PORTB |= BUTTON_MASK; //Activate pull-up resistor for button
	
	InitTimers(); //Setup timers
	InitADC(); //Setup ADC
	
    while (1) 
    {
		if(button_down == 1) //If button is pressed
		{
			button_down = 0;
			if(channel_state == 0) //If current channel is POT
			{
				channel_state = 1; //Switch to SENSOR
			}	
			else //If current channel is SENSOR
			{
				channel_state = 0; //Switch to POT
			}
		}
		
		PORTB &= 0xF0; //Clears LEDs
		
		if(channel_state == 0)
		{
			ReadADC(POT_CHANNEL);	
		}
		else
		{
			ReadADC(SNSR_CHANNEL);	
		}

		filtered_value = filter(ADCH, &filtered_value); //Filters the ADC value to smooth it out
		PORTB |= (filtered_value >> 4) & 0x0F; //ORs the filtered shifted value with the LED bits
		OCR0A = scale(filtered_value, POT_MIN, POT_MAX, SRV_MIN, SRV_MAX); //Changes pulse width of servo according to filtered value
    }
	return 0;
}

/*****************************************************************************************************
* Function: InitTimers()
* Purpose: Initializes timers and interrupts
* Preconditon: No timers or interrupts
* Postcondition: Timers configured properly and interrupts enabled
*****************************************************************************************************/
void InitTimers()
{
	TCNT0 = 0; //Timer counts
	TCNT1 = 0;
	TCNT2 = 0;
		
	TCCR0B |= (1 << CS02); //256 prescaler for timer 0
	TCCR1B |= (1 << CS11) | (1 << CS10); //64 prescaler for timer 1
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); //1024 prescaler for timer 2
		
	TCCR0A = 0; //Timer 0 register counter -> normal mode
		
	OCR0A = 95; //Timer 0 comparator A value between 32 and 152
	OCR1A = 250; //Timer 1 comparator A value
	OCR2A = 250; //Timer 2 comparator A value 
		
	TIMSK0 |= (1 << OCIE0A); //Enable compare interrupts
	TIMSK1 |= (1 << OCIE1A);
	TIMSK2 |= (1 << OCIE2A);
		
	sei(); //Enable interrupts
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
	ADMUX &= POT_CHANNEL;
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
* Function: filter(uint16_t reading, uint8_t *last_value)
* Purpose: Smooths the data received from the ADC by comparing it to the previous value read
* Preconditon: Unstable data
* Postcondition: Smooth, consistent data
*****************************************************************************************************/
uint8_t filter(uint16_t reading, uint8_t *last_value)
{
	uint16_t temp = *last_value;
	temp = reading + temp * 31;
	temp = temp >> 5;
	*last_value = (uint8_t) temp;
	return (uint8_t)temp;
}

/*****************************************************************************************************
* Function: debounce(void)
* Purpose: Counteracts switch bounce
* Preconditon: Unstable data
* Postcondition: Smooth, consistent
*****************************************************************************************************/
static inline void debounce(void)
{
	static uint8_t count = 0;
	static uint8_t button_state = 0;
	uint8_t current_state = (~PINB & BUTTON_MASK)!=0;

	if(current_state != button_state)
	{
		count++;
		if (count >= 4)
		{
			button_state = current_state;
			if (current_state != 0)
			{
				button_down = 1;
			}
		}
	}
	else
	{
		count = 0;
	}
}

// Enables servo and clears timer counts
ISR(TIMER2_COMPA_vect)
{
	PORTB |= (1 << DDB4);
	TCNT2 = 0;
	TCNT0 = 0;
}
// Calls debounce() and clears timer count
ISR(TIMER1_COMPA_vect)
{
	debounce();
	TCNT1 = 0;
}
// Disables servo and clears timer count
ISR(TIMER0_COMPA_vect)
{
	PORTB &= ~(1 << DDB4);
	TCNT0 = 0;
}