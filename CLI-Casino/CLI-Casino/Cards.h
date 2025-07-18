//sebastian solorzano - cscn71030 s25 - project (casino)
//interface for all card functions. card struct, setting up deck, drawing,
// discard, painting, etc.

#pragma once

typedef enum suit {
	heart,
	diamond,
	club,
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
	int address;
}CARD;

typedef struct deckNode {
	CARD c;
	struct deckNode* next;
}DECKNODE, * PDECKNODE;


//PDECKNODE initDeck();

//void addto(PDECKNODE* existing, CARD c);

//void removefrom(PDECKNODE* existing, CARD c);

