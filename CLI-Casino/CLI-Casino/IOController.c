// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of IOController module

#include "IOController.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void mainMenu(USER User) {
    while (1)
    {
        // Display menu
        displayMainMenuOptions();

        // Ask for input
        char userInput = getUserInput("abcq");

        // Switch case select
        switch (userInput) {
        case 'a':
            printf("\n[DEBUG] Slots selected\n\n");
            // SlotsGame(User);
            break;
        case 'b':
            printf("\n[DEBUG] Poker selected\n\n");
            // PokerGame(User);
            break;
        case 'c':
            printf("\n[DEBUG] Blackjack selected\n\n");
            // BlackjackGame(User);
            break;
        case 'q':
            printf("\nExiting the game. Thank you for playing!\n");
            return;
        default:
            printf("\nInvalid selection. Please try again.\n\n");
            break;
        }
    }
}

void displayMainMenuOptions() {
    printf("Which game do you want to play?\n");
    printf("---------------------------\n");
    printf("a. Slots\n");
    printf("b. Poker (Vegas Style)\n");
    printf("c. Blackjack\n");
    printf("---------------------------\n");
    printf("q. Quit\n");
}

/// Asks users to input char selection, if character is not in validChars, tell user and ask again
char getUserInput(char* validChars) {
    char selected;
    bool valid = false;

    while (!valid) {
        printf("Please enter your selection (%s): ", validChars);
        selected = fgetc(stdin);
        // Consume any extra input until newline
        while (getchar() != '\n');

        // Check if selected is in validChars
        for (int i = 0; validChars[i] != '\0'; i++) {
            if (selected == validChars[i]) {
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