#include <stdio.h>

extern int isqrt(int temp);
extern void output_string(char* ptr);
extern void uart_init(void);

void main(void)
{
    char mystr[100];
    int i, j;
    
    uart_init(); // setup uart1 for output

    for(i = 1; i <= 200; i++) {
       j = isqrt(i);
       sprintf(mystr, "The isqrt of %u is %u. Check: %u^2 = %u, %u^2 = %u\n", i, j, j, j*j, j+1, (j+1)*(j+1));
       output_string(mystr);
    }

}
