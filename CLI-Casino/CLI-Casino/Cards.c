//sebastian solorzano - cscn71030 s25 - project (casino)
//imp for all card functions. card struct, setting up deck, drawing,
// discard, painting, etc.


#include "Cards.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//basically, we're treating the text file like a block of memory
//card art is a fixed size, so we can essentially treat the start of each card as an address
//its dimensions are 25 x 17, or 25 'bits' and 17 'bits' per 'byte'/'address' 
//card art is unfinished so currently placeholder values
#define LINE_LEN 7 //25
#define NUM_LINES 3 //17
#define BYTE LINE_LEN * NUM_LINES
#define CARDS_IN_DECK 52


//code probably runs



//CARD functions

CARD createCard(SUIT s, RANK r, int address) {
	CARD c;
	c.sui = s;
	c.ran = r;
	c.address = address; //refers to location on "deck.txt" (position number)
	return c;
}

CARD copyCard(CARD c) {
	//self explanatory
	CARD copy = createCard(c.sui, c.ran, c.address);
	return copy;
}


//linked list (decknode) functions

void addCardtoPile(PDECKNODE* existing, CARD c) {
	//standard malloc
	PDECKNODE newnode = (PDECKNODE)malloc(sizeof(DECKNODE));
	if (newnode == NULL) {
		fprintf(stderr, "no mem :(\n");
		exit(EXIT_FAILURE);
	}
	else {
		//its a linked list, what more to say
		newnode->car = copyCard(c);
		newnode->next = *existing;
		*existing = newnode;
	}
}

//this function is basically used for card draw, so we don't look for a specific card like we normally would with a remove function
//instead we take an index, move to it, and remove that card (whatever it is)
CARD removeCardfromPile(PDECKNODE* existing, int index) {
	PDECKNODE current = *existing;
	//if at top of list
	if (current != NULL && index == 0) {
		*existing = current->next;

		CARD removed = copyCard(current->car);
		//dont need to delete card since its in stack
		free(current);
		return removed;
	}

	PDECKNODE prev = NULL;

	//move toward the index
	for (int i = 0; i < index;i++) {
		prev = current;
		current = current->next;

		//since this isn't done in a while loop like normal, we have to constantly check we're not going over
		if (current == NULL) {
			fprintf(stderr, "card draw went out of bounds\n");
			exit(EXIT_FAILURE);
			//if we dont want to crash the program, we can instead return the error card on position 54
		}
	}
	//if things go normally:
	prev->next = current->next;
	CARD removed = copyCard(current->car);
	free(current);
	return removed;

	//it'd be nice if we could return the pointer itself but that would require a second version of the add and remove functions
	//since we still need the regular ones for init and stuff. so not worth it
}

void destroyPile(PDECKNODE* existing) {
	//deletes linked list, nothing unusual
	PDECKNODE current = *existing;
	while (current != NULL) {
		PDECKNODE temp = current;
		current = current->next;
		//dont need to delete card
		free(temp);
	}
}


//initializes a draw pile with full 52 cards
//cards are not shuffled, but it doesn't matter
PDECKNODE initDrawpile() {
	//creates an empty one first
	PDECKNODE drawp = NULL;

	int cardnum = 0;
	//both suit and rank are enums so you can just do this
	for (int i = 0; i <= spade;i++) {
		for (int j = 0; j <= King;j++) {
			CARD c = createCard(i, j, cardnum * BYTE);
			cardnum++;
			addCardtoPile(&drawp, c);
		}
	}

	return drawp;
} 


//functions for the deck as a whole (two linked lists for draw and discard)

//can be used as both draw and discard
CARD drawCard(FULLDECK* fd) {

	//if the deck is empty, reshuffle it (shouldn't happen in either poker or blackjack)
	//could in theory lead to duplicates of a card in player's hand, not actuall a problem (just tell them we added a deck)
	if (fd->remainingInDraw == 0) {
		shuffle(fd);
	}

	//the reason it doesnt matter that deck is unshuffled:
	srand(time(NULL));

	//basically, instead of shuffling the deck so that the top card is random, we just pick randomly from anywhere in the deck
	CARD drawn = removeCardfromPile(&fd->drawPile, (rand() % fd->remainingInDraw)); 
			//mod remaining so that it doesnt pick card 49 when there's only 30 cards left in the deck
	//card being removed from draw pile naturally means it cant be drawn again

	fd->remainingInDraw--;

	//card is immediately placed in discardpile and also sent to the player; being in hand or discarded is effectively the same thing
	//if player just wants to discard, simply ignore return value here
	//this has nothing to do with player discarding from their hand, this module doenst deal with hands
		//ie figure that out yourself
	addCardtoPile(&fd->discardPile, drawn);
	return drawn;
}

