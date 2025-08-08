// CLI Casino | Ricardo Pineda Pelaez | CSCN71030 
//int for all Poker stuff.
#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include "User.h"
#include "Cards.h"
#include "IOController.h"
#include "FileIO.h"

#define BUY_IN				30
#define HAND_SIZE			5

typedef struct hand {
	CARD cards[HAND_SIZE];
}HAND, *PHAND;


#define ROYAL_FLUSH_PAYOUT					150
#define FOUR_OF_A_KIND_PAYOUT				8
#define FULL_HOUSE_PAYOUT					5
#define FLUSH_PAYOUT						4
#define STRAIGHT_PAYOUT						3
#define THREE_OF_A_KIND_PAYOUT				2
#define TWO_PAIR_PAYOUT						1
#define PAIR_PAYOUT							0.5
#define HIGH_CARD_PAYOUT					0


//Betting stuff

bool BuyIn(PUSER user, int* pot);

bool Raise(PUSER user, int *pot);

void Check();

HAND DrawCardSorted(FULLDECK* fd, HAND hand, int* size);

void SortHandByRank(HAND* hand, int size);

int getRankValue(RANK r);

void countRanksAndSuits(HAND hand, int* rankCount, int* suitCount);

//Checking hand type
bool IsRoyalFlush(HAND hand);

bool IsFourOfaKind(HAND hand);

bool IsFullHouse(HAND hand);

bool IsFlush(HAND hand);

bool IsStraight(HAND hand);

bool IsThreeOfaKind(HAND hand);

bool IsTwoPair(HAND hand);

bool IsPair(HAND hand);

bool IsHighCard();

void CalculateScore(HAND hand, PUSER user, int* pot);

//Running the game
void IngamePokerMenu(PUSER user, FULLDECK fd, int* pot);

int CardsToDiscard();

int RedrawCards(HAND* hand, FULLDECK* fd);

void RunPoker(PUSER user, int pot);

void PokerMenu(PUSER user);