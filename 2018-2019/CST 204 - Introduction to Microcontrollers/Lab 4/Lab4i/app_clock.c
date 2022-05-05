#include <xc.h>
#include <stdio.h>
#include <string.h>

#define LCD_COMMAND		0
#define LCD_DATA		1
#define LCD_CMD_CLEAR	0x01
#define LCD_CMD_DATA	0x80
#define LCD_CLK_HOUR	7		//LCD position of most significant Hours digit
#define LCD_CLK_MIN		10		//LCD position of most significant Minutes digit
#define LCD_CLK_SEC		13		//LCD position of most significant Seconds digit

extern int clock_second;
extern int clock_minute;
extern int clock_hour;
extern int clock_count;
extern int clock_state;

extern void lcd_wait_for_not_busy(void);
extern void lcd_write(int RS_SEL, int CMD_ADDR);
extern void lcd_write_string(char LCD_BUFFER[]);

extern char clock_str[20];

////////////////////////////////////////////////////////////////////////////////
// Place the clock field value into the clock_str buffer
// clockfield: Value of the clock field
// field_type: Which field is being updated (hour, minute or second). If 7 is
//		passed, it is assumed to be the hour field. This field is also used for
//		where in clock_str the converted ints should be placed
////////////////////////////////////////////////////////////////////////////////
void clockfield_to_lcdstr(int clockfield, int field_type) {
	char ones = (clockfield % 10) + 0x30; // Ones field
	char tens = (clockfield / 10) + 0x30; // Tens field

	if (field_type == 7 && tens == '0') {
		tens = ' ';
	}

	clock_str[field_type] = tens;
	clock_str[field_type + 1] = ones;
}

////////////////////////////////////////////////////////////////////////////////
// Initalize the app_clock
////////////////////////////////////////////////////////////////////////////////
void lcd_time_init(void) {
	lcd_wait_for_not_busy();
	lcd_write(LCD_COMMAND, LCD_CMD_DATA | 0x00);	// Write to first line

	clockfield_to_lcdstr(clock_second, LCD_CLK_SEC);	
	clockfield_to_lcdstr(clock_minute, LCD_CLK_MIN);	
	clockfield_to_lcdstr(clock_hour, LCD_CLK_HOUR);	

	lcd_write_string(clock_str);
}

void app_clock(void) {

	if (clock_count < 100) {
		++clock_count;
	} else {
		clock_count = 0;
	}

	// Only 1 state transition for each cycle
	switch (clock_state) {
		case 0:
			if (clock_count == 100) {
				if (clock_second < 59) {
					++clock_second;				
					clock_state = 1;
				} else if (clock_second >= 59 && clock_minute < 59) {
					clock_second = 0;
					++clock_minute;
					clock_state = 2;
				} else if (clock_second >= 59 && clock_minute >= 59
						&& clock_hour < 12 || clock_hour >= 12) {

					clock_second = 0;
					clock_minute = 0;
					
					// If 12 hours have passed, instead reset the hour counter
					if (clock_hour >= 12) {
						clock_hour = 1;
					} else {
						++clock_hour;
					}

					clock_state = 3;
				}
			}
			break;

		case 1: // Update seconds field and return to state 0
			clockfield_to_lcdstr(clock_second, LCD_CLK_SEC);	

			// Move cursor to seconds field
			lcd_wait_for_not_busy();
			lcd_write(LCD_COMMAND, LCD_CMD_DATA | LCD_CLK_SEC);
			
			// Write the characters for the seconds field, cursor is advaned
			// with each write call
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_SEC]);
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_SEC + 1]);

			clock_state = 0; // Return to counting state
			break;

		case 2: // Update minute field and go to state 1
			clockfield_to_lcdstr(clock_minute, LCD_CLK_MIN);	

			// Move cursor to minutes field
			lcd_wait_for_not_busy();
			lcd_write(LCD_COMMAND, LCD_CMD_DATA | LCD_CLK_MIN);
			
			// Write the characters for the seconds field, cursor is advaned
			// with each write call
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_MIN]);
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_MIN + 1]);

			clock_state = 1; // Return to counting state
			break;

		case 3: // Update hour field and return to state 2
			clockfield_to_lcdstr(clock_hour, LCD_CLK_HOUR);	

			// Move cursor to hour field
			lcd_wait_for_not_busy();
			lcd_write(LCD_COMMAND, LCD_CMD_DATA | LCD_CLK_HOUR);
			
			// Write the characters for the seconds field, cursor is advaned
			// with each write call
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_HOUR]);
			lcd_wait_for_not_busy();
			lcd_write(LCD_DATA, clock_str[LCD_CLK_HOUR + 1]);

			clock_state = 2; // Return to counting state
			break;
	}

}