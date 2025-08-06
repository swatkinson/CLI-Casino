//sebastian solorzano - cscn71030 s25 - project (casino)
//imp for blackjack
#define _CRT_SECURE_NO_WARNINGS
#include "Blackjack.h"
#include <stdbool.h>
#include <stdio.h>
#include <Windows.h>

#define ROYAL_VAL 10//for tens and aces too

//moves cursor to desired position
void moveCursor(CURLOC loc) {
	printf("\033[%d;0H",loc);
	if (loc == End || loc == Player)
		printf("\033[J");//clears everything below 
	if (loc == Status)
		printf("\033[K"); //clears line

}

//prints game menu
void printBJmenu() {
	WipeScreen();
	printf("welcome to blackjack\na. play game\nq. quit to menu\n");
}


//runs the game's main loop
void runBJ(USER u) {
	int bet;
	FULLDECK fd = initDeck();

	bool running=true;
	while (running) {

		printBJmenu();

		//buy-in is done within the game, so the only options are play and quit
		char input = GetUserInput("aq");
		switch (input) {
		case 'a':
			if (u.balance < 2) {
				printf("insufficient balance\n");
				break;
			}

			bet = getBet(&u);
			playRound(u, &fd, bet);
			shuffle(&fd);
			break;
		case 'q':

			running = false;
			break;
		}
	}
	return;
}


BJPLAYER initplayer() {
	BJPLAYER p = { 0 };
	//array is already initialized? doesn't let me touch it
	p.handsize = STARTING_HSIZE;
	p.handsize = STARTING_HSIZE;
	p.state = Firsthand;
	p.hasSplit = false;

	return p;
}


void playRound(USER u, FULLDECK* fd, int bet) {
	BJPLAYER player = initplayer();
	player.bet = bet; //cant be done in init because of dealer
	BJPLAYER dealer = initplayer();

	//easiest way I can think of to deal with splits, kinda gross tho
	BJPLAYER splitp = initplayer();
	splitp.state = Normal;//splits cant split, bj or dd
	 




	deal(fd,&player,&dealer);
	printf("\033[0;0H playerscore: %d, dealerscore: %d   PB: %s  BPJ: %s  DB: %s  DBJ: %s", player.score, dealer.score, (player.state==Busted)?"yes":"no",(player.state==BJed)?"yes":"no", (dealer.state == Busted) ? "yes" : "no", (dealer.state == BJed)?"yes" : "no");
	moveCursor(End);
	
	if (player.state != BJed && dealer.state != BJed) { //avoids continuing if anyone has a natty
		playerTurn(&u, fd, &player, &splitp);
		if (player.hasSplit) {
			moveCursor(Status);
			printf("playing split 2");
			playerTurn(&u, fd, &splitp, &splitp);//no default values; so sad :(...
		}
		dealerTurn(fd, &dealer);
	}
	else
		Sleep(800);//tension
	
	if (player.hasSplit)
		payout(&u, &splitp, &dealer); //runs split hand first
	payout(&u, &player,&dealer);

	moveCursor(End);
}


