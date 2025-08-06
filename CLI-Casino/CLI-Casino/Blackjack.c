//sebastian solorzano - cscn71030 s25 - project (casino)
//imp for blackjack
#define _CRT_SECURE_NO_WARNINGS
#include "Blackjack.h"
#include <stdio.h>

#define ROYAL_VAL 10//for tens and aces too
#define MIN_BET 2//arbitrary according to real life table mins
#define POSSIBLE_ACTIONS 5 //possible actions a player can take: hit, stand, split, double down, \0
#define DEALER_STAND_VAL 17//based on real life rules, dealer must stand on 17 or higher
#define BJ_PAYOUT 2.5 //blackjack pays out 3:2; since we already subtracted the bet amount we have to return that as well
#define REG_PAYOUT 2 //regular win pays out 1:1; since we already subtracted the bet amount we have to return that as well


BJPLAYER initplayer() {
	BJPLAYER p = { 0 };
	//array is already initialized? doesn't let me touch it
	p.handsize = STARTING_HSIZE;
	p.handsize = STARTING_HSIZE;
	p.state = Firsthand;//can only take special actions or get blackjack on first hand
	p.hasSplit = false;//c doesn't like uninitialized bools

	return p;
}


int getBet(USER* u) {
	int bet;
	bool valid = false;

	while (!valid) {

		printf("input bet (minimum 2)");

		int a = scanf("%d", &bet);
		ClearInputBuffer();//for annoying stuff

		if (a != 1 || bet < MIN_BET) { //a for garbage inputs in scanf
			WipeScreen();
			printf("please enter valid amount\n");
		}
		else if (bet > u->balance) {
			WipeScreen();
			printf("cannot place a bet higher than your balance\n");//not allowing debt, sadly
		}
		else {
			u->balance -= bet; //immediatly removes from balance
			valid = true;
		}
	}
	return bet;
}


//runs the game's main loop
void runBJ(USER u) {//change to *u once we integrate
	int bet;
	FULLDECK fd = initDeck();

	bool running = true;
	while (running) {

		printBJmenu();

		//buy-in is done within the game, so the only options are play and quit
		char input = GetUserInput("aq");
		switch (input) {
		case 'a':

			//otherwise inescapable within the getbet function
			if (u.balance < MIN_BET) {
				printf("insufficient balance\n");
				break;
			}

			//players aren't initialized yet, so we use an int to send the bet
			bet = getBet(&u);
			playRound(u, &fd, bet);

			//not strictly necessary, but prevents card counting(kinda? it auto-reshuffles when empty so idk if it was possible to begin with)
			shuffle(&fd);
			break;
		case 'q':
			running = false;
			break;
		}
	}
	return;
}



void playRound(USER u, FULLDECK* fd, int bet) {
	BJPLAYER player = initplayer();
	player.bet = bet; //cant be done in init because of dealer
	BJPLAYER dealer = initplayer();

	//easiest way I can think of to deal with splits, kinda gross tho
	BJPLAYER splitp = initplayer();
	splitp.state = Normal;//splits cant split, bj or dd


	//we recieved fd as a pointer already, so no *fds below

	deal(fd, &player, &dealer);

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
		Sleep(800);//dramatic tension

	if (player.hasSplit)
		payout(&u, &splitp, &dealer); //runs split hand first

	payout(&u, &player, &dealer);

	moveCursor(End);
}


void deal(FULLDECK* fd, BJPLAYER* p, BJPLAYER* d) {
	//using 0 and 1 here because handsize is 2rn and that would be the wrong index
	p->hand[0] = drawCard(fd);
	d->hand[0] = drawCard(fd);
	p->hand[1] = drawCard(fd);
	d->hand[1] = fd->facedown;//dealer card stays hidden


	//displaying the cards, sleeps are to make it look good (insant full hands looks bad)
	//sleep numbers are magic I guess but I really don't think they matter?
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
	d->score = scoreHand(d->hand, d->handsize, &d->state);
	p->score = scoreHand(p->hand, p->handsize, &p->state);

	
	//if dealer has a possibility of blackjack
	if (getValue(d->hand[0]) >= ROYAL_VAL) {//cant use score here because its specifically about the first card
		Sleep(700);//tension

		if (d->state == BJed) {
			moveCursor(Dealer);
			displayHand(d->hand, STARTING_HSIZE); //reveals their blackjack!!
			moveCursor(End);
		}
		else {
			moveCursor(Status);
			printf("dealer does not have blackjack\n");//just so you know
			moveCursor(End);
		}
	}
	//this is all the same as in real casinos, where dealers will check for blackjack if they might have it. game ends early if they do
	//(this is a good thing since there's no way for you to win if they do anyway)
	return;
}


