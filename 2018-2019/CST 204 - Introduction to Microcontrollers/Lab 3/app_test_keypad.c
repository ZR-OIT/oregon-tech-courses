#include <xc.h>
#include <stdio.h>
#include <string.h>

#define LCD_COMMAND		0
#define LCD_DATA		1
#define LCD_CMD_CLEAR	0x01
#define LCD_CMD_DATA	0x80
#define LCD_KEYPAD_ROW	5		//LCD position of ROW digit
#define LCD_KEYPAD_COL	14		//LCD position of COL digit

extern int KEY_PRESSED;
extern int keypad_row_mask;
extern int keypad_col_mask;
extern int app_test_keypad_state;

extern void lcd_wait_for_not_busy(void);
extern void lcd_write(int RS_SEL, int CMD_ADDR);
extern void lcd_write_string(char LCD_BUFFER[]);

extern char keypad_str_none[20];
extern char keypad_str_pressed[20];

void app_test_keypad (void){

switch (app_test_keypad_state) {
	case 0:
        //output no key pressed
		if (KEY_PRESSED == 0){
            lcd_wait_for_not_busy();
            lcd_write(LCD_COMMAND, LCD_CMD_DATA | 0x40);
            lcd_write_string(keypad_str_none);
            app_test_keypad_state = 0;
        }
        else {
        // Write to 2nd line
            lcd_wait_for_not_busy();
            lcd_write(LCD_COMMAND, LCD_CMD_DATA | 0x40);
            
            switch (keypad_row_mask) {
                    case 1: keypad_str_pressed[LCD_KEYPAD_ROW] = 0x30; //decodes the masks output
                    break;
                    case 2: keypad_str_pressed[LCD_KEYPAD_ROW] = 0x31; //decodes the masks output
                    break;
                    case 4: keypad_str_pressed[LCD_KEYPAD_ROW] = 0x32; //decodes the masks output
                    break;
                    case 8: keypad_str_pressed[LCD_KEYPAD_ROW] = 0x33; //decodes the masks output
                    break;
            }
            
            switch (keypad_col_mask) {
                    case 1: keypad_str_pressed[LCD_KEYPAD_COL] = 0x30; //decodes the masks output
                    break;
                    case 2: keypad_str_pressed[LCD_KEYPAD_COL] = 0x31; //decodes the masks output
                    break;
                    case 4: keypad_str_pressed[LCD_KEYPAD_COL] = 0x32; //decodes the masks output
                    break;
                    case 8: keypad_str_pressed[LCD_KEYPAD_COL] = 0x33; //decodes the masks output
                    break;
            }
           
            lcd_write_string(keypad_str_pressed);
            app_test_keypad_state = 1;
		}
		break;

	case 1:
            //output key pressed here
		if (KEY_PRESSED == 0){
            app_test_keypad_state = 0;
        }
        else{
            app_test_keypad_state = 1;
        }	
        break;
    }
}