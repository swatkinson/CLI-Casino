// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of Slots module

#include "Slots.h"

// 2D array of symbols for the slot machine (array of strings, since we are using UTF-8 symbols)
const char* Symbols[] = { "💎", "💲", "🍀", "🪙", "🍒" };

void PrintSlotsMenu(int Bet) {
    printf(
        "┌───────────────────────────────────────┬───────────────────────────────────────┬──────────────────────────────────────┐\n"
        "│            A - Pull Lever             │            B - Change Bet             │               Q - Quit               │\n"
        "├───────────────────────────────────────┴───────────────────────────────────────┴──────────────────────────────────────┤\n"
        "\n" // UpdateSlotsMenu function writes in the user info here
        "└──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n"
    );

    PrintSlotMachine(Bet);
}

void UpdateSlotsMenu(PUSER User, int Bet) {
    printf("\033[7;0H│                                  Current Bet: %-10d           Current Balance: %-10.0lf                       │\n", Bet, User->balance);
}

void MoveCursorToInput() {
    // Moves cursor to input line, and clears all of the lines beneath it to get rid of old messages
    printf("\033[23;0H\033[J");
}

void DisplayWinnings(double Winnings) {
    if (Winnings > 0) { // V Moves cursor centered under slot machine
        PrintUnderSlots("\033[22;50H 🎉 You won %5.0lf! 🎉 ", Winnings);
    }
    else {
        PrintUnderSlots("\033[22;55H Try again :/");
    }
}

void PrintUnderSlots(const char* format, ...) {
    // Moves to line under slot machine, clears line
    printf("\033[22;0H\033[2K");

    // This is an exact copy of what printf does, to handle putting variables into the string with format specifiers
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}

void SlotsGame(PUSER User) {
    int bet = INITIAL_BET;

    // Initialize Display
    WipeScreen();
    PrintSlotsMenu(bet);

    while (1) {

        UpdateSlotsMenu(User, bet);
        MoveCursorToInput();

        char userInput = GetUserInput("abq");

        switch (userInput) {
        case 'a': // Run Slots

            if (User->balance < bet) {
                PrintUnderSlots("You do not have enough balance to place this bet. Please lower your bet.\n");
                continue; // Go back to the menu
            }

            // Charge user bet, and display that in menu
            User->balance -= bet;
            UpdateSlotsMenu(User, bet);

            // Run slot machine
            double winnings = RunSlots(bet);
            User->balance += winnings;

            // Winning message under slot machine
            DisplayWinnings(winnings);

            break;

        case 'b': // Change Bet
            printf("How much do you want to bet? (min = 1, no max) \n");

            int newBet;
            // Check if it got 1, greater than 0 symbol
            if (scanf("%d", &newBet) != 1 || newBet < 1) {
                PrintUnderSlots("Invalid bet entry. Please enter an integer greater or equal to 1.\n");
            }
            else {
                bet = newBet;
                // Reprint screen with updated bet + menu
                WipeScreen();
                PrintSlotsMenu(bet);
            }

            ClearInputBuffer();
            break;

        case 'q': // Quit
            return;
            break;
        } // No default needed, input checking exists in the getuserinput function

    }
}

const char* GetRandomSymbol() {
    int weights[SYMBOL_COUNT] = { DIAMOND_RARITY, DOLLAR_RARITY, CLOVER_RARITY, COIN_RARITY, CHERRY_RARITY };

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

    SlotMachineAnimation(curSymbols[0], curSymbols[1], curSymbols[2]);

    return CalculateWinnings(curSymbols[0], curSymbols[1], curSymbols[2], Bet);
}

double GetMultiplier(const char* Symbol) {
    if (strcmp(Symbol, "💎") == 0) return DIAMOND_MODIFIER;
    if (strcmp(Symbol, "💲") == 0) return DOLLAR_MODIFIER;
    if (strcmp(Symbol, "🍀") == 0) return CLOVER_MODIFIER;
    if (strcmp(Symbol, "🪙") == 0)  return COIN_MODIFIER;
    if (strcmp(Symbol, "🍒") == 0) return CHERRY_MODIFIER;
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
        return Bet * GetMultiplier(match) / DOUBLE_DIVISOR;
    }

    // Winnings if there are no matches, but there is a diamond
    if ((S1 != NULL && strcmp(S1, "💎") == 0) || 
        (S2 != NULL && strcmp(S2, "💎") == 0) ||
        (S3 != NULL && strcmp(S3, "💎") == 0))
        return (float)Bet / 2;

    // No match, no diamond
    return 0;
}

