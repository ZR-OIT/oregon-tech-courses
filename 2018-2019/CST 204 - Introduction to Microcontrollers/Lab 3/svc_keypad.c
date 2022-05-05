////////////////////////////////////////////////////////////////////////////////
// File:	svc_keypad.c
//
// Lab:		3
////////////////////////////////////////////////////////////////////////////////
extern int keypad_input_pin (void);
extern int KEY_PRESSED;
extern int keypad_row_mask;
extern int keypad_col_mask;
extern int svc_keypad_state;

void svc_keypad(void) {

	switch (svc_keypad_state) {
		char i = 0;
		case 0:					//STATE ZERO - Has a keypress been detected?
			// Check current row
			for (i = 1; i < 16; i <<= 1) {
				keypad_col_mask = i;			
				if (keypad_input_pin() == 0) {	//was a keypress detected by keypad_input_pin() in keypad.S
					svc_keypad_state = 1;	//goto case/state 1 after you return from the return to main in next line of code
					return; // Only accept first pin, and don't update row_mask; return to main for 10ms delay
				}			//main's next call for svc_keypad will goto case 1 if key was pressed
			}

			switch (keypad_row_mask) {
				case 1:
					keypad_row_mask = 2;
					break;
				case 2:
					keypad_row_mask = 4;
					break;
				case 4:
					keypad_row_mask = 8;
					break;
				default:
					keypad_row_mask = 1;
					break;
			}

			break;

		case 1:
			// Debounce state
			// Inputs haven't changed,  
			// 10MS delay caused by returning to mainin if statement in case 0 is enough for a debounce to ensure
			// that the button is still pressed
			if (keypad_input_pin() == 0) {  //if key still pressed goto case/state 2
				svc_keypad_state = 2;
				KEY_PRESSED = 1;	//key is pressed
			} else {
				svc_keypad_state = 0;	//mechanical switch still "bouncing"
			}
			break;

		case 2:
			// Once keypad_input_pin() returns 1, the button has been released
			//wait for button to be released before going to next case/state
			//program does not response to other key presses in this case/state
			if (keypad_input_pin() == 0) 
                svc_keypad_state = 2;
			else if (keypad_input_pin() == 1)
                svc_keypad_state = 3;
			
			
			break;

		case 3:
			// Debounce state
			// Inputs haven't changed, 10MS is enough for a debounce to ensure
			// that the button is still pressed
			
			if (keypad_input_pin() == 1) {  //if key still pressed goto case/state 2
				svc_keypad_state = 0;
				KEY_PRESSED = 0;	//key is pressed
			} else {
				svc_keypad_state = 2;//mechanical switch still "bouncing"
			}
			
			
			break;

		default:
			svc_keypad_state = 0;
			break;
	}
}
