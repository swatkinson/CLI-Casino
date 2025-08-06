//sebastian solorzano - cscn71030 s25 - project (casino)
//interface for blackjack
#pragma once
#include "IOController.h"
#include "Cards.h"
#include "User.h"
#include <stdbool.h>
#define HAND_MAX 11 // 1+1+1+1+2+2+2+2+3+3+3 = 21, therfore handsize cannot exceed 11
#define BLACKJACK 21
#define STARTING_HSIZE 2


typedef enum playerStatus {
	Firsthand,
	BJed,
	Normal,
	Ddowned,
	Busted
}STAT;

//for both players and dealer, though dealer doesn't use second hand
typedef struct bjplayer {
	CARD hand[HAND_MAX];
	int handsize;
	int score;
	int bet; //dealer has this parameter but doesn't use it
	STAT state;
	bool hasSplit; //cant be a state because it can get overriden by busting


}BJPLAYER;

typedef enum cursorLocation {
	Dealer = 3,
	Player = 21,
	Status =20,
	End=38
}CURLOC;


BJPLAYER initplayer();

void runBJ(USER u);

int getBet(USER* u);

void deal(FULLDECK* fd, BJPLAYER* p, BJPLAYER* d);

void playerTurn(USER* u, FULLDECK* fd, BJPLAYER* p, BJPLAYER* splip);

int scoreHand(CARD hand[], int len, STAT* s);

void availableMoves(BJPLAYER* p, char options[]);


void dealerTurn(FULLDECK* fd, BJPLAYER* d);

void payout(USER* u, BJPLAYER* p, BJPLAYER* d);

void playRound(USER u, FULLDECK* fd, int bet);