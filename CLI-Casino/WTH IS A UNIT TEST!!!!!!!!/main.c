#include "worknetting.h"
#include <stdio.h>

//so I made this because how else am i supposed to test the network code when we have the entire rest of the project running

int main(void) {

	CLIENSOCKS CS;
	SERVSOCKS SS;

	
	int a;
	scanf_s("%d", &a);
	if (a == 1) {
		LANStart(&SS, NULL);
		runServ(&SS);
	}
	else {
		LANStart(NULL, &CS);
		runClien(&CS);
	}

	LANEnd();
	return 0;
}