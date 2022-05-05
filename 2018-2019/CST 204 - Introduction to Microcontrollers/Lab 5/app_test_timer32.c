#include <xc.h>

extern int KEY_PRESSED;
extern int app_timer32_state;
extern int FLASHER;

void app_test_timer32 (void){

switch (app_timer32_state) {
	case 0:
		if (KEY_PRESSED == 0){
            app_timer32_state = 0;
        }
        else{
            FLASHER = 1;
            IFS0SET = 0x1000;
            app_timer32_state = 1;
        }  
        break;
    case 1:
        if(KEY_PRESSED == 1){
            app_timer32_state = 1;
        }
        else {
            FLASHER = 0;
            app_timer32_state = 0;
        }
        break;
    }
}