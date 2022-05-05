/****************************************************************************************************
* Author: Zak Rowland
* Filename: main.c
* Date Created: 5/17/2018
* Modifications:
*****************************************************************************************************
* Assignment: Lab 7
*
* Overview: For the lab you will create a linked list. That list node will have a note to play,
*			 as well as a number of beats. This will allow us to create a melody.
*
* Input: Data input from user.
*
* Output: A song!
*
*****************************************************************************************************
* The calculation of the tones is made following the
* mathematical operation:
* timeHigh = period / 2 = 1 / (2 * toneFrequency)
* where the different tones are described as in the table:
* ----------------------------------
* |Note |frequency |period |timeHigh|
* ----------------------------------
* c		261.63Hz	3822	1911 compare 30576
* d		293.66Hz	3405	1702 compare 27232
* e		329.63Hz	3034	1517 compare 24272
* f		349.23Hz	2864	1432 compare 22912
* g		392.00Hz	2549	1275 compare 20400
* a		440.00Hz	2273	1136 compare 18176
* b		493.88Hz	2025	1012 compare 16192
* C		523.25Hz	1911	956  compare 15296
* r		0.0Hz		0		0	 compare 0
********************************************************/
#define BUZZER_MASK (1 << DDB1)

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "uartDriver.h"

struct node
{
	uint16_t note;
	uint8_t beats;
	struct node * next;
};
uint16_t twinkle_twinkle[60] = { 'c', 'c', 'g',   'g', 'a',   'a', 'g', 'f',   'f', 'e', 
								   'e', 'd',   'd', 'c','g',   'g', 'f',   'f', 'e',  
								 'e', 'd', 'g',   'g', 'f',   'f', 'e',   'e', 'd', 'c',  
								 'c', 'g',   'g', 'a',   'a', 'g', 'f',   'f', 'e',   'e',
								 'd',   'd', 'c' };
								 
uint16_t mary_lamb[26] = { 'e', 'd', 'c', 'd', 'e',   'e',   'e', 'd',   'd',   'd', 'e',
						   'g',   'g', 'e', 'd', 'c', 'd', 'e',   'e',   'e',   'e', 'd',
						     'd', 'e', 'd', 'c'};
	
uint16_t note_comp[9] = { 30576, 27232, 24272, 22912, 20400, 18176, 16192, 15296, 0 };
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

void InitTimer(void);
void PlayTone(uint16_t note, uint8_t beats);
void SelectNote(uint16_t note, uint8_t beats, struct node ** head);
struct node * CreateNode(uint16_t note, uint8_t beats);
void AppendNode(struct node ** head, struct node * newNode);
void ClearSong(struct node ** head);
uint16_t freeRAM(void);

