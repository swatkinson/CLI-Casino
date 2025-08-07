// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
//interface for blackjack
#pragma once
#include "IOController.h"
#include "Cards.h"
#include "User.h"
#include <stdbool.h>
#define HAND_MAX 11 // 1+1+1+1+2+2+2+2+3+3+3 = 21, therfore handsize cannot exceed 11
#define BLACKJACK 21
#define STARTING_HSIZE 2

#define DEALER_LOC 3
#define MENU_LOC 20
#define BETTING_LOC 23
#define STATUS_LOC 25
#define OPTION_LOC 27
#define PLAYER_LOC 29
#define END_LOC 46

//extern bool IntegrationTestFlag;


//player's possible statuses across the game
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
	bool hasSplit; //cant be a state because it could get overriden by busting


}BJPLAYER;




//(BJ) initializes a player for blackjack
BJPLAYER initplayer();

//(BJ) gets user's bet. 
int getBet(USER* u);
//for blackjack only, since it specifically takes at beginning or round
//could work for buy-in on other card games?? not sure. if so, move to cards or iocontroller


//main loop for blackjack
void runBJ(USER* u);

//(BJ) runs a single round/game of blackjack
void playRound(USER* u, FULLDECK* fd, int bet);


//(BJ) starting deal for player and dealer
void deal(FULLDECK* fd, BJPLAYER* p, BJPLAYER* d);

//(BJ) runs the player's turn
void playerTurn(USER* u, FULLDECK* fd, BJPLAYER* p, BJPLAYER* splitp);
//(BJ) checks which moves are available to the player
void availableMoves(BJPLAYER* p, char options[]);

//(BJ) runs the dealer's turn
void dealerTurn(FULLDECK* fd, BJPLAYER* d);

//(BJ) pays out bets 
void payout(USER* u, BJPLAYER* p, BJPLAYER* d);




//(BJ) gets value of a card
int getValue(CARD c);
//designed for blackjack, kqj=10, a=11,
//though it could work for other games if they share those values. man i wish we had virtual functions

//(BJ) scores hand
int scoreHand(CARD hand[], int len, STAT* s);
//only for blackjack, since it checks for blackjack or busted and modifies ace values accordingly


//(BJ) moves cursor to a specific location
void moveCursor(int loc);
//locations specifically designed with blackjack in mind. might work for other card games???
//assuming they follow the same visual style. if so move this to cards or iocontroller?

//prints menu for blackjack
void printBJmenu();

//(BJ) prints a status message onto the bjmenu
void printStatus(char message[]);

//(BJ) prints available options onto the bj menu
void printOptions(char opt1[], char opt2[], char opt3[], char opt4[]);

//(BJ) prints bet and balance onto the bj menu
void printBet(int be, int ba);

void tension(int ttimems);






