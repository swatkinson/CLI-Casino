#define _CRT_SECURE_NO_WARNINGS
#include "Poker.h"
#include <stdio.h>
#include <Windows.h>

bool BuyIn(PUSER user, int* pot) {
	if (user->balance - BUY_IN < 0) {
		printf("You do not have enough funds to enter the table.");
		return false;
	}
	else {
		user->balance -= BUY_IN;
		*pot += BUY_IN;
		return true;
	}
}

bool Raise(PUSER user, int* pot) {
	int raiseAmount = 0;

	while (1) {
		printf("How much would you like to raise by? ");
		if (scanf_s("%d", &raiseAmount) != 1) {
			printf("Invalid input. Please try again.\n");
		}
		else
		{
			if (raiseAmount > user->balance) {
				printf("you can't raise by that much, the maximum you can raise by is %.0lf\n", user->balance);
			}
			else {
				user->balance -= raiseAmount;
				*pot += raiseAmount;
				return true;
			}
		}
	}
}

void Check() {
	//nothing to do here, check just keeps 
	//the game going without adding anything to the pot
}

void Fold() {
	printf("You have folded.\n");
}

HAND DrawCardSorted(FULLDECK* fd, HAND hand, int* size) {
	CARD cardIN = drawCard(fd);

	int i = *size - 1;

	// Shift elements to the right to make room
	while (i >= 0 && hand.cards[i].ran > cardIN.ran) {
		hand.cards[i + 1] = hand.cards[i];
		i--;
	}

	// Insert the new value
	hand.cards[i + 1] = cardIN;
	(*size)++;
	return hand;
}

void SortHandByRank(HAND* hand, int size) {

	if (size > HAND_SIZE)
		return;

	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (hand->cards[j].ran > hand->cards[j + 1].ran) {
				CARD temp = hand->cards[j];
				hand->cards[j] = hand->cards[j + 1];
				hand->cards[j + 1] = temp;
			}
		}
	}
}

int getRankValue(RANK r) {
	if (r == Ace) return 14; // Ace high
	return (int)r + 1; // Convert enum 0-based to 1-based
}

void countRanksAndSuits(HAND hand, int* rankCount, int* suitCount) {
	for (int i = 0; i < HAND_SIZE; ++i) {
		int val = getRankValue(hand.cards[i].ran);
		rankCount[val]++;
		suitCount[hand.cards[i].sui]++;
	}
}

bool IsRoyalFlush(HAND hand) {
	// Check if all cards are the same suit
	SUIT suit = hand.cards[0].sui;
	for (int i = 1; i < 5; i++) {
		if (hand.cards[i].sui != suit)
			return false;
	}

	// Expected ranks in order: 10, J, Q, K, A -> values: 10 to 14
	for (int i = 0; i < 5; i++) {
		if (getRankValue(hand.cards[i].ran) != 10 + i)
			return false;
	}

	return true;
}

bool IsFourOfaKind(HAND hand) {
	int rankCount[15] = { 0 };
	int suitCount[4] = { 0 };
	countRanksAndSuits(hand, rankCount, suitCount);

	for (int i = 2; i <= 14; ++i) {
		if (rankCount[i] == 4) {
			return true;
		}
	}
	return false;
}

bool IsFullHouse(HAND hand) {
	return IsThreeOfaKind(hand) && IsPair(hand);
}

bool IsFlush(HAND hand) {
	for (int i = 1; i < HAND_SIZE; ++i) {
		if (hand.cards[i].sui != hand.cards[0].sui)
			return false;
	}
	return true;
}

bool IsStraight(HAND hand) {
	// Check normal straight
	for (int i = 0; i < 4; i++) {
		int curr = getRankValue(hand.cards[i].ran);
		int next = getRankValue(hand.cards[i + 1].ran);
		if (next != curr + 1)
			break;
		if (i == 3)
			return true;
	}

	// Check Ace-low straight (A, 2, 3, 4, 5)
	// hand ranks should be: 2,3,4,5,14 (Ace at end)
	int ranks[5];
	bool hasAce = false;
	for (int i = 0; i < 5; i++) {
		ranks[i] = getRankValue(hand.cards[i].ran);
		if (ranks[i] == 14)
			hasAce = true;
	}
	if (!hasAce)
		return false;

	// Check if first 4 cards are 2,3,4,5 exactly
	if (ranks[0] == 2 && ranks[1] == 3 && ranks[2] == 4 && ranks[3] == 5)
		return true;

	return false;
}

bool IsThreeOfaKind(HAND hand) {
	int rankCount[15] = { 0 };
	int suitCount[4] = { 0 };
	countRanksAndSuits(hand, rankCount, suitCount);

	for (int i = 2; i <= 14; ++i)
		if (rankCount[i] == 3) {
			return true;
		}

	return false;
}

