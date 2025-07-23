// CLI Casino | Spencer Watkinson - Ricardo Pineda Pelaez - Sebastian Solorzano | CSCN71030
// Implementation of Slots module

#include "Slots.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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