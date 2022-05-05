/*
 * ssegs_and_leds.c
 *
 *  Created on: May 1, 2020
 *      Author: Zak Rowland
 */

#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"

#define DELAY 100000
//#define DEBOUNCE_DELAY 20000

int main()
{
	int delay_count = 0; // Counter for delay, to make changes visible
	//int led_count = 0; // Store count displayed on LEDs
	int led_state = 0;
	//int debounce_count = 0; // Counter for button debounce delay
	int button_states = 0;
	int toggle_leds = 0;
	int last_button_states = 0;

	static int sseg[6] = { SSEG_BASE, SSEG1_BASE, SSEG2_BASE, SSEG3_BASE, SSEG4_BASE, SSEG5_BASE };

	unsigned int sseg_counts[6] = { 0 };

	//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_count);
	IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, 0);

	IOWR_ALTERA_AVALON_PIO_DATA(sseg[0], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[1], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[2], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[3], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[4], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[5], 0);

	while (1)
	{
		delay_count = 0;
		//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_count);
		IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_state);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[0], sseg_counts[0]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[1], sseg_counts[1]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[2], sseg_counts[2]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[3], sseg_counts[3]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[4], sseg_counts[4]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[5], sseg_counts[5]);

		while(delay_count < DELAY) delay_count++; // Delay

		last_button_states = button_states;
		button_states = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);

		if(button_states != last_button_states && button_states != 3) toggle_leds = 1;
		else toggle_leds = 0;

		if(toggle_leds == 1)
		{
			if(led_state == 0b1111111111) led_state = 0b0000000000;
			else led_state = 0b1111111111;
		}

		//if(led_count == 1023) led_count = 0;
		//else led_count++;

		if(sseg_counts[2] == 2){ // If at 2xx, only count to 255

			if(sseg_counts[1] == 5)
			{
				if(sseg_counts[0] == 5)
				{
					sseg_counts[2] = 0;
					sseg_counts[1] = 0;
					sseg_counts[0] = 0;
				}
				else sseg_counts[0]++;
			}
			else
			{
				if(sseg_counts[0] == 9)
				{
					sseg_counts[1]++;
					sseg_counts[0] = 0;
				}
				else sseg_counts[0]++;
			}

		}
		else if(sseg_counts[0] == 9){
			if(sseg_counts[1] == 9){
				if(sseg_counts[2] == 2){
					sseg_counts[2] = 0;
					sseg_counts[1] = 0;
					sseg_counts[0] = 0;
				}
				else sseg_counts[2]++;
				sseg_counts[1] = 0;
			}
			else sseg_counts[1]++;
			sseg_counts[0] = 0;
		}
		else sseg_counts[0]++;

		if(sseg_counts[2] > 1)
		{
			sseg_counts[3] = 16;
			sseg_counts[4] = 16;
			sseg_counts[5] = 16;
		}
		else if(sseg_counts[1] > 4)
		{
			sseg_counts[3] = 15;
			sseg_counts[4] = 14;
			sseg_counts[5] = 13;
		}
		else
		{
			sseg_counts[3] = 12;
			sseg_counts[4] = 11;
			sseg_counts[5] = 10;
		}

	}
	return 0;
}
