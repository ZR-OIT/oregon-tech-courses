//FOR DEVCFG2
    //FPLLIDIV=DIV_2, FPLLMUL = MUL_20, and FPLLODIV = DIV_4
    .section .config_BFC02FF4, code
    .word 0xFFFAFFD9
    
 //FOR DECCFG1
 // Set FNOSC = PRIPLL, POSCMOD = XT, and FWDTEN = OFF
 .section .config_BFC02FF8, code
 .word 0xFF7FFDFB