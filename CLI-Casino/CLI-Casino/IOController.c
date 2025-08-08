// CLI Casino | Spencer Watkinson | CSCN71030
// Implementation of IOController module

#define _CRT_SECURE_NO_WARNINGS
#include "IOController.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Slots.h"
#include "Blackjack.h"
#include "Poker.h"

void MainMenu(PUSER User) {
	while (1)
	{
		// Display menu
		WipeScreen();
		DisplayMainMenuOptions(User);

		// Ask for input
		char userInput = GetUserInput("abcq");

		// Switch case select
		switch (userInput) {
		case 'a':
			SlotsGame(User);
			break;
		case 'b':
			WipeScreen();
			PokerMenu(User);
			break;
		case 'c':
			WipeScreen();
			runBJ(User);
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

void DisplayMainMenuOptions(PUSER User) {
	printf("Welcome %s!\n", User->username);
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
	ClearInputBuffer();
	return selected;
}

void WipeScreen() {
	system("cls");
	printf("\033[91m 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 CLI CASINO 💎 💲 🍀 🪙 🍒 \n \033[0m");
	printf("\033[90m=======================================================================================================================\n\033[0m");
}

void ClearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

TEST_TYPE CheckCommandLineArgs(int Argc, char* Argv[]) {
	if (Argc == 1) return NO_TEST; // No command line arguments provided

	// Valid flags:
	if (strcmp(Argv[1], ALL_FLAG) == 0)			return ALL_TEST;
	if (strcmp(Argv[1], SLOTS_FLAG) == 0)		return SLOT_TEST;
	if (strcmp(Argv[1], POKER_FLAG) == 0)		return POKER_TEST;
	if (strcmp(Argv[1], BLACKJACK_FLAG) == 0)	return BLACKJACK_TEST;

	// If no valid flag was given:
	printf("Usage: .\\%s <test flag>\n", EXE_NAME);
	printf(
		"Valid test flags: \n"
		"%-10s - All Integration Tests \n"
		"%-10s - Slots Integration Tests \n"
		"%-10s - Poker Integration Tests \n"
		"%-10s - Blackjack Integration Tests \n",
		ALL_FLAG, SLOTS_FLAG, POKER_FLAG, BLACKJACK_FLAG
	);

	exit(EXIT_FAILURE);

}

// Draws a window border and prompts user to resize if needed
void DisplayWindowBoundary(int width, int height) {
	WipeScreen();

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 && j == 0)
				printf("┌");
			else if (i == 0 && j == width - 1)
				printf("┐");
			else if (i == height - 1 && j == 0)
				printf("└");
			else if (i == height - 1 && j == width - 1)
				printf("┘");
			else if (i == 0 || i == height - 1)
				printf("─");
			else if (j == 0 || j == width - 1)
				printf("│");
			else
				printf(" ");
		}
		printf("\n");
	}

	// Centered message
	const char* centerMessage = "Please enlarge your terminal or zoom out until you see all borders. Press any enter to continue.";
	int messageRow = height / 2 - 10;
	int messageCol = (width - (int)strlen(centerMessage)) / 2;

	// Move cursor to the center
	printf("\033[%d;%dH%s", messageRow, messageCol, centerMessage); 

	fgetc(stdin); // Pause to let user view message
}