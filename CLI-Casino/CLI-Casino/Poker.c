#include "Poker.h"
#include <stdio.h>

bool BuyIn(PUSER user) {
	if (user->balance - BUY_IN < 0) {
		printf("You do not have enough funds to enter the table.");
		return false;
	}
	else {
		user->balance -= BUY_IN;
		return true;
	}
}

bool Raise(PUSER user) {
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
				return true;
				break;
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


bool IsRoyalFlush(PHAND hand) {

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

int CalculateScore(HAND hand) {
	if (IsRoyalFlush(&hand))
		return;
	else if (IsFourOfaKind(hand))
		return;
	else if (IsFullHouse(hand))
		return;
	else if (IsFlush(hand))
		return;
	else if (IsStraight(hand))
		return;
	else if (IsThreeOfaKind(hand))
		return;
	else if (IsTwoPair(hand))
		return;
	else if (IsPair(hand))
		return;
	else if (IsHighCard(hand))
		return;
	else {
		printf("Invalid hand.");
		exit(EXIT_FAILURE);
	}
}

void IngamePokerMenu(PUSER user, FULLDECK fd) {
	printf("would you like to:\n"
		"a. Raise\n"
		"b. Check\n"
		"q. Fold\n"
	);

	char choice = GetUserInput("abq");

	switch (choice)
	{
	case 'a':
		Raise(user);
		drawCard(&fd);
		break;
	case'b':
		Check();
		drawCard(&fd);
		break;
	case'q':
		Fold();
		return;
		break;
	default:
		break;
	}
}

void RunPoker(PUSER user) {
	FULLDECK fd;
	HAND hand = { 0 };
	int size = 0;
	//if these magic numbes are still here, its cuz I forgot to remove them after I was done testing
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);
	hand = DrawCardSorted(&fd, hand, &size);

	IngamePokerMenu(user, fd);

	IngamePokerMenu(user, fd);


}

void PokerMenu(PUSER user) {
	printf("a. Play\nq. Leave");

	char choice = GetUserInput("aq");

	switch (choice)
	{
	case'a':
		if (BuyIn) {
			RunPoker(user);
		}
		break;
	case'q':
		break;
	default:
		break;
	}
}