bool IsTwoPair(HAND hand) {
	int rankCount[15] = { 0 };
	int suitCount[4] = { 0 };
	countRanksAndSuits(hand, rankCount, suitCount);

	int pairs = 0;
	for (int i = 2; i <= 14; ++i)
		if (rankCount[i] == 2) {
			pairs++;
		}
	if (pairs == 2) {
		return true;
	}
			

	return false;
}

bool IsPair(HAND hand) {
	int rankCount[15] = { 0 };
	int suitCount[4] = { 0 };
	countRanksAndSuits(hand, rankCount, suitCount);

	for (int i = 2; i <= 14; ++i) {
		if (rankCount[i] == 2) {
			return true;
		}
	}
	return false;
}

bool IsHighCard() {
	return true;
}

void CalculateScore(HAND hand, PUSER user, int* pot) {
	float mult = 1;
	
	if (IsRoyalFlush(hand))
		mult = 21;
	else if (IsFourOfaKind(hand))
		mult = 17;
	else if (IsFullHouse(hand))
		mult = 14;
	else if (IsFlush(hand))
		mult = 9;
	else if (IsStraight(hand))
		mult = 6;
	else if (IsThreeOfaKind(hand))
		mult = 4;
	else if (IsTwoPair(hand))
		mult = 1;
	else if (IsPair(hand))
		mult = 0.5;
	else if (IsHighCard())
		mult = 0;
	else {
		printf("Invalid hand.");
		exit(EXIT_FAILURE);
	}

	int winnings = (int)(*pot * mult);
	user->balance += winnings;
	*pot = 0; // reset pot after payout
	printf("New balance is: %lf", user->balance);
}

void IngamePokerMenu(PUSER user, FULLDECK fd, int* pot) {
	printf("would you like to:\n"
		"a. Raise\n"
		"b. Check\n"
		"q. Fold\n"
	);

	char choice = GetUserInput("abq");

	switch (choice)
	{
	case 'a':
		Raise(user, pot);
		break;
	case'b':
		Check();
		break;
	case'q':
		Fold();
		return;
		break;
	default:
		break;
	}
	WipeScreen();
}

int CardsToDiscard() {
	int card = 0;
	while (1) {
		printf("Which card would you like to discrad (1-5)");
		if (scanf("%d", &card) != 1) {
			printf("invalid input. Please try again!\n");
		}
		else {
			if (card > HAND_SIZE || card <= 0) {
				printf("Invalid number of cards inputed. Please try again!\n");
			}
			else {
				
				return card;
			}
		}
	}
}

int RedrawCards(HAND* hand, FULLDECK* fd) {
	printf("Do you want to discard any cards? y/n: ");
	char answer = GetUserInput("yn");

	if (answer == 'n') return 0;

	int numDiscard = 0;
	printf("How many cards do you want to discard (1–4)? ");
	(void)scanf("%d", &numDiscard);

	if (numDiscard <= 0 || numDiscard >= HAND_SIZE) {
		printf("Invalid number.\n");
		return 0;
	}

	int indexes[4] = { -1, -1, -1, -1 };
	for (int i = 0; i < numDiscard; ++i) {
		indexes[i] = CardsToDiscard() - 1;
		if (indexes[i] < 0 || indexes[i] >= HAND_SIZE) {
			printf("Invalid card number. Try again.\n");
			return 0;
		}
	}

	for (int i = 0; i < numDiscard; ++i) {
		hand->cards[indexes[i]] = drawCard(fd);
	}

	SortHandByRank(hand, HAND_SIZE);
	return numDiscard;
}


void RunPoker(PUSER user, int pot) {
	FULLDECK fd = initDeck();
	HAND hand = { 0 };
	int size = 0;
	WipeScreen();
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);
	displayHand(hand.cards, 5);
	
	IngamePokerMenu(user, fd, &pot);

	displayHand(hand.cards, 5);

	int missing = RedrawCards(&hand, &fd);
	
	for (int i = 0; i < missing; i++) {
		hand = DrawCardSorted(&fd, hand, &size);
	}
	
	displayHand(hand.cards, 5);

	CalculateScore(hand, user, &pot);

	Sleep(2000);
}

void PokerMenu(PUSER user) {
	printf("a. Play\nq. Leave");
	int pot = 0;
	char choice = GetUserInput("aq");

	switch (choice)
	{
	case'a':
		if (BuyIn(user, &pot)) {
			RunPoker(user, pot);
		}
		break;
	case'q':
		break;
	default:
		break;
	}
}