/*****************************************************************************************************
* Function: main
* Purpose: Reads data from user and calls appropriate functions to form a song linked list.
* Preconditon: No data or song.
* Postcondition: Song made from dynamically allocated linked list.
*****************************************************************************************************/
int main(void)
{
	FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
	FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
	uart_init();
	stdout = &uart_output;
	stdin = &uart_input;

	InitTimer();

	DDRB |= BUZZER_MASK;

	struct node * head = NULL;

	uint16_t temp_note = '0';
	uint8_t temp_beats = 0;
	uint8_t finished = 0;
	char option = '0';

    while(1)
	{
		printf("\n-|( Zak's Song Generator )|-\n");
		printf("\n\nFree memory: %i\n", freeRAM());
		printf("Press 1 to make a song or press 2 to listen to premade songs: ");
		option = getchar();
		
		//Make a song
		if(option == '1')
		{
			while (finished == 0)
			{
				//User inputs note
				printf("\nEnter a note (a, b, c, etc.): ");
				temp_note = getchar();
				
				//User inputs beat number
				printf("\nEnter number of beats (0, 1, 2, etc.): ");
				temp_beats = getchar();
				temp_beats -= '0';
				
				//Appends a new note node depending on user selection
				SelectNote(temp_note, temp_beats, &head);

				//Asks for another note
				printf("\nAdd another note? (Y / N): ");
				option = getchar();
				if((option == 'N') || (option == 'n'))
				{
					finished = 1;
				}
			}

			finished = 0;
			
			while(finished == 0)
			{
				//Pointer to first note
				struct node * travel = head;
				
				printf("\n\nFree memory: %i\n", freeRAM());
				printf("\n\nPlaying song...\n");
				while(travel != NULL)
				{
					PlayTone(travel->note, travel->beats);
					travel = travel->next;
				}
				printf("\n\nFree memory: %i\n", freeRAM());
				printf("\n\nPlay song again? (Y / N)");
				option = getchar();
				
				if((option == 'N') || (option == 'n'))
				{
					finished = 1;
				}
			}
			printf("\n\nFree memory: %i\n", freeRAM());
			ClearSong(&head);
			printf("\n\nFree memory: %i\n", freeRAM());
			temp_note = '0';
			temp_beats = 0;
			finished = 0;
			option = '0';	
		}
		//Hear a song
		else if(option == '2')
		{
			printf("\n\nPress 1 for Twinkle Twinkle Little Star\nPress 2 for Mary Had a Little Lamb: ");
			option = getchar();
			switch(option)
			{
				//Twinkle Twinkle
				case '1':
				{
					for(uint8_t i = 0; i < 60; i++)
					{
						SelectNote(twinkle_twinkle[i], 1, &head);
					}
					while(finished == 0)
					{
						//Pointer to first note
						struct node * travel = head;
									
						printf("\n\nPlaying song...\n");
						while(travel != NULL)
						{
							PlayTone(travel->note, travel->beats);	
							travel = travel->next;
						}
									
						printf("\n\nPlay song again? (Y / N)");
						option = getchar();
									
						if((option == 'N') || (option == 'n'))
						{
							finished = 1;
						}
					}
					
					ClearSong(&head);
					printf("\n\nFree memory: %i\n", freeRAM());
					temp_note = '0';
					temp_beats = 0;
					finished = 0;
					option = '0';	
					break;
				}
				//Mary's Lamb
				case '2':
				{
					for(uint8_t i = 0; i < 26; i++)
					{
						SelectNote(mary_lamb[i], 1, &head);
					}
					while(finished == 0)
					{
						//Pointer to first note
						struct node * travel = head;
						
						printf("\n\nFree memory: %i\n", freeRAM());
						printf("\n\nPlaying song...\n");
						while(travel != NULL)
						{
							PlayTone(travel->note, travel->beats);
							travel = travel->next;
						}
						
						printf("\n\nPlay song again? (Y / N)");
						option = getchar();
						
						if((option == 'N') || (option == 'n'))
						{
							finished = 1;
						}
					}
					printf("\n\nFree memory: %i\n", freeRAM());
					ClearSong(&head);
					printf("\n\nFree memory: %i\n", freeRAM());
					temp_note = '0';
					temp_beats = 0;
					finished = 0;
					option = '0';
					break;
				}
				default:
				{
					printf("\nInvalid option, please try again.\n");
					break;
				}
			}
		}
		//Error
		else
		{
			printf("\nInvalid option, please try again.\n");
		}
	}
}

/*****************************************************************************************************
* Function: InitTimer(void)
* Purpose: Configures timer 1 for use.
* Preconditon: Timer 1 not enabled or configured.
* Postcondition: Timer 1 configured.
*****************************************************************************************************/
void InitTimer(void)
{
	TCNT1 = 0; //Timer count
	TCCR1B |= (1 << CS10); //1 pre-scaler for timer 1
	OCR1A = 0; //Timer 1 comparator A value
	TIMSK1 |= (1 << OCIE1A); //Enable compare interrupts
}

