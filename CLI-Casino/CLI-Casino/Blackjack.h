//sebastian solorzano - cscn71030 s25 - project (casino)
//interface for blackjack
#pragma once
#include "IOController.h"
#include "Cards.h"
#include "User.h"


typedef enum cursorLocation {
	Dealer = 3,
	Player = 20,
	Status =37,
	End=38
}CURLOC;

void runBJ(USER u);

int getBet(USER* u);

void deal(FULLDECK* fd, CARD phand[], CARD dhand[]);

int playerTurn(FULLDECK* fd, CARD hand[], int len);

int scoreHand(CARD hand[], int len);

int dealerTurn(FULLDECK* fd, CARD hand[], int len);

void payout(USER* u, int bet, CARD phand[], int phandlen, CARD dhand[], int dhandlen);