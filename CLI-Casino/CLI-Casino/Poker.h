#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "User.h"
#include "Cards.h"
#include "IOController.h"
#include "FileIO.h"

#define BUY_IN				2
#define HAND_SIZE			5

typedef struct hand {
	CARD cards[HAND_SIZE];
}HAND, *PHAND;


//Betting stuff

bool BuyIn(PUSER user);

bool Raise(PUSER user);

void Check();

void Fold();

//Checking hand type
bool IsRoyalFlush(PHAND hand);

bool IsFourOfaKind(HAND hand);

bool IsFullHouse(HAND hand);

bool IsFlush(HAND hand);

bool IsStraight(HAND hand);

bool IsThreeOfaKind(HAND hand);

bool IsTwoPair(HAND hand);

bool IsPair(HAND hand);

bool IsHighCard();

int CalculateScore();

//Running the game
void IngamePokerMenu(PUSER user, FULLDECK fd);

void RunPoker(PUSER user);

void PokerMenu(PUSER user);