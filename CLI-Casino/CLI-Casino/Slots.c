// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of Slots module

#define _CRT_SECURE_NO_WARNINGS

#include "Slots.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "IOController.h"

#define SYMBOL_COUNT 5
#define SPIN_STEPS 30
#define DELAY_MS 80

// 2D array of symbols for the slot machine (array of strings, since we are using UTF-8 symbols)
const char* Symbols[] = { "💎", "💲", "🍀", "🪙", "🍒" };

// Returns payout multiplier for a given symbol
double GetMultiplier(const char* Symbol) {
    if (strcmp(Symbol, "💎") == 0) return 10;
    if (strcmp(Symbol, "💲") == 0) return 8;
    if (strcmp(Symbol, "🍀") == 0) return 6;
    if (strcmp(Symbol, "🪙") == 0) return 4;
    if (strcmp(Symbol, "🍒") == 0) return 2;
    return 0;
}

double CalculateWinnings(const char* S1, const char* S2, const char* S3, int Bet) {
    // Winnings if all 3 symbols match
    if (strcmp(S1, S2) == 0 && strcmp(S2, S3) == 0) {
        return Bet * GetMultiplier(S1);
    }

    // Winnings if 2 of 3 symbols match
    if (strcmp(S1, S2) == 0) {
        return Bet * GetMultiplier(S1) / 2;
    }
    else if (strcmp(S1, S3) == 0) {
        return Bet * GetMultiplier(S1) / 2;
    }
    else if (strcmp(S2, S3) == 0) {
        return Bet * GetMultiplier(S2) / 2;
    }

    // No match
    return 0;
}

USER SlotsGame(USER User) {
    int bet = 10;
    while (1) {
        PrintSlotsMenu(User, bet);
        char userInput = GetUserInput("abq");

        switch (userInput) {
        case 'a':
            // Run slots
            WipeScreen();

			if (User.balance < bet) {
				printf("You do not have enough balance to place this bet. Please lower your bet.\n");
				continue; // Go back to the menu
			}

            printf("[DEBUG] Slots run\n");
            break;
        case 'b':
            printf("How much do you want to bet? (min = 1, no max) \n");
            int newBet;
            // Check if it got 1, greater than 0 symbol
            if (scanf("%d", &newBet) != 1 || newBet < 1) {
                WipeScreen();
                printf("Invalid bet entry. Please enter an integer greater or equal to 1.\n");
            }
            else {
                bet = newBet;
                WipeScreen();
                printf("Bet updated to %d.\n", bet);
            }

            ClearInputBuffer();
            break;
        case 'q':
            return User;
            break;
        default:
            WipeScreen();
            printf("\nInvalid selection. Please try again.\n\n");
            break;
        }

    }
}

void PrintSlotsMenu(USER User, int Bet) {
    printf("---------------------------\n");
    printf("Current Balance: %lf\n", User.balance);
    printf("Current Bet: %d\n", Bet);
    printf("---------------------------\n");
    printf("Pick an option:\n");
    printf("a. Pull\n");
    printf("b. Change Bet\n");
    printf("q. Quit\n");
}