.global	FLAG_10MS
.global	heartbeat_state
.global	heartbeat_count

.global lcd_test_state
.global lcd_test_count
.global LCD_TEST_LINE1
.global LCD_TEST_LINE2

.data
	FLAG_10MS:		.word	0
	heartbeat_state:	.word	0
	heartbeat_count:	.word	0
    
	lcd_test_state:		.word	0
	lcd_test_count:		.word	0
.text
	LCD_TEST_LINE1:		.asciiz "This is line 1"
	LCD_TEST_LINE2:		.asciiz "This is line 2"