//i wanted to call this reshuffle but was vetoed
void shuffle(FULLDECK* fd) {

	int discardnum = CARDS_IN_DECK - fd->remainingInDraw; //should be self-evident

	//empties discard pile, places back in drawpile
	for (int i = 0; i < discardnum;i++) {
		CARD shuffleback = removeCardfromPile(&fd->discardPile, 0);//just taking the top element until empty, no need to be fancy
		addCardtoPile(&fd->drawPile, shuffleback);
	}
	//cards end up being added in reverse draw order, though as I said deck order doesn't actually matter
	fd->remainingInDraw = CARDS_IN_DECK;
}

void destroyDeck(FULLDECK* fd) {
	//FULLDECK itself is in stack
	destroyPile(&fd->drawPile);
	destroyPile(&fd->discardPile);
}

FULLDECK initDeck() {
	FULLDECK fd;
	fd.drawPile = initDrawpile();
	fd.remainingInDraw = CARDS_IN_DECK;

	fd.discardPile = NULL; //starts empty

	//facedown card for dealer cards and rivers and etc. not actually a card and should always be accesible, so its placed here
	//shouldn't be used for anything other than display functions, set its rank and suit to -1 either way
	fd.facedown = createCard(-1, -1, (CARDS_IN_DECK) * BYTE);//starts at 0, so 52 is card no. 53

	return fd;
}



//draws a selected hand to the screen. hand has to be placed in an array beforehand
//due to the size of the card art, handsize >6 starts looking wrong if you don't zoom out the screen
		//for the full-size cards, i mean. temp cards you can probably fit like 20 of em
void displayHand(CARD c[], int handsize) {

	//spencer uses UTF-8 for the rest of the program, but its a multi-byte encoding and only has 128 single-byte characters
	//437 (the default on windows/visual studio) has double that, so I use it instead
	//I need single-byte (or at least constant) chars because reading the art file works on the basis that each card is a fixed size
	//there's probably a more elegant solution to this, but I haven't been able to think of one
	SetConsoleOutputCP(437);

	char buf[LINE_LEN - 1]; //buffer for printing
	FILE* fp = fopen("deck.txt", "r"); //file where art is stored


	//rather than reading the file and storing it into an array (which would be huge, 884 * 25),
	//we just jump to where we want and read it directly

	//if we want to add color to the card art, we could add 'control' characters onto the art itself,
		//and %c for them instead of %s ing lines. this would slow things down, need lottsa if statements, and not work for face cards (too dense, no place to put them)
	//otherwise we could create a seperate colors file, and reference it when drawing a card. this would still need %c and if statements,
		//but wouldn't require modification of the original art file
	//tell me if you can think of a better solution

	//lines are drawn one at a time so that cards can be drawn next to each other
	for (int j = 0; j < NUM_LINES; j++) {
		for (int i = 0; i < handsize; i++) {

			//jumps to (start of card) + (line number/offset)
			fseek(fp, c[i].address + (j * LINE_LEN), SEEK_SET);

			//copies to buffer and prints
			fgets(buf, LINE_LEN - 1, fp); //smaller than line so \n gets cut off (intentional)
			//this is fine because  we end up seeking to somewhere else after that anyways
			printf("%s", buf);
			printf("   "); //just a pit of spacing so the cards aren't right next to each other
		}
		printf("\n"); //adds newline the current line for all cars has been drawn
	}
	fclose(fp); //important
}





//semi-temp function that creates all the cards and loads them into a 52-card deck (array of 52)
//once the linked list is implemented we'll instead put the cards there
//keeping it here cus why not. use it for testing or something
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