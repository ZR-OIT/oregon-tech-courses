/*
 * ssegs_and_leds.c
 *
 *  Created on: May 1, 2020
 *      Author: Zak Rowland
 */

// AND UART

#include "sys/alt_stdio.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_jtag_uart_regs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DELAY 100000 // Time delay between loops

int main()
{
	int delay_count = 0; // Counter for delay, to make changes visible
	//int led_count = 0; // Store count displayed on LEDs
	int led_state = 0; // State of 10 LEDs
	int button_states = 0; // State of buttons
	int toggle_leds = 0; // 1 if LEDs should toggle, 0 if not
	int last_button_states = 0; // Stores the button state from the previous loop

	static int sseg[6] = { SSEG_BASE, SSEG1_BASE, SSEG2_BASE, SSEG3_BASE, SSEG4_BASE, SSEG5_BASE }; // Addresses for each digit on the SSEG

	unsigned int sseg_counts[6] = { 0 }; // Counters for each digit on the SSEG

	FILE * fp = NULL; // Pointer for the jtag_uart

	const char * button_string = "\nThe is button is currently: ";
	const char * count_string = "\nThe current count value is: ";

	char int_to_str[8] = { 0 }; // Space for integer to string conversion

	//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_count);
	IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, 0); // Turn LEDs off

	IOWR_ALTERA_AVALON_PIO_DATA(sseg[0], 0); // Turn all SSEGs off
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[1], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[2], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[3], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[4], 0);
	IOWR_ALTERA_AVALON_PIO_DATA(sseg[5], 0);

	while (1)
	{
		fp = fopen("/dev/jtag_uart", "w"); //Open jtag uart for writing
		delay_count = 0; // Reset delay counter
		//IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_count); // Write count value to LEDs
		IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, led_state); // Write state to LEDs
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[0], sseg_counts[0]); // Write counters to their sseg displays
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[1], sseg_counts[1]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[2], sseg_counts[2]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[3], sseg_counts[3]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[4], sseg_counts[4]);
		IOWR_ALTERA_AVALON_PIO_DATA(sseg[5], sseg_counts[5]);

		while(delay_count < DELAY) delay_count++; // Delay

		last_button_states = button_states; // Store last button state
		button_states = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE); // Read current button state
		if(fp) // Write button state to jtag uart
		{
			fwrite(button_string, strlen(button_string), 1, fp);
			if(button_states != 3) fwrite("pressed", strlen("pressed"), 1, fp);
			else fwrite("not pressed", strlen("not pressed"), 1, fp);

		}

		if(button_states != last_button_states && button_states != 3) toggle_leds = 1; // If button is pressed
		else toggle_leds = 0;

		if(toggle_leds == 1)
		{
			if(led_state == 0b1111111111) led_state = 0b0000000000; // Invert LEDs
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

		if(fp) // Convert counter digits to strings and write to jtag uart
		{
			fwrite(count_string, strlen(button_string), 1, fp);
			itoa(sseg_counts[2], int_to_str, 10);
			fwrite(int_to_str, strlen(int_to_str), 1, fp);
			itoa(sseg_counts[1], int_to_str, 10);
			fwrite(int_to_str, strlen(int_to_str), 1, fp);
			itoa(sseg_counts[0], int_to_str, 10);
			fwrite(int_to_str, strlen(int_to_str), 1, fp);
		}

		fclose (fp); // Close jtag uart
	}
	return 0;
}
