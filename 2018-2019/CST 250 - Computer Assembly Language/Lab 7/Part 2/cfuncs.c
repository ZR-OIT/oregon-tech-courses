#include <stdio.h>

//extern int isqrt(int temp);
extern void output_string(char* ptr);
//extern void uart_init(void);

void print_str(int i, int j)
{
    char mystr[100];
    
    sprintf(mystr, "The isqrt of %u is %u. Check: %u^2 = %u, %u^2 = %u\n", i, j, j, j*j, j+1, (j+1)*(j+1));
    output_string(mystr);

}
