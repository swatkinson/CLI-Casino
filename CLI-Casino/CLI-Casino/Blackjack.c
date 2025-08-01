//sebastian solorzano - cscn71030 s25 - project (casino)
//imp for blackjack
#define _CRT_SECURE_NO_WARNINGS
#include "Blackjack.h"

#include <stdio.h>


void runBJ(USER u) {
	FULLDECK fd = initDeck();
	int in = 1;
	while (in) {
		CARD dealer[11] = { drawCard(&fd),fd.facedown };
		CARD player[11] = { drawCard(&fd),drawCard(&fd) };
		displayHand(dealer, 2);
		Sleep(250);
		displayHand(player, 2);
		scanf("%d", &in);
	}
}