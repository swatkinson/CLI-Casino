// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of IOController module

#include "IOController.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "Slots.h"

void MainMenu(PUSER User) {
	while (1)
	{
		// Display menu
		WipeScreen();
		DisplayMainMenuOptions();

		// Ask for input
		char userInput = GetUserInput("abcq");

		// Switch case select
		switch (userInput) {
		case 'a':
			SlotsGame(User);
			break;
		case 'b':
			WipeScreen();
			printf("\n[DEBUG] Poker selected\n\n");
			// PokerGame(User);
			break;
		case 'c':
			WipeScreen();
			printf("\n[DEBUG] Blackjack selected\n\n");
			// BlackjackGame(User);
			break;
		case 'q':
			WipeScreen();
			printf("\nExiting the game. Thank you for playing!\n\n");
			return;
		default:
			WipeScreen();
			printf("\nInvalid selection. Please try again.\n\n");
			break;
		}
	}
}

void DisplayMainMenuOptions() {
	printf("Which game do you want to play?\n");
	printf("---------------------------\n");
	printf("a. Slots\n");
	printf("b. Poker (Vegas Style)\n");
	printf("c. Blackjack\n");
	printf("---------------------------\n");
	printf("q. Quit\n");
}

/// Asks users to input char selection, if character is not in validChars, tell user and ask again
char GetUserInput(char* ValidChars) {
	char selected;
	bool valid = false;

	while (!valid) {
		printf("Please enter your selection (%s): ", ValidChars);
		selected = fgetc(stdin);
		
		ClearInputBuffer();

		// Check if selected is in validChars
		for (int i = 0; ValidChars[i] != '\0'; i++) {
			if (selected == ValidChars[i]) {
				valid = true;
				break;
			}
		}
		if (!valid) {
			printf("Invalid selection. Please try again.\n");
		}
	}
	return selected;
}

void WipeScreen() {
	system("cls");
	printf("\033[91m 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 \n \033[0m");
	printf("\033[90m======================================================================================================================= \n\033[0m");
}

void ClearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}