void payout(USER* u,BJPLAYER* p, BJPLAYER* d) {
	//just in case
	p->score = scoreHand(p->hand, p->handsize, &p->state);
	d->score = scoreHand(d->hand, d->handsize, &d->state);
	moveCursor(Dealer);
	displayHand(d->hand, d->handsize);
	moveCursor(Player);
	displayHand(p->hand, p->handsize);

	if (p->state == Ddowned) {
		moveCursor(Player);
		displayHand(p->hand, p->handsize);
		Sleep(500);//tension
	}



	int winnings;

	if (p->state == Busted) {
		winnings = 0;
	}
	else if (p->score == d->score) {
		winnings = p->bet;
	}
	else if (p->state==BJed) {
		winnings = p->bet * 2.5;
	}
	else if (BLACKJACK - p->score < BLACKJACK - d->score || d->state==Busted) {
		winnings = p->bet * 2;
	}
	else {
		winnings = 0;
	}

	printf("\033[1;1H bet %d", p->bet);
	moveCursor(Status);
	printf("Won % d",winnings);
	u->balance += winnings;
	moveCursor(End); 
	printf("a.payout\n");
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


void deal(FULLDECK* fd, BJPLAYER* p, BJPLAYER* d) {
	p->hand[0] = drawCard(fd);
	d->hand[0] = drawCard(fd);
	p->hand[1] = drawCard(fd);
	d->hand[1] = fd->facedown;//dealer card stays hidden

	WipeScreen();
	Sleep(100);
	moveCursor(Dealer);
	displayHand(d->hand, d->handsize);
	Sleep(400);
	moveCursor(Player);
	displayHand(p->hand, p->handsize);

	//now that we're done printing we can just add dealer's second card to hand, screen won't be updated until dealerturn anyway
	d->hand[1] = drawCard(fd);


	//we don't actually really care about score at this point, but taking it just makes things simpler
	//what we really want is status, since game ends early if anyone has bj
	d->score=scoreHand(d->hand, d->handsize, &d->state);
	p->score=scoreHand(p->hand, p->handsize, &p->state);



	//if dealer has a possibility of blackjack
	if (getValue(d->hand[0]) >= ROYAL_VAL) {//cant use score here because its specifically about the first card
		Sleep(700);//tension

		if (d->state == BJed) {
			moveCursor(Dealer);
			displayHand(d->hand, STARTING_HSIZE);
			moveCursor(End);
		}
		else {
			moveCursor(Status);
			printf("dealer does not have blackjack\n");
			moveCursor(End);
		}
	}
	return;
}

void availableMoves(BJPLAYER* p, char options[]) {
	bool canhit = false;
	bool canstand = true;//always true
	bool cansplit = false;
	bool canddown = false;
	int n = 0;

	if (p->state!=Busted) {
		canhit = true;
		options[n] = 'a';
		n++;
	}
	options[n] = 'b';
	n++;
	if (p->hand[0].ran == p->hand[1].ran && p->state==Firsthand) {
		cansplit = true;
		options[n] = 'c';
		n++;
	}
	if (p->score > 8 && p->score < 12 && p->state==Firsthand) {
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

void playerTurn(USER* u, FULLDECK* fd,BJPLAYER* p,BJPLAYER* splip) {
	moveCursor(Player);
	displayHand(p->hand, p->handsize);
	moveCursor(End);

	//since this can loop multiple times we should take it at the start
	p->score = scoreHand(p->hand, p->handsize, &p->state);

	if (p->state==Busted) {
		moveCursor(Status);
		printf("Busted...\n");
		return;
	}


	char options[5];
	availableMoves(p, options);
	int input = GetUserInput(options);
	switch (input) {
	case 'a':
		p->hand[p->handsize] = drawCard(fd);
		p->handsize++;
		p->state = Normal;
		playerTurn(u,fd, p,splip); //eww recursion, I know, but this seemed like a easier way of doing it
			//spli wont get used at all but needed because no default values in c
		break;
	case 'b':
		break;
	case 'c':
		moveCursor(Status);
		printf("playing split 1");

		//for split hand
		splip->hand[0] = p->hand[1];
		splip->hand[1] = drawCard(fd);
		splip->bet = p->bet;
		u->balance -= p->bet;

		//continuing to play first hand
		p->hand[1] = drawCard(fd); //not incrementing because we're replacing the card we had
		p->state = Normal;
		p->hasSplit = true;
		playerTurn(u, fd, p, splip); //eww recursion, I know, but this seemed like a easier way of doing it
			//spli wont get used at all but needed because no default values in c

		break;
	case 'd':
		moveCursor(Status);
		printf("doubled down");
		u->balance -= p->bet;
		p->bet += p->bet;
		
		//visuals for facedown card
		p->hand[p->handsize] = fd->facedown;
		moveCursor(Player);
		displayHand(p->hand, p->handsize+1);
		moveCursor(End);
		//actual card and status
		p->hand[p->handsize] = drawCard(fd);
		p->handsize++;//we didn't raise it earlier because we want to replace the facedown card
		p->state = Ddowned;

		break;
	}
}

void dealerTurn(FULLDECK* fd,BJPLAYER* d) {
	Sleep(500);//tension

	//reveals their hidden card
	moveCursor(Dealer);
	displayHand(d->hand, d->handsize);

	while (d->score < 17) {
		Sleep(500);//more tension
		moveCursor(Dealer);//to overwrite previously drawn
		d->hand[d->handsize] = drawCard(fd);
		d->handsize++;
		displayHand(d->hand, d->handsize);
		d->score = scoreHand(d->hand, d->handsize, &d->state);
	}
	moveCursor(End);
}

//not accepting a player struct directly because then it gets annoying with hidden cards and the like
int scoreHand(CARD hand[], int len, STAT* s) {
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

	if (*s == Firsthand && score == BLACKJACK) //notably, blackjackwont be counted on splits
		*s = BJed;
	else if (score > BLACKJACK)
		*s = Busted;

	return score;
}


int getValue(CARD c) {
	if (c.ran == Ace) return ROYAL_VAL+1;
	else if (c.ran >= Jack) return ROYAL_VAL;
	else return c.ran + 1;
}
