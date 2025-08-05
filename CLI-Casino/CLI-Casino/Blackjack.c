//sebastian solorzano - cscn71030 s25 - project (casino)
//imp for blackjack
#define _CRT_SECURE_NO_WARNINGS
#include "Blackjack.h"
#include <stdbool.h>
#include <stdio.h>
#include <Windows.h>
#define HAND_MAX 11 // 1+1+1+1+2+2+2+2+3+3+3 = 21, therfore handsize cannot exceed 11
#define BLACKJACK 21
#define STARTING_HSIZE 2
#define ROYAL_VAL 10//for tens and aces too

void moveCursor(CURLOC loc) {
	printf("\033[%d;0H",loc);
	if (loc == End)
		printf("\033[J");
	if (loc == Status)
		printf("\033[K");

}

void printBJmenu() {
	WipeScreen();
	printf("welcome to blackjack\na. play game\nq. quit to menu\n");
}



void runBJ(USER u) {

	int bet;
	FULLDECK fd = initDeck();
	CARD phand[HAND_MAX];
	CARD dhand[HAND_MAX];


	bool running=true;
	while (running) {
		printBJmenu();
		char input = GetUserInput("aq");
		switch (input) {
		case 'a':
			bet = getBet(&u);
			deal(&fd, phand, dhand);
			int finalphand=playerTurn(&fd,phand,STARTING_HSIZE);
			int finaldhand=dealerTurn(&fd, dhand, STARTING_HSIZE);
			payout(&u, bet, phand, finalphand, dhand, finaldhand);
			break;
		case 'q':
			running = false;
			break;
		}
	}
	return;
}

void payout(USER* u, int bet, CARD phand[],int phandlen, CARD dhand[], int dhandlen) {
	int playerScore = scoreHand(phand, phandlen);
	int dealerScore = scoreHand(dhand, dhandlen);
	int winnings;

	if (playerScore > BLACKJACK) {
		winnings = 0;
	}
	else if (playerScore == dealerScore) {

		winnings = bet;
	}
	else if (playerScore == BLACKJACK && phandlen == STARTING_HSIZE) {

		winnings = bet * 2.5;
	}
	else if (BLACKJACK - playerScore < BLACKJACK - dealerScore || dealerScore>BLACKJACK) {

		winnings = bet * 2;
	}
	else {

		winnings = 0;
	}


	moveCursor(Status);
	printf("Won %d \na. payout\n", winnings);
	u += winnings;
	int in = GetUserInput("a");
}

int getBet(USER* u) {
	int bet;
	bool valid = false;
	while (!valid) {
		printf("input bet (minimum 2)");
		int a = scanf("%d", &bet);
		ClearInputBuffer();
		if (a != 1 || bet<2) {
			WipeScreen();
			printf("please enter valid amount\n");
		}
		else if (bet > u->balance) {
			WipeScreen();
			printf("cannot place a bet higher than your balance\n");
		}
		else{
			u->balance -= bet;
			valid = true;
		}
	}
	return bet;
}


void deal(FULLDECK* fd, CARD phand[], CARD dhand[]) {
	phand[0] = drawCard(fd);
	dhand[0] = drawCard(fd);
	phand[1] = drawCard(fd);
	dhand[1] = fd->facedown;
	CARD dealersecret = drawCard(fd);

	WipeScreen();
	Sleep(100);
	displayHand(dhand, STARTING_HSIZE);
	Sleep(400);
	displayHand(phand, STARTING_HSIZE);
	if(getValue(dhand[0])>=ROYAL_VAL)
		Sleep(700);

	CARD temp[] = { dhand[0],dealersecret };
	if (scoreHand(temp, STARTING_HSIZE) == BLACKJACK) {//only possible with nattys
		dhand[1] = dealersecret;
		moveCursor(Dealer);
		displayHand(dhand, STARTING_HSIZE);
		moveCursor(End);
	}
	else if (getValue(dhand[0]) >= ROYAL_VAL) {
		moveCursor(Status);
		printf("dealer does not have blackjack\n");
		moveCursor(End);
	}
	dhand[1] = dealersecret;
	return;
}

void availableMoves(CARD hand[], int len, char options[]) {
	bool canhit = false;
	bool canstand = true;//always true
	bool cansplit = false;
	bool canddown = false;
	int n = 0;

	if (scoreHand(hand, len) < BLACKJACK) {
		canhit = true;
		options[n] = 'a';
		n++;
	}
	options[n] = 'b';
	n++;
	if (hand[0].ran == hand[1].ran) {
		cansplit = true;
		options[n] = 'c';
		n++;
	}
	if (scoreHand(hand, len) > 8 && scoreHand(hand, len) < 12) {
		canddown = true;
		options[n] = 'd';
		n++;
	}
	options[n] = '\0';

	if (canhit)
		printf("a. hit     ");
	if (canstand)
		printf("b.stand     ");
	if (cansplit)
		printf("c. split     ");
	if (canddown)
		printf("d. double down");
	printf("\n");

	return options;
}

int playerTurn(FULLDECK* fd,CARD hand[], int len) {
	moveCursor(Player);
	displayHand(hand, len);
	moveCursor(End);

	if (scoreHand(hand, len) == BLACKJACK && len==STARTING_HSIZE) {
		moveCursor(Status);
		printf("BlackJack!\n");
		return len;
	}
	else if (scoreHand(hand, len) > BLACKJACK) {
		moveCursor(Status);
		printf("Busted...\n");
		return len;
	}


	char options[5];
	availableMoves(hand, len, options);
	int input = GetUserInput(options);
	switch (input) {
	case 'a':
		hand[len] = drawCard(fd);
		len=playerTurn(fd, hand, len + 1);
		break;
	case 'b':
		break;
	case 'c':
		printf("subtracting equal bet\n");

		break;
	case 'd':
		printf("doubling");
		break;
	}
	return len;
}

int dealerTurn(FULLDECK* fd,CARD hand[], int len) {
	Sleep(500);
	moveCursor(Dealer);
	displayHand(hand, len);
	moveCursor(End);

	while (scoreHand(hand, len) < 17) {
		hand[len] = drawCard(fd);
		len++;
		moveCursor(Dealer);
		Sleep(500);
		displayHand(hand, len);
		moveCursor(End);
	}
	return len;
}

int scoreHand(CARD hand[], int len) {
	int score=0;
	bool hasAce = false;

	for (int i = 0; i < len;i++) {
		if (hand[i].ran == Ace) 
			hasAce = true;
		score += getValue(hand[i]);
		if (score > BLACKJACK && hasAce == true) {
			score -= ROYAL_VAL;//stripping it of its royalty
			hasAce = false; //in case of multiple aces
		}
	}
	return score;
}


int getValue(CARD c) {
	if (c.ran == Ace) return ROYAL_VAL+1;
	else if (c.ran >= Jack) return ROYAL_VAL;
	else return c.ran + 1;
}
