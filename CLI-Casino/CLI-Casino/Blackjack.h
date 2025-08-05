//sebastian solorzano - cscn71030 s25 - project (casino)
//interface for blackjack
#pragma once
#include "IOController.h"
#include "Cards.h"
#include "User.h"


typedef enum cursorLocation {
	Dealer=3,
	Player=20,
	End=37
}CURLOC;

void runBJ(USER u);

int getBet(USER* u);

void deal(FULLDECK* fd, CARD* phand[], CARD* dhand[]);

void playerTurn(FULLDECK* fd, CARD hand[], int len);

int scoreHand(CARD hand[], int len);

void dealerTurn(FULLDECK* fd, CARD hand[], int len);