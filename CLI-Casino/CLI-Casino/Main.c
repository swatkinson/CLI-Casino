#include "Cards.h"
#include <stdio.h>

int main(void) {

	FULLDECK f = initDeck();
	CARD hand1[5] = {drawCard(&f),drawCard(&f),drawCard(&f),drawCard(&f),drawCard(&f) };
	displayHand(hand1, 5);
	shuffle(&f);
	CARD hand2[5] = { drawCard(&f),drawCard(&f),drawCard(&f),drawCard(&f),drawCard(&f) };
	displayHand(hand2, 5);
	destroyDeck(&f);

}