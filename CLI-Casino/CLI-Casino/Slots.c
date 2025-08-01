// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of Slots module

#define _CRT_SECURE_NO_WARNINGS

#include "Slots.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "IOController.h"
#include <stdbool.h>

#define SYMBOL_COUNT 5
#define INITIAL_BET 50
// Slot Animation Numbers:
#define SPIN_STEPS 20
#define SPIN_DELAY 50

// 2D array of symbols for the slot machine (array of strings, since we are using UTF-8 symbols)
const char* Symbols[] = { "💎", "💲", "🍀", "🪙", "🍒" };

void PrintSlotsMenu(USER User, int Bet) {

    PrintSlotMachine(Symbols[0], Symbols[0], Symbols[0]);

    printf("---------------------------\n");
    printf("Current Balance: %.0lf\n", User.balance);
    printf("Current Bet: %d\n", Bet);
    printf("---------------------------\n");
    printf("Pick an option:\n");
    printf("a. Pull\n");
    printf("b. Change Bet\n");
    printf("q. Quit\n");
}

USER SlotsGame(USER User) {
    int bet = INITIAL_BET;

    PrintSlotsMenu(User, bet);

    while (1) {
        char userInput = GetUserInput("abq");

        switch (userInput) {
        case 'a': // Run Slots

            if (User.balance < bet) {
                printf("You do not have enough balance to place this bet. Please lower your bet.\n");
                continue; // Go back to the menu
            }

            // Run slot machine with their bet, and add their winnings to their balance
            User.balance -= bet;
            User.balance += RunSlots(bet);

            break;

        case 'b': // Change Bet
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

        case 'q': // Quit
            return User;
            break;

        default:
            WipeScreen();
            printf("\nInvalid selection. Please try again.\n\n");
            break;
        }

    }
}

char* GetRandomSymbol() {
    int weights[SYMBOL_COUNT] = { 1, 2, 3, 3, 4 }; // 💎, 💲, 🍀, 🪙, 🍒

    // Get total of weights array
    int totalWeight = 0;
    for (int i = 0; i < SYMBOL_COUNT; ++i) {
        totalWeight += weights[i];
    }

    // Pics a random number between 0 and totalWeight
    int r = rand() % totalWeight;

    // Finds the symbol that corresponds to the 0-totalWeight random number
    int cumulative = 0;
    for (int i = 0; i < SYMBOL_COUNT; ++i) {
        cumulative += weights[i];
        if (r < cumulative)
            return Symbols[i];
    }

    return NULL; // This wont happen, just to silence the error of no return path
}

double RunSlots(int Bet) {
    const char* curSymbols[3];
    curSymbols[0] = GetRandomSymbol();
    curSymbols[1] = GetRandomSymbol();
    curSymbols[2] = GetRandomSymbol();

    double winnings = CalculateWinnings(curSymbols[0], curSymbols[1], curSymbols[2], Bet);

    // Display visuals
    SlotMachineAnimation(curSymbols[0], curSymbols[1], curSymbols[2]);
    if (winnings > 0) {
        printf("\t You won %.0lf! 🎉\n", winnings);
    }
    else {
        printf("\t Try again :/ \n");
    }
   
    return winnings;
}

double GetMultiplier(const char* Symbol) {
    if (strcmp(Symbol, "💎") == 0) return 15;
    if (strcmp(Symbol, "💲") == 0) return 8;
    if (strcmp(Symbol, "🍀") == 0) return 6;
    if (strcmp(Symbol, "🪙") == 0) return 4;
    if (strcmp(Symbol, "🍒") == 0) return 2;
    return 0;
}

double CalculateWinnings(const char* S1, const char* S2, const char* S3, const int Bet) {
    // Winnings if all 3 symbols match
    if (strcmp(S1, S2) == 0 && strcmp(S2, S3) == 0) {
        return Bet * GetMultiplier(S1);
    }

    // Winnings if 2 of 3 symbols match
    const char* match = NULL;

    if (strcmp(S1, S2) == 0) match = S1;
    else if (strcmp(S1, S3) == 0) match = S1;
    else if (strcmp(S2, S3) == 0) match = S2;

    if (match != NULL) {
        return Bet * GetMultiplier(match) / 3;
    }

    // Winnings if there are no matches, but there is a diamond
    if ((S1 != NULL && strcmp(S1, "💎") == 0) || 
        (S2 != NULL && strcmp(S2, "💎") == 0) ||
        (S3 != NULL && strcmp(S3, "💎") == 0))
        return Bet / 2;

    // No match, no diamond
    return 0;
}

void SlotMachineAnimation(const char* S1, const char* S2, const char* S3) {
    // Slot machine 'fills out' column by column, so this animation locks the columns at certain points in the apinning animation
    bool colLock1 = false, colLock2 = false;

    for (int i = 0; i < SPIN_STEPS*3; i++) {

        if (i >= SPIN_STEPS) colLock1 = true;   // Locks column 1 symbol after SPIN_STEPS
        if (i >= SPIN_STEPS*2) colLock2 = true; // Locks column 2 sylbol after SPIN_STEPS x2

        printf("\033[9;7H %s", colLock1 ? S1 : Symbols[i % SYMBOL_COUNT]);
        printf("\033[9;13H %s", colLock2 ? S2 : Symbols[i % SYMBOL_COUNT]);
        printf("\033[9;19H %s", Symbols[i % SYMBOL_COUNT]);

        Sleep(SPIN_DELAY);
    }
}

void PrintSlotMachine(const char* S1, const char* S2, const char* S3) {
    printf(
        "⠀⣀⣤⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣤⣤⣀⠀⠀⠀⠀\n"
        "⠀⢿⣿⣿⣿ CLI CASINO SLOTS ⣿⣿⣿⡿⠀⠀⠀⠀\n"
        "⠀⠀⢙⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⡋⠀⠀⠀⠀⠀\n"
        "⠀⠀⢸⣿⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⣿⡇⠀⠀⣤⣄⠀\n"
        "⠀⠀⢸⣿⠀⢸⠛⠛⠛⠛⡇⢸⠛⠛⠛⠛⡇⢸⠛⠛⠛⠛⡇ ⣿⡇⠀⠀⣿⠛⠀\n"
        "⠀⠀⢸⣿⠀| %s || %s || %s | ⣿⡇⠀⠀⣿  \n"
        "⠀⠀⢸⣿⠀⢸⣤⣤⣤⣤⡇⢸⣤⣤⣤⣤⡇⢸⣤⣤⣤⣤⡇ ⣿⡇⠀⣾⡇⠀⠀\n"
        "⠀⠀⢸⣿⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣿⡆⣿⡿⠀⠀⠀\n"
        "⠀ ⢀⣴⣿⠟⠛⠛⢻⡿⠛⠛⠛⢻⣿⣿⣿⣿⡟⠋⠉⠉⠛⢿⣦⡀⠀⠀⠀⠀ \n"
        "⠀ ⣿⣿⣤⣤⣤⣤⣾⣧⣤⣤⣤⣿⣿⣿⣿⣿⣷⣦⣤⣤⣶⣿⣿⣿⠀⠀⠀⠀ \n"
        "⠀ ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀ \n"
        "⠀ ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀ \n"
        "⠀ ⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀ \n"
        , S1, S2, S3);
}