void SlotMachineAnimation(const char* S1, const char* S2, const char* S3) {
    // Slot machine 'fills out' column by column, so this animation locks the columns at certain points in the apinning animation
    bool colLock1 = false, colLock2 = false, colLock3 = false;

    for (int i = 0; i <= SPIN_STEPS*3; i++) {

        if (i >= SPIN_STEPS) colLock1 = true;   // Locks column 1 symbol after SPIN_STEPS
        if (i >= SPIN_STEPS*2) colLock2 = true; // Locks column 2 symbol after SPIN_STEPS x2
        if (i >= SPIN_STEPS*3) colLock3 = true; // Locks column 3 symbol after SPIN_STEPS x3

        // Moves Cursor v         v Locks Columns
        printf("\033[14;53H %s", colLock1 ? S1 : Symbols[i % SYMBOL_COUNT]);
        printf("\033[14;59H %s", colLock2 ? S2 : Symbols[i % SYMBOL_COUNT]);
        printf("\033[14;65H %s", colLock3 ? S3 : Symbols[i % SYMBOL_COUNT]);

        Sleep(SPIN_DELAY);
    }
}

void PrintSlotMachine(int Bet) {
    printf( //Spaced out so its in the middle of the screen
        "                                              ⠀⣀⣤⣤⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣤⣤⣀⠀⠀⠀⠀    ┌───────────────┐           \n"
        "                                              ⠀⢿⣿⣿⣿ CLI CASINO SLOTS ⣿⣿⣿⡿⠀⠀⠀⠀    │  Match of 3   │           \n"
        "                                              ⠀⠀⢙⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⣛⡋⠀⠀⠀⠀⠀    │ 💎 = %-9d│          \n"
        "                                              ⠀⠀⢸⣿⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⣿⡇⠀⠀⣤⣄⠀    │ 💲 = %-9d│  \n"
        "                                              ⠀⠀⢸⣿⠀⢸⠛⠛⠛⠛⡇⢸⠛⠛⠛⠛⡇⢸⠛⠛⠛⠛⡇ ⣿⡇⠀⠀⣿⠛⠀    │ 🍀 = %-9d│  \n"
        "                                              ⠀⠀⢸⣿⠀| 💎 || 💎 || 💎 | ⣿⡇⠀⠀⣿      │ 🪙 = %-9d│   \n"
        "                                              ⠀⠀⢸⣿⠀⢸⣤⣤⣤⣤⡇⢸⣤⣤⣤⣤⡇⢸⣤⣤⣤⣤⡇ ⣿⡇⠀⣾⡇⠀⠀    │ 🍒 = %-9d│  \n"
        "                                              ⠀⠀⢸⣿⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣤⣿⡆⣿⡿⠀⠀⠀    ├───────────────┤          \n"
        "                                              ⠀ ⢀⣴⣿⠟⠛⠛⢻⡿⠛⠛⠛⢻⣿⣿⣿⣿⡟⠋⠉⠉⠛⢿⣦⡀⠀⠀⠀⠀     │ Pairs return  │           \n"
        "                                              ⠀ ⣿⣿⣤⣤⣤⣤⣾⣧⣤⣤⣤⣿⣿⣿⣿⣿⣷⣦⣤⣤⣶⣿⣿⣿⠀⠀⠀⠀     │ 1/%d of above  │          \n"
        "                                              ⠀ ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀     ├───────────────┤           \n"
        "                                              ⠀ ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀     │ 1x 💎 = %-6d│           \n"
        "                                              ⠀ ⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠀⠀⠀⠀     └───────────────┘         \n"
        , Bet * DIAMOND_MODIFIER, Bet * DOLLAR_MODIFIER, Bet * CLOVER_MODIFIER, Bet * COIN_MODIFIER, Bet * CHERRY_MODIFIER
        , DOUBLE_DIVISOR, Bet / 2);
}