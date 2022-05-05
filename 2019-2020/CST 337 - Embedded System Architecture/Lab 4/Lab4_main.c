/*******************************************************************************
* Name: Zak Rowland
* Date: 10/29/2019
* Lab: 4
* Description: Memory Allocation and Initialization Test
*******************************************************************************/

#include <xc.h>
#include <string.h>

const char a[] = "CST 337 Lab 4";
char b[] =       "Initialized Global Var";
const char c[] = "Initialized Constant String";
char d[100] =    "Initialized String Array";
unsigned int gc = 0; //global initialized to 0
unsigned int gd; //global uninitialized
unsigned int ge = 0x45; //global initialized to 0x45

int main(void)
{
    char * test_string = NULL;
    
    unsigned int ic = 0x0F1E2D3C;
    unsigned int id = 1;
    unsigned int ie;
    const unsigned int icf = 0x98765432;
    static unsigned int isf = 0x67452301;
    static const unsigned int iscf = 0xABCDEFFE;

    unsigned long long Lc = 0x4B5A69788796A5B4LL;
    static const unsigned long long Lcc = 0xFEDCBA9876543210LL;
    unsigned long long Ld = 1;
    unsigned long long Le;

    char la[] = "Local String Test";
    
    ie = 0x19283746;
    ic = icf;
    ic = isf;
    ic = iscf;
    id = gc;

    Le = 0x0123456789ABCDEFLL;

    strcpy(d,b); // Copy the b string into the d string
    strcpy(d,a);
    strcpy(d,c);
    strcpy(b,c);
    
    test_string = (char*) malloc((strlen(c)+1)*sizeof(char)); 
    if(test_string != NULL)
    {
        strcpy(test_string, c);
        free(test_string);
    }
    test_string = NULL;
}
