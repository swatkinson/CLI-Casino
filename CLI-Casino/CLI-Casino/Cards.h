//sebastian solorzano - cscn71030 s25 - project (casino)
//interface for all card functions. card struct, setting up deck, drawing,
// discard, painting, etc.

#pragma once

//basically, we're treating the text file like a block of memory
//card art is a fixed size, so we can essentially treat the start of each card as an address
//its dimensions are 25 x 17, or 25 'bits' and 17 'bits' per 'byte'/'address' 
//card art is unfinished so currently placeholder values
#define LINE_LEN 25
#define NUM_LINES 17
#define ADDR LINE_LEN * NUM_LINES
#define CARDS_IN_DECK 52


typedef enum suit {
	club,
	diamond,
	heart,
	spade
}SUIT;

typedef enum rank {
	Ace,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Jack,
	Queen,
	King,
}RANK;

typedef struct card {
	SUIT sui;
	RANK ran;
	int address; //reference to pos. in art file
}CARD;


//linked list in case you couldn't tell
typedef struct deckNode {
	CARD car;
	struct deckNode* next;
}DECKNODE, * PDECKNODE;


typedef struct fullDeck {
	PDECKNODE drawPile;
	int remainingInDraw;

	PDECKNODE discardPile;

	//facedown card for dealer cards and rivers and etc.
	CARD facedown;
}FULLDECK;


//card functions:
CARD createCard(SUIT s, RANK r, int address);
CARD copyCard(CARD c);
//cards not in heap, dont need to be deleted


//linked list (decknode) functions:
void addCardtoPile(PDECKNODE* head, CARD c);

CARD removeCardfromPile(PDECKNODE* head, int index);//not a typical remove function, dont worry about it

void destroyPile(PDECKNODE* head);


PDECKNODE initDrawpile(); //initializes a deck of 52 cards in the drawpile


//fulldeck functions:
CARD drawCard(FULLDECK* fd); //draws card from drawpile

void shuffle(FULLDECK* fd); //doesn't actually shuffle, just puts discards back into drawpile

void destroyDeck(FULLDECK* fd);

FULLDECK initDeck();


//draws hand to screen
//games have to make hands themselves, not here
void displayHand(CARD d[], int handsize);


//should the void functions return their status with a bool? i don't think most of them'd fail though


//temporary function while linked list hasn't been made yet
//keeping it here for testing or whatever
void loaddeck(CARD d[]);



