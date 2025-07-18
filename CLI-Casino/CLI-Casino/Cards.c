


#include "Cards.h"
#include <stdio.h>
#include <stdlib.h>

//basically, we're treating the text file like a block of memory
//card art is a fixed size, so we can essentially treat the start of each card as an address
//its dimensions are 25 x 17, or 25 'bits' and 17 'bits' per 'byte'/'address' 
//these can be renamed if you don't like them
//card art is unfinished so currently placeholder values
#define LINE 7 //25
#define NUM_LINES 3 //17
#define BYTE LINE * NUM_LINES


//PDECKNODE initDeck(){}

//void addto(PDECKNODE* existing, CARD c){}

//void removefrom(PDECKNODE* existing, CARD c){}


//semi-temp function that creates all the cards and loads them into a 52-card deck (array of 52)
//once the linked list is implemented we'll instead put the cards there
void loaddeck(CARD d[]) {
	int a = 0;
	for (int i = 0; i <= spade; i++) {
		for (int j = 0; j <= King; j++) {
			CARD c;
			c.sui = i;
			c.ran = j;
			c.address = a * BYTE;
			d[a] = c;
			a++;
		}
	}
}

//draws a selected hand to the screen. hand has to be placed in an array beforehand
//due to the size of the card art, handsize >6 starts looking wrong if you don't zoom out the screen
void paintHand(CARD c[], int handsize) {

	char buf[LINE - 1]; //buffer for printing
	FILE* fp = fopen("deck.txt", "r"); //file where art is stored


	//rather than reading the file and storing it into an array (which would be huge, 884 * 25),
	//we just jump to where we want and read it directly

	//lines are drawn one at a time so that cards can be drawn next to each other
	for (int j = 0; j < NUM_LINES; j++) {
		for (int i = 0; i < handsize; i++) { 

			//jumps to (start of card) + (line number/offset)
			fseek(fp, c[i].address + (j * LINE), SEEK_SET); 

			//copies to buffer and prints
			fgets(buf, LINE - 1, fp); //smaller than line so \n gets cut off (intentional)
			printf("%s", buf);
			printf("   ");
			fgets(buf, LINE - 1, fp);
		}
		printf("\n"); //adds newline once all cards have been drawn
	}
	fclose(fp);
}