void playerTurn(USER* u, FULLDECK* fd, BJPLAYER* p, BJPLAYER* splip) {

	//since this can loop multiple times we should do all this at the start
	moveCursor(Player);
	displayHand(p->hand, p->handsize);
	moveCursor(End);

	p->score = scoreHand(p->hand, p->handsize, &p->state);


	//end immediatly if they bust. also a basecase/exitcase
	if (p->state == Busted) {
		moveCursor(Status);
		printf("Busted...\n");
		return;
	}


	char options[5];
	//checks what options are actually available to the player
	availableMoves(p, options);
	//allowed input based on those options
	int input = GetUserInput(options); 
	switch (input) {
	case 'a':

		//draws a card and advances handsize to next index
		p->hand[p->handsize] = drawCard(fd);
		p->handsize++;
		//disallows special moves after
		p->state = Normal;

		playerTurn(u, fd, p, splip); //eww recursion, I know, but this seemed like an easier way of doing it
		//spli wont get used at all but needed because no default values in c
		break;
	case 'b':
		//simply ends turn, also an exit case
		break;
	case 'c':
		
		//if you dont say it can get confusing
		moveCursor(Status);
		printf("playing split 1");

		//for split hand
		splip->hand[0] = p->hand[1];
		splip->hand[1] = drawCard(fd);
		splip->bet = p->bet; //split bet is same as starting bet
		u->balance -= p->bet; //removing balance directly kind of feels off, but whatever

		//continuing to play first hand
		p->hand[1] = drawCard(fd); //not incrementing because we're replacing the card we had
		p->state = Normal;
		p->hasSplit = true; //so it knows to play again and score twice
		playerTurn(u, fd, p, splip); //eww recursion, I know, but this seemed like a easier way of doing it
		//spli wont get used at all but needed because no default values in c

		break;
	case 'd':

		moveCursor(Status);
		printf("doubled down");
		//as its name implies, bet is doubled
		u->balance -= p->bet; //removing balance directly kind of feels off, but whatever
		p->bet += p->bet;//this surprisingly works

		//visuals for facedown card
		p->hand[p->handsize] = fd->facedown;
		moveCursor(Player);
		displayHand(p->hand, p->handsize + 1);
		moveCursor(End);

		//actual card and status
		p->hand[p->handsize] = drawCard(fd);
		p->handsize++;//we didn't raise it earlier because we want to replace the facedown card
		p->state = Ddowned;

		break;
	}
}

void availableMoves(BJPLAYER* p, char options[]) {
	bool canhit = false;
	bool canstand = true;//always true
	bool cansplit = false;
	bool canddown = false;
	int n = 0;

	if (p->state != Busted) {
		canhit = true;
		options[n] = 'a';
		n++;
	}
	options[n] = 'b';
	n++;
	if (p->hand[0].ran == p->hand[1].ran && p->state == Firsthand) {
		cansplit = true;
		options[n] = 'c';
		n++;
	}
	if (p->score > 8 && p->score < 12 && p->state == Firsthand) {
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


void dealerTurn(FULLDECK* fd, BJPLAYER* d) {
	Sleep(500);//tension

	//reveals their hidden card
	moveCursor(Dealer);
	displayHand(d->hand, d->handsize);

	while (d->score < DEALER_STAND_VAL) {

		d->hand[d->handsize] = drawCard(fd);
		d->handsize++;
		d->score = scoreHand(d->hand, d->handsize, &d->state);

		Sleep(500);//more tension
		moveCursor(Dealer);//to overwrite previously drawn
		displayHand(d->hand, d->handsize);
	}
	moveCursor(End);
}


void payout(USER* u, BJPLAYER* p, BJPLAYER* d) {
	//just in case it not updated (such as for splits, or with hidden card on blackjack)
	p->score = scoreHand(p->hand, p->handsize, &p->state);
	d->score = scoreHand(d->hand, d->handsize, &d->state);
	moveCursor(Dealer);
	displayHand(d->hand, d->handsize);
	moveCursor(Player);
	displayHand(p->hand, p->handsize);


	//player's facedown card is revealed at the end
	if (p->state == Ddowned) {
		moveCursor(Player);
		displayHand(p->hand, p->handsize);
		Sleep(500);//tension
	}


	int winnings;

	//order of if statements is based on priority: 
	//if you bust, you lose no matter what, if you tie, you get back what you payed (even if it was blackjack)
	//if you blackjack, you win(naturally), if your score is closer to 21 or dealer busts, you win
	//and otherwise(dealer is closer to 21), you lose
	if (p->state == Busted) {
		winnings = 0; //lose
	}
	else if (p->score == d->score) {
		winnings = p->bet; //get your bet back; 'push'
	}
	else if (p->state == BJed) {
		winnings = p->bet * BJ_PAYOUT; //big win!
	}
	else if (BLACKJACK - p->score < BLACKJACK - d->score || d->state == Busted) {
		winnings = p->bet * REG_PAYOUT;//win!
	}
	else {
		winnings = 0;
	}

	moveCursor(Status);
	printf("Won % d", winnings);
	u->balance += winnings;
	moveCursor(End);

	//small thing to cashout, for fun and the fact that otherwise the screen would clear immediatly and you wouldn't see what happened
	printf("a.payout\n");
	int in = GetUserInput("a");

	return;
}




int getValue(CARD c) {
	//enum starts at 0 so we add+1
	if (c.ran == Ace) return ROYAL_VAL + 1;
	else if (c.ran >= Jack) return ROYAL_VAL;
	else return c.ran + 1; //man i love enums
}


int scoreHand(CARD hand[], int len, STAT* s) {
	int score=0;
	bool hasAce = false;

	for (int i = 0; i < len;i++) {
		//since aces can change their value we have to check for them
		if (hand[i].ran == Ace) 
			hasAce = true;

		score += getValue(hand[i]);

		if (score > BLACKJACK && hasAce == true) {
			score -= ROYAL_VAL;//stripping it of its royalty
			hasAce = false; //in case of multiple aces
		}

	}

	if (*s == Firsthand && score == BLACKJACK) //notably, blackjack wont be counted on splits
		*s = BJed;
	else if (score > BLACKJACK)
		*s = Busted;

	return score;
}


//moves cursor to desired position
void moveCursor(CURLOC loc) {

	printf("\033[%d;0H", loc);

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