/*****************************************************************************************************
* Function: PlayTone(uint16_t note, uint8_t beats)
* Purpose: Changes the compare value for timer 1 to change the tone of the buzzer.
* Preconditon: No sound.
* Postcondition: A tone played based on user input data.
*****************************************************************************************************/
void PlayTone(uint16_t note, uint8_t beats)
{
	if(note == '0' || note == 0)
	{
		for(int c = 0; c < beats; c++)
		{
			_delay_ms(500);
		}
	}
	else
	{
		OCR1A = note;
		for(int b = 0; b < beats; b++)
		{
			sei();
			_delay_ms(500);
		}	
		cli();	
		_delay_ms(100);
	}
}
void SelectNote(uint16_t note, uint8_t beats, struct node ** head)
{
	if(note == 'c')
	{
		AppendNode(*&head, CreateNode(note_comp[0], beats));
	}
	else if(note == 'd')
	{
		AppendNode(*&head, CreateNode(note_comp[1], beats));
	}
	else if(note == 'e')
	{
		AppendNode(*&head, CreateNode(note_comp[2], beats));
	}
	else if(note == 'f')
	{
		AppendNode(*&head, CreateNode(note_comp[3], beats));
	}
	else if(note == 'g')
	{
		AppendNode(*&head, CreateNode(note_comp[4], beats));
	}
	else if(note == 'a')
	{
		AppendNode(*&head, CreateNode(note_comp[5], beats));
	}
	else if(note == 'b')
	{
		AppendNode(*&head, CreateNode(note_comp[6], beats));
	}
	else if(note == 'C')
	{
		AppendNode(*&head, CreateNode(note_comp[7], beats));
	}
	else if(note == 'r')
	{
		AppendNode(*&head, CreateNode(note_comp[8], beats));
	}
}
/*****************************************************************************************************
* Function: CreateNode(uint16_t note, uint8_t beats)
* Purpose: Creates a note node using data input by user
* Preconditon: No node.
* Postcondition: A new note node.
*****************************************************************************************************/
struct node * CreateNode(uint16_t note, uint8_t beats)
{
	struct node * newNode = NULL;
	newNode = (struct node *)malloc(sizeof(struct node));

	newNode->note = note;
	newNode->beats = beats;
	newNode->next = NULL;

	return newNode;
}

/*****************************************************************************************************
* Function: AppendNode(struct node ** head, struct node * newNode)
* Purpose: Adds a note node to the end of the current linked list.
* Preconditon: A linked list.
* Postcondition: A linked list with another node added.
*****************************************************************************************************/
void AppendNode(struct node ** head, struct node * newNode)
{
	if(*head == NULL) //List is empty
	{
		*head = newNode;
	}
	else
	{
		struct node * travel = *head;

		while(travel->next != NULL)
		{
			travel = travel->next;
		}
		travel->next = newNode;
	}
}

/*****************************************************************************************************
* Function: ClearSong(struct node ** head)
* Purpose: Frees memory allocated by linked list and deletes the list.
* Preconditon: A linked list.
* Postcondition: Memory freed.
*****************************************************************************************************/
void ClearSong(struct node ** head)
{
	if(*head != NULL)
	{
		struct node * travel = *head;
		struct node * trail = *head;
		while(travel != NULL)
		{
			free(travel);
			travel = trail->next;
			trail = travel;
		}
		*head = NULL;
	}
}

/*****************************************************************************************************
* Function: freeRAM(void)
* Purpose: Displays the amount of free memory on the board.
* Preconditon:
* Postcondition:
*****************************************************************************************************/
uint16_t freeRAM(void)
{
	uint8_t newVariable;

	if((uint16_t)__brkval == 0)
	{
		return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
	}
	else
	{
		return (((uint16_t)&newVariable) - ((uint16_t)&__brkval));
	}
}

ISR(TIMER1_COMPA_vect)
{
	PORTB ^= BUZZER_MASK;
	TCNT1 = 0